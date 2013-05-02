#ifndef __DUMMY_LIBS_H__
#define __DUMMY_LIBS_H__

/* ------ EVALD INPUT ------ */
typedef struct {
	char *userid;
	char *hash;
	char *filename_text;
	void *priv;
} evald_input_t;
	
typedef struct {
	int len;
	evald_input_t *entries;
} evald_input_table_t;

int evald_input_next(evald_input_table_t *ptable);
void evald_input_free( evald_input_table_t *ptable);
void evald_unlink_input_file( char *filename );

/* ------- D2V -----*/
struct d2v_element {
	int id; // term id
	int count; // count
};

struct d2v_vector{
	int length; // number of elements
	struct d2v_element* elements;
};
typedef struct d2v_vector d2v_vector_t;

/* Return:
 * 	0: Successful
 * 	<0: Error
 */
int d2v_get_document_vector( void *ctx, char *filename, int flag,  d2v_vector_t *vector);

void d2v_vector_free(d2v_vector_t *vector);

/* Return:
 * 	Negative: error
 * 	Positive: total number of terms in the pdvl for the specified user
 */
int pdvl_get( char *username, d2v_vector_t *pdvl, d2v_vector_t *filter );

float nve( d2v_vector_t *dv, d2v_vector_t *pdvl_subset, int pdvl_total_terms);

void dummy_libs_init(void);
#endif

