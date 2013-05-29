#!/bin/sh

#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${PWD}/../lib
#export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:../lib
echo "=== Make sure you executed as 'source $0' in bash ==="
echo "Now you are ready to execute binaries in this directory"
