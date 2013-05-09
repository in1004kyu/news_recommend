How to build
===========
<pre>
$ make
nvcc -g -m64 --compile -o nvmuldiv_cpu.o nvmuldiv_cpu.c
nvcc -g -m64 --compile -o nvmuldiv_cuda_thrust.o nvmuldiv_cuda_thrust.cu
nvcc -g -m64 --compile -o nvmuldiv_cuda.o nvmuldiv_cuda.cu
nvcc -g -m64 --compile -o vdiv.o vdiv.cu
nvcc -g -m64 --compile -o reduce_mul.o reduce_mul.cu
gcc -shared -fPIC -o libnvmuldiv.so nvmuldiv_cpu.o nvmuldiv_cuda_thrust.o nvmuldiv_cuda.o vdiv.o reduce_mul.o -lstdc++ -lcuda -lcudart -L/usr/local/cuda/lib
nvcc -g -m64 --compile -o test.o test.c
nvcc -g -m64 -o test_nvmuldiv test.o  -lnvmuldiv -L.
cp libnvmuldiv.so ../../lib
cp test_nvmuldiv ../../bin
</pre>
- Requires NVidia CUDA Driver/Toolkit in order to run nvcc to build the library and the test program
- Once built you will have ../../lib/libnvmuldiv.so and ../../bin/test_nvmuldiv

How to run the test program
===========================
<pre>
$ cd ../../bin	# change current directory to (src_root)/bin
$ . env.sh # make sure DYLD_LIBRARH_PATH points to (src_root)/lib 
$ ./test_nvmuldiv
reduce_mul: blocks:1, threads per block:128, smem size:512
reduce_mul:480.000000
Number of input data:60000 of 128 datasets
p:0x103f18000, end:0x112977ff0
CPU...
GPU-CUDA
vdiv:CUDA kernel launch with 7500 blocks of 1024 threads
aligned_length: len:128 -> m:128
reduce_mul_seg: blocks:60000, threads per block:64, smem size:256
Finished
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

Multiply/Division Algorithm Implementations
======================================
1. Host CPU (x86) Version
    - nvemuldiv_cpu( numerators, denominators, len )
    - synchronous
2. CUDA Thrust Version
    - nvemuldiv_cuda_thrust( numerators, denominators, len )
    - synchronous
3. CUDA Version ( Directly Implemented Kernel Based )
    - nvemuldiv_cuda( numerators, denominators, len )
    - synchronous
    - Planned, Not Implemented Yet.

Multiple Dataset Instances in Parallel
======================================
It would be more efficient if multiple sets of input data (numerators/denominatos pairs) can be processed in parallel.
It is not possible to to achieve with the current version of Thrust thrust::reduce(), 1.6 as of today, according to 
- Thrust Roadmap ( Bulk Synchronous Data Parallel Kernel Launch, https://developer.nvidia.com/content/expressive-algorithmic-programming-thrust )

Therefore, it would be more reasonable to implement a reduce() kernel that multiplies all the elements in an input array.
- Optimizing Parallel Reduction in CUDA, http://developer.download.nvidia.com/compute/cuda/1.1-Beta/x86_website/projects/reduction/doc/reduction.pdf

The prototype of the API function for the multiple dataset would look something like,
<pre>
int nvemuldiv_cuda_multi( float *numerators[], float *denominators[], int len[] );
// or
int nvemuldiv_cuda_queue( nvemuldiv_ctx, float numerators[], float denominators[], int len, priv, callback );
</pre>
- nvemuldiv_ctx Context Structure for nvemuldiv API
- priv void * type private data will be passed to callback when the result is available
- callback(priv, result, status) called back when the result is available or error occured and set to 'status'
