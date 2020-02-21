#!/bin/bash

function show_error()
{
	echo -e "\033[31m$1\033[0m"
}

function show_info()
{
	echo -e "\033[32m$1\033[0m"
}

function cp_partition_files()
{
	src_dir=$1
	dst_dir=$2

	images="bin/asic/sparse_images/rawprogram_unsparse0.xml rawprogram1.xml rawprogram2.xml rawprogram3.xml rawprogram4.xml rawprogram5.xml patch0.xml patch1.xml patch2.xml patch3.xml patch4.xml patch5.xml gpt_main0.bin gpt_main1.bin gpt_main2.bin gpt_main3.bin gpt_main4.bin gpt_main5.bin gpt_backup0.bin gpt_backup1.bin gpt_backup2.bin gpt_backup3.bin gpt_backup4.bin gpt_backup5.bin"

	for image in ${images}; do
        if [ ! -f "${src_dir}${image}" ]; then
            show_error "${src_dir}${image} is not found"
            exit -1
        fi

		cp ${src_dir}${image} ${dst_dir}
	done


	show_info "All partition files are synchronized"
}

if [ -z "$1" ]; then
    src_dir="../../sm8250_Ali/aibox/src/non-hlos/test_device/common/build/ufs/"
else
    src_dir="$1"
fi

if [ ! -d "${src_dir}" ]; then
    show_error "${src_dir} is not found"
    exit -1
fi

if [ -z "$2" ]; then
    dst_dir="../../sm8250_Ali/self_data/partition_file/"
else
    dst_dir="$2"
fi

if [ ! -d "${dst_dir}" ]; then
    mkdir ${dst_dir}
fi

cp_partition_files ${src_dir} ${dst_dir}

