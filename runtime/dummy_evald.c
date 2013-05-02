#include <stdio.h>
#include <unistd.h>
#include "dummy_libs.h"

int main( int argc, char *argv[] ) 
{

    /*
     * loop: each input <user,file>
     *    file -> [D2V] -> doc_vector
     *    user -> [PDVL] -> user_pdvl
     *
     *    <doc_vector, user_pdvl> -> [NVE] -> score
     */
    int i;
    evald_input_table_t table;
    int num_input = 0;
    int result = 0;
    float score;
    d2v_vector_t vector;
    d2v_vector_t pdvl;
    //FILE *fpout;
    long total_len_vector = 0;


    // Internal Initialization
    dummy_libs_init();

    // Take the next input: table.len has the number of input entries
    num_input = evald_input_next(&table);

    fprintf(stderr, "evald: Input Data Ready\n" );

    // Prepare for output
    //fpout = fopen( "outQ/dummy.sct", "w" );
    //fprintf( fpout, "USERID, HASH, SCORE\n");
    for( i = 0; i < num_input; i++ ) {
            // PRINT: USERID, HASH
            //fprintf( fpout, "%s, %s", table.entries[i].userid, table.entries[i].hash );

            // D2V:  file content: filename_text -> vector
            result = d2v_get_document_vector( 0, table.entries[i].filename_text, 0, &vector );
            if ( result == 0 ) {
                // PDVL: userid -> pdvl, result: number of total terms in PDVL for the user
                result = pdvl_get( table.entries[i].userid, &pdvl, &vector );
                if ( result > 0 ) {
			total_len_vector += vector.length;

                        // vector and pdvl ar ready
                        // Measure the score: 'score'
                        score = nve( &vector, &pdvl, result );

                        d2v_vector_free( &vector );
                        d2v_vector_free( &pdvl );

                        // Output to SCT
                        //fprintf( fpout, ", %f\n",  score );

                }
            }
            evald_unlink_input_file( table.entries[i].filename_text );

            if (  ((i + 1) % (num_input / 10) ) == 0)  {
                fprintf( stderr, "evald: working...\n" );
            }
                            
    }

    //fclose(fpout);
#ifdef NVE_DO_CALC
    fprintf( stderr, "evald: multiplies:%ld divisions:%ld\n", total_len_vector, total_len_vector);
#endif
    

    if ( num_input > 0 ) {
        evald_input_free(&table);
    }
    return 0;
}

