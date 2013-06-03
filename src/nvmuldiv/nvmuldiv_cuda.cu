#include <thrust/version.h>
#include <iostream>
#include <thrust/device_vector.h>
#include <stdio.h>

#include <stdlib.h>
#include <time.h>

#include "nvmuldiv.h"

extern "C" nvmuldiv_status_t _nvmuldiv_cuda_init(void)
{
	static bool deviceMapHostSet = false;
	cudaError_t result = cudaSuccess;
	if ( !deviceMapHostSet ) {
		result = cudaSetDeviceFlags(cudaDeviceMapHost);
		if ( result == cudaSuccess ) {
			deviceMapHostSet = true;
		}
	}
	if ( result != cudaSuccess ) {
        	fprintf(stderr, "_nvmuldiv_cuda_init(error code %x:%s)!\n", result, cudaGetErrorString(result));
		return nvmuldiv_status_generic_cuda;
	}

	return nvmuldiv_status_success;
}

extern "C" float nvmuldiv_cuda( float numerators[], float denominators[], int len)
{
	float *vr = (float *) malloc( sizeof(float) * len );

	// divide: vr = n / d
	vdiv_cuda( numerators, denominators, vr, len );

	// multiply: reduce(vr)
	/*
	thrust::device_vector<float> dvr( vr, vr + len );
	float score = thrust::reduce(dvr.begin(), dvr.end(), (float) 1, thrust::multiplies<float>());
	*/
	float score = 0;
	reduce_mul( vr, len, &score);

	free(vr);
	return score;
}


extern "C" void * nvmuldiv_mapped_alloc( size_t size )
{
	void *p_h = NULL;
	cudaError_t result;

	result = cudaHostAlloc( &p_h, size, cudaHostAllocMapped );
	if ( result != cudaSuccess ) {
        	fprintf(stderr, "nvmuldiv_mapped_alloc(error code %x:%s)!\n", result, cudaGetErrorString(result));
	}
	return p_h;
}

extern "C" void nvmuldiv_mapped_free( void *p_h )
{
	cudaFreeHost( p_h );
}

extern "C" void *nvmuldiv_mapped_device( void *p_h )
{
	void *p_d = NULL;
	cudaError_t err;
	err = cudaHostGetDevicePointer( &p_d, p_h, 0);
	if ( err != cudaSuccess ) {
        	fprintf(stderr, "nvmuldiv_mapped_device(error code %x:%s)!\n", err, cudaGetErrorString(err));
		return NULL;
	}
	return p_d;
}

extern "C" void *nvmuldiv_device_alloc( size_t size )
{
	void *p_d = NULL;
	cudaError_t err = cudaSuccess;
	err = cudaMalloc( &p_d, size );
	if ( err != cudaSuccess ) {
        	fprintf(stderr, "nvmuldiv_device_alloc(error code %x:%s)!\n", err, cudaGetErrorString(err));
		return NULL;
	} else {
        	fprintf(stderr, "nvmuldiv_device_alloc: %p size:%ld\n", p_d, size);
	}

	return p_d;
}

extern "C" void nvmuldiv_device_free( void *p_d )
{
	cudaFree( p_d );
}

