#! /bin/bash

while [ "$#" -gt "0" ]
do
    echo "$@"
    echo -e "\$1 is $1\n"
    shift
done 

echo $$
