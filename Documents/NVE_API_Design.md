// To be defined by D2V Module (형준)
// struct vector and vector_list
// Suggested names: struct d2v_vector, struct d2v_vector_list

struct vector {
	int id;
	int count;
};
// D2V
struct vector_list{
	int length;
	struct vector* vectors;
};

/*
// Performs Naive Bayesian Calculation of input 'dvl', by measuring it's similarity with input 'pdvl' and then returns the resulting score 
// Input 
// @param dvl Input Document Vector 
// @param pdvl_subset Input PDVL, Subset of the entire PDVL collected terms only those in the input 'dvl'
// @param pdvl_full_length The full length of PDVL, before subset extraction. Used as input parameter to Naive Bayesian Calculation (denominators) 
// 
// @return score Measured similarity 
// Discussion 
// We assume the following constraint due to performance and memory usage issues 
// dvl.length <= approx. 10K 
// pdvl.length <= approx. 10K (80KB) 
/* 

float nve(struct vector_list dvl, struct vector_list* pdvl_subset, int pdvl_full_length);
