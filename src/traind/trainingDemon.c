#include "../d2vlib/d2v.h"
#include <stdlib.h>
int main()
{
	d2v_ctx_t d2v_ctx;
	d2v_status_t ret;
	d2v_vector_t doc_vec;
	int i;
	int cnt = 0;

	for(cnt = 1; cnt <22; cnt++){
		char filePath[40];
		char filename[25] = "../example/training/test";
		char filetype[5] = ".txt";
		sprintf(filePath, "%s%d%s", filename, cnt, filetype);
		printf("%s\n", filePath);
		
	// Open input text file: test.txt
	ret = d2v_open(&d2v_ctx,"../example/training/test10.txt");
	if( ret != D2V_STATUS_SUCCESS ){
		printf("d2v open error!\n");
		return 0;
	}

	// Convert the input to it's document vector representation: doc_vec
	d2v_get_document_vector(&d2v_ctx, &doc_vec);

	for( i = 0; i < doc_vec.length; i++){
		printf("%d , %d \n" ,
				doc_vec.element[i].id,
				doc_vec.element[i].count);
	}

	// Cleanup
	d2v_free_vector(&doc_vec);
	d2v_close(&d2v_ctx);
	}
	return 0;
}

