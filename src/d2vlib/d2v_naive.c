/*
 *  Docuemnt to Vector Library
 */

/************************ d2v_naive.c ***********************/

#include"d2v.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE 32768

d2v_status_t d2v_open(d2v_ctx_t *pctx)
{
	gtt_status_t ret;
	ret = gtt_open(&pctx->gtt_ctx,"default.gtt");

	if( ret != GTT_STATUS_SUCCESS )
		return D2V_STATUS_ERROR_OPEN;

	return D2V_STATUS_SUCCESS;
}

d2v_status_t d2v_get_document_vector(d2v_ctx_t *pctx, char *filename)
{
	char line[MAX_LINE];
	unsigned int input_count=0;
	char input_term[MAX_LINE];
	unsigned int TID;
	
	pctx->input_fp = fopen(filename, "r");
	
	while( fgets(line, MAX_LINE, pctx->input_fp ) != NULL ){
		sscanf(line, "%s %d", input_term, &input_count);
		gtt_update_term(&pctx->gtt_ctx,input_term, &TID);
		pctx->document_vector.element[pctx->document_vector.length].id = TID;
		pctx->document_vector.element[pctx->document_vector.length].count = input_count;
		pctx->document_vector.length++;
	}

	return D2V_STATUS_SUCCESS;
}

d2v_status_t d2v_close(d2v_ctx_t *pctx)
{
	gtt_status_t ret;
	ret = gtt_close(&pctx->gtt_ctx);
	if( ret != GTT_STATUS_SUCCESS)
		return D2V_STATUS_ERROR_CLOSE;
	return D2V_STATUS_SUCCESS;
}


