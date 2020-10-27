#! /bin/bash

count=$(cat count.txt)

echo "this is the $count times test"

#count=`expr $count + 1`
#count=$(($count + 1))
count=$[$count + 1]

echo $count > count.txt

exit 0
