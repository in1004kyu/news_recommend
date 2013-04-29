/*
 * Personalized Document Vector List Library
 */

/********************** pdvl.h **********************/


#include<stdio.h>
#include"document_vector.h"

/* API status
 * return values must be one of these
 */
typedef enum {
	PDVL_STATUS_SUCCESS = 1,
	PDVL_STATUS_FIAL = 0,
	/* add as implementation progresses */
} pdvl_status_t;

/* 
 * Perconalized Document Vector List Context Type
 */
typedef struct {
	FILE *pdvl_fd;
	FILE *dv_fd;
	FILE *temp_fd;
	char *pdvl_filename;
	int swap_flag;
	document_vector_t *pdv;
} pdvl_ctx_t;	

typedef unsigned int pdvl_tid_t;
typedef unsigned int pdvl_count_t;


/*
 * API list
 */
pdvl_status_t pdvl_open(pdvl_ctx_t *pctx,char *filename);
pdvl_status_t pdvl_update_tid_count(pdvl_ctx_t *pctx, pdvl_tid_t dv_tid, pdvl_count_t dv_count);
pdvl_status_t pdvl_close(pdvl_ctx_t *pctx);
pdvl_status_t pdvl_add_ctx_to_pdvl_table(pdvl_ctx_t *pctx, pdvl_tid_t tid, pdvl_count_t count);
pdvl_tid_t pdvl_get_count(pdvl_ctx_t* pctx, pdvl_tid_t tid);





/* 
 void pdvl_sample(void)
 {
	pdvl_ctx_t pdvl;
	pdvl_status_t ret;
	
	// 1. Open and Load GTT in a fikle -> pdvl
	ret = pdvl_open( &pdvl, "default.pdvl" );
	
	if ( ret == GTT_STATUS_SUCCESS ) {
		// "hello", "world", "shit"
		pdvl_tid_t TID = -1;
		
		// update term and count for "hello"
		// TID has the TID value for the term
		pdvl_update_term_count(&pdvl, "hello", 3, &TID);
		// print: TID, 3
		pdvl_update_term_count(&pdvl, "world", 12, &TID);
		// print: TID, 12
		pdvl_update_term_count(&pdvl, "shit", 1, &TID);
		// print: TID, 1	

		pdvl_close(&pdvl);
	}
 }
*/
