/*
 * Global Term ID Table Library
 */
#include"gtt.h"
#include<stdio.h>
#include<stdlib.h>

#define MAX_LINE 32768

/********************** gtt_naive.c **********************/
 
gtt_status_t gtt_open( gtt_ctx_t *pctx,char *filename) 
{
	pctx->gtt_fd	= fopen( filename, "w+");
	if( pctx->gtt_fd )
		return GTT_STATUS_ERROR_FILEOPEN;
	return GTT_STATUS_SUCCESS;
}
 
gtt_status_t gtt_close( gtt_ctx_t *pctx) 
{
	close(pctx->gtt_fd);
	return GTT_STATUS_SUCCESS;
}

gtt_status_t gtt_add_ctx_to_gtt_table(gtt_ctx_t *pctx, gtt_tid_t tid ,gtt_term_t term)
{
	fprintf(pctx->gtt_fd, "%3d  %s\n", tid,term);
	return GTT_STATUS_SUCCESS;
}

gtt_status_t gtt_update_term_count(gtt_ctx_t *pctx, gtt_term_t doc_term,gtt_tid_t *TID)
{
	char line[MAX_LINE];		// file buffer
	gtt_tid_t tid=0;		// tid of gtt
	char gtt_term[MAX_LINE];	// term of gtt
	int match_flag=0; 		// strcmp result 

	while( fgets(line, MAX_LINE, pctx->gtt_fd ) != NULL ){
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
		gtt_add_ctx_to_gtt_table(pctx,tid,doc_term);
	}
	fseek( pctx->gtt_fd, 0, SEEK_SET ); // gtt file point reset

	return GTT_STATUS_SUCCESS;
}

/*gtt_tid_t gtt_get_tid(gtt_ctx_t* pctx, gtt_term_t term)
{
	char line[MAX_LINE];		// file buffer
	gtt_tid_t tid=0;		// tid of gtt
	int freq;			// frequency or count of gtt
	char gtt_term[MAX_LINE];	// term of gtt
	int match_flag=0; 		// strcmp result 
	FILE *swap_temp;

	while( fgets(line, MAX_LINE, pctx->table_fd ) != NULL ){
		sscanf(line,"%d %u %s", &tid, &freq, gtt_term);
		if( strcmp( gtt_term, term ) == 0 ){ 
			// match tid table term and document term
			return tid;
		}
	}
	fseek( pctx->table_fd, 0, SEEK_SET ); // gtt file point reset
	return -1 //NOT FOUND
}*/
