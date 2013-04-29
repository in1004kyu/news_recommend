/*
 * Personalized Document Vector List Library
 */
#include"pdvl.h"
#include<stdio.h>
#include<stdlib.h>

#define MAX_LINE 32768
#define TEMPFILENAME "temptable.txt"

/********************** pdvl_naive.c **********************/
 
pdvl_status_t pdvl_open( pdvl_ctx_t *pctx,char *filename) 
{
	pctx->pdvl_filename = filename;
	pctx->pdvl_fd	= fopen( filename, "w+");
	pctx->temp_fd	= fopen( TEMPFILENAME, "w+");
	pctx->swap_flag = 0;
	if( pctx->pdvl_fd == NULL || pctx->temp_fd == NULL )
		return PDVL_STATUS_FIAL;
	return PDVL_STATUS_SUCCESS;
}
 
pdvl_status_t pdvl_close( pdvl_ctx_t *pctx ) 
{
	close(pctx->pdvl_fd);
	close(pctx->temp_fd);
	if( pctx->swap_flag == 0){
		remove(TEMPFILENAME);
	}
	else{
		remove(pctx->pdvl_filename);
		rename(TEMPFILENAME ,pctx->pdvl_filename);
	}
	return PDVL_STATUS_SUCCESS;
}

pdvl_status_t pdvl_add_ctx_to_pdvl_table(pdvl_ctx_t *pctx, pdvl_tid_t tid ,pdvl_count_t count)
{
	fprintf(pctx->temp_fd, "%3u  %u\n", tid,count);
	return PDVL_STATUS_SUCCESS;
}

pdvl_status_t pdvl_update_tid_count(pdvl_ctx_t *pctx, pdvl_tid_t dv_tid, pdvl_count_t dv_count)
{
	char line[MAX_LINE];		// file buffer
	pdvl_tid_t tid=0;		// tid of pdvl
	pdvl_count_t count;		// count of pdvl
	char pdvl_term[MAX_LINE];	// term of pdvl
	int match_flag=0; 		// strcmp result 
	FILE *swap_fd;

	while( fgets(line, MAX_LINE, pctx->pdvl_fd ) != NULL ){
		sscanf(line,"%u %u", &tid, &count);
		if( match_flag == 0 &&  tid == dv_tid ){ 
			// match pdvltable tid and document tid
			pdvl_add_ctx_to_pdvl_table(pctx,dv_tid,dv_count+count);
			match_flag=1;
		}
		else{
			pdvl_add_ctx_to_pdvl_table(pctx,tid,count);
		}
	}

	swap_fd = pctx->pdvl_fd;
	pctx->temp_fd = pctx->pdvl_fd;
	pctx->pdvl_fd = swap_fd;
	pctx->swap_flag = (pctx->swap_flag+1)%2;
	fseek( pctx->pdvl_fd, 0, SEEK_SET ); // pdvl file point reset
	fseek( pctx->temp_fd, 0, SEEK_SET ); // temp file point reset
	return PDVL_STATUS_SUCCESS;
}

pdvl_count_t pdvl_get_count(pdvl_ctx_t* pctx, pdvl_tid_t dv_tid)
{
	char line[MAX_LINE];		// file buffer
	pdvl_tid_t tid=0;		// tid of pdvl
	pdvl_count_t count;			// count of pdvl
	int match_flag=0; 		// strcmp result 

	while( fgets(line, MAX_LINE, pctx->pdvl_fd ) != NULL ){
		sscanf(line,"%u %u", &tid, &count);
		if( tid == dv_tid ){ 
			// match pdvltable term and document term
			fseek( pctx->pdvl_fd, 0, SEEK_SET ); // pdvl file point reset
			return count;
		}
	}
	fseek( pctx->pdvl_fd, 0, SEEK_SET ); // pdvl file point reset
	return -1; //NOT FOUND
}
