#include<stdio.h>
#include"d2v.h"

int main()
{
	d2v_ctx_t d2v_ctx;
	d2v_status_t ret;
	int i;

	ret = d2v_open(&d2v_ctx);
	if( ret != D2V_STATUS_SUCCESS ){
		printf("d2v open error!\n");
		return 0;
	}

	d2v_get_document_vector(&d2v_ctx, "test.txt");

	for( i = 0; i < d2v_ctx.document_vector.length; i++){
		printf("%d , %d \n" , 
				d2v_ctx.document_vector.element[i].id,
				d2v_ctx.document_vector.element[i].count);
	}

	d2v_close(&d2v_ctx);

	return 0;
}
