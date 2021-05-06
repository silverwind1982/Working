#! /bin/bash

call_function()
{
  echo "xx and yy are: ${xx} and ${yy}"
  xx=${1}
  yy=${2}
}

assign_parameter_function()
{
    STR=$(date)
#    expr "${1}=\"${STR}\""
    xxx=${STR}
}

xx="1111"
yy="2222"

echo "xx: ${xx}, yy: ${yy}"



call_function bob letmein Bob

echo "xx: ${xx}, yy: ${yy}"



call_function ${xx} ${yy}
echo "xx: ${xx}, yy: ${yy}"

echo $1 > UDC


assign_parameter_function xx
assign_parameter_function yy

echo "xxx: ${xxx}, yyy: ${yyy}"
