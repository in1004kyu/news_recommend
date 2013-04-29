#include <stdio.h>
#include <stdlib.h>
struct vector {
	int id;
	int count;
};

struct vector_list{
	int length;
	struct vector* vectors;
};

float nve(struct vector_list dvl, struct vector_list pdvl_subset,int pdvl_full_length);
