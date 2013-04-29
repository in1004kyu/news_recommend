#include "gtt.h"
#include<stdio.h>

void main(void)
{
	gtt_ctx_t gtt;
	gtt_status_t ret;
	
	// 1. Open and Load GTT in a fikle -> gtt
	ret = gtt_open( &gtt, "default.gtt" );
	
	if ( ret == GTT_STATUS_SUCCESS ) {
		// "hello", "world", "shit"
		gtt_tid_t TID = -1;
		
		// update term and count for "hello"
		// TID has the TID value for the term
//		gtt_update_term(&gtt, "test", &TID);
//		printf("Term : 'test' , TID : %d\n",TID);
		gtt_update_term(&gtt, "hello", &TID);
		printf("Term : 'hello' , TID : %d\n",TID);
		gtt_update_term(&gtt, "world", &TID);
		printf("Term : 'world' , TID : %d\n",TID);
		gtt_update_term(&gtt, "hello", &TID);
		printf("Term : 'hello' , TID : %d\n",TID);
		gtt_update_term(&gtt, "gtt", &TID);
		printf("Term : 'gtt' , TID : %d\n",TID);
		gtt_update_term(&gtt, "name", &TID);
		printf("Term : 'name' , TID : %d\n",TID);

		gtt_close(&gtt);
	}
}
