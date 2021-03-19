#! /bin/bash

ls > /dev/null
bbbb > /dev/null

ls 2> /dev/null
bbbb 2> /dev/null

ls 2>&1 > /dev/null
bbbb 2>&1 > /dev/null

ls > /dev/null 2>&1
bbbb > /dev/null 2>&1

