#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "nvmuldiv.h"

#define NUM_DEFAULT_DATA	60000

void nvmuldiv_data_fill_random( int len, float *d1, float*d2 )
{
	int i;
	float value;
	for( i = 0; i < len; i++ ) {
		value = ( (double) (random() % 10000 + 1) ) / ((double) (random() % 1000 +1));
		d1[i] = value;
		value = ( (double) (random() % 1000 + 1) ) / ((double) (random() % 100 +1));
		d2[i] = value;

		if ( d1[i] == 0 || d2[i] == 0 ) {
			fprintf( stderr, "d1[%d]=%f, d2[%d]=%f\n", i, d1[i], i, d2[i] );
		}
	}
}

void test_reduce_mul(void)
{
	float v[256];
	float result = 0;
	int i;
	v[0] = 2;
	v[1] = 4;
	v[2] = 6;
	v[3] = 8;
	v[4] = 10;
	for( i = 5; i < 256; i++ ) v[i] = 1.0;

	reduce_mul( v, 256, &result );
	fprintf( stderr, "reduce_mul:%f\n", result );
}

int main(void)
{

	int i;
	float *datasets1[NUM_DEFAULT_DATA];
	float *datasets2[NUM_DEFAULT_DATA];
	float *bd1;	// bulk dataset 1
	float *bd2;	// bulk dataset 2
// Generate random data for test
	srandom( time(0) );
	int num_data = NUM_DEFAULT_DATA;
	int len_dataset = 512;

	test_reduce_mul();

	printf( "Number of input data:%d of %d datasets\n", num_data, len_dataset );
	float *bds = malloc( sizeof(float) * num_data * len_dataset * 2);
	float *br = malloc( sizeof(float) * num_data );	// bulk result;
	float *br2 = malloc( sizeof(float) * num_data );	// bulk result;
	if ( bds == NULL || br == NULL || br2 == NULL ) {
		fprintf( stderr, "memory allocation error\n" );
		return -1;
	}
	printf( "p:%p, end:%p\n", bds, bds + (sizeof(float) * num_data * len_dataset * 2) - sizeof(float));

	float *p = bds;
	bd1 = p;
	bd2 = p + (num_data * len_dataset);
	for (i = 0; i < num_data; i++ ) {
		datasets1[i] = p; 
		datasets2[i] = p + (num_data * len_dataset);
		nvmuldiv_data_fill_random( len_dataset, datasets1[i], datasets2[i] );

		p += len_dataset;
	}

// Multiply
	printf( "CPU...\n" );
	nvmuldiv_seg( bd1, bd2, num_data * len_dataset, br, len_dataset );
	/*
	for ( i = 0; i < num_data; i++ ) {
		printf( "br[%d]:%f\n", i, br[i]);
	}
	*/

	printf( "GPU-CUDA\n" );
	nvmuldiv_seg_cuda( bd1, bd2, num_data * len_dataset, br2, len_dataset );
#ifdef __NVMULDIV_ENABLE_VERIFY__
	for ( i = 0; i < num_data; i++ ) {
		if ( fabs(br[i] - br2[i]) > 1e-5 ) {
			printf( "br[%d]: CPU:%f, GPU:%f\n", i, br[i], br2[i]);
		}
	}
#endif

	printf( "Finished\n" );
	free(bds);
	free(br);
	return 0;
}
