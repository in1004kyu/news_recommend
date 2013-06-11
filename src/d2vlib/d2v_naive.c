/*
 *  Docuemnt to Vector Library
 */

/************************ d2v_naive.c ***********************/

#include"d2v.h"
#include "header/ham-ndx.h"
#include "../../include/iconv.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define MAX_LINE 32768
#define MAX_ELEMENT_SIZE 1024
#define MAX_COLS 32768





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


d2v_status_t d2v_iconv_euc_text(d2v_ctx_t *pctx)
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
	{
		int discard_ilseq = 1;
		iconvctl(cd, ICONV_SET_DISCARD_ILSEQ, (void *) &discard_ilseq );
	}

	if( (nRet = iconv(cd, (char ** __restrict__)&pszIn, &nIn, &pszOut, &nOut)) == (size_t)-1 )
	{
		printf("iconv:euc_kr to utf8 - fail to iconv()\n");
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

d2v_status_t d2v_iconv_utf_word(char *input_word, char *output_word)
{
	char szIn[MAX_LINE], szOut[MAX_LINE];
	char *pszIn = NULL, *pszOut = NULL;
	iconv_t cd = NULL;
	size_t  i = 0 ,nRet = 0, nIn = 0, nOut = 0;

	nIn = sprintf( szIn, "%s" , input_word );
	pszIn = szIn;
	pszOut = szOut;
	nOut = sizeof(szOut);
	memset(szOut, 0x00, sizeof(szOut));

	if( (cd = iconv_open("UTF-8","EUC-KR")) == (iconv_t)(-1))
	{
		printf("fail to iconv_open()\n");
		return D2V_STATUS_ERROR_OPEN;
	}
	{
		int discard_ilseq = 1;
		iconvctl(cd, ICONV_SET_DISCARD_ILSEQ, (void *) &discard_ilseq );
	}

	if( (nRet = iconv(cd, (char ** __restrict__)&pszIn, &nIn, &pszOut, &nOut)) == (size_t)-1 )
	{
		printf("iconv:utf8 to euc_kr - fail to iconv()\n");
		return D2V_STATUS_ERROR_OPEN;
	}
	nOut = pszOut - szOut;

	for( i = 0; i < nOut; i++)
	{
		output_word[i] = szOut[i];
	}

	return D2V_STATUS_SUCCESS;
}

d2v_status_t d2v_get_terms_text(d2v_ctx_t *pctx,d2v_vector_t *doc_vec)
{
	/*========================== KTL Variable ===========================*/
	HAM_TERMLIST Term[MAX_TERMS_DOC];	/* extracted terms */
	HAM_TERMMEMORY TM;	/* termtext.h: memories needed for term extraction */
	HAM_RUNMODE mode;
	int i,n=0,op1 = 0,op2 = 3, op3 = 1;
	char *optstr=NULL;
	gtt_tid_t TID;
	char iconv_word[1024];
	/*======================================================================*/

	if( open_HAM_index(&mode, optstr, "./hdic/KLT2000.ini")){
		return D2V_STATUS_ERROR_GET_DOC_VEC;
	}

	n = get_terms_text(pctx->text, Term, &TM, &mode, op1, op2, op3);

	//	put_terms(fpoutf, Term, n, TM.memTermString);

/*
	printf("------------------------------------------------------------------------\n");
	printf("Term\t\tFreq\n");
	printf("------------------------------------------------------------------------\n");
*/
	doc_vec->element = (d2v_element_t *)malloc(n*sizeof(d2v_element_t));
	for( i = 0; i < n; i++)
	{
		memset(iconv_word, 0x00, sizeof(iconv_word));
		d2v_iconv_utf_word((char *)TM.memTermString+Term[i].offset,iconv_word);
/*
		printf("%s\t\t%3d\n", 
				iconv_word,
				Term[i].tf);
*/
		gtt_update_term(&pctx->gtt_ctx,
				(gtt_term_t)iconv_word,
				&TID);
		doc_vec->element[doc_vec->length].id = TID;
		doc_vec->element[doc_vec->length].count = Term[i].tf;
		doc_vec->length++;

	}

//	printf("------------------------------------------------------------------------\n");

	close_HAM_index(&mode);

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

	d2v_iconv_euc_text(pctx);

	return D2V_STATUS_SUCCESS;
}

d2v_status_t d2v_get_document_vector(d2v_ctx_t *pctx, d2v_vector_t *doc_vec)
{
	d2v_get_terms_text(pctx,doc_vec);
	return D2V_STATUS_SUCCESS;
}

d2v_status_t d2v_close(d2v_ctx_t *pctx)
{
	gtt_status_t ret;
	ret = gtt_close(&pctx->gtt_ctx);
	if( ret != GTT_STATUS_SUCCESS)
		return D2V_STATUS_ERROR_CLOSE;
	fclose(pctx->input_fp);
	free(pctx->text);
	return D2V_STATUS_SUCCESS;
}

d2v_status_t d2v_free_vector(d2v_vector_t *doc_vec)
{
	doc_vec->length = 0;
	free(doc_vec->element);
	return D2V_STATUS_SUCCESS;
}

