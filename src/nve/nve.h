#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int id;
	int count;
}d2v_element_t;

typedef struct{
	int length;
	d2v_element_t* elements;
}d2v_vector_t;

float nve(d2v_vector_t dv, d2v_vector_t pdvl_subset,int pdvl_full_length);
