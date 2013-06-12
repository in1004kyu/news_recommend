SNS News Recommendation Project
===============================

Project Description
-------------------
본 서비스에 가입한 사용자를 위해서 인터넷 뉴스의 목록을 제공함과 동시에 사용자가 좋아하는것으로 표시한 뉴스와 유사한 주제의 최신뉴스를 추가적으로 제공한다.
뉴스의 선호도 판별은 Naive Bayesian Algorithm을 사용한다
제공되는 뉴스의 목록은 아래와 같은 경로로 유입된다.
- 사용자의 Facebook News Feed에 올라오는 내용 중에 포함된 인터넷 주소 (URL)에 있는 Web Article
- 사용자의 Twitter Timeline에 있는 Tweet중에 포함된 인터넷 주소 (URL)에 있는 Web Article
- 사용자가 구독신청한 RSS Feed의 각 항목에 포함된 인터넷 주소 (URL)에 있는 Web Article
- 그밖에 시스템이 발전하면서 추가적으로 지원할 수 있는 뉴스 소스
- 사용자의 선호뉴스인지 여부를 판단하기 위한 알고리즘은 NVIDIA CUDA가 장착된 Linux 서버에서 동작한다


Directory Descriptions
----------------------
- Documents/
    - Project가 진행됨에 따라 필요에 의해서 작성되는 각종 문서들
- D2V/
    - Document 2 Vector Module
    - 입력문서 (Plain Text) 를 Document Vector로 변환하며 그에 따라 Global Term Table을 갱신한다
- PDVL/
    - Personal Document Vector List Module
    - 사용자별로 선호하는것으로 표시된 뉴스의 Document Vector를 보관하고, 이를 다시 읽어오는 기능을 수행한다
- NVE/
    - Naive Bayesian Algorithm
    - D2V를 통해서 변환된 Document Vector와 PDVL간의 유사도를 평가하는 기능을 수행한다
- nvmuldiv/
    - NVE 내부에서 Naive Bayesian Algorithm을 수행하는데 필요한 산술적인 연산을 CUDA 기반으로 구현

How to Run the test program
--------------------------
- Make
	- 상위폴더에서 make 실행
	- /bin 에서 . env.sh 커맨드 실행
- Download test data
	- mysql.h 라이브러리를 설치해야한다. 
	- 따로 evaluation 할 뉴스 데이터가 있으면 /example/incomming에 test[0부터 n].txt 포맷으로 데이터를 넣어둔다.
	- /src/collectData에서 make 실행후 ./collect_test 실행 
	- 약 7만여개의 테스트용 뉴스 데이터를 다운받는다.
- Training Data
	- /bin에서 ./train_test 실행
- Evaluation 방법
 	- TESTSIZE 값을 테스트할 뉴스의 갯수를 지정해둔다
	- 만약 50이라고 되있으면 /example/incomming 안의 test0.txt ~ test50.txt 파일을 판별해서 추천한다.
	- /bin에서 ./eval_test 를 실행하면 프로그램이 추천을 해준다

- 아웃풋 설명
	- Best Recommend -> 추천 기준값인 Threshold 보다 높은 뉴스들
	- Recommend news -> Threshold의 반값보다 높은 뉴스들중 탑 10인 뉴스들
	- New news 		 -> 그외 새로 들어온 뉴스들
	- 문서이름, 출몰한 단어수들 / 점수

Program Out put
===============

<pre>
$ ./eval\_test

----------- Best Recommend news -----------

 ---------- Recommend news ----------
test37 cnt:135 / score 0.475241
test17 cnt:132 / score 0.447840
test19 cnt:188 / score 0.442869
test20 cnt:175 / score 0.427068
test38 cnt:355 / score 0.389160
test16 cnt:177 / score 0.386215
test40 cnt:184 / score 0.378799
test28 cnt:218 / score 0.365119
test0 cnt:144 / score 0.359486
test15 cnt:253 / score 0.354698

 ---------- New news ----------
test6 cnt:161 / score 0.350886
test3 cnt:34 / score 0.345171
test31 cnt:292 / score 0.342474
test21 cnt:158 / score 0.341217
test12 cnt:151 / score 0.337439
test34 cnt:33 / score 0.336271
test41 cnt:190 / score 0.325008
test8 cnt:33 / score 0.324298
test39 cnt:162 / score 0.323943
test35 cnt:151 / score 0.318997
test29 cnt:167 / score 0.314065
test23 cnt:55 / score 0.311884
test26 cnt:279 / score 0.306288
test22 cnt:133 / score 0.302019
test47 cnt:70 / score 0.300523
test33 cnt:21 / score 0.300249
test45 cnt:235 / score 0.295877
test44 cnt:221 / score 0.276998
test46 cnt:193 / score 0.276193
test49 cnt:50 / score 0.266307
test30 cnt:117 / score 0.265254
test7 cnt:185 / score 0.257255
test42 cnt:281 / score 0.255018
test9 cnt:81 / score 0.242776
test14 cnt:473 / score 0.228771
test2 cnt:330 / score 0.225335
test43 cnt:54 / score 0.224021
test11 cnt:126 / score 0.219120
test4 cnt:134 / score 0.218573
test1 cnt:128 / score 0.216613
test5 cnt:131 / score 0.215403
test48 cnt:288 / score 0.214243
test10 cnt:121 / score 0.213930
test27 cnt:263 / score 0.213595
test25 cnt:89 / score 0.212898
test24 cnt:156 / score 0.211615
test18 cnt:82 / score 0.207674
test36 cnt:120 / score 0.201029
test32 cnt:220 / score 0.180201
test13 cnt:76 / score 0.129105
</pre>


Schedule
--------
- 형준
    - D2V API Design, Implemetation - 9일
    - Cuda Algorithm [나누기] - 13일
    - [책임] Poster & Presentation 20일 시작 21일까지

- 인규
    - Makefile Tree - 10일
    - Cuda Algorithm [곱하기] - 11일
    - NVE + NVEMULDIV - 12일
    - Cuda add 연산 optimize - 13일
    - NVE parallelization API - 16일
    - NVE parallelization Implementation - 18일 
    - [책임] Poster 1차 13일에 시작 14일까지

- 상모
    - Trainer Daemon 20일
    - EvaluD 26일
