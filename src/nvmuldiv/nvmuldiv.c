#include "nvmuldiv_private.h"
#include <sys/time.h>
#include <stdio.h>

long nvmuldiv_timestamp(void)
{
	long result;
	struct timeval tv;
	gettimeofday( &tv, NULL );

	result = tv.tv_sec;
	result *= 1000000;
	result += tv.tv_usec;
	//fprintf( stderr, "timestamp: %ld, sec:%ld, usec:%ld\n", result, (long) tv.tv_sec, (long) tv.tv_usec );
	return result;
}

nvmuldiv_status_t nvmuldiv_init(void)
{
	_nvmuldiv_cpu_init();
	_nvmuldiv_cuda_init();
}
