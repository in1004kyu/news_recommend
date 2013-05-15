#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>

#include "nvmuldiv.h"

#define NUM_DEFAULT_DATA	60000
#define NUM_LEN_DATASET		512
#define NUM_TEST_LOOP		100

void test_print_duration( char *label, long t_us );

void nvmuldiv_data_fill_random( int len, float *d1, float*d2 )
{
	int i;
	float value;
	for( i = 0; i < len; i++ ) {
		value = ( (float) ((random() % 10) + 1) );
		d1[i] = value;
		value = ( (float) ((random() % 10) + 1) );
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

void test_muldiv_cpu(float *bd1, float *bd2, int num_data, int len_dataset, float *br)
{
	int i;
	long ts1, ts2;
	fprintf(stderr, "CPU...\n" );

	ts1 = nvmuldiv_timestamp();
	for( i = 0; i < NUM_TEST_LOOP; i++ ) {
		nvmuldiv_seg( bd1, bd2, num_data * len_dataset, br, len_dataset );
	}
	ts2 = nvmuldiv_timestamp();
	/*
	for ( i = 0; i < num_data; i++ ) {
		printf( "br[%d]:%f\n", i, br[i]);
	}
	*/
	test_print_duration( "Elapsed time", ts2-ts1 );
}

void test_print_duration( char *label, long t_us )
{
	fprintf( stderr, "%s:", label );
	if ( t_us >= 1000000 ) {
		// second
		fprintf( stderr, "%ld.%lds\n", t_us / 1000000, (t_us % 1000000) / 1000);
	} else if ( t_us >= 1000 ) {
		// ms
		fprintf( stderr, "%ldms\n", t_us  / 1000);
	} else {
		// us
		fprintf( stderr, "%ldus\n", t_us );
	}
}
void test_muldiv_cuda(float *bd1, float *bd2, int num_data, int len_dataset, float *br)
{
	int i;
	long ts1, ts2;
	int result = 0;

	fprintf(stderr, "CUDA...\n" );
	ts1 = nvmuldiv_timestamp();

	for( i = 0; result == 0 && i < NUM_TEST_LOOP; i++ ) {
		result = nvmuldiv_seg_cuda( bd1, bd2, num_data * len_dataset, br, len_dataset );
	}
	ts2 = nvmuldiv_timestamp();
	if ( result != 0 ) {
		fprintf( stderr, "Error occured at %dth iteration\n", i );
	} else {
		test_print_duration( "Elapsed time", ts2-ts1 );
	}
}

void test_muldiv_cuda_pagelocked(float *bd1, float *bd2, int num_data, int len_dataset, float *br)
{
	int i;
	long ts1, ts2;


	float *bd1_h = nvmuldiv_mapped_alloc( sizeof(float) * num_data * len_dataset);
	float *bd2_h = nvmuldiv_mapped_alloc( sizeof(float) * num_data * len_dataset);
	float *br_h = nvmuldiv_mapped_alloc( sizeof(float) * num_data );

	float *bd1_d;
	float *bd2_d;
	float *br_d;

	fprintf(stderr, "CUDA Page Locked...\n" );

	if ( bd1_h != NULL && bd2_h != NULL && br_h != NULL ) {
		bd1_d = nvmuldiv_mapped_device( bd1_h );
		bd2_d = nvmuldiv_mapped_device( bd2_h );
		br_d = nvmuldiv_mapped_device( br_h) ;

		memcpy( bd1_h, bd1, sizeof(float) * num_data * len_dataset );
		memcpy( bd2_h, bd2, sizeof(float) * num_data * len_dataset );
		memcpy( br_d, br, sizeof(float) * num_data );

		float *vr_d = NULL;
		vr_d = nvmuldiv_device_alloc( sizeof(float) * num_data * len_dataset );
		//cudaMalloc( &vr_d, sizeof(float) * num_data * len_dataset );
		int result = 0;

		ts1 = nvmuldiv_timestamp();
		for( i = 0; result == 0 && i < NUM_TEST_LOOP; i++ ) {
			result = nvmuldiv_seg_cuda_devmem( bd1_d, bd2_d, num_data * len_dataset, br_d, len_dataset, vr_d );
			cudaDeviceSynchronize();
		}
		ts2 = nvmuldiv_timestamp();

		if ( result != 0 ) {
			fprintf( stderr, "Error occured at %dth iteration\n", i );
		} else {
			memcpy(br, br_h, sizeof(float) * num_data );
			test_print_duration( "Elapsed time", ts2-ts1 );
		}
		nvmuldiv_mapped_free( bd1_h );
		nvmuldiv_mapped_free( bd2_h );
		nvmuldiv_mapped_free( br_h );
		if ( vr_d != NULL ) nvmuldiv_device_free( vr_d );
	} else {
		fprintf( stderr, "test_muldiv_cuda_pagelocked: memory allocation error\n" );
		fprintf( stderr, " - bd1_h:%p\n", bd1_h );
		fprintf( stderr, " - bd2_h:%p\n", bd2_h );
		fprintf( stderr, " - br_h:%p\n", br_h );
	}
}

void test_dump_dataset( float *d1, float *d2, int len_dataset )
{
	int i;
	float reduce = 1;
	for( i = 0; i < len_dataset; i++ ) {
		printf( "d[%d]: { %f / %f = %f }\n", i, d1[i], d2[i], d1[i] / d2[i] );
		reduce *= d1[i] / d2[i];
	}
	printf( " - reduce:%f\n", reduce );
}

void test_verify_result(float *bd1, float *bd2, float *br, float *br2, int num_data, int len_dataset )
{
#ifdef __NVMULDIV_ENABLE_VERIFY__
	{
		int error_count = 0;
		int i;
		fprintf( stderr, "Verifying result...\n" );
		for ( i = 0; i < num_data; i++ ) {
			if ( fabs(br[i] - br2[i]) > 1e-5 ) {
				printf( "br[%d]: CPU:%f, GPU:%f\n", i, br[i], br2[i]);
				test_dump_dataset( &bd1[len_dataset * i], &bd2[len_dataset * i], len_dataset );
				error_count++;
			}
		}

		if ( error_count == 0 ) {
			fprintf( stderr, "No error found\n" );
		} else {
			fprintf( stderr, "%d errors found\n", error_count );
		}
	}
#endif
}
int main(void)
{

	int i;
	float *datasets1[NUM_DEFAULT_DATA];
	float *datasets2[NUM_DEFAULT_DATA];
	float *bd1;	// bulk dataset 1
	float *bd2;	// bulk dataset 2
	long ts1;
	long ts2;
// Generate random data for test
	srandom( time(0) );
	int num_data = NUM_DEFAULT_DATA;
	int len_dataset = NUM_LEN_DATASET;
	int result;

	nvmuldiv_init();
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

		p += len_dataset;
	}
	nvmuldiv_data_fill_random( len_dataset * num_data, bd1, bd2 );

// Multiply
#if 1
	test_muldiv_cpu( bd1, bd2, num_data, len_dataset, br );
#endif

#if 0
	test_muldiv_cuda( bd1, bd2, num_data, len_dataset, br2 );
	test_verify_result( bd1, bd2, br, br2, num_data, len_dataset );
#endif 

	test_muldiv_cuda_pagelocked( bd1, bd2, num_data, len_dataset, br2 );
#if 1
	test_verify_result( bd1, bd2, br, br2, num_data, len_dataset );
#endif

	printf( "Finished\n" );
	free(bds);
	free(br);
	free(br2);
	return 0;
}
