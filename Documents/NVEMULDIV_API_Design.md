NVEMULDIV API Design Document
=======================

Revision History
----------------
- Apr. 29th 2013, Initial Draft


Module Repository Information
-----------------------------
- Directory: &lt;src&gt;/nvemuldiv/nvemuldiv
- Headers: include/nvmuldiv/nvmuldiv.h


Module Description
------------------
NVE Module 내부에서 Naive Bayesian Algorithm을 수행하는데 필요한 산술적인 연산을 CUDA 기반으로 구현

Data Types
----------
N/A

Functions
---------
- <code>float nvmuldiv( numerators, denominators, len )</code>
    - Performs the primitive Naive Bayesian Probability Calculation
    - Input
        - numerators Input Array of numerators
        - denominators Input Array of denominators
        - len number of elements in numerators[] and denominators[]
    - Return
        - <code>(d1[0] / d2[0]) x (d1[1] / d2[1]) x ... x (d1[len-1] x d2[len-2] )</code>
    - Discussion
        - Current Implementation Performs Calculations on the HOST CPU
        - nvmuldiv_cuda_thrust() Performs the Equivalent Calculations on CUDA using thrust library
        - The Final Implementation Will Perform on CUDA (Or, configured by a build time flag)

- <code>float nvmuldiv_cuda_thrust( numerators, denominators, len )</code>
    - Explicitly Performs the primitive Naive Bayesian Probability Calculation on CUDA using thrust library
    - Input
        - numerators Input Array of numerators
        - denominators Input Array of denominators
        - len number of elements in numerators[] and denominators[]
    - Return
        - <code>(d1[0] / d2[0]) x (d1[1] / d2[1]) x ... x (d1[len-1] x d2[len-2] )</code>
- <code>int nvmuldiv_seg( float n[], float d[], int len, float r[], int len_r )</code>
    - Multi-segment bulk processing of <code>nvmuldiv()</code>
    - n: combined vector of numerators. 'len' elements
    - d: combined vector of denominators. 'len' elements
    - len: length of 'n' and'd'
    - r: output result vector where score of each segment. 'len_r' elements
    - len_r: length of each segment. number of segment = len / len_r. 
    - example: 
<pre>
nvmuldiv_seg( { 1, 2, 3, ... 256}, { 1, 2, 3, ... 256 }, 256, &r, 64 );
    - 4 segments ( = 256 / 64 )
    - numerators at segment 0 : n[0] ~ n[63]
</pre>

<pre>
float nvmuldiv( float numerators[], float denominators[], int len);

float nvmuldiv_cuda_thrust( float numerators[], float denominators[], int len);
</pre>
