#! /bin/bash

call_function()
{
  echo "parameter 1 and 2 are: ${1} and ${2}"
  xx=ddd
  yy=aaa
}

xx=aaa

call_function bob letmein Bob

echo "xx: ${xx}, yy: ${yy}"

echo $1 > UDC

