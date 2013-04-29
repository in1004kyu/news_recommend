NVEMULDIV API Design Document
=======================

Revision History
----------------
- Apr. 29th 2013, Initial Draft


Module Repository Information
-----------------------------
- Directory: &lt;src&gt;/nvemuldiv/nvemuldiv
- Headers: nvemuldiv.h


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

<pre>
float nvmuldiv( float numerators[], float denominators[], int len);

float nvmuldiv_cuda_thrust( float numerators[], float denominators[], int len);
</pre>
