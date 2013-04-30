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
  char *pdvl_filename;  // pdvl 파일이름
  FILE *pdvl_fp;        // pdvl 파일포인터
  FILE *temp_fp;        // pdvl 파일오퍼레이션에 대한 tempfile 파일포인터
  int swap_flag;        // pdvl_fp와 temp_fp의 스압 플래그
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
 4. get count : PDVL에서 TID에 해당하는 count 값을 반환

- pdvl_status_t pdvl_open( pdvl_ctx_t *pctx, char *filename)
    - <i> 다른 오버레이션(함수)의 작업이 실행될 리스트 파일을 연다. 인자 중 filename 이 테이블 파일의 위치를 나타낸다.</i>
    - Input
        - pdvl_ctx_t *pctx : 라이브러리에서 공유할 데이터를 저장한 pdvl 데이터 타입에 대한 포인터 (파일포인터)
        - char *filename : 라이브러리에서 사용할 파일 위치 정보
    - Return
        - pdvl status 타입에 정의 된 내용 값 반환
    - Discussion
        - 예: 
        - pdvl_ctx_t pdvl_ctx
        - pdvl_open(&pdvl_ctx, "default.pdvl")

- pdvl_status_t pdvl_update_count(pdvl_ctx_t *pctx, pdvl_tid_t doc_tid, pdvl_count_t doc_count)
    - <i> Personalize Document Vector List에 해당 tid의 count를 업데이트 한다. TID가 PDVL에 없을 시 추가한다. TID가 PDVL에 있을 시 기존 count에 + 한다 </i>
    - Input
        - pdvl_ctx_t *pctx : 라이브러리에서 공유할 데이터를 저장한 pdvl 데이터 타입에 대한 포인터
        - pdvl_tid_t doc_tid : 입력 TID, PDVL의 TID 목록과 비교할 TID
        - pdvl_count_t doc_cout : 입력 TID의 count 값, PDVL에 같은 단어 존재 시 이미 존재하는 TID의 count를 업데이트, 없을 시 추가
    - Return
        - pdvl status 타입에 정의 된 내용 값 반환
    - Discussion
        - 예 :
        - pdvl_ctx_t pdvl_ctx
        - pdvl_tid_t doctid
        - pdvl_count_t count = 3
        - pdvl_update_count(&pdvl_ctx,doctid,count)

- pdvl_status_t pdvl_close( pdvl_ctx_t *pctx)
    -<i> PDVL 오버레이션의 작업이 실행되었던 열었던 테이블 파일을 닫는다.</i>
    - Input
        - pdvl_ctx_t *pctx : 라이브러리에서 공유할 데이터를 저장한 pdvl 데이터 타입에 대한 포인터
    - Return
        - pdvl status 타입에 정의 된 내용 값 반환
    - Discussion
        - 예 :
        - pdvl_ctx_t pdvl_ctx
        - pdvl_close(&pdvl_ctx)

- pdvl_count_t pdvl_get_count( pdvl_ctx_t *pctx, pdvl_tid_t tid)
    -<i> PDVL 에서 입력 TID에 해당하는 Count 값을 리턴한다.</i>
    - Input
        - pdvl_ctx_t *pctx : 라이브러리에서 공유할 데이터를 저장한 pdvl 데이터 타입에 대한 포인터
        - pdvl_tid_t tid : 입력 TID, PDVL의 TID 목록과 비교할 TID
    - Return
        - pdvl_count_t 타입의 TID의 count를 반환, TID가 없을 시 -1을 리턴한다.
    - Discussion
        - 예:
        - pdvl_ctx_t pdvl_ctx
        - pdvl_tid_t tid = 1
        - pdvl_count_t count
        - count = pdvl_get_count(&pdvl_ctx,tid)
