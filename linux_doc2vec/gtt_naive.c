/*
 * Global Term ID Table Library
 */
#include"gtt.h"

/********************** gtt_naive.c **********************/
 
gtt_status_t gtt_open( gtt_ctx_t *pctx, char *filename ) 
{
	if( pctx->fd = open( filename, O_RDONLY) == -1 )
		return GTT_STATUS_ERROR_FILEOPEN;

	return GTT_STATUS_SUCCESS;
}
 
gtt_status_t gtt_close( gtt_ctx_t *pctx ) 
{
	close(pctx->fd);
	return GTT_STATUS_SUCCESS;
}

gtt_status_t gtt_add_new_ctx_to_term_table()
{}

gtt_status_t gtt_add_ctx_to_modify_table()
{}

gtt_status_t gtt_add_ctx_to_temp_table()
{}

gtt_status_t gtt_update_term_count(gtt_ctx_t *pctx, gtt_term_t doc_term, int count, gtt_tid_t *TID)
{
	char line[MAX_LINE];
	char m_line[MAX_LINE];
	gtt_term_t tid=0,m_tid;
	int freq;
	char gtt_term[MAX_LINE];
	int match_flag=0;

	while( fgets(line, MAX_LINE, pctx->fd) != NULL ){
		sscanf(line,"%d %u %s", &tid, &freq, gtt_term);
		if( strcmp( gtt_term, doc_term ) == 0 ){ 
			// match tid table term and document term
			gtt_add_ctx_to_modify_table(pctx,tid,freq+count,gtt_term);
			match_flag=1;
			break;
		}
	}
	// unmatch tid table term and document term, add new line
	if(match_flag != 1 )
		gtt_add_new_ctx_to_term_table(pctx,++tid,count,doc_term);
	fseek( pctx->fd, 0, SEEK_SET); // gtt file point reset
	fseek( pctx->m_fd, 0, SEEK_SET); // modify list file point reset

	while( fgets( line, MAX_LINE, pctx-m_fd) != NULL ){
		sscanf(line,"%d %u %s", &tid, &freq, gtt_term);
	}
	


	return GTT_STATUS_SUCCESS;
}
