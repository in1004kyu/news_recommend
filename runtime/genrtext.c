#include <stdio.h>
#include <stdlib.h>
#include "dummy_libs.h"

/*
    int len_text;
        char *data;
	    char path[LEN_FILENAME + 4 + 1];

	        sprintf( path, "inQ/%s", filename );
		    FILE *fp = fopen( path, "w" );
		        if ( fp ) {
			        len_text = dummy_libs_random( 1000, 5000 );
				        evald_gen_random_text( fp, len_text );
        fclose(fp);
	    }
*/
int main( int argc, char *argv[] ) 
{
	int len = 5000;
	if ( argc > 1 ) {
		len = atoi( argv[1] );
		if ( len <= 0 ) {
			len = 5000;
			fprintf( stderr, "usage: genrtext [<num_chars=5000>]\n" );
		}
	}

	dummy_libs_init();
	evald_gen_random_text( stdout, len );
	fprintf( stdout, "\n" );
	return 0;
}

