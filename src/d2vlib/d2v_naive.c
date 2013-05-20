/*
 *  Docuemnt to Vector Library
 */

/************************ d2v_naive.c ***********************/

#include"d2v.h"
#include "header/ham-ndx.h"
#include "../include/iconv.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define MAX_LINE 32768
#define MAX_ELEMENT_SIZE 1024
#define MAX_COLS 32768


/*========================== Global Variable ===========================*/
HAM_TERMLIST Term[MAX_TERMS_DOC];	/* extracted terms */
HAM_TERMMEMORY TM;	/* termtext.h: memories needed for term extraction */
/*======================================================================*/



/****************************************Util function***********************************/
// file context >>> char *p
d2v_status_t d2v_load_text(d2v_ctx_t *pctx)
{
	FILE *fp = pctx->input_fp;
	long n;
	unsigned char *p;

	fseek(fp, 0L, 2);
	n = ftell(fp);	/* n: byte size of file 'fp' */

	fseek(fp, 0L, 0);
	pctx->malloc_size = n*2;
	p = (unsigned char *) malloc(n*2);	/* memory allocation */
	if (p == NULL) return D2V_STATUS_ERROR_OPEN;

	fread(p, sizeof(unsigned char), n, fp);	/* read 'fp' to 'p' */
	*(p+n) = '\0';

	pctx->text = p;

	return D2V_STATUS_SUCCESS;
}


d2v_status_t d2v_utf_to_euc(d2v_ctx_t *pctx)
{
	char szIn[MAX_LINE], szOut[MAX_LINE];
	char *pszIn = NULL, *pszOut = NULL;
	iconv_t cd = NULL;
	size_t  i = 0 ,nRet = 0, nIn = 0, nOut = 0;

	nIn = sprintf( szIn, "%s" , pctx->text );
	pszIn = szIn;
	pszOut = szOut;
	nOut = sizeof(szOut);
	memset(szOut, 0x00, sizeof(szOut));

	if( (cd = iconv_open("EUC-KR","UTF-8")) == (iconv_t)(-1))
	{
		printf("fail to iconv_open()\n");
		return D2V_STATUS_ERROR_OPEN;
	}

	if( (nRet = iconv(cd, (char ** __restrict__)&pszIn, &nIn, &pszOut, &nOut)) == (size_t)-1 )
	{
		printf("fail to iconv()\n");
		return D2V_STATUS_ERROR_OPEN;
	}
	nOut = pszOut - szOut;
	for( i = 0; i < pctx->malloc_size; i++)
		pctx->text[i] = 0x00;

	for( i = 0; i < nOut; i++)
	{
		pctx->text[i] = szOut[i];
	}
	return D2V_STATUS_SUCCESS;
}

d2v_status_t d2v_euc_to_utf(d2v_ctx_t *pctx)
{
	char szIn[MAX_LINE], szOut[MAX_LINE];
	char *pszIn = NULL, *pszOut = NULL;
	iconv_t cd = NULL;
	size_t  i = 0 ,nRet = 0, nIn = 0, nOut = 0;

	nIn = sprintf( szIn, "%s" , pctx->text );
	pszIn = szIn;
	pszOut = szOut;
	nOut = sizeof(szOut);
	memset(szOut, 0x00, sizeof(szOut));

	if( (cd = iconv_open("UTF-8","EUC-KR")) == (iconv_t)(-1))
	{
		printf("fail to iconv_open()\n");
		return D2V_STATUS_ERROR_OPEN;
	}

	if( (nRet = iconv(cd, (char ** __restrict__)&pszIn, &nIn, &pszOut, &nOut)) == (size_t)-1 )
	{
		printf("fail to iconv()\n");
		return D2V_STATUS_ERROR_OPEN;
	}
	nOut = pszOut - szOut;
	for( i = 0; i < pctx->malloc_size; i++)
		pctx->text[i] = 0x00;

	for( i = 0; i < nOut; i++)
	{
		pctx->text[i] = szOut[i];
	}

	return D2V_STATUS_SUCCESS;
}



















/**************************************API function **********************************/
d2v_status_t d2v_open(d2v_ctx_t *pctx,char *filename)
{
	gtt_status_t gtt_ret;
	d2v_status_t d2v_ret;

	gtt_ret = gtt_open(&pctx->gtt_ctx,"default.gtt");
	if( gtt_ret != GTT_STATUS_SUCCESS )
		return D2V_STATUS_ERROR_OPEN;

	pctx->input_fp = fopen(filename, "r");
	if( pctx->input_fp == NULL )
		return D2V_STATUS_ERROR_OPEN;
	d2v_ret = d2v_load_text(pctx);
	if( d2v_ret != D2V_STATUS_SUCCESS )
		return D2V_STATUS_ERROR_OPEN;

	// test encoding utf-8 <-> euc-kr
	/*d2v_euc_to_utf(pctx);
	printf("%s\n",pctx->text);
	d2v_utf_to_euc(pctx);
	printf("%s\n",pctx->text);*/
	d2v_utf_to_euc(pctx);


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
	free(pctx->text);
	if( ret != GTT_STATUS_SUCCESS)
		return D2V_STATUS_ERROR_CLOSE;
	return D2V_STATUS_SUCCESS;
}

d2v_status_t d2v_free_vector(d2v_vector_t *doc_vec)
{
	free(doc_vec->element);
	return D2V_STATUS_SUCCESS;
}

