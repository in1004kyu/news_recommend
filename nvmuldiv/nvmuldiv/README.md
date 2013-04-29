How to build
===========
<pre>
$ ./build.sh
</pre>
- Requires NVidia CUDA Driver/Toolkit in order to run nvcc to build the library and the test program

How to run the test program
===========================
<pre>
$ ./test
</pre>

What Test Program Does
----------------------
- Generates 2 arrays with random number of elements and random values: numerator[] and denominators[]
- Performs Host CPU Multiply/Div
- Performs CUDA Multiply/Div using thrust
- Prints Results

API Design
==========
- NVEMULDIV API Design: https://github.com/in1004kyu/news_recommend/blob/master/Documents/NVEMULDIV_API_Design.md
