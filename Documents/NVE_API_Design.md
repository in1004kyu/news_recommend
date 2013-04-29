NVE API Design Document
=======================

Revision History
----------------
- Apr. 17th 2013, Initial Draft
- Apr. 29th 2013, Design Document Format Re-organized
- Apr. 29th 2013, modification source location info


Module Repository Information
-----------------------------
- Directory: <src>/nve.c
- Headers: nve.h


Module Description
------------------
D2V를 통해서 생성된 Document Vector와 지정된 PDVL간의 유사도를 Naive Bayesian Algorithm으로 평가하고 그 결과 점수 (score)를 산출 해 낸다

Data Types
----------
임시로 d2v_element와 d2v_vector type을 정의해서 사용하고 있음. D2V API Desgin이 완료되면 그에 따른 data type을 사용하게 되고, 아래에 정의된 data type은 삭제된다.

- struct d2v_element
    - 정확한 이름은 D2V API Design Document서 결정된 내용을 사용하게 된다
    - 즉, d2v.h를 #include 하여 사용한다
<pre>
struct d2v_element {
	int id;          // term id
	int count;       // count
};
</pre>
- struct d2v_vector
<pre>
struct d2v_vector{
	int length;      // number of elements
	struct d2v_element* elements;
};
</pre>
Functions
---------

- float nve(dv, pdvl_subset, pdvl_full_length)
    - Performs Naive Bayesian Calculation of input 'dvl', by measuring it's similarity with input 'pdvl' and then returns the resulting score 
    - Input
        - dv Input Document Vector
        - pdvl_subset Input PDVL, Subset of the entire PDVL collected terms only those in the input 'dvl'
        - pdvl_full_length The full length of PDVL, before subset extraction. Used as input parameter to Naive Bayesian Calculation (denominators) 
    - Return
        - score Measured similarity
    - Discussion
        - We assume the following constraint due to performance and memory usage issues 
        - dv.length <= approx. 10K 
        - pdvl.length <= approx. 10K (80KB) 
<pre>
float nve(struct vector_list dvl, struct vector_list* pdvl_subset, int pdvl_full_length);
</pre>
