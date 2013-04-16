/*
 * Global Term ID Table Library
 */
#include"gtt.h"
#include<stdio.h>
#include<stdlib.h>

#define MAX_LINE 32768
#define TABLEFILE "termtable.txt"
#define TEMPFILE "temptable.txt"

/********************** gtt_naive.c **********************/
 
gtt_status_t gtt_open( gtt_ctx_t *pctx) 
{
	pctx->table_fd	= fopen( TABLEFILE , "w+");
	pctx->temp_fd	= fopen( TEMPFILE , "w+");

	if( pctx->table_fd == NULL | pctx->temp_fd == NULL )
		return GTT_STATUS_ERROR_FILEOPEN;

	return GTT_STATUS_SUCCESS;
}
 
gtt_status_t gtt_close( gtt_ctx_t *pctx) 
{
	int case_number;
	int result;

	if( pctx->table_fd < pctx->temp_fd )
		case_number = 1;  // table_fd is new table
	else
		case_number = 2;  // temp_fd is new table

	close(pctx->table_fd);
	close(pctx->temp_fd);

	if( case_number == 1 ){ 
		if( remove( TEMPFILE ) != 0 )
			return GTT_STATUS_ERROR_FILEREMOVE;
	}
	else{ // tempfile is new table
		if( remove( TABLEFILE ) != 0 )
			return GTT_STATUS_ERROR_FILEREMOVE;
	  	result= rename( TEMPFILE , TABLEFILE );
		if ( result != 0 )
			return GTT_STATUS_ERROR_FILERENAME;
	}

	return GTT_STATUS_SUCCESS;
}

gtt_status_t gtt_add_ctx_to_temp_table(gtt_ctx_t *pctx, gtt_tid_t tid , int count, gtt_term_t term)
{
	fprintf(pctx->temp_fd, "%3d  %5u  %s\n", tid,count,term);
	return GTT_STATUS_SUCCESS;
}

gtt_status_t gtt_update_term_count(gtt_ctx_t *pctx, gtt_term_t doc_term, int count)
{
	char line[MAX_LINE];		// file buffer
	gtt_tid_t tid=0;		// tid of gtt
	int freq;			// frequency or count of gtt
	char gtt_term[MAX_LINE];	// term of gtt
	int match_flag=0; 		// strcmp result 
	FILE *swap_temp;

	while( fgets(line, MAX_LINE, pctx->table_fd ) != NULL ){
		sscanf(line,"%d %u %s", &tid, &freq, gtt_term);
		if( strcmp( gtt_term, doc_term ) == 0 ){ 
			// match tid table term and document term
			gtt_add_ctx_to_temp_table(pctx,tid,freq+count,gtt_term);
			match_flag=1;
			break;
		}
		else
			gtt_add_ctx_to_temp_table(pctx,tid,freq,gtt_term);
	}

	// unmatch tid table term and document term, add new line
	if(match_flag != 1 ){
		gtt_add_ctx_to_temp_table(pctx,++tid,count,doc_term);
	}

	swap_temp = pctx->table_fd;
	pctx->table_fd = pctx->temp_fd;
	pctx->temp_fd = swap_temp;

	fseek( pctx->table_fd, 0, SEEK_SET ); // gtt file point reset
	fseek( pctx->temp_fd,  0, SEEK_SET ); // temp file point reset

	return GTT_STATUS_SUCCESS;
}

gtt_tid_t gtt_get_tid(gtt_ctx_t* pctx, gtt_term_t term)
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
}
