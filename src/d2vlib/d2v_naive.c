/*
 *  Docuemnt to Vector Library
 */

/************************ d2v_naive.c ***********************/

#include"d2v.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE 32768
#define MAX_ELEMENT_SIZE 1024

d2v_status_t d2v_open(d2v_ctx_t *pctx,char *filename)
{
	gtt_status_t ret;
	ret = gtt_open(&pctx->gtt_ctx,"default.gtt");
	pctx->input_fp = fopen(filename, "r");

	if( ret != GTT_STATUS_SUCCESS )
		return D2V_STATUS_ERROR_OPEN;

	return D2V_STATUS_SUCCESS;
}

d2v_status_t d2v_get_document_vector(d2v_ctx_t *pctx, d2v_vector_t *doc_vec)
{
	char line[MAX_LINE];
	unsigned int input_count=0;
	char input_term[MAX_LINE];
	unsigned int TID;
	int len = 0;
	
	while( fgets(line, MAX_LINE, pctx->input_fp ) != NULL ){
		len++;
	}
	fseek( pctx->input_fp, 0, SEEK_SET );
	doc_vec->element = (d2v_element_t *)malloc(len*sizeof(d2v_element_t));

	while( fgets(line, MAX_LINE, pctx->input_fp ) != NULL ){
		sscanf(line, "%s %d", input_term, &input_count);
		gtt_update_term(&pctx->gtt_ctx,input_term, &TID);
		doc_vec->element[doc_vec->length].id = TID;
		doc_vec->element[doc_vec->length].count = input_count;
		doc_vec->length++;
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

d2v_status_t d2v_free_vector(d2v_vector_t *doc_vec)
{
	free(doc_vec->element);
	return D2V_STATUS_SUCCESS;
}

