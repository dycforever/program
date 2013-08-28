#!/bin/bash
i=0
sum=0
while [ $i -lt 100 ];do
	echo i=$i
	i=$(($i+1))
#	i=`expr $i + 1`
#	i=$(($i+1))
#	./run
	random=$RANDOM
	ret=$?
	echo "ret=$ret  random=$random"
	sum=$(($sum+$ret))
done
avg=$(($sum/$i))
echo "avg time is $avg" > result
