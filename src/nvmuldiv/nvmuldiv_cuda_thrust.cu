#include <thrust/version.h>
#include <iostream>
#include <thrust/device_vector.h>

#include <stdlib.h>
#include <time.h>

#include "nvmuldiv.h"

float reduce_mul_vector( thrust::device_vector<float> &d1 )
{
	return thrust::reduce(d1.begin(), d1.end(), (float) 1, thrust::multiplies<float>());
}

extern "C" float nvmuldiv_cuda_thrust( float numerators[], float denominators[], int len)
{
	// divide
	float *vr = (float *) malloc( sizeof(float) * len );
	vdiv_cuda(numerators, denominators, vr, len);

	// reduce with multiply
	thrust::device_vector<float> d1( vr, vr + len );
	float score = reduce_mul_vector( d1 );
	free(vr);
	return score;
}
