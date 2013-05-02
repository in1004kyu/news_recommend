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

real	2m17.273s
user	2m16.508s
sys	0m0.452s

real	1m43.267s
user	1m42.929s
sys	0m0.227s
</pre>

Estimated running times of evald_nve_random and evald_nve_calc will be printed using 'time' command
