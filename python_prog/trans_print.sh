#!/bin/bash

if [ $# -lt 1 ] ; then
    echo "argument not enough"
    exit -1
fi
# trans 'print xxx' to 'print(xxx)'
sed "s/\(\W*\)print \(.*\)$/\1print(\2)/" -i $1
