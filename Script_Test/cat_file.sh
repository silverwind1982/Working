#! /bin/bash
set -e

sleep 0.000001

value=$(cat ./integer.txt)
if [ "${value}" -eq 0 ]; then
    echo "value -eq 0"
elif [ "${value}" -eq 1 ]; then
    echo "value -eq 1"
elif [ "${value}" -eq 2 ]; then
    echo "value -eq 2"
elif [ "${value}" -eq 3 ]; then
    echo "value -eq 3"
else
    echo "value NOT -eq 0, 1, 2, 3"
fi;

string=$(cat ./string.txt)

if [ "${string}" == "host" ]; then
    echo "string == host"
elif [ "${string}" == "peripheral" ]; then
    echo "string == peripheral"
elif [ "${string}" == "test" ]; then
    echo "string == test"
elif [ "${string}" == "not" ]; then
    echo "string == not"
else
    echo "partial_update NOT !== host, peripheral, not"
fi;

exit 0
