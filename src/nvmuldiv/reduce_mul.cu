#include <thrust/version.h>
#include <iostream>
#include <thrust/device_vector.h>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "nvmuldiv.h"
#define MAX_BLOCKS		65535
#define MAX_THREADS_PER_BLOCK	1024

/* --- reduce --- */
__global__ void kern_reduce_mul(float *g_idata, float *g_odata) { 
	extern __shared__ float sdata[];

	// each thread loads one element from global to shared mem
	unsigned int tid = threadIdx.x;					// 0..127
	unsigned int i = blockIdx.x * (blockDim.x * 2) + threadIdx.x; 	// 0..127
	sdata[tid] = g_idata[i] * g_idata[i+blockDim.x];		// 0..127, 0..127, 128..255
	__syncthreads();

	// do reduction in shared mem: 64 > 32 > 16 > 8 > 4> 2
	for(unsigned int s=blockDim.x/2; s > 32; s >>= 1) { 
		if (tid < s) {
			sdata[tid] *= sdata[tid + s]; 			// 0..63, 64...127
		}
		__syncthreads(); 
	}
	if ( tid < 32 ) {
		// unroll the loop at the last warp
		// within a warp where instructions are SIMD synchronous
		// no need __syncthreads
		sdata[tid] *= sdata[tid + 32];
		sdata[tid] *= sdata[tid + 16];
		sdata[tid] *= sdata[tid + 8];
		sdata[tid] *= sdata[tid + 4];
		sdata[tid] *= sdata[tid + 2];
		sdata[tid] *= sdata[tid + 1];
	}
	if ( tid == 0 ) {
		g_odata[blockIdx.x] = sdata[0];
	}
}

extern "C" int reduce_mul( float *v, int len, float *result )
{
	cudaError_t err = cudaSuccess;

	int dimBlock = 128;	// threads per block : half the length
	int dimGrid = ((len/2) + dimBlock - 1) / dimBlock;	// number of blocks
	int padded_len = dimGrid * (dimBlock * 2);	// threads x 2 x blocks
	size_t smemSize = padded_len/2 * sizeof(float);

	float *d_v = NULL;
	float *d_r = NULL;

	// Device Memory for input:d_v[padded_len] and output:d_r[dimGrid]
	err = cudaMalloc( (void **) &d_v, padded_len * sizeof(float));
	if ( err == cudaSuccess ) {
		err = cudaMalloc( (void **) &d_r, dimGrid * sizeof(float));
	}

	if ( err == cudaSuccess ) {
		err = cudaMemcpy( d_v, v, len * sizeof(float), cudaMemcpyHostToDevice );
	}

	// Launch Kernel: number of blocks, threads per block, shared memory size in bytes
	// printf( "reduce_mul: blocks:%d, threads per block:%d, smem size:%d\n", dimGrid, dimBlock, (int) smemSize);
	if ( err == cudaSuccess ) {
		kern_reduce_mul<<< dimGrid, dimBlock, smemSize >>>(d_v, d_r);
		err = cudaGetLastError();
	}

	if ( err == cudaSuccess ) {
		float value = 1;
		float *r = (float *) malloc( sizeof(float) * dimGrid );
		err = cudaMemcpy( r, d_r, sizeof(float) * dimGrid, cudaMemcpyDeviceToHost);
		if ( err == cudaSuccess ) {
			//printf( "d_r[] = {" );
			for ( int i = 0; i < dimGrid; i++ ) {
			//	printf( "%f,", r[i] );
				value *= r[i];
			}
			//printf( "}\n" );
			*result = value;
		}
	}

	if ( err == cudaSuccess ) {
		err = cudaFree(d_v);
	}
	if ( err == cudaSuccess ) {
		cudaFree(d_r);
	}
	if ( err != cudaSuccess ) {
        	fprintf(stderr, "CUDA (error code: %x: %s)\n", err, cudaGetErrorString(err));
	}

	return 0;
}

int aligned_length( int len )
{
	// 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2
	int m = 4;
	while ( m < 1024 ) {
		if ( m >= len ) {
			break;
		}
		m <<= 1;
	}
	//printf( "aligned_length: len:%d -> m:%d\n", len, m );
	return m;
}
extern "C" int reduce_mul_seg( float v[], int len, float r[], int len_r )
{
	cudaError_t err = cudaSuccess;

	int numSegs = len / len_r;
	if ( numSegs > MAX_BLOCKS ) {
		fprintf( stderr, "reduce_mul_seg: too many segments (%d / %d = %d > MAX_BLOCKS (%d) )\n", len, len_r, len / len_r, MAX_BLOCKS );
		return -1;
	}
	int aligned_len_r = aligned_length( len_r );
	int dimBlock = aligned_len_r / 2;	// threads per block : half the length
	int dimGrid = numSegs;	// number of blocks: number of segments
	int padded_len = dimGrid * aligned_len_r;	// segment length x blocks
	size_t smemSize = aligned_len_r/2 * sizeof(float);

	float *d_v = NULL;
	float *d_r = NULL;


	// Device Memory for input:d_v[padded_len] and output:d_r[numSegs]
	err = cudaMalloc( (void **) &d_v, padded_len * sizeof(float));
	if ( err == cudaSuccess ) {
		err = cudaMalloc( (void **) &d_r, numSegs * sizeof(float));
	}

	if ( err == cudaSuccess ) {
		err = cudaMemcpy( d_v, v, len * sizeof(float), cudaMemcpyHostToDevice );
	}

	// Launch Kernel: number of blocks, threads per block, shared memory size in bytes
	// printf( "reduce_mul_seg: blocks:%d, threads per block:%d, smem size:%d\n", dimGrid, dimBlock, (int) smemSize);
	if ( err == cudaSuccess ) {
		kern_reduce_mul<<< dimGrid, dimBlock, smemSize >>>(d_v, d_r);
		err = cudaGetLastError();
	}

	if ( err == cudaSuccess ) {
		err = cudaMemcpy( r, d_r, sizeof(float) * numSegs, cudaMemcpyDeviceToHost);
#ifdef __NVMULDIV_ENABLE_VERIFY__
		if ( err == cudaSuccess ) {
			printf( "d_r[] = {" );
			for ( int i = 0; i < dimGrid; i++ ) {
				printf( "%f,", r[i] );
			}
			printf( "}\n" );
		}
#endif
	}

	if ( err == cudaSuccess ) {
		err = cudaFree(d_v);
	}
	if ( err == cudaSuccess ) {
		cudaFree(d_r);
	}
	if ( err != cudaSuccess ) {
        	fprintf(stderr, "CUDA (error code: %x: %s)\n", err, cudaGetErrorString(err));
	}

	return 0;
}
