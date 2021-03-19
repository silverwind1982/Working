#! /bin/bash

if [ -n "${something}" ]; then
	echo "something: ${something}"
elif [ -n "${something_else}" ]; then
	echo "something_else: ${something_else}"
elif [ -n "${something_eelse}" ]
then
	echo "something_else: ${something_eelse}"
else
	echo "None of the above"
fi
