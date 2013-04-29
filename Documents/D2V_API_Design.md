D2V API Design Document
=======================

Revision History
----------------
- Apr. 29th 2013, Design Document Format Re-organized


Module Repository Information
-----------------------------
- Directory: <src>/d2v
- Headers: d2v.h


Module Description
------------------
Example: <i>D2V를 통해서 생성된 Document Vector와 지정된 PDVL간의 유사도를 Naive Bayesian Algorithm으로 평가하고 그 결과 점수 (score)를 산출 해 낸다</i>

Data Types
----------
- struct XXX
    - 이 Data Type의 용도와 그 밖의 사용법에 대한 설명

struct XXX {
  int a;
  int b;
};



Functions
---------
<i>이 Module에서 제공하는 함수의 목록과 그에 대한 설명, 입력/출력 parameter, return value, 사용법, 기타 주의사항등을 설명</i>

- float func_xyz(param1, param2, param3)
    - <i>역할설명</i>
    - Input
        - param1 설명
        - param2 설명
        - param3 설명
    - Return
        - return 값의 의미 설명, 가능한 값의 범위 설명
    - Discussion
        - 추가적인 설명, 예:
        - We assume the following constraint due to performance and memory usage issues 
        - dvl.length <= approx. 10K 
        - pdvl.length <= approx. 10K (80KB) 

float nve(struct vector_list dvl, struct vector_list* pdvl_subset, int pdvl_full_length);
