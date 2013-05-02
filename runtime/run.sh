#!/bin/sh
time gprof -b ./evald_nve_random
time gprof -b ./evald_nve_calc
