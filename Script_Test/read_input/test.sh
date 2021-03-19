#! /bin/bash

echo -n "What is your name [ `whoami` ] "
read myname
echo "Your name is : ${myname:-`whoami`}"

echo "myname: ${myname}"
