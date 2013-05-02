Runtime Environment
===================

Daemons (Trainer and Evaluation) Runtime Directory that includes
- Input Data Structure and File Name Convensions
- Output Data Structure and File Name Convensions
- Template Daemon Program Runs based on Dummy Modules Generate Random Value Output
    - D2V
    - PDVL
    - NVE


How to build
------------

<pre>
$ ./build.sh
</pre>
Now, you have two binaries
- <code> evald_nve_random </code>
- <code> evald_nve_calc </code>

How to test
-----------
<pre>
$ ./run.sh
-------------------------------
Testing Random Score (NVE IDLE)
-------------------------------
evald:num_input:100000
evald: Input Data Ready
evald: working...
evald: working...
evald: working...
evald: working...
evald: working...
evald: working...
evald: working...
evald: working...
evald: working...
evald: working...

real	0m13.117s
user	0m13.051s
sys	0m0.063s
-------------------------------
Testing Calculated Score
-------------------------------
evald:num_input:100000
evald: Input Data Ready
nve: Calculation Enabled
evald: working...
evald: working...
evald: working...
evald: working...
evald: working...
evald: working...
evald: working...
evald: working...
evald: working...
evald: working...
evald: multiplies:2501457737 divisions:2501457737

real	0m25.536s
user	0m25.458s
sys	0m0.069s
</pre>

Estimated running times of evald_nve_random and evald_nve_calc will be printed using 'time' command

Random Text Generator
=====================

<pre>
$ ./genrtext 200
wlrb mqbhcd r owkk hiddqsc xrjm wfr sjyb dbef arcbynecd ggx pklore lnmpapqfwk opkm oqhnwnkue hsqmgbbuq ljjivswmd q bx xmvtr bljptnsn wzqf mafadrrwso sbcnuv hffbsaq wp c cehch vf kmlnozjkpq xrjxki zyxa
</pre>
