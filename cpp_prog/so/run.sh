#!/bin/bash
make
strip main
rm -rf prof.data
CPUPROFILE=./prof.data LD_PRELOAD=~/tools/gperftools/lib/libprofiler.so ./main > /dev/null
pprof --text ./main ./prof.data 
