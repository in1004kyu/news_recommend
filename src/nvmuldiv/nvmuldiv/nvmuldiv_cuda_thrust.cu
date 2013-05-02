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
	printf( "num:%f\n", num );
	printf( "den:%f\n", den );
	return num / den;
}
