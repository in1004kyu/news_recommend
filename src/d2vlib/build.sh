#!/bin/sh
# Added -Wall flags to print all the warnings - simon
gcc -Wall -c d2v_naive.c
gcc -Wall -o test test.c d2v_naive.o ../gttlib/gtt_naive.o
