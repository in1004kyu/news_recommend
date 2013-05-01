/*
 *  Document to Vector Library
 */

/********************** d2v.h **********************/


#include<stdio.h>
#include"document_vector.h"

/* API status
 * return values must be one of these
 */
typedef enum {
	D2V_STATUS_SUCCESS = 1,
	D2V_STATUS_ERROR_OPEN = -1,
	D2V_STATUS_ERROR_GET_DOC_VEC = -2,
	D2V_STATUS_ERROR_CLOSE = -3,
	/* add as implementation progresses */
} d2v_status_t;

/* D2V operation flag
 * set opertaion of get_document_vector function
 */
typedef enum {
	D2V_OPERATION_PDVL_UPDATE = 0,
	D2V_OPERATION_PDVL_NOUPDATE = 1,
} d2v_operation_flag;

/* 
 * Context Type
 */
typedef struct {
	FILE *d2v_fp;
	document_vector_t *dvp;
} d2v_ctx_t;	


/*
 * API list
 */
d2v_status_t d2v_open(d2v_ctx_t *pctx,char *username);
d2v_status_t d2v_get_document_vector(d2v_ctx_t *pctx, char *filename,d2v_operation_flag op_flag);
d2v_status_t d2v_close(d2v_ctx_t *pctx);


