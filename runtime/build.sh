#!/bin/sh
gcc -pg dummy_evald.c dummy_libs.c -o evald_nve_random -Wall -g -Xlinker -pg
gcc -pg dummy_evald.c dummy_libs.c -o evald_nve_calc -DNVE_DO_CALC -Wall -g -Xlinker -pg
