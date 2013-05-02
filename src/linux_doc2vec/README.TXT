Unzip files in a folder that you downloaded from my website http://nlp.kookmin.ac.kr/.

At a location(foloder).

1) Following two file should be located at a folder name 'EXE'

- index2  -- execution file corresponding to index.exe at Windows
- indexT2 -- execution file corresponding to indexT.exe at Windows

2) KLT_INDEX library libindex-TEST.a should be located at the same folder of KLT2000-TEST.DLL.

Seung-Shik Kang, 2013/04/10


------------------------------------------------------

1) 컴파일 방법

- 필요 파일 : main.c , header 폴더, libindex-TEST.a
- 컴파일 명령 : $ gcc main.c -o News_Recommand -lindex-TEST -L./
              + libindex-TEST.a를 링크 , -L./ 는 libindex-TEST.a 파일 경로

2) 폴더 구성

-test 디렉토리 : 컴파일 결과물 파일을 해당 디렉토리에 넣고 실행해야 한다. 
		형태소 분석기의 실행에 필요한 KLT2000-TEST.DLL 파일, 사전(hdic) 폴더, sample 텍스트 파일이 들어있다.
-prebuild 드렉토리 : 교수님이 주신 테스트용 형태소 분석기 실행파일이 들어있다. 실행방법은 다음과 같다
		=    $ 명령어 <텍스트파일> 
-header 디렉토리 : 컴파일에 필요한 헤드파일


