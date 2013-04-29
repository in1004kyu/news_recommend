#!/bin/sh

gcc -Wall -c pdvl_naive.c
gcc -Wall -o test test.c pdvl_naive.o
