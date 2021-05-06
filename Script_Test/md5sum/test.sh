#! /bin/bash

if [ ! -f "./md5sum/golden_md5sum.txt" ]; then
    echo "./md5sum/golden_md5sum.txt does NOT exist"
    mkdir "./md5sum"
    touch "./md5sum/golden_md5sum.txt"
    md5sum ./md5sum/golden_md5sum.txt > ./md5sum/golden_md5sum.txt
    if [ ${?} == 0 ]; then
		echo "/persist/md5sum/golden_md5sum.txt has been created." >> ./log.txt
	else
		echo "Error in calculating md5sum of Golden Slot." >> ./log.txt
	fi
else
    echo "./md5sum/golden_md5sum.txt does exist"
fi;
