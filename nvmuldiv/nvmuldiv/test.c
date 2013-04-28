#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nvmuldiv.h"

#define NUM_MAX_DATA	90000
#define NUM_MIN_DATA	50000

void nvmuldiv_data_fill_random( int len, float *d1, float*d2 )
{
	int i;
	float value;
	for( i = 0; i < len; i++ ) {
		value = ( (double) (random() % 1000 + 1) ) / (double) (random() % 1000 +1);;
		d1[i] = value;
		value = ( (double) (random() % 1000 + 1) ) / (double) (random() % 1000 +1);;
		d2[i] = value;
	}
}

int main(void)
{

// Generate random data for test
	srandom( time(0) );
	int num_data = random() % NUM_MAX_DATA;
	if ( num_data < NUM_MIN_DATA ) num_data = NUM_MIN_DATA;

	printf( "Number of input data:%d\n", num_data );
	float *d1 = malloc( sizeof(float) * num_data );
	float *d2 = malloc( sizeof(float) * num_data );

	nvmuldiv_data_fill_random( num_data, d1, d2 );

// Multiply
	float result = nvmuldiv( d1, d2, num_data );
	printf( "CPU Result: %4f\n", result );
	result = nvmuldiv_cuda_thrust( d1, d2, num_data );
	printf( "GPU Result: %4f\n", result );
	return 0;
}
