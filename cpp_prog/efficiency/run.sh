#!/bin/bash
for ((i=0;i<20;i++)) 
do
    ./cache_line $((1 << i)) 
done
