#!/bin/sh
nvcc -o test test.c nvmuldiv_cpu.c nvmuldiv_cuda_thrust.cu
