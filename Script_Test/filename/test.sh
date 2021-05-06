#! /bin/bash

file="/sbin/ab/test/log.txt"

echo "full path:                 ${file}"
echo "folder path:               ${file%\/*}"
echo "filename:                  ${file##*/}"
echo "filename extension:        ${file##*.}"
echo "filename except extension: ${file%.*}"
