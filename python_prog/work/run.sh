#!/usr/bin/bash

source run.conf

if [ ! -f run.conf ]; then
    echo "error! can not find run.conf"
        exit 1
fi

pid=$$
./argparser.py ipList=$ipList \
                inputList=$inputList \
                --output=_statistics.out.$pid \
                --fr=$fr \
                --reqFrom=$from \
                --ve=$ve \
                --host=$host \
                --location=$location && \
sort -n _statistics.out.$pid > $output 
rm -rf _statistics.out.$pid

