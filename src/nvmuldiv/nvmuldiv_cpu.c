#include "nvmuldiv.h"
#include <stdio.h>

float nvmuldiv( float numerators[], float denominators[], int len)
{
	int i = 0;
	float result;
	float num = numerators[i];
	float den = denominators[i];
	result = num / den;
	while( ++i < len ) {
		result *= numerators[i] / denominators[i];
	}
	return result;
}

int nvmuldiv_seg( float n[], float d[], int len, float r[], int len_r )
{
	float *pn = &n[0];
	float *pd = &d[0];
	int i = 0;

	while( len > 0 ) {

		r[i] = nvmuldiv(pn, pd, len_r );
		len -= len_r;
		i++;
		pn += len_r;
		pd += len_r;
	}
	return 0;
}
