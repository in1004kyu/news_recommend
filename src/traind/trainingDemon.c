//#include "../d2vlib/d2v.h"
#include "../pdvllib/pdvl.h"
#include "../cosine/cosine.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE 256

 void init(d2v_vector_t* vector_list, int len){
     vector_list->length = len;
     vector_list->element = (d2v_element_t*)malloc(sizeof(d2v_element_t) * len);
 }
 void vector_free(d2v_vector_t* vector_list){
     free(vector_list->element);
 }

void getThreshold(float score){
		FILE *wfp, *rfp;
		float savedscore;
		float avg;
        rfp = fopen("threshold.txt", "r");
    
		fscanf(rfp, "%f", &savedscore); 
		

		if(savedscore < 0.00001){
			wfp = fopen("threshold.txt", "w");
			fprintf(wfp, "%f", score);		
			fclose(wfp);
			printf("threshold -> %f\n", score);
			return;
		}
		avg = ((score + savedscore)/2);
		wfp = fopen("threshold.txt", "w");
		fprintf(wfp, "%f", avg);
		printf("threshold -> %f\n", avg);
		fclose(wfp);
        fclose(rfp);
}

int main()
{
	d2v_ctx_t d2v_ctx;
	d2v_status_t ret;
	d2v_vector_t doc_vec;
	
	// for create threshhold
	d2v_vector_t pdvlVector;
	float score;
	int pdvlcount =0;

	pdvl_ctx_t pdvl;
	pdvl_status_t pdvlRet;
	pdvl_count_t getcount;

	int i, j;
	int cnt;

	//pdvl open
	pdvlRet = pdvl_open(&pdvl, "default.pdvl");
	if(pdvlRet == PDVL_STATUS_FAIL){		
		printf("pdvl open error!\n");
		return 0;
	}

//	for(cnt = 1; cnt <2; cnt++){	
	for(cnt = 1; cnt <24; cnt++){
		char filePath[40];
		char filename[25] = "../example/training/test";
		char filetype[5] = ".txt";
		sprintf(filePath, "%s%d%s", filename, cnt, filetype);
		printf("%s\n", filePath);

		// Open input text file: test.txt
		ret = d2v_open(&d2v_ctx,filePath);
		if( ret != D2V_STATUS_SUCCESS ){
			printf("d2v open error!\n");
			return 0;
		}
		

		// Convert the input to it's document vector representation: doc_vec
		d2v_get_document_vector(&d2v_ctx, &doc_vec);
		

		// traing
		for( i = 0; i < doc_vec.length; i++){
			pdvl_update_count(&pdvl, doc_vec.element[i].id, doc_vec.element[i].count);
		}

		
		// traing한후 pdvl과 d2v와의 threshold를 저장하자
		init(&pdvlVector, doc_vec.length);
		
		for(j = 0; j < doc_vec.length; j++){
			getcount = pdvl_get_count(&pdvl, doc_vec.element[j].id);
			if(getcount == -1)
				pdvlcount = 0;
			else
				pdvlcount = getcount;
			pdvlVector.element[j].id = doc_vec.element[j].id;
			pdvlVector.element[j].count = pdvlcount;
		}
		
		score = cosineSim(doc_vec, pdvlVector);

		getThreshold(score);			
		vector_free(&pdvlVector);
		/////////////////////////////////////////////////
		// Cleanup
		d2v_free_vector(&doc_vec);
		d2v_close(&d2v_ctx);
	}
		pdvl_close(&pdvl);


	return 0;
}

