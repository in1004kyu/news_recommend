#include <iostream>
#include <stdio.h>
#include <stdlib.h>

__global__ void
vectorDiv(const float *A, const float *B, float *C, int numElements)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;

    if (i < numElements) {
        C[i] = A[i] / B[i];
    }
}

int vdiv_cuda( float v1[], float v2[], float vr[], int len )
{
    
    // Error code to check return values for CUDA calls
    cudaError_t err = cudaSuccess;

    // Print the vector length to be used, and compute its size
    int numElements = len;
    size_t size = numElements * sizeof(float);
    //printf("[Vector addition of %d elements]\n", numElements);

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
    bool bPageLocked = true;
#if 0
    // Try if vr is page locked mermory
    err = cudaHostGetDevicePointer( &d_C, vr, 0 );
    if ( err != cudaSuccess ) {
        d_C = NULL;
        err = cudaMalloc((void **)&d_C, size);
    bPageLocked = false;
        fprintf( stderr, "Use of device memory for result at %p\n", d_C );
    } else {
        fprintf( stderr, "Use of page locked memory at %p\n", vr );
    }
#else
        err = cudaMalloc((void **)&d_C, size);
    bPageLocked = false;
#endif


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
    int threadsPerBlock = 1024;
    int blocksPerGrid =(numElements + threadsPerBlock - 1) / threadsPerBlock;
    //printf("vdiv:CUDA kernel launch with %d blocks of %d threads\n", blocksPerGrid, threadsPerBlock);
    vectorDiv<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, numElements);
    err = cudaGetLastError();

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to launch vectorDiv kernel (error code %x:%s)!\n", err, cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    // Copy the device result vector in device memory to the host result vector
    // in host memory.
//    printf("Copy output data from the CUDA device to the host memory\n");
    if (!bPageLocked) {
        err = cudaMemcpy(vr, d_C, size, cudaMemcpyDeviceToHost);

        if (err != cudaSuccess)
        {
            fprintf(stderr, "Failed to copy vector C from device to host (error code %s)!\n", cudaGetErrorString(err));
            exit(EXIT_FAILURE);
        }
    }


#ifdef __NVMULDIV_ENABLE_VERIFY__
#if 0
    // Verify that the result vector is correct
    for (int i = 0; i < numElements; ++i)
    {
        if (fabs(v1[i] / v2[i] - vr[i]) > 1e-5)
        {
            fprintf(stderr, "Result verification failed at element %d!\n", i);
        fprintf(stderr, "v1[i]: %f v2[i]: %f vr[i]:%f, expected:%f\n", v1[i], v2[i], vr[i], v1[i]/v2[i]);
        }
    }
#endif
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
    if ( !bPageLocked) {
    err = cudaFree(d_C);

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to free device vector C (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
    }

    // Reset the device and exit
#if 1
    err = cudaDeviceReset();

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to deinitialize the device! error=%s\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
#endif

//    printf("Done\n");
    return 0;
}

int vdiv_cuda_devmem( float *v1, float *v2, float *vr, int len )
{
    
    // Error code to check return values for CUDA calls
    cudaError_t err = cudaSuccess;

    // Print the vector length to be used, and compute its size
    int numElements = len;
    //size_t size = numElements * sizeof(float);
    //printf("[Vector addition of %d elements]\n", numElements);


    // Launch the Vector Add CUDA Kernel
    int threadsPerBlock = 1024;
    int blocksPerGrid =(numElements + threadsPerBlock - 1) / threadsPerBlock;
    //printf("vdiv:CUDA kernel launch with %d blocks of %d threads\n", blocksPerGrid, threadsPerBlock);
    vectorDiv<<<blocksPerGrid, threadsPerBlock>>>(v1, v2, vr, numElements);
    err = cudaGetLastError();

    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to launch vectorDiv kernel (error code %x:%s)!\n", err, cudaGetErrorString(err));
	return -1;
    }

//    printf("Done\n");
    return 0;
}
