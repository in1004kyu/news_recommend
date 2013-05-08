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
	thrust::device_vector<float> dvr( vr, vr + len );
	float score = thrust::reduce(dvr.begin(), dvr.end(), (float) 1, thrust::multiplies<float>());

	free(vr);
	return score;
}
