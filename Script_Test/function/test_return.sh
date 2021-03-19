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

square_by_return ${1}
echo "return answer = $?"


answer=$(square_by_echo ${1})
echo "echo answer = ${answer}"


answer=$(square_by_echo_and_return ${1})
echo "$?"
echo "echo answer = ${answer}"

