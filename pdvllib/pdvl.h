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
	char* pdvl_filename;
	FILE *pdvl_fp;
	FILE *temp_fp;
	int swap_flag;
	document_vector_t *pdv;
} pdvl_ctx_t;	

typedef unsigned int pdvl_tid_t;
typedef unsigned int pdvl_count_t;


/*
 * API list
 */
pdvl_status_t pdvl_open(pdvl_ctx_t *pctx,char *filename);
pdvl_status_t pdvl_update_tid_count(pdvl_ctx_t *pctx, pdvl_tid_t doc_tid, pdvl_count_t doc_count);
pdvl_status_t pdvl_close(pdvl_ctx_t *pctx);
pdvl_count_t pdvl_get_count(pdvl_ctx_t* pctx, pdvl_tid_t tid);

