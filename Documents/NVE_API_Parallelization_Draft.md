<pre>
nve_handle = nve_parallel( dv[], pdvl[], pdvl_cnt[], int num_dv, nvep_callback);

void nvep_callback( int num_dv, dv[], pdvl[], int status, float score[] ) {

  if ( status == ERROR ) {
	} else if ( num_dv == global_num_dv ) {
	} 
}


float nve( dv, pdvl, count ) {

	float score = NaN;
	dvl[0] = dv;
	pdvll[0] = pdvl;
	nve_handle = nve_parallel( dvl[], pdvll[], 1, 0 ) ;
	nve_status_t status = nve_get_lasterror();
	if ( status == NVE_SUCCEED ) {

		score = nve_get_score( nve_handle );
	}
	
	return score;
}

test() {
	float score = nve( ...);
	if ( nve_get_lasterror() == NVE_SUCCEED ) {
		printf( "score: %f\n", score" );
	} else {
		printf( "error: %d", nve_get_lasterror() );
	}
}


1. Sequential
nve_handle = nve_parallel( dv[], pdvl[], pdvl_cnt[], int num_dv, nvep_callback)
{
	float scores[]
	for ( i = 0; i &lt; num_dv; i++ ) {
		scores[i] = __nve(dv[i], pdvl[i], pdvl_cnt[i] );
	}
	nve_set_scores( handle, scores );
	nvep_callback( num_dv, dv[], pdvl[], NVE_SUCCEED, scores[] );
	return handle;
}


2. Parallelized

nve_handle = nve_parallel( dv[], pdvl[], pdvl_cnt[], int num_dv, nvep_callback)
{
	float scores[]
	for ( i = 0; i &lt; num_dv; i++ ) {
		scores[i] = __cuda_nve(dv[i], pdvl[i], pdvl_cnt[i] );
	}
	//nvep_callback( num_dv, dv[], pdvl[], NVE_SUCCEED, scores[] );
	return handle;
}
</pre>
