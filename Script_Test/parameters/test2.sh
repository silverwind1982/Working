#! /bin/bash

echo "all parameters are: $@"
echo "\$@ in for loop"
for p in "$@"
do
    echo "${p}"
done
echo -e "\n"


echo "all parameters are: $*"
echo "\$* in for loop"
for p in "$*"
do
    echo "${p}"
done
