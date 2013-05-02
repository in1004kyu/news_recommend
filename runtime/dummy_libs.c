#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "dummy_libs.h"

#define LEN_USERID	12	// 999,999,999,999
#define LEN_HASH		21  // 168bit
#define LEN_EXT_INPROC	6
#define LEN_FILENAME		(LEN_USERID + LEN_HASH + LEN_EXT_INPROC + 1)
#define SIZE_EVALID_INPUT_ENTRY_HEAP	( LEN_USERID + 1 + LEN_HASH + 1 + LEN_FILENAME + 1)

static long dummy_libs_random(int min, int max);
static void dummy_libs_random_string(char *dst, int len);
static void dummy_libs_random_hex(char *dst, int len);
static void dummy_libs_random_text(char *dst, int len);

void evald_write_random_text( char *filename )
{
	int len_text;
	char *data;
	char path[LEN_FILENAME + 4 + 1];

	sprintf( path, "inQ/%s", filename );
	FILE *fp = fopen( path, "w" );
	if ( fp ) {
		len_text = dummy_libs_random( 1000, 5000 );
		data = (char *) malloc( len_text + 1 );
		dummy_libs_random_text(data, len_text );
		data[len_text] = 0;

		fwrite( data, len_text, 1, fp );
		fclose(fp);
		free(data);
	}
}

/* ------ EVALD INPUT ------ */
int evald_input_next(evald_input_table_t *ptable)
{
	int ret = 0;
	// random number of input
	// random userid
	// random hash
	// filename: userid-hash.inproc
	int num_input;

	//num_input = dummy_libs_random( 10000, 100000 ); // 100 ~ 100 input entries
	num_input = 10000;

	evald_input_t *entries = (evald_input_t *) malloc( (sizeof(evald_input_t ) * num_input ));
	void *heap = malloc( (SIZE_EVALID_INPUT_ENTRY_HEAP) * num_input );
	if ( heap == NULL ) {
		ret = -1;	// memory
	}
	fprintf(stderr, "evald: ALLOC entries:%p, heap:%p\n", entries, heap );
	
	if ( entries ) {
		int i;
		unsigned char *p = (unsigned char *) heap;
		evald_input_t *pentry;
		fprintf(stderr, "evald:num_input:%d\n", num_input );
		for( i = 0; i < num_input; i++ ) {
			pentry = &entries[i];
			pentry->priv = p;

			pentry->userid = (char *)p;
			pentry->hash = (char *) (p + LEN_USERID + 1);
			pentry->filename_text = (char *) (p + LEN_USERID + 1 + LEN_HASH + 1);
			p += SIZE_EVALID_INPUT_ENTRY_HEAP;


			dummy_libs_random_hex( pentry->userid, LEN_USERID );
			pentry->userid[LEN_USERID] = 0;
			dummy_libs_random_hex( pentry->hash, LEN_HASH );
			pentry->hash[LEN_HASH] = 0;
			sprintf( pentry->filename_text, "%s-%s.inproc", pentry->userid, pentry->hash );
			pentry->filename_text[LEN_FILENAME] = 0;
			// fprintf(stderr, "evald: %s, %s, %s\n", pentry->userid, pentry->hash, pentry->filename_text );
			//evald_write_random_text( pentry->filename_text );
		}
		ret = num_input;
		ptable->entries = entries;
	}

	return ret;
}

void evald_input_free( evald_input_table_t *ptable)
{

	fprintf(stderr, "evald: FREE entries:%p, heap:%p\n", ptable->entries, ptable->entries[0].priv );
	free( ptable->entries[0].priv );
	free( ptable->entries );
	ptable->entries = 0;
}

void evald_unlink_input_file( char *filename )
{
	char path[LEN_FILENAME + 4 + 1];
	sprintf( path, "inQ/%s", filename );
	//unlink(path);
}

struct d2v_element *d2v_element_alloc( int num )
{
	struct d2v_element * result = (struct d2v_element *) malloc( sizeof(struct d2v_element) * num );
	return result;
}

void d2v_element_free( struct d2v_element *p ) {
	free(p);
}

void d2v_vector_free( d2v_vector_t *vector ) {
	d2v_element_free(vector->elements);
	vector->elements = 0;
	vector->length = 0;
}

/* ------- D2V -----*/
int d2v_get_document_vector( void *ctx, char *filename, int flag,  d2v_vector_t *vector)
{
	int len_vector;
	int i;

	len_vector = dummy_libs_random( 20000, 30000 );
	vector->elements = d2v_element_alloc( len_vector );
	vector->length = len_vector;

	for( i = 0; i < len_vector; i++ ) {
		vector->elements[i].id = (i + 1);
		vector->elements[i].count = dummy_libs_random( 1, 10 );
	}
	return 0;
}


/* Return:
 * 	Negative: error
 * 	Positive: total number of terms in the pdvl for the specified user
 */
int pdvl_get( char *username, d2v_vector_t *pdvl, d2v_vector_t *filter )
{
	int len_pdvl_items;
	int i;
	int total_pdvl_items;

	len_pdvl_items = filter->length;
	pdvl->elements = d2v_element_alloc( len_pdvl_items );
	pdvl->length = len_pdvl_items;
	for( i = 0; i < len_pdvl_items; i++ ) {
		pdvl->elements[i].id = filter->elements[i].id;
		pdvl->elements[i].count = dummy_libs_random( 1, 100 );
	}
	
	total_pdvl_items = dummy_libs_random( 300, 3000 );
	if ( total_pdvl_items < len_pdvl_items ) {
			total_pdvl_items = len_pdvl_items + 500;
	}
	return total_pdvl_items;
}

float nve( d2v_vector_t *dv, d2v_vector_t *pdvl_subset, int pdvl_total_terms)
{
	//fprintf( stderr, "nve: dv[%d], pdvl[%d], pdvl_total:%d\n", dv->length, pdvl_subset->length, pdvl_total_terms );
	float score = 1;
#ifdef NVE_DO_CALC
	int i;
	for( i = 0; i < dv->length; i++ ) {
		score *= dv->elements[i].count / pdvl_subset->elements[i].count;
	}
#else
	// random
	score = dummy_libs_random( 100, 10000 );
	score /= 1000;
#endif

	return score;
}


void dummy_libs_init(void)
{
	srandom(time(0));
}

long dummy_libs_random(int min, int max)
{
	long r = random() % (max + 1 - min);
	return r + min;
}

void dummy_libs_random_hex( char *dst, int len)
{
	int i;
	for( i = 0; i < len; i++ ) {
		dst[i] = (char) dummy_libs_random( 0, 15 );
		if ( dst[i] > 9 ) {
			dst[i] += 'A' - 10;
		} else {
			dst[i] += '0';
		}
	}
}

void dummy_libs_random_string( char *dst, int len)
{
	int i;
	for( i = 0; i < len; i++ ) {
		dst[i] = (char) dummy_libs_random( 'a', 'z' );
	}
}

void dummy_libs_random_text( char *dst, int len ) 
{
	int len_word;
	int len_word_max;
	int len_left = len;
	char *p = dst;


	while( len_left > 0 ) {
		len_word_max = ( len_left > 10 ? 10 : len_left );
		len_word = dummy_libs_random( 1, len_word_max );
		dummy_libs_random_string( p, len_word );
		p[len_word] = ' ';
		p += len_word + 1;
		len_left -= len_word + 1;
	}
}