extern "C" int nvmuldiv_seg_cuda_devmem( float *n_d, float *d_d, int len, float *r_d, int len_r, float *vr_d )
{
	int result = 0;
	bool localAlloc = false;
// alloc
	if ( vr_d == NULL ) {
		vr_d = (float *) nvmuldiv_device_alloc( len * sizeof(float) );
		localAlloc = true;
		//fprintf( stderr, "nvmuldiv_seg_cuda_devmem: vr_d: %p local-allocated\n", vr_d );
	}
// kernel
	/*result = vdiv_cuda_devmem( n_d, d_d, vr_d, len );
	if ( result == 0 ) {
		result = reduce_mul_seg_devmem( vr_d, len, r_d, len_r );
	}*/
	reduce_divmul_seg_devmem(n_d,d_d,vr_d,len,r_d,len_r);
// free
	if ( localAlloc ) {
		//fprintf( stderr, "nvmuldiv_seg_cuda_devmem: freeing vr_d: %p local-allocated\n", vr_d );
		nvmuldiv_device_free( vr_d );
	}
	return result;
}
void reduce_mul_dummy(float *v, int len, float *result )
{
	float r = 1;
	for ( int i = 0; i < len; i++ ) r *= v[i];
	*result = r;
}
extern "C" int nvmuldiv_seg_cuda( float n[], float d[], int len, float r[], int len_r )
{
	int result = -1;
#if 1
	float *vr = (float *) malloc( sizeof(float) * len );
	vdiv_cuda( n, d, vr, len );
	reduce_mul_seg( vr, len, r, len_r );
	/*
	for( int i = 0; i < len / len_r; i++ ) {
		reduce_mul( &vr[i*len_r], len_r, &r[i] );
		//reduce_mul_dummy( &vr[i*len_r], len_r, &r[i] );
	}
	*/
	free(vr);
	result = 0;
#else
	

	float *n_h = (float *) nvmuldiv_mapped_alloc( sizeof(float) * len );
	float *d_h = (float *) nvmuldiv_mapped_alloc( sizeof(float) * len );
	float *n_d;
	float *d_d;
	float *vr_d = NULL;
	float *r_d = NULL;
	cudaError_t err;
	cudaDeviceProp prop;
	cudaGetDeviceProperties( &prop, 0 );
	long ts1, ts2, ts3, ts4;

	ts1 = nvmuldiv_timestamp();

	if ( !prop.canMapHostMemory) {
		result = -2;
		fprintf( stderr, "nvmuldiv: cannot map host memory to device\n" );
		return result;
	}

	err = cudaMalloc( &vr_d, sizeof(float) * len );
	if ( err != cudaSuccess ) {
		return -1;	// insufficient memory
	}
	if ( err == cudaSuccess ) {
		err = cudaMalloc( &r_d, sizeof(float) * (len / len_r) );
	}
	if ( err == cudaSuccess ) {
		memcpy( n_h, n, len * sizeof(float) );
		memcpy( d_h, d, len * sizeof(float) );
	}

	if ( err == cudaSuccess ) {
		err = cudaHostGetDevicePointer( &n_d, n_h, 0);
	}
	if ( err == cudaSuccess ) {
		err = cudaHostGetDevicePointer( &d_d, d_h, 0);
	}
#if 0
	// vdiv
	//	n_d: input, page locked
	//	d_d: input, page locked
	// 	vr_d: output, intermediate, device memory
	if ( err == cudaSuccess ) {
		fprintf(stderr, "nvmuldiv: n_h=%p, n_d=%p\n", n_h, n_d );
		result = vdiv_cuda_devmem( n_d, d_d, vr_d, len );
	}
	// reduce
	//	vr_d: input, device memory
	//	r_d: output, device_memory
	if ( err == cudaSuccess && result == 0 ) {
		result = reduce_mul_seg_devmem( vr_d, len, r_d, len_r );
	}
#endif
	ts2 = nvmuldiv_timestamp();

	if ( err == cudaSuccess ) {
		long ts1, ts2;
		ts1 = nvmuldiv_timestamp();
		result = nvmuldiv_seg_cuda_devmem( n_d, d_d, len, r_d, len_r, vr_d );
		ts2 = nvmuldiv_timestamp();
		fprintf( stderr, "nvmuldiv_seg_cuda_devmem(): %ldus\n", (ts2-ts1) );
	}
	ts3 = nvmuldiv_timestamp();
	// grab the result
	//	r_d: device memory
	//	r: host memory
	if ( err == cudaSuccess && result == 0 ) {
		err = cudaMemcpy( r_d, r, sizeof(float) * (len / len_r), cudaMemcpyHostToDevice );
	}
	if ( vr_d != NULL ) cudaFree( vr_d );
	if ( r_d != NULL ) cudaFree( r_d );
	nvmuldiv_mapped_free( n_h );
	nvmuldiv_mapped_free( d_h );

	ts4 = nvmuldiv_timestamp();
	fprintf( stderr, "nvmuldiv_seg_cudam(): alloc/copy:%ldus, copy/free:%ldus\n", (ts2-ts1), (ts4-ts3));
#endif
	return result;
}
