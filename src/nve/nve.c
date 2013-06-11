#include "nve.h"
#include <math.h>
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
#define DIVIDEND 0 // 분자
#define DIVISOR 1  // 분모
#define NOTAVAILABLE 0
#define AVAILABLE 1

// 출현빈도만 나온것이기 때문에 비교를 위해선 P(class)를 곱해줘서 비교해줘야한다.
// dvl, pdvl, 총길이
float nve(d2v_vector_t dv, d2v_vector_t pdvl_subset, int pdvl_full_length, int pdvl_full_element_count){
	// 이건 지워질놈
	//float** frequencies;
	// 이거 쓸꺼야
	float* probability;
	//	float score = 1;
	float score = 0;
	int pdvl_cnt_sum = 0;
	int frequency_index = 0;
	int i, j, h;
	int dv_cnt_sum = 0;
	int prolength = 0;
	int islaplace = NOTAVAILABLE;
	int islaplace2 = NOTAVAILABLE;

	float result_dividend = 1;
	float result_divisor = 1;

	// 값을 받아서 나누고 그 값을 1차 배열에 넣고 주르르륵 곱해서 결과를 도출해야할듯
	// 안나누고 곱먼저하면 값이 너무커져 계산불가능
	float dividend;
	float divisor;

	int weight = 1;
		
	pdvl_cnt_sum = pdvl_full_element_count;

	if(dv.length == 0){
		return 0;
	}

	// 나이브 베이지안 연산에서 분모에 들어갈 pdvl의 전체 단어의 수
	/*
	for(i = 0; i < pdvl_subset.length; i++){
		pdvl_cnt_sum += pdvl_subset.element[i].count;
		}
	}
	*/
	// 새로 들어온 dv의 전체 단어의 수. 확률계산할 때 각 P들이 들어간다 
	for(i = 0; i< dv.length; i++)
		dv_cnt_sum += dv.element[i].count;

	//probability = (float *)malloc(sizeof(float)*dv_cnt_sum);
	probability = (float *)malloc(sizeof(float)*dv.length);

//	printf("full count %d\n", pdvl_cnt_sum);
//	printf("dv.length %d, dv.elemet[0].count %d, pdvl_subbset.length %d \n", dv.length, dv.element[0].count, pdvl_subset.length);

	// dv의 길이 만큼 반복 
	for(i = 0; i< dv.length; i++){
		weight = 1;
		// dv에서 같은 단어가 나올시 똑같은연산을 해야한다. 그러기 때문에 각 단어의 count 만큼 반복
		for(j = 0; j< dv.element[i].count; j++){
			//dividend = (float)pdvl_subset.element[i].count+1;
			weight++;
		}
//		for(j = 0; j< dv.element[i].count; j++){
			// dv와 pdvl의 단어가 일치하면 일치하는 pdvl의 갯수를 분자로
			// 전체 pdvl가 가지고 있는 단어의 갯수를 분자로 하면 각 단어의 출현 확률값이 나온다.
//			if(dv.element[i].id == pdvl_subset.element[i].id){
				//dividend = (float)pdvl_subset.element[h].count+1;
				
				dividend = (float)pdvl_subset.element[i].count+1;
				divisor = (float)pdvl_cnt_sum + pdvl_full_length;
				probability[frequency_index] = (dividend/divisor)*weight;
		//		printf("%f %f %f\n", dividend, divisor, probability[frequency_index]);
				frequency_index++;
//			} 
//		}
	}

//	for(i = 0; i < dv_cnt_sum; i++){
	for(i = 0; i < dv.length; i++){
//		printf("probability is %f\n", log10(probability[i]));
//		score *= probability[i];		
		//		printf("%f\n", probability[i]);
		score += log10(probability[i]);		
//		printf("scoreis %f\n", score);
	}

	free(probability);
	/*
	// 분모 분자를 곱해준다
	for(i = 0; i < dv_cnt_sum; i++){
	result_dividend *= frequencies[DIVIDEND][i];
	result_divisor  *= frequencies[DIVISOR][i];

	}
	*/
	//printf("%f %f\n", result_dividend, result_divisor);
	/*
	   for(i = 0; i<2; i++)
	   free(frequencies[i]);
	   free(frequencies);
	   */
	//return result_dividend/result_divisor;

	return score;
}

