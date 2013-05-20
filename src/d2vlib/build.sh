#!/bin/sh
# Added -Wall flags to print all the warnings - simon
gcc -Wall -c d2v_naive.c
gcc -Wall -o d2v_test test.c d2v_naive.o gtt_naive.o -L. -lindex-TEST
