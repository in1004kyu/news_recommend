#include<thrust/version.h>
#include<iostream>
#include<thrust/device_vector.h>

#include<stdlib.h>
#include<time.h>
#include<stdio.h>

#include"nvmuldiv.h"
#define MAX_BLOCKS 65535
#define MAX_THREADS_PER_BLOCK 1024

#define ENABLE_WARP_SCHEDULING


__global__ void kern_reduce_divmul (const float *v1,const float *v2,float d_v[],float d_r[],int len,int len_r)
{
	extern __shared__ float sdata[];

	unsigned int tid = threadIdx.x; //0 ..127
	unsigned int i = blockIdx.x * (blockDim.x * 2) + threadIdx.x;
	sdata[tid] = (v1[i]/v2[i] ) * (v1[i+blockDim.x]/v2[i+blockDim.x]);
	__syncthreads();

#ifdef ENABLE_WARP_SCHEDULING
	for(unsigned int s=blockDim.x/2; s>32; s>>=1){
		if(tid < s) {
			sdata[tid] *= sdata[tid+s];
		}
		__syncthreads();
	}
	if( tid < 32 ){
		volatile float *smem =sdata;
		smem[tid] *= smem[tid+32];
		smem[tid] *= smem[tid+16];
		smem[tid] *= smem[tid+8];
		smem[tid] *= smem[tid+4];
		smem[tid] *= smem[tid+2];
		smem[tid] *= smem[tid+1];
	}
#else
	for(unsigned int s=blockDim.x/2; s>0; s>>=1){
		if( tid < s) {
			sdata[tid] *= sdata[tid+s];
		}
		__syncthreads();
	}
#endif
	if( tid == 0 ){
		d_r[blockIdx.x] = sdata[0];
	}
}

extern "C" int reduce_divmul_seg_devmem( float *v1, float *v2, float d_v[] , int len, float d_r[] ,int len_r)
{
	cudaError_t err = cudaSuccess;

	int numSegs = len / len_r;
	if( numSegs > MAX_BLOCKS ){
		fprintf(stderr, "reduce_divmul_seg: too many segments (%d / %d = %d > MAX_BLOCKS (%d) )\n",len , len_r, len/len_r,MAX_BLOCKS);
		return -1;
	}
	int dimGrid = numSegs;
	int aligned_len_r = len_r;
	int padded_len = dimGrid * aligned_len_r;
	int dimBlock = aligned_len_r / 2;
	size_t smemSize = aligned_len_r/2 * sizeof(float);

	if( padded_len != len){
		fprintf(stderr, "len(%d)/len_r(%d) != padded_len(%d)\n", len,len_r,padded_len);
		return -2;
	}
	
	kern_reduce_divmul<<< dimGrid, dimBlock, smemSize >>> (v1,v2,d_v,d_r,len,len_r);
	err = cudaGetLastError();

	if(err != cudaSuccess){
		fprintf(stderr, "CUDA (error code : %x: %s)\n", err, cudaGetErrorString(err));
	}

	return 0;
}
