#ifndef __NVMULDIV_H__
#define __NVMULDIV_H__

#ifdef __cplusplus 
extern "C" {
#endif

float nvmuldiv( float numerators[], float denominators[], int len);
float nvmuldiv_cuda_thrust( float numerators[], float denominators[], int len);
float nvmuldiv_cuda( float numerators[], float denominators[], int len);
#ifdef __cplusplus 
}
int vdiv_cuda( float v1[], float v2[], float vr[], int len );
#endif
#endif
