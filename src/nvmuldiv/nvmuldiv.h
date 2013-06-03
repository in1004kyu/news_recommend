#ifndef __NVMULDIV_H__
#define __NVMULDIV_H__
#include <stdlib.h>

typedef enum {
	nvmuldiv_status_success = 0,
	nvmuldiv_status_unknown_error = -1,
	nvmuldiv_status_generic_cuda = -2,
	nvmuldiv_status_cuda_memory = -3,
} nvmuldiv_status_t;

#ifdef __cplusplus 
extern "C" {
#endif

nvmuldiv_status_t nvmuldiv_init(void);
long nvmuldiv_timestamp(void);
void *nvmuldiv_mapped_alloc( size_t size );
void nvmuldiv_mapped_free( void *p_h);
void *nvmuldiv_mapped_device( void *p_h );
void *nvmuldiv_device_alloc( size_t size );
void nvmuldiv_device_free( void *p_d );

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
int reduce_mul_seg_devmem( float d_v[], int len, float d_r[], int len_r );
int reduce_divmul_seg_devmem(float *v1,float *v2, float d_v[],int len, float d_r[] ,int len_r);
int nvmuldiv_seg_cuda_devmem( float *n_d, float *d_d, int len, float *r_d, int len_r, float *vr_d );
int nvmuldiv_seg_fused_cuda_devmem( float *n_d, float *d_d, int len, float *r_d, int len_r, float *vr_d );
#ifdef __cplusplus 
}
int vdiv_cuda( float v1[], float v2[], float vr[], int len );
int vdiv_cuda_devmem( float *v1, float *v2, float *vr, int len );
#endif
#endif
