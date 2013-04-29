/*
 * Global Term ID Table Library
 */

/********************** gtt.h **********************/


#include<stdio.h>
#include"document_vector.h"

/* API status
 * return values must be one of these
 */
typedef enum {
	GTT_STATUS_SUCCESS = 1,
	GTT_STATUS_ERROR_UNKNOWN = -1,
	GTT_STATUS_ERROR_FILEOPEN = -2,
	/* add as implementation progresses */
} gtt_status_t;

/* 
 * Global Term Id table Context Type
 */
typedef struct {
	FILE *gtt_fd;
} gtt_ctx_t;	

typedef char* gtt_term_t;
typedef unsigned int gtt_tid_t;


/*
 * API list
 */
gtt_status_t gtt_open(gtt_ctx_t *pctx,char *filename);
gtt_status_t gtt_update_term(gtt_ctx_t *pctx, gtt_term_t doc_term, gtt_tid_t *TID);
gtt_status_t gtt_close(gtt_ctx_t *pctx);
gtt_status_t gtt_add_ctx_to_gtt_table(gtt_ctx_t *pctx, gtt_tid_t tid, gtt_term_t term);
//gtt_tid_t gtt_get_tid(gtt_ctx_t* pctx, gtt_term_t term);




