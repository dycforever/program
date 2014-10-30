#!/bin/bash

gcc -g sample.c -o sample
objdump -h sample

objdump --dwarf=info sample
objdump --dwarf=loc sample
objdump --dwarf=decodedline sample
