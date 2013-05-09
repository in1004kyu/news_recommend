#ifndef __NVMULDIV_H__
#define __NVMULDIV_H__

#ifdef __cplusplus 
extern "C" {
#endif

float nvmuldiv( float numerators[], float denominators[], int len);

// bulk processing
// Multi-segment bulk processing of nvmuldiv()
// n: combined vector of numerators. 'len' elements
// d: combined vector of denominators. 'len' elements
// len: length of 'n' and'd'
// r: output result vector where score of each segment. 'len_r' elements
// len_r: length of each segment. number of segment = len / len_r. 
// example: nvmuldiv_seg( { 1, 2, 3, ... 256}, { 1, 2, 3, ... 256 }, 256, &r, 64 );
// 	4 segments ( = 256 / 64 )
// 	numerators at segment 0 : n[0] ~ n[63]
int nvmuldiv_seg( float n[], float d[], int len, float r[], int len_r );

// low level CUDA reduce functions
int reduce_mul( float *v, int len, float *result );
int reduce_mul_seg( float v[], int len, float r[], int len_r );

// To be deprecated
float nvmuldiv_cuda( float numerators[], float denominators[], int len);
float nvmuldiv_cuda_thrust( float numerators[], float denominators[], int len);
int nvmuldiv_seg_cuda( float n[], float d[], int len, float r[], int len_r );
#ifdef __cplusplus 
}
int vdiv_cuda( float v1[], float v2[], float vr[], int len );
#endif
#endif
