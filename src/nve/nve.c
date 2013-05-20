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
#define DIVIDEND 0 // 분자
#define DIVISOR 1  // 분모
#define NOTAVAILABLE 0
#define AVAILABLE 1

// 출현빈도만 나온것이기 때문에 비교를 위해선 P(class)를 곱해줘서 비교해줘야한다.
float nve(d2v_vector_t dv, d2v_vector_t pdvl_subset, int pdvl_full_length){
	// 이건 지워질놈
	//float** frequencies;
   	// 이거 쓸꺼야
	float* probability;
	float score = 1;
	int pdvl_cnt_sum = 0;
	int frequency_index = 0;
	int i, j, h;
	int dv_cnt_sum = 0;
	int islaplace = NOTAVAILABLE;

	float result_dividend = 1;
	float result_divisor = 1;

	// 값을 받아서 나누고 그 값을 1차 배열에 넣고 주르르륵 곱해서 결과를 도출해야할듯
    // 안나누고 곱먼저하면 값이 너무커져 계산불가능
	float dividend;
	float divisor;

	if(dv.length == 0){
		return 0;
	}

	// 나이브 베이지안 연산에서 분모에 들어갈 pdvl의 전체 단어의 수
	for(i = 0; i < pdvl_subset.length; i++)
		pdvl_cnt_sum += pdvl_subset.element[i].count;

	// 새로 들어온 dv의 전체 단어의 수. 확률계산할 때 각 P들이 들어간다 
	for(i = 0; i< dv.length; i++)
		dv_cnt_sum += dv.element[i].count;


	probability = (float *)malloc(sizeof(float)*dv_cnt_sum);

	// 안쓸거야 start
	// 나이브 베이지안 연산하기 위한 배열 두개 메모리 확보 
	/*
	frequencies = (float **)malloc(sizeof(float*)*2);

	// 각 배열에 dv_cnt_sum 만큼 메모리 확보, 하나는 분모, 하나는 분자가 된다
	for(i = 0; i<2; i++)
		frequencies[i] = (float *)malloc(sizeof(float)*dv_cnt_sum);
	*/
	// 안쓸꺼야 end


	// dv의 길이 만큼 반복 
	for(i = 0; i< dv.length; i++){
		// dv에서 같은 단어가 나올시 똑같은연산을 해야한다. 그러기 때문에 각 단어의 count 만큼 반복
		for(j = 0; j< dv.element[i].count; j++){
			// 각 dv element와 pdvl의 element끼리 비교해서 
			for(h = 0; h < pdvl_subset.length; h++){
				// dv와 pdvl의 단어가 일치하면 일치하는 pdvl의 갯수를 분자로
				// 전체 pdvl가 가지고 있는 단어의 갯수를 분자로 하면 각 단어의 출현 확률값이 나온다.
				if(dv.element[i].id == pdvl_subset.element[h].id){

					dividend = (float)pdvl_subset.element[h].count; 
					divisor = (float)pdvl_cnt_sum;
					
		printf("dividend is %f\n", dividend);
		printf("divisor is %f\n", divisor);
					probability[frequency_index] = dividend/divisor;
					
					/*
					frequencies[DIVIDEND][frequency_index] = (float)pdvl_subset.element[h].count;
					frequencies[DIVISOR][frequency_index] = (float)pdvl_cnt_sum;
				    */
					// 값을 넣고 배열의 인덱스를 늘린다.
					frequency_index++;
					// 단어가 나왔을 경우 laplace를 안해도 된다.
					islaplace = AVAILABLE;
					break;
					// 중복된계산을 피하기 위해서인데 잘안되서 보류 
					//		} else if(dvl.vectors[i].id > pdvl_subset.vectors[h].id && islaplace == NOTAVAILABLE){
		    	} 
			}
			// 단어가 하나도 안나왔을 경우를 대비해서 0.5를 곱해주는 laplace 기법
			if(islaplace == NOTAVAILABLE){
				probability[frequency_index] = 0.5;
				/*
				frequencies[DIVIDEND][frequency_index] = (float)1;
				frequencies[DIVISOR][frequency_index] = (float)2;
				*/
				frequency_index++;

			}
			islaplace = NOTAVAILABLE;
		}
	}
	for(i = 0; i < dv_cnt_sum; i++){
		printf("probability is %f\n", probability[i]);
		score *= probability[i];		
		printf("scoreis %e\n", score);
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

	// 나눠서 나온값은 score이다.
	//return result_dividend/result_divisor;
	return score;
}

