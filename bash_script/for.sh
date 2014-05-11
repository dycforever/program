#!/bin/bash

i=0
sum=0
while [ $i -lt 100 ];do
	echo i=$i
    false
	i=$(($i+1))
#	i=`expr $i + 1`
	random=$RANDOM
	ret=$?
	echo "ret=$ret  random=$random"
	sum=$(($sum+$ret))
done
avg=$(($sum/$i))
echo "avg time is $avg" > result
