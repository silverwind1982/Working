#! /bin/bash

echo "I was called with $# parameters"
echo "My full name is $0"
echo "My name is `basename $0`"
echo "My first parameter is $1"
echo "My second parameter is $2"
echo "All parameters are $@"
echo "All parameters are $*"
echo ""
echo "13th parameter is composed of \$1 and "3": $13"
