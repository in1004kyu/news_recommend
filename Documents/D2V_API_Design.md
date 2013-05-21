D2V API Design Document
=======================

Revision History
----------------
- Apr. 29th 2013, Design Document Format Re-organized
- May. 1st 2013, Design Document to Vector API


Module Repository Information
-----------------------------
- Directory: src/d2v
- Headers: d2v.h


Module Description
------------------
<i>Plane text를 입력값으로 넣는다. 해당 문서에 대해 형태소 분석기를 통해 단어와 카운터 값을 추출하고 단어에 대해서는 Term ID를 생성하여, <TID,Count> 의 벡터값을 돌려준다.</i>

Data Types
----------
- d2v_ctx_t
	- D2V API를 사용 시 필요한 데이터 집합
	- Input 파일 포인터
	- Input text 저장소
	- Input text 저장할 메모리 할당 크기
	- D2V 에서 사용할 gtt library 를 위한 gtt_ctx_t 변수

<pre>
typedef struct {
	FILE *input_fp;
	unsigned char *text;
	int malloc_size;
	gtt_ctx_t gtt_ctx;
} d2v_ctx_t;
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


- d2v_vector_t 
	- Document Vector 타입
	- 한 문서에서의 단어(TID) , 빈도를 벡터 형태의 데이터로 저장
	- 단어의 갯수, 각 단어(TID)와 빈도를 저장한 d2v_element_t의 배열로 구성
	- d2v_element_t 은 TID 와 COUNT를 저장
	- MAX_ELEMENT_SIZE 는 저장가능한 총 element 수를 정의

<code>#define MAX_ELEMENT_SIZE 512</code>

<pre>
typedef struct{
	int id;
	int count;
}d2v_element_t;

typedef struct{
	int length;
	d2v_element_t element[MAX_ELEMENT_SIZE];
}d2v_vector_t;
</pre>

Functions
---------

1. open : D2V library에서 사용할 GTT 라이브러리 사용 준비
2. get_document_vector : 입력 문서를 넣었을 때, < TID, count > 형태의 벡터값을 생성
3. close : D2V library를 사용 종료를 위해 close
4. free_vector : 생성 된 Document Vector를 해제

- <code>d2v_status_t d2v_open(d2v_ctx_t *pctx, char *filename)</code>
    - <i>API 사용을 위한 GTT 라이브러리 사용 준비 pctx->text 에 input text 내용을 저장해 놓는다.</i>
    - Input
    	- d2v_ctx_t *pctx : 라이브러리에서 공유 할 데이터 저장한 d2v 데이터 타입에 대한 포인터
	- char *filename : 입력 문서 이름
    - Return
    	- d2v status 타입에 정의 된 내용 반환
    - Discussion
    	- 예:
    	- d2v_ctx_t d2v_ctx;
    	- d2v_open(&d2v_ctx,"input.txt")


- <code>d2v_status_t d2v_get_document_vector(d2v_ctx_t *pctx, d2v_vector_t *doc_vec)
	- <i>filename에 저장된 단어와 COUNT 정보를 통해 단어에 TID를 부여하여, TID, COUNT 형태의 벡터값을 만들어 준다. </i>
	- Input
		- d2v_ctx_t *pctx : 라이브러리에서 공유 할 데이터를 저장한 d2v 데이터에 대한 포인터
		- d2v_vector_t *doc_vec : 생성 된 Document Vector를 저장하는 백터 데이터값에 대한 포인터
	- Return
		- d2v status 타입에 정의 된 내용값 반환
	- Descussion
		- 예
		- d2v_ctx_t d2v_ctx
		- d2v_vector_t doc_vec
		- d2v_get_document_vector(&d2v_ctx,&doc_vec)
		- printf("TID : %d, COUNT : %d\n",
				doc_vec.element[i].id,
				doc_vec.element[i].count);

- <code>d2v_status_t d2v_close(d2v_ctx_t *pctx)
	- <i> D2V 오버레이션 사용에 필요했던 GTT 라이브러리를 close 한다. </i>
	- Input
		- d2v_ctx_t *pctx : 라이브러리에서 공유할 데이터 포인터
	- Return
		- d2v status 타입에 정의 된 내용 값 반환
	- Discussion
		- 예 :
		- d2v_ctx_t d2v_ctx
		- d2v_close(&d2v_ctx)

- <code>d2v_status_t d2v_free_vector(d2v_vector_t *doc_vec)
	- <i> D2V에서 Document Vector를 생성해줄 때 할당했던 메모리를 해제한다. </i> 
	- Input
		- d2v_vector_t *doc_vec : 해제 할Document Vector 에대 한포인터
	- Return
		- d2v status 타입 에정 의 된내 용 값반 환
	- Discussion
		-  예 :
		- d2v_vector_t doc_vec
		- d2v_free_vector( &doc_vec )
