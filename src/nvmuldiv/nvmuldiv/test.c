#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nvmuldiv.h"

#define NUM_MAX_DATA	900
#define NUM_MIN_DATA	700
#define LEN_MAX_DATASET	2000000
#define LEN_MIN_DATASET	1000000

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

	int i;
	float *datasets1[NUM_MAX_DATA];
	float *datasets2[NUM_MAX_DATA];
// Generate random data for test
	srandom( time(0) );
	int num_data = NUM_MIN_DATA + (random() % NUM_MAX_DATA - NUM_MIN_DATA);
	int len_dataset = LEN_MIN_DATASET + (random() % LEN_MAX_DATASET - LEN_MIN_DATASET);

	printf( "Number of input data:%d of %d datasets\n", num_data, len_dataset );
	for (i = 0; i < num_data; i++ ) {
		datasets1[i] = malloc( sizeof(float) * len_dataset );
		datasets2[i]= malloc( sizeof(float) * len_dataset );

		nvmuldiv_data_fill_random( len_dataset, datasets1[i], datasets2[i] );
	}

// Multiply
	printf( "CPU...\n" );
	for ( i = 0; i < num_data; i++ ) {
		nvmuldiv( datasets1[i], datasets2[i], len_dataset );
	}
	printf( "GPU-Thrust\n" );
	for ( i = 0; i < num_data; i++ ) {
		nvmuldiv_cuda_thrust( datasets1[i], datasets2[i], len_dataset );
	}
	printf( "GPU-CUDA\n" );
	for ( i = 0; i < num_data; i++ ) {
		nvmuldiv_cuda( datasets1[i], datasets2[i], len_dataset );
	}
	printf( "Finished\n" );
	return 0;
}
