/*
 * Global Term ID Table Library
 */
#include"gtt.h"
#include<stdio.h>
#include<stdlib.h>

#define MAX_LINE 32768

gtt_status_t gtt_add_term(gtt_ctx_t *pctx, gtt_tid_t tid, gtt_term_t term);

/********************** gtt_naive.c **********************/
 
gtt_status_t gtt_open( gtt_ctx_t *pctx,char *filename) 
{
	pctx->gtt_fp	= fopen( filename, "rw+");
	if( pctx->gtt_fp == NULL )
		return GTT_STATUS_ERROR_FILEOPEN;
	return GTT_STATUS_SUCCESS;
}

gtt_status_t gtt_close( gtt_ctx_t *pctx) 
{
	close(pctx->gtt_fp);
	return GTT_STATUS_SUCCESS;
}

gtt_status_t gtt_add_term(gtt_ctx_t *pctx, gtt_tid_t tid ,gtt_term_t term)
{
	fprintf(pctx->gtt_fp, "%3d  %s\n", tid,term);
	return GTT_STATUS_SUCCESS;
}

gtt_status_t gtt_update_term(gtt_ctx_t *pctx, gtt_term_t doc_term,gtt_tid_t *TID)
{
	char line[MAX_LINE];		// file buffer
	gtt_tid_t tid=0;		// tid of gtt
	char gtt_term[MAX_LINE];	// term of gtt
	int match_flag=0; 		// strcmp result 

	while( fgets(line, MAX_LINE, pctx->gtt_fp ) != NULL ){
		sscanf(line,"%d %s", &tid, gtt_term);
		if( strcmp( gtt_term, doc_term ) == 0 ){ 
			// match tid table term and document term
			*TID = tid;	
			match_flag=1;
			break;
		}
	}

	// unmatch tid table term and document term, add new line
	if(match_flag != 1 ){
		*TID = ++tid;
		gtt_add_term(pctx,tid,doc_term);
	}
	fseek( pctx->gtt_fp, 0, SEEK_SET ); // gtt file point reset

	return GTT_STATUS_SUCCESS;
}
