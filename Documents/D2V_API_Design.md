D2V API Design Document
=======================

Revision History
----------------
- Apr. 29th 2013, Design Document Format Re-organized
- May. 1st 2013, Design Document to Vector API


Module Repository Information
-----------------------------
- Directory: &lt;src&gt;/d2v
- Headers: d2v.h


Module Description
------------------
<i>Plane text를 입력값으로 넣는다. 해당 문서에 대해 형태소 분석기를 통해 단어와 카운터 값을 추출하고 단어에 대해서는 Term ID를 생성하여 표현하여, TID와 카운터의 벡터값을 돌려준다. PDVL을 업데이트하면서 벡터값을 추출하거나, 업데이트 없이 벡터값을 추출한다.</i>

Data Types
----------
- d2v_ctx_t
	- D2V API를 사용 시 필요한 데이터 집합
	- D2V에 입력되는 데이터의 유져 정보
	- 반환되는 벡터값에 대한 포인터

<pre>
typedef struct{
	char *username;
	document_vector_t *dvp;
}d2v_ctx_t;
</pre>

- d2v_status_t
	- API 리턴 타입,  각 API 기능의 수행 여부를 리턴

<pre>
typedef enum {
	D2V_STATUS_SUCCESS = 1,
	D2V_STATUS_ERROR_OPEN = -1,
	D2V_STATUS_ERROR_GET_DOC_VEC = -2,
	D2V_STATUS_ERROR_CLOSE = -3,
}d2v_status_t;
</pre>

- d2v_operation_flag
	- get_document_vector 함수의 PDVL 업데이트 여부를 판단하 는 플래그

<pre>
typedef enum{
	D2V_OPERATION_PDVL_UPDATE = 0,
	D2V_OPERATION_PDVL_NOUPDATE = 1,
} d2v_operation_flag;
</pre>


Functions
---------

1. open : D2V library 를사용 할유져정보 를 저장,  각필요라이브러 리 사용준비
2. get_document_vector : 입력 문서를 넣었을 때, < TID, count > 형태의 벡터값을 반환
3. close : D2V library를 사용 종료를 위해 close

- <code>d2v_status_t d2v_open(d2v_ctx_t *pctx,char *username)</code>
    - <i>API 사용을 위한 유져 정보를 저장하고,각 라이브러리 사용 준비</i>
    - Input
	- d2v_ctx_t *pctx : 라이브러리에서 공유 할 데이터 저장한 d2v 데이터 타입에 대한 포인터 (유저정보,반환문서벡터)
	- char *username : 저장 될 유져 정보
    - Return
    	- d2v status 타입에 정의 된 내용 반환
    - Discussion
    	-  예:
	- d2v_ctx_t d2v_ctx;
	- d2v_open(&d2v_ctx,"username")

- <code>float func_xyz(param1, param2, param3)</code>
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

