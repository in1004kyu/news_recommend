#include <thrust/version.h>
#include <iostream>
#include <thrust/device_vector.h>

#include <stdlib.h>
#include <time.h>

#define NUM_MAX_DATA	1024
#define NUM_MIN_DATA	2

float reduce_mul_vector( thrust::device_vector<float> &d1 )
{
	return thrust::reduce(d1.begin(), d1.end(), (float) 1, thrust::multiplies<float>());
}

extern "C" float nvmuldiv_cuda_thrust( float numerators[], float denominators[], int len)
{
	std::vector<float> vnum (numerators, numerators + len );
	std::vector<float> vden (denominators, denominators + len );

	thrust::device_vector<float> d1( vnum );
	thrust::device_vector<float> d2( vden );
	float num = reduce_mul_vector( d1 );
	float den = reduce_mul_vector( d2 );
	return num / den;
}

/* --- CUDA - NO THRUST CALLS --- */
extern "C" int vdiv_cuda( float v1[], float v2[], float vr[], int len );

extern "C" float nvmuldiv_cuda( float numerators[], float denominators[], int len)
{
	float *vr = (float *) malloc( sizeof(float) * len );
	vdiv_cuda( numerators, denominators, vr, len );
	std::vector<float> vvr (vr, vr + len );

	thrust::device_vector<float> dvr( vvr );
	float score = reduce_mul_vector( dvr );

	free(vr);
	return score;
}

__global__ void
vectorDiv(const float *A, const float *B, float *C, int numElements)
{
	int i = blockDim.x * blockIdx.x + threadIdx.x;

	if (i < numElements) {
		C[i] = A[i] / B[i];
	}
}

extern "C" int vdiv_cuda( float v1[], float v2[], float vr[], int len )
{
	
    // Error code to check return values for CUDA calls
    cudaError_t err = cudaSuccess;

    // Print the vector length to be used, and compute its size
    int numElements = len;
    size_t size = numElements * sizeof(float);
//    printf("[Vector addition of %d elements]\n", numElements);

    // Allocate the device input vector A
    float *d_A = NULL;
    err = cudaMalloc((void **)&d_A, size);

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to allocate device vector A (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Allocate the device input vector B
    float *d_B = NULL;
    err = cudaMalloc((void **)&d_B, size);

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to allocate device vector B (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Allocate the device output vector C
    float *d_C = NULL;
    err = cudaMalloc((void **)&d_C, size);

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to allocate device vector C (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Copy the host input vectors A and B in host memory to the device input vectors in
    // device memory
//    printf("Copy input data from the host memory to the CUDA device\n");
    err = cudaMemcpy(d_A, v1, size, cudaMemcpyHostToDevice);

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy vector A from host to device (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    err = cudaMemcpy(d_B, v2, size, cudaMemcpyHostToDevice);

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy vector B from host to device (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Launch the Vector Add CUDA Kernel
    int threadsPerBlock = 256;
    int blocksPerGrid =(numElements + threadsPerBlock - 1) / threadsPerBlock;
//    printf("CUDA kernel launch with %d blocks of %d threads\n", blocksPerGrid, threadsPerBlock);
    vectorDiv<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, numElements);
    err = cudaGetLastError();

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to launch vectorAdd kernel (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Copy the device result vector in device memory to the host result vector
    // in host memory.
//    printf("Copy output data from the CUDA device to the host memory\n");
    err = cudaMemcpy(vr, d_C, size, cudaMemcpyDeviceToHost);

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy vector C from device to host (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

#ifdef __NVMULDIV_ENABLE_VERIFY__
    // Verify that the result vector is correct
    for (int i = 0; i < numElements; ++i)
    {
        if (fabs(v1[i] / v2[i] - vr[i]) > 1e-5)
        {
            fprintf(stderr, "Result verification failed at element %d!\n", i);
	    fprintf(stderr, "v1[i]: %f v2[i]: %f vr[i]:%f, expected:%f\n", v1[i], v2[i], vr[i], v1[i]/v2[i]);
            exit(EXIT_FAILURE);
        }
    }
#endif

    // Free device global memory
    err = cudaFree(d_A);

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to free device vector A (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
    err = cudaFree(d_B);

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to free device vector B (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
    err = cudaFree(d_C);

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to free device vector C (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Reset the device and exit
    err = cudaDeviceReset();

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to deinitialize the device! error=%s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

//    printf("Done\n");
    return 0;
}
