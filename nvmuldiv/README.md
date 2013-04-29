nvmuldiv/
=========
- float nvmuldiv( float d1[], float d2[], int len );
- result = (d1[0] / d2[0]) x (d1[1] / d2[1]) x ... x (d1[len-1] x d2[len-2] )
- Current implementation has 
-- 1. Host CPU
-- 2. CUDA thrust library
- versions

thrust_samples/
===============
- sample code for thrust library, especially reduce() algorithm
