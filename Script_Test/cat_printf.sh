#! /bin/bash
set -e

if [ -n "${1}" ] ; then
    exe="${1}"
else
    exe="./printf_hello"
fi

#result=${exe}
result=$(${exe})

if [ "${result}" == "_a" ] ; then
    echo "print _a"
elif [ "${result}" == "_b" ] ; then
    echo "print _b"
elif [ "${result}" == "hello" ] ; then
    echo "print hello"
else
    echo "print :"
    echo "${result}"
fi

exit 0
