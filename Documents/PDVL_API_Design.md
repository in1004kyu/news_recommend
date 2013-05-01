PDVL API Design Document
=======================

Revision History
----------------
- Apr. 29th 2013, Design Document Format Re-organized
- Apr. 29th 2013, Describe API function usage


Module Repository Information
-----------------------------
- Directory: /pdvllib
- Headers: pdvl.h 
- Source: pdvl_naive.c 


Module Description
------------------
- Personalize Document Vector List  에 관련 오버레이션을 담당하는 API module.
- 오버레이션 종 류: List creat, List update, Get Word Count 

Data Types
----------
- struct pdvl_ctx_t
    - PDVL library 에서 사용 될 데이터들이 저장되어 있는 데이터
    - API function 을 사용하기 전에 정의하고 포인터를 함수로 인자로 사용

<pre>
struct pdvl_ctx_t {
  char *pdvl_filename;  // Save pdvl filename
  FILE *pdvl_fp;  	// pdvl file pointer
  FILE *temp_fp;	// pdvl temp file pointer
  int swap_flag;	// file pointer swap 상황을 저장.
  document_vector_t *pdv;
};
</pre>

- enum pdvl_status_t
    - PDVL 각 함수의 리턴 값에 대한 정의 
    - 에러 종류 판단에 사용

<pre>
enum pdvl_status_t{
  PDVL_STATUS_SUCCESS = 1,
  PDVL_STATUS_FAIL = 0,
}
</pre>

- pdvl_tid_t : pdvl library에서 document tid을 다루는 데이터 타입, unsigned int 로 정의되어 있다.

<pre>
typedef unsigned int pdvl_tid_t;
</pre>

- pdvl_count_t : pdvl library에서 document count 을 다루는 데이터 타입, unsigned int 로 정의되어 있다.

<pre>
typedef unsigned int pdvl_count_t;
</pre>

Functions
---------
---함수목록---
 1. open : PDVL library 사용 기위 해 personalize document vector list file 을 open
 2. update count : PDVL 에 TID를 추가하고, count 업데이트
 3. close : PDVL library 사용종료를 위해 close
 4. get count : PDVL  에저장 된TID

- pdvl_status_t pdvl_open( pdvl_ctx_t *pctx, char *filename)
    - <i> 다른 오버레이션(함수)의 작업이 실행될 리스트 파일을 연다. 인자 중 filename 이 테이블 파일의 위치를 나타낸다.</i>
    - Input
        - pdvl_ctx_t *pctx : 라이브러리에서 공유할 데이터를 저장한 gtt 데이터 타입에 대한 포인터 (파일포인터)
        - char *filename : 라이브러리에서 사용할 테이블 파일 위치 정보
    - Return
        - pdvl status 타입에 정의 된 내용 값 반환
    - Discussion
        - 예: 
        - pdvl_ctx_t pdvl_ctx
        - pdvl_open(&pdvl_ctx, "default.gtt")

- gtt_status_t gtt_update_term(gtt_ctx_t *pctx, gtt_term_t doc_term, gtt_tid_t *TID)
    - <i> Global Tid Table에 Term을 업데이트 한다. 만약 입력 단어가 테이블에 없는 단어라면 새로운 TID를 생성한다. 함수인자 중 TID 포인터 값에 새로 생성된 TID 혹은 이미 생성된 TID 값이 들어간다. </i>
    - Input
        - gtt_ctx_t *pctx : 라이브러리에서 공유할 데이터를 저장한 gtt 데이터 타입에 대한 포인터
        - gtt_term_t doc_term : 입력 단어, GTT의 단어 목록과 비교할 단어
        - gtt_tid_t *TID : 입력 단어에 대한 TID 포인터, GTT에 같은 단어 존재 시 이미 존재하는 TID를 삽입, 새로운 단어가 출현 시 새로운 TID를 생성하여 삽입
    - Return
        - gtt status 타입에 정의 된 내용 값 반환
    - Discussion
        - 예 :
        - gtt_ctx_t gtt_ctx
        - gtt_tid_t newtid
        - char *newterm = "new"
        - gtt_update_term(&gtt_ctx,newterm,&newtid)

- gtt_status_t gtt_close( gtt_ctx_t *pctx)
    -<i> GTT 오버레이션의 작업이 실행되었던 열었던 테이블 파일을 닫는다.</i>
    - Input
        - gtt_ctx_t *pctx : 라이브러리에서 공유할 데이터를 저장한 gtt 데이터 타입에 대한 포인터
    - Return
        - gtt status 타입에 정의 된 내용 값 반환
    - Discussion
        - 예 :
        - pdvl_ctx_t pdvl_ctx
        - pdvl_close(&pdvl_ctx)
    
