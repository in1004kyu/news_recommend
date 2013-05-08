/*
 *  Document to Vector Library
 */

/********************** d2v.h **********************/


#include<stdio.h>
#include"../gttlib/gtt.h"

//#define MAX_ELEMENT_SIZE 512

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

/* 
 *  D2V document Vector Type
 */
typedef struct{
	int id;		//term id
	int count;	//count
}d2v_element_t;
/*
typedef struct{
	int length;	//number of elements
	d2v_element_t element[MAX_ELEMENT_SIZE];
}d2v_vector_t;
*/
typedef struct{
	int length;	//number of elements
	d2v_element_t *element;
}d2v_vector_t;

/* 
 * Context Type
 */
typedef struct {
	FILE *input_fp;
	gtt_ctx_t gtt_ctx;
} d2v_ctx_t;	


/*
 * API list
 */
d2v_status_t d2v_open(d2v_ctx_t *pctx, char *filename);
d2v_status_t d2v_get_document_vector(d2v_ctx_t *pctx, d2v_vector_t *doc_vec);
d2v_status_t d2v_close(d2v_ctx_t *pctx);
d2v_status_t d2v_free_vector(d2v_vector_t *doc_vec);
