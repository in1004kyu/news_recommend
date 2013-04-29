#include "nve.h"
#define PDVL_COUNT	4
#define DVL_COUNT	3
#define PDVLSUB_COUNT 3
void init(struct d2v_vector* vector_list, int len){
	int i;
	vector_list->length = len;
	vector_list->elements = (struct d2v_element*)malloc(sizeof(struct d2v_element) * len);

	for(i = 0; i < len; i++){		
		vector_list->elements[i].id = i;
		vector_list->elements[i].count = (rand() % len) + 1;
	}
}

void vector_free(struct d2v_vector* vector_list){
	free(vector_list->elements);
}
void vector_print(struct d2v_vector vector_list){
	int i;
	printf("id / count\n");
	for(i = 0; i<vector_list.length; i++){
		printf("%d / %d\n", vector_list.elements[i].id, vector_list.elements[i].count);
	}
}

int main(){
	struct d2v_vector pdvl;
	struct d2v_vector dvl;
	struct d2v_vector pdvl_subset;
	init(&pdvl, PDVL_COUNT);
	init(&dvl, DVL_COUNT);

	dvl.elements[0].id = 100;

	printf("--personal document vector list--\n");
	vector_print(pdvl);
	printf("--input document vector list--\n");
	vector_print(dvl);
	

	printf("score is %f\n",nve(dvl, pdvl, PDVL_COUNT) );

	vector_free(&pdvl);
	vector_free(&dvl);
}
