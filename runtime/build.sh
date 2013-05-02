#!/bin/sh
gcc -pg dummy_evald.c dummy_libs.c -o evald_nve_random -Wall -g 
gcc -pg dummy_evald.c dummy_libs.c -o evald_nve_calc -DNVE_DO_CALC -Wall -g 
