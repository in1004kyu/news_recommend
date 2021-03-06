#include "nve.h"
#define PDVL_COUNT	100
#define DVL_COUNT	10
#define PDVLSUB_COUNT 3
void init(d2v_vector_t* vector_list, int len){
	int i;
	vector_list->length = len;
	vector_list->element = (d2v_element_t*)malloc(sizeof(d2v_element_t) * len);

	for(i = 0; i < len; i++){		
		vector_list->element[i].id = i;
		vector_list->element[i].count = (rand() % (len/2)) + 1;
	}
}

void vector_free(d2v_vector_t* vector_list){
	free(vector_list->element);
}
void vector_print(d2v_vector_t vector_list){
	int i;
	printf("id / count\n");
	for(i = 0; i<vector_list.length; i++){
		printf("%d / %d\n", vector_list.element[i].id, vector_list.element[i].count);
	}
}

int main(){
	d2v_vector_t dvl;
	d2v_vector_t pdvl;
	int i;
	int pdvl_full_count = 0;
//	for(i = 0; i<10; i++){
	init(&pdvl, PDVL_COUNT);
	init(&dvl, DVL_COUNT);

	dvl.element[0].id = 100;

//	printf("--personal document vector list--\n");
//	vector_print(pdvl);
//	printf("--input document vector list--\n");
//	vector_print(dvl);

	for(i = 0; i < PDVL_COUNT; i++)
		pdvl_full_count += pdvl.element[i].count;

	printf("score is %f\n",nve(dvl, pdvl, PDVL_COUNT, pdvl_full_count) );

	vector_free(&pdvl);
	vector_free(&dvl);
//	}
}
