#! /bin/bash

square_by_return() {
    return $((${1} * ${1}))
}

square_by_echo() {
    echo $((${1} * ${1}))
}

square_by_echo_and_return() {
    echo $((${1} * ${1}))
    return 3
}

if [ -n ${1} ]; then
   integer=15
fi

square_by_return ${integer}
echo "return answer = $?"


answer=$(square_by_echo ${integer})
echo "echo answer = ${answer}"


answer=$(square_by_echo_and_return ${integer})
echo "$?"
echo "echo answer = ${answer}"

