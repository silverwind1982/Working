#! /bin/bash
set -e

echo "first argument: ${1}"
echo "second argument: ${2}"
echo "third argument: ${3}"

partial_update=0
if [ -n "${2}" ]; then
    if [ "${2}" == "partial" ]; then
        partial_update=1
    elif [ "${2}" == "golden" ]; then
        partial_update=1
    fi
fi

echo "partial_update = ${partial_update}"

if [ "${partial_update}" -eq 1 ]; then
    echo "partial_update -eq 1"
else
    echo "partial_update NOT -eq 1"
fi;

exit 0
