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
