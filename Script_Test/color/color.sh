#!/bin/sh
set -e

Black="\033[1;30m"        # Black
Red="\033[0;31m"          # Red
Green="\033[1;32m"        # Green
Yellow="\033[0;33m"       # Yellow
Blue="\033[0;34m"         # Blue
Purple="\033[0;35m"       # Purple
Cyan="\033[0;36m"         # Cyan
White="\033[0;37m"        # White
error="\033[0;38m"        # 
warning="\033[0;39m"        # 
NC='\033[0m' # No Color

function print_info () {
        echo -e ${Red}$1${NC}
}

function print_error () {
        echo -e ${error}$1${NC}
}

function print_warning () {
        echo -e ${warning}$1${NC}
}

function print_title () {
        echo -e ${Purple}$1${NC}
}

function print_orange () {
        echo -e ${Yellow}$1${NC}
}

print_info "${0}"
print_error "${0}"
print_warning "${0}"
print_title "${0}"
