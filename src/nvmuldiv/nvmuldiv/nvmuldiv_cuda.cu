#include <thrust/version.h>
#include <iostream>
#include <thrust/device_vector.h>

#include <stdlib.h>
#include <time.h>

#include "nvmuldiv.h"

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

extern "C" int nvmuldiv_seg_cuda( float n[], float d[], int len, float r[], int len_r )
{
	float *vr = (float *) malloc( sizeof(float) * len );
	vdiv_cuda( n, d, vr, len );

	reduce_mul_seg( vr, len, r, len_r );
	/*
	float *pvr = vr;
	int i = 0;
	while( len > 0 ) {

		//thrust::device_vector<float> dvr( pvr, pvr + len_r );
		////r[i] = thrust::reduce(dvr.begin(), dvr.end(), (float) 1, thrust::multiplies<float>());
		reduce_mul( pvr, len_r, &r[i] );

		len -= len_r;
		pvr += len_r;
		i++;
	}
	*/

	free(vr);
	return 0;
}
