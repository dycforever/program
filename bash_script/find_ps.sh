#!/bin/bash
for ps in `ls /proc`
do
#    if [[ $ps =~ ^[0-9]+$ ]] ; then
    if [[ $ps =~ ^[[:digit:]]+$ ]] ; then
        echo ps=$ps
        cd /proc/$ps
        ls -l  2>/dev/null | grep dyc
    fi
done
