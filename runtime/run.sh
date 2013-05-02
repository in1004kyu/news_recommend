#!/bin/sh
echo "-------------------------------"
echo "Testing Random Score (NVE IDLE)"
echo "-------------------------------"
time ./evald_nve_random
echo "-------------------------------"
echo "Testing Calculated Score"
echo "-------------------------------"
time ./evald_nve_calc
