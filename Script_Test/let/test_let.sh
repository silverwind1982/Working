#! /bin/bash

i=0

while [ ${i} -lt 8 ]; do
    if [ ${i} -lt 2 ]; then
        i=$((i+1))
    elif [ ${i} -lt 3 ]; then
        ((i=i+1))
    elif [ ${i} -lt 4 ]; then
        ((j+1))
        ((i=i+1))
    elif [ ${i} -lt 5 ]; then
        ((i+=1))
    elif [ ${i} -lt 6 ]; then
        let "i+=1"
    else
        let "i=i+1"
    fi
    echo "i = ${i}"
done

