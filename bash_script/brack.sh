#!/bin/bash
mkdir tmp1
cd tmp1
touch tmp_{1,2,3,4,5,6}
cd ..

mkdir tmp2
cp tmp1/tmp_{1,2,3,4,5,6} tmp2/
