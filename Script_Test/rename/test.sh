#! /bin/bash

ext_from=111
ext_to=222

for i in *.${ext_from}
do
    name=$(echo ${i} | cut -d. -f1)
    echo "rename ${i} to ${name}.${ext_to}"
    mv ${i} ${name}.${ext_to}
done


