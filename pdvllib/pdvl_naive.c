/*
 * Personalized Document Vector List Library
 */
#include"pdvl.h"
#include<stdio.h>
#include<stdlib.h>

#define MAX_LINE 32768
#define TEMPFILENAME "temptable.txt"

pdvl_status_t pdvl_update_count(pdvl_ctx_t *pctx, pdvl_tid_t tid, pdvl_count_t count);
/********************** pdvl_naive.c **********************/
 
pdvl_status_t pdvl_open( pdvl_ctx_t *pctx,char *filename) 
{
	pctx->pdvl_filename = filename;
	pctx->pdvl_fp	= fopen( filename, "r+");
	pctx->temp_fp	= fopen( TEMPFILENAME, "w+");
	pctx->swap_flag = 0;
	if( pctx->pdvl_fp == NULL || pctx->temp_fp == NULL )
		return PDVL_STATUS_FIAL;
	return PDVL_STATUS_SUCCESS;
}
 
pdvl_status_t pdvl_close( pdvl_ctx_t *pctx ) 
{
	/* pdvl_fp와 연결된 파일 이 최종 pdvl파일이 된다.*/
	fclose(pctx->pdvl_fp);
	fclose(pctx->temp_fp);
	if( pctx->swap_flag == 0){
		remove(TEMPFILENAME);
	}
	else{
		remove(pctx->pdvl_filename);
		rename(TEMPFILENAME ,pctx->pdvl_filename);
	}
	return PDVL_STATUS_SUCCESS;
}

pdvl_status_t pdvl_add_count(pdvl_ctx_t *pctx, pdvl_tid_t tid ,pdvl_count_t count)
{
	fprintf(pctx->temp_fp, "%3u  %u\n", tid,count);
	return PDVL_STATUS_SUCCESS;
}

pdvl_status_t pdvl_update_count(pdvl_ctx_t *pctx, pdvl_tid_t doc_tid, pdvl_count_t doc_count)
{
	char line[MAX_LINE];		// file buffer
	pdvl_tid_t tid=0;		// tid of pdvl
	pdvl_count_t count;		// count of pdvl
	char pdvl_term[MAX_LINE];	// term of pdvl
	int match_flag=0; 		// strcmp result 
	FILE *swap_fd;

	while( fgets(line, MAX_LINE, pctx->pdvl_fp ) != NULL ){
		sscanf(line,"%u %u", &tid, &count);
		if( match_flag == 0 &&  tid == doc_tid ){ 
			// match pdvltable tid and document tid
			pdvl_add_count(pctx,doc_tid,doc_count+count);
			match_flag=1;
		}
		else{
			pdvl_add_count(pctx,tid,count);
		}
	}

	if( match_flag == 0 ){
		pdvl_add_count(pctx, doc_tid, doc_count);
	}

	/* ********************
	   read pdvl file -> update temp file
	   change file pointer pdvl file -> temp file
	   ******************** */
	swap_fd = pctx->pdvl_fp;
	pctx->pdvl_fp = pctx->temp_fp;
	pctx->temp_fp = swap_fd;
	pctx->swap_flag = (pctx->swap_flag+1)%2;
	fseek( pctx->pdvl_fp, 0, SEEK_SET ); // pdvl file point reset
	fseek( pctx->temp_fp, 0, SEEK_SET ); // temp file point reset
	return PDVL_STATUS_SUCCESS;
}

pdvl_count_t pdvl_get_count(pdvl_ctx_t* pctx, pdvl_tid_t doc_tid)
{
	char line[MAX_LINE];		// file buffer
	pdvl_tid_t tid=0;		// tid of pdvl
	pdvl_count_t count;			// count of pdvl
	int match_flag=0; 		// strcmp result 

	while( fgets(line, MAX_LINE, pctx->pdvl_fp ) != NULL ){
		sscanf(line,"%u %u", &tid, &count);
		if( tid == doc_tid ){ 
			// match pdvltable term and document term
			fseek( pctx->pdvl_fp, 0, SEEK_SET ); // pdvl file point reset
			return count;
		}
	}
	fseek( pctx->pdvl_fp, 0, SEEK_SET ); // pdvl file point reset
	return -1; //NOT FOUND
}
