/******************************************
      D2V 컴파일 방법 및 테스트 방법
******************************************/

Compile
$ make

필요 파일
test/n1_utf.txt
test/default.gtt
test/hidc(사전)

실행
$ cd test
$ ./d2v_test

결과 출력
n1_uft.txt 파일에 단어 및 빈도수를 추출하여
추출한 단어를 gtt table에 업데이트하고,
TID, 빈도수에 대한 document vector를 생성한다.



