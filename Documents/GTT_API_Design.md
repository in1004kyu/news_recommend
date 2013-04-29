GTT API Design Document
=======================

Revision History
----------------
- Apr. 29th 2013, Design Document Format Re-organized
- Apr. 29th 2013, Describe API function usage


Module Repository Information
-----------------------------
- Directory: <src>/gttlib
- Headers: gtt.h


Module Description
------------------
- Global TID Table  에 관련 오버레이션을 담당하는 API module.
- 오버레이션 종 류: 테이블 생성, 테이블 업데이트, Term ID 얻기 

Data Types
----------
- struct gtt_ctx_t
    - GTT의 각 함수 사용 시 GTT file 에 대한 포인터를 저장
    - API function 을 사용하기 전에 정의하고 포인터를 함수로 인자로 사용

struct gtt_ctx_t {
  FILE *gtt_fp;  
};

- enum gtt_status_t
    - GTT 각 함수의 리턴 값에 대한 정의 
    - 에러 종류 판단에 사용

enum gtt_status_t{
  GTT_STATUS_SUCCESS = 1,
  GTT_STATUS_ERROR_UNKNOWN = -1,
  GTT_STATUS_ERROR_FILEOPEN = -2,
}

Functions
---------
---함수목록---
 1. open : GTT library 사용 기위 해 global tid table file 을 open
 2. update term : GTT 에 해당단어를 추가하고 TID를 할당, TID 가 없을 시 생성, TID 를 반환
 3. close : GTT library 사용종료를 위해 close

- gtt_status_t gtt_open( gtt_ctx_t *pctx, char *filename)
    - <i> 다른 오버레이션(함수)의 작업이 실행될 테이블 파일을 연다. 인자 중 filename 이 테이블 파일의 위치를 나타낸다.</i>
    - Input
        - gtt_ctx_t *pctx : 라이브러리에서 공유할 데이터를 저장한 gtt 데이터 타입에 대한 포인터 (현재는 파일포인터)
        - char *filename : 라이브러리에서 사용할 테이블 파일 위치 정보
    - Return
        - gtt status 타입 예정의 된 내용값 반환
    - Discussion
        - 예: 
        - gtt_ctx_t gtt_ctx
        - gtt_open(&gtt_ctx)



