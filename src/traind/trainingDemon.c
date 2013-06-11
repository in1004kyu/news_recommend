#include "../d2vlib/d2v.h"
#include "../pdvllib/pdvl.h"
#include <stdlib.h>
int main()
{
	d2v_ctx_t d2v_ctx;
	d2v_status_t ret;
	d2v_vector_t doc_vec;

	pdvl_ctx_t pdvl;
	pdvl_status_t pdvlRet;
//	pdvl_count_t getcount;

	int i;
	int cnt = 0;

	//pdvl open
	pdvlRet = pdvl_open(&pdvl, "default.pdvl");
	if(pdvlRet == PDVL_STATUS_FAIL){		
		printf("pdvl open error!\n");
		return 0;
	}

	for(cnt = 1; cnt <24; cnt++){	
//	for(cnt = 2; cnt <3; cnt++){
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
		
		/*
		//pdvl open
		pdvlRet = pdvl_open(&pdvl, "default.pdvl");
		if(pdvlRet == PDVL_STATUS_FAIL){		
			printf("pdvl open error!\n");
			return 0;
		}
		*/

		// Convert the input to it's document vector representation: doc_vec
		d2v_get_document_vector(&d2v_ctx, &doc_vec);
		

		for( i = 0; i < doc_vec.length; i++){
			pdvl_update_count(&pdvl, doc_vec.element[i].id, doc_vec.element[i].count);
		}
		
		// Cleanup
		d2v_free_vector(&doc_vec);
		d2v_close(&d2v_ctx);
	}
		pdvl_close(&pdvl);

/*	
	if(ret == PDVL_STATUS_SUCCESS){
		pdvl_tid_t TID = -1;
        // update tid and count
         for( i = 1; i < 4; i++){
             pdvl_update_count( &pdvl, i,(10-i) );
             printf("Update > TID : %d , Count : %d\n",i,(10-i));
         }
         pdvl_close(&pdvl);

	}
*/

	return 0;
}

