#include "nve.h"
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

	frequencies = (float **)malloc(sizeof(float*)*2);

	for(i = 0; i<2; i++)
		frequencies[i] = (float *)malloc(sizeof(float)*dvl_cnt_sum);

	for(i = 0; i< dvl.length; i++){
		for(j = 0; j< dvl.vectors[i].count; j++){
			for(h = 0; h < pdvl_subset.length; h++){
				if(dvl.vectors[i].id == pdvl_subset.vectors[h].id){
					frequencies[DIVIDEND][frequency_index] = (float)pdvl_subset.vectors[h].count;
					frequencies[DIVISOR][frequency_index] = (float)pdvl_cnt_sum;
					frequency_index++;
					islaplace = AVAILABLE;
					break;
					//		} else if(dvl.vectors[i].id > pdvl_subset.vectors[h].id && islaplace == NOTAVAILABLE){
		    	} 
			}
			if(islaplace == NOTAVAILABLE){
				frequencies[DIVIDEND][frequency_index] = (float)1;
				frequencies[DIVISOR][frequency_index] = (float)2;
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

