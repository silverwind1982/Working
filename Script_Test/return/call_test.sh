#! /bin/bash

./test1.sh > /dev/null 2>&1

echo -e "test1.sh return ${?}\n"

./test2.sh > /dev/null 2>&1

echo -e "test2.sh return ${?}\n"

exit 0
