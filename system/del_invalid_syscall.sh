#!/bin/bash

for lnum in $(awk 'BEGIN{FS=":"}{print $2}' make.error | sort -n -r )
do 
    sed -i "$lnum d" syscall2str.h
done