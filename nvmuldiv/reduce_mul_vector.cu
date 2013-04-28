#include <thrust/version.h>
#include <iostream>
#include <thrust/device_vector.h>

#include <stdlib.h>
#include <time.h>

#define NUM_MAX_DATA	1024
#define NUM_MIN_DATA	2

double reduce_mul_vector( thrust::device_vector<double> &d1 )
{
	return thrust::reduce(d1.begin(), d1.end(), (double) 1, thrust::multiplies<double>());
}

int main(void)
{

// Generate random data for test
	srandom( time(0) );
	int num_data = random() % NUM_MAX_DATA;
	if ( num_data < NUM_MIN_DATA ) num_data = NUM_MIN_DATA;

	printf( "Number of input data:%d\n", num_data );
	
	thrust::device_vector<double> d1(num_data, 0);
	double value;
	for ( int i = 0; i < num_data; i++ ) {

		value = ( (double) (random() % 1000 + 1) ) / (double) (random() % 1000 +1);;
		d1[i] = value;

		printf( " %4.1f", value );
		if ( ((i+1) % 8) == 0 ) printf( "\n" );
	}
	printf( "\n" );

// Multiply
	double mul = reduce_mul_vector( d1 );

	printf( "Result: %4f\n", mul );
	return 0;
}
