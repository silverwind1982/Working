#! /bin/bash

echo -n "What is your name [ `whoami` ] "
read myname

myname=${myname:="default_myname"}
#echo ${myname:='default_myname'} > /dev/null 2>&1
echo "myname: ${myname}"

