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
