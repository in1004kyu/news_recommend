//#include "../d2vlib/d2v.h"
#include "../pdvllib/pdvl.h"
//#include "../nve/nve.h"
#include "../cosine/cosine.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TESTSIZE 50

 void init(d2v_vector_t* vector_list, int len){
     vector_list->length = len;
     vector_list->element = (d2v_element_t*)malloc(sizeof(d2v_element_t) * len);
 }
 void vector_free(d2v_vector_t* vector_list){
     free(vector_list->element);
 }

struct result{
	float score;
	int filenum;
	int cnt;
	int recommend;
};

int partition(const void* num1, const void* num2)
{
	if( ((struct result*)num1)->score > ((struct result*)num2)->score )
		return -1;
	return ((struct result*)num1)->score < ((struct result*)num2)->score;
}

void recommend(struct result result[]){
	FILE *rfp;
	float threshold;
	float downThreshold;
	int i;
	int top = 0;
	rfp = fopen("threshold.txt", "r");
	fscanf(rfp, "%f", &threshold);
	fclose(rfp);

	downThreshold = threshold/2;

	for(i = 0; i<TESTSIZE; i++){
		if(threshold <= result[i].score)
			result[i].recommend = 1;
		else if(downThreshold <= result[i].score){
			if(top < 10){
				result[i].recommend = 2;
				top++;
			}
			else
				result[i].recommend = 0;
		}
		else 
			result[i].recommend = 0;
	}
	printf("\n ---------- Best Recommend news -----------\n");
	for(i = 0; i<TESTSIZE; i++){
		if(result[i].recommend == 1)
			printf("test%d cnt:%d / score %f\n", result[i].filenum, result[i].cnt, result[i].score);
	}	
	printf("\n ---------- Recommend news ----------\n");	
	for(i = 0; i<TESTSIZE; i++){
		if(result[i].recommend == 2)
			printf("test%d cnt:%d / score %f\n", result[i].filenum, result[i].cnt, result[i].score);
	}	
	printf("\n ---------- New news ----------\n");	
	for(i = 0; i<TESTSIZE; i++){
		if(result[i].recommend == 0)
			printf("test%d cnt:%d / score %f\n", result[i].filenum, result[i].cnt, result[i].score);
	}	

}

int main(){
	int i, j;
	d2v_ctx_t d2v_ctx;
    d2v_status_t ret;
    d2v_vector_t doc_vec;
	
	d2v_vector_t pdvlVector;
 
    pdvl_ctx_t pdvl;
    pdvl_status_t pdvlRet;
    pdvl_count_t getcount;

	char filePath[40] = "";
	char filename[28] = "../example/incoming/test";
	char filetype[5] = ".txt";
	struct result result[TESTSIZE];

	int pdvlcount = 0;
	pdvlRet = pdvl_open(&pdvl, "default.pdvl");
	if(pdvlRet == PDVL_STATUS_FAIL){
		printf("pdvl open error!\n");
		return 0;
	}

	// d2v로 읽어서 gtt 업데이트하고
	// 방금 읽은 걸루 pdvl하고 비교해서
	// naive 알고리즘에 적용하기
	for(i = 0; i < TESTSIZE; i++){
		 sprintf(filePath, "%s%d%s", filename, i, filetype);

		  // Open input text file: test.txt
          ret = d2v_open(&d2v_ctx,filePath);
          if( ret != D2V_STATUS_SUCCESS ){
              printf("d2v open error!\n");
              return 0;
          }
		
		// incomming 뉴스에서 d2v 가져오고(gtt추가) 
		d2v_get_document_vector(&d2v_ctx, &doc_vec);
		result[i].cnt = doc_vec.length;
		// 추출한 d2v의 id를 통해 pdvl에서 해당 아이디와 매칭되는 count를 가져온다
		// incomming 뉴스의 id, count, pdvl의 count를 가지고 있다 이걸 사용해 naive 사용
		// pdvl 백터 생성
		init(&pdvlVector, doc_vec.length);	

		for(j = 0; j < doc_vec.length; j++){	
			getcount = pdvl_get_count(&pdvl, doc_vec.element[j].id);
			if(getcount == -1){	
				pdvlcount = 0;
			}else{
				pdvlcount = getcount;
			}
			pdvlVector.element[j].id = doc_vec.element[j].id;
			pdvlVector.element[j].count = pdvlcount;
		}
		result[i].filenum = i;

		result[i].score = cosineSim(doc_vec, pdvlVector);

		vector_free(&pdvlVector);
		d2v_free_vector(&doc_vec);
		d2v_close(&d2v_ctx);
	}
		pdvl_close(&pdvl);

		qsort(result, TESTSIZE, sizeof(struct result), partition);
		recommend(result);
/*
		for(i = 0; i<TESTSIZE; i++){
			printf("test%d cnt:%d / score %f\n", result[i].filenum, result[i].cnt, result[i].score);
		}
*/
	return 0;
}

