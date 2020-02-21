#!/bin/bash

function show_error()
{
    echo -e "\033[31m$1\033[0m"
}

function show_info()
{
    echo -e "\033[32m$1\033[0m"
}

if [ -z "$1" ]; then
    src_dir="../../sm8250_Ali/self_data/hlos_images/"
else
    src_dir="$1"
fi

if [ ! -d "${src_dir}" ]; then
    show_error "${src_dir} is not found"
    exit -1
fi

if [ ! -z "$2" ]; then
    slot="$2"
fi


if [ ${slot} == "a" ] || [ -z ${slot} ]; then
    fastboot flash persist  ${src_dir}sm8250-persist.ext4
    fastboot flash cache    ${src_dir}sm8250-cache.ext4
    fastboot flash systemrw ${src_dir}sm8250-systemrw.ext4
    fastboot flash system_a ${src_dir}sm8250-sysfs.ext4
    fastboot flash userdata ${src_dir}sm8250-usrfs.ext4

    fastboot flash boot_a   ${src_dir}sm8250-boot.img
    fastboot flash alidata  ${src_dir}sm8250-alifs.ext4
fi

if [ ${slot} == "b" ] || [ -z ${slot} ]; then
    fastboot flash system_b ${src_dir}sm8250-sysfs.ext4
    fastboot flash boot_b   ${src_dir}sm8250-boot.img
fi

show_info "All images are flashed"

