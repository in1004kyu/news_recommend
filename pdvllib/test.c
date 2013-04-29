#include "pdvl.h"
#include<stdio.h>

void main(void)
{
	pdvl_ctx_t pdvl;
	pdvl_status_t ret;
	int i;
	pdvl_count_t getcount;
	
	// 1. Open and Load PDVL in a fikle -> pdvl
	ret = pdvl_open( &pdvl, "default.pdvl" );
	
	if ( ret == PDVL_STATUS_SUCCESS ) {
		// "hello", "world", "shit"
		pdvl_tid_t TID = -1;
		
		// update tid and count
		for( i = 1; i < 4; i++){
			pdvl_update_count( &pdvl, i,(10-i) );
			printf("Update > TID : %d , Count : %d\n",i,(10-i));
		}
		for( i = 1; i < 5; i++){
			pdvl_update_count( &pdvl, i,(5-i) );
			printf("Update > TID : %d , Count : %d\n",i,(5-i));
		}
		for( i = 3; i > 0; i--){
	        	getcount = pdvl_get_count( &pdvl ,i );
			printf("Get count : Tid = %d >> count = %d \n",i ,getcount);
		}
		pdvl_close(&pdvl);
	}
}

