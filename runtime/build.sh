#!/bin/sh
gcc -pg dummy_evald.c dummy_libs.c -o evald_nve_random -Wall -g  -DDVPDVL_COUNT_RANDOM
gcc -pg dummy_evald.c dummy_libs.c -o evald_nve_calc -DNVE_DO_CALC -Wall -g  -DDVPDVL_COUNT_RANDOM
gcc -pg -g -Wall genrtext.c dummy_libs.c -o genrtext
