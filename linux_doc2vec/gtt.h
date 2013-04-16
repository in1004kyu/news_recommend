/*
 * Global Term ID Table Library
 */

/********************** gtt.h **********************/


#include<stdio.h>

/* API status
 * return values must be one of these
 */
typedef enum {
	GTT_STATUS_SUCCESS = 1,
	GTT_STATUS_ERROR_UNKNOWN = -1,
	GTT_STATUS_ERROR_FILEOPEN = -2,
	GTT_STATUS_ERROR_FILECLOSE = -3,
	GTT_STATUS_ERROR_FILEREMOVE = -4,
	GTT_STATUS_ERROR_FILERENAME = -5,
	/* add as implementation progresses */
} gtt_status_t;

/* 
 * Global Term Id table Context Type
 */
typedef struct {
	FILE *table_fd;
	FILE *temp_fd;
} gtt_ctx_t;	

typedef char* gtt_term_t;
typedef unsigned int gtt_tid_t;


/*
 * API list
 */
gtt_status_t gtt_open(gtt_ctx_t *pctx);
gtt_status_t gtt_update_term_count(gtt_ctx_t *pctx, gtt_term_t doc_term, int count);
gtt_status_t gtt_close(gtt_ctx_t *pctx);
gtt_status_t gtt_add_ctx_to_temp_table(gtt_ctx_t *pctx, gtt_tid_t tid, int count, gtt_term_t term);





/* 
 void gtt_sample(void)
 {
	gtt_ctx_t gtt;
	gtt_status_t ret;
	
	// 1. Open and Load GTT in a fikle -> gtt
	ret = gtt_open( &gtt, "default.gtt" );
	
	if ( ret == GTT_STATUS_SUCCESS ) {
		// "hello", "world", "shit"
		gtt_tid_t TID = -1;
		
		// update term and count for "hello"
		// TID has the TID value for the term
		gtt_update_term_count(&gtt, "hello", 3, &TID);
		// print: TID, 3
		gtt_update_term_count(&gtt, "world", 12, &TID);
		// print: TID, 12
		gtt_update_term_count(&gtt, "shit", 1, &TID);
		// print: TID, 1	

		gtt_close(&gtt);
	}
 }
*/
