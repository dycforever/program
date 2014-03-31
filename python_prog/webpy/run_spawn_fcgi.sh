#!/bin/bash
workdir=`pwd`
/home/dyc/tools/spawn-fcgi/bin/spawn-fcgi -n -u dyc -d $workdir -f $workdir/first.py -a 127.0.0.1 -p 9002
