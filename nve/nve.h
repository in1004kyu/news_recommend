#include <stdio.h>
#include <stdlib.h>
struct d2v_element {
	int id;
	int count;
};

struct d2v_vector{
	int length;
	struct d2v_element* elements;
};

float nve(struct d2v_vector dv, struct d2v_vector pdvl_subset,int pdvl_full_length);
