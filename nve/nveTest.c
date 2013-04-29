#include "nve.h"
#define PDVL_COUNT	4
#define DVL_COUNT	3
#define PDVLSUB_COUNT 3
void init(struct vector_list* vector_list, int len){
	int i;
	vector_list->length = len;
	vector_list->vectors = (struct vector*)malloc(sizeof(struct vector) * len);

	for(i = 0; i < len; i++){		
		vector_list->vectors[i].id = i;
		vector_list->vectors[i].count = (rand() % len) + 1;
	}
}

void vector_free(struct vector_list* vector_list){
	free(vector_list->vectors);
}
void vector_print(struct vector_list vector_list){
	int i;
	printf("id / count\n");
	for(i = 0; i<vector_list.length; i++){
		printf("%d / %d\n", vector_list.vectors[i].id, vector_list.vectors[i].count);
	}
}

int main(){
	struct vector_list pdvl;
	struct vector_list dvl;
	struct vector_list pdvl_subset;
	init(&pdvl, PDVL_COUNT);
	init(&dvl, DVL_COUNT);

	dvl.vectors[0].id = 100;

	printf("--personal document vector list--\n");
	vector_print(pdvl);
	printf("--input document vector list--\n");
	vector_print(dvl);


	printf("score is %f\n",nve(dvl, pdvl, PDVL_COUNT) );

	vector_free(&pdvl);
	vector_free(&dvl);
}
