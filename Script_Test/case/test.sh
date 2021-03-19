#! /bin/bash

echo "Please talk to me ..."
while :
do
  read INPUT_STRING
  case $INPUT_STRING in
	hello)
		echo "Hello $USER!"
		;;
	bye)
		echo "See you soon!"
		break
		;;
	*)
		echo "That's cool"
		;;
  esac
done
