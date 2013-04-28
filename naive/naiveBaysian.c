#include "naiveBaysian.h"
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


/*
// Performs Naive Bayesian Calculation of input 'dvl', 
by measuring it's similarity with input 'pdvl' and then returns the resulting score 

// Input 
// @param dvl Input Document Vector 
// @param pdvl_subset Input PDVL, 
Subset of the entire PDVL collected terms only those in the input 'dvl'
// @param pdvl_full_length The full length of PDVL, 
before subset extraction. Used as input parameter to Naive Bayesian Calculation (denominators) 
// 
// @return score Measured similarity 

// Discussion 
// We assume the following constraint due to performance and memory usage issues 
// dvl.length <= approx. 10K 
// pdvl.length <= approx. 10K (80KB) 
*/
#define DIVIDEND 0 //ºÐÀÚ
#define DIVISOR 1  //ºÐžð
#define NOTAVAILABLE 0
#define AVAILABLE 1

float nve(struct vector_list dvl, struct vector_list pdvl_subset, int pdvl_full_length){
	float** frequencies;
	int pdvl_cnt_sum = 0;
	int frequency_index = 0;
	int i, j, h;
	int dvl_cnt_sum = 0;
	int islaplace = NOTAVAILABLE;

	float result_dividend = 1;
	float result_divisor = 1;

	if(dvl.length == 0){
		return 0;
	}

	for(i = 0; i < pdvl_subset.length; i++)
		pdvl_cnt_sum += pdvl_subset.vectors[i].count;

	for(i = 0; i< dvl.length; i++)
		dvl_cnt_sum += dvl.vectors[i].count;

	printf("%d %d\n", pdvl_cnt_sum, dvl_cnt_sum);

	frequencies = (float **)malloc(sizeof(float*)*2);

	for(i = 0; i<2; i++)
		frequencies[i] = (float *)malloc(sizeof(float)*dvl_cnt_sum);

	for(i = 0; i< dvl.length; i++){
		for(j = 0; j< dvl.vectors[i].count; j++){
			for(h = 0; h < pdvl_subset.length; h++){
				if(dvl.vectors[i].id == pdvl_subset.vectors[h].id){
					frequencies[DIVIDEND][frequency_index] = (float)pdvl_subset.vectors[h].count;
					printf("%f\n", frequencies[DIVIDEND][frequency_index]);
					frequencies[DIVISOR][frequency_index] = (float)pdvl_cnt_sum;
					frequency_index++;
					islaplace = AVAILABLE;
					break;
					//		} else if(dvl.vectors[i].id > pdvl_subset.vectors[h].id && islaplace == NOTAVAILABLE){
		    	} 
			}
			if(islaplace == NOTAVAILABLE){
				printf("id is %d %d\n", dvl.vectors[i].id, pdvl_subset.vectors[h].id);
				frequencies[DIVIDEND][frequency_index] = (float)1;
				frequencies[DIVISOR][frequency_index] = (float)2;
				printf("%f\n", frequencies[DIVIDEND][frequency_index]);
				frequency_index++;

			}
			islaplace = NOTAVAILABLE;

		}
	}

	for(i = 0; i < dvl_cnt_sum; i++){
		result_dividend *= frequencies[DIVIDEND][i];
		result_divisor  *= frequencies[DIVISOR][i];
	}

	printf("%f %f\n", result_dividend, result_divisor);


	for(i = 0; i<2; i++)
		free(frequencies[i]);
	free(frequencies);

	return result_dividend/result_divisor;
}

int main(){
	struct vector_list pdvl;
	struct vector_list dvl;
	struct vector_list pdvl_subset;
	init(&pdvl, PDVL_COUNT);
	init(&dvl, DVL_COUNT);
	init(&pdvl_subset, PDVLSUB_COUNT);

	printf("--personal document vector list--\n");
	vector_print(pdvl);
	printf("--input document vector list--\n");
	vector_print(dvl);

	printf("score is %f\n",nve(dvl, pdvl, PDVL_COUNT) );

	vector_free(&pdvl);
	vector_free(&dvl);
}
