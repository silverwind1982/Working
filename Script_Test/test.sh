#!/bin/bash

check_link()
{
    retry_count=0
    if ! [ -n "${1}" ]; then
        return 1;
    fi

    while [ ${retry_count} -lt 3 ]; do
        readlink "${1}"
        if [ ${?} == 0 ]; then
            return 0
        else
            let "retry_count+=1"
            sleep 1
        fi

    done

    echo "there is NO ${1}"
    return 1
}

echo "bash source : $BASH_SOURCE"
SCRIPT_DIR="$(dirname "$(realpath "$BASH_SOURCE")")"
echo "script dir: $SCRIPT_DIR"

TOP_DIR=$(realpath "$SCRIPT_DIR/../../..")
echo "Top dir: $TOP_DIR"

file="/home/emb/sm8250_Ali/aibox/abc"
check_link "${file}"
