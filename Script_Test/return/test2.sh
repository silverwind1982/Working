#! /bin/bash

ls ./non-exist-file > /dev/null 2>&1

echo -e "return value is: ${?}\n"

ls ${0} > /dev/null 2>&1

echo -e "return value is: ${?}\n"

exit 1
