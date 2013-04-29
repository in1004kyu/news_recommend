#!/bin/sh
# Added -Wall flags to print all the warnings - simon
gcc -Wall -c gtt_naive.c
gcc -Wall -o test test.c gtt_naive.o
gcc -Wall -o test2 test2.c gtt_naive.o
