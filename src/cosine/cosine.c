#include "cosine.h"
#include <math.h>
#define DIVIDEND 0 // 분자
#define DIVISOR 1  // 분모
#define NOTAVAILABLE 0
#define AVAILABLE 1

// 출현빈도만 나온것이기 때문에 비교를 위해선 P(class)를 곱해줘서 비교해줘야한다.
// dvl, pdvl, 총길이
float cosineSim(d2v_vector_t dv, d2v_vector_t pdvl_subset){


	int dividend = 0;
	double divisor = 0;
	
	int d2vvisor = 0;
	int pdvlvisor = 0;

	double d2vv;
	double pdv;

	float score;
	int i;
	for(i = 0; i < dv.length; i++){
		dividend += (dv.element[i].count * pdvl_subset.element[i].count);
		d2vvisor += (dv.element[i].count * dv.element[i].count);
		pdvlvisor += (pdvl_subset.element[i].count * pdvl_subset.element[i].count);
	}

	d2vv = sqrt((double)d2vvisor);
	pdv = sqrt((double)pdvlvisor);
	
	divisor = d2vv*pdv;

 	 score = (float)((double)dividend / divisor);

	return score;		
}

