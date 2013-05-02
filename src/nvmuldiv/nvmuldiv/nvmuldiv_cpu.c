#include "nvmuldiv.h"
#include <stdio.h>

float nvmuldiv( float numerators[], float denominators[], int len)
{
	int i = 0;
	float num = numerators[i];
	float den = denominators[i];
	while( ++i < len ) {
		num *= numerators[i];
		den *= denominators[i];
	}
	printf( "num:%f\n", num );
	printf( "den:%f\n", den );
	return num/den;
}
