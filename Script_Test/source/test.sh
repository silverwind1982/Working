#! /bin/bash


source ./source_file.sh

if [ ${?} == 0 ]; then
    echo "Source successfully"
else
    echo "Failed to source"
fi

if [ ${?} == 0 ]; then
    /bin/bash ./binbash_file.sh
else
    /bin/bash ./binbash_file.sh
fi

exit ${?}
