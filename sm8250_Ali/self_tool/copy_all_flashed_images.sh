#!/bin/bash

function show_error()
{
    echo -e "\033[31m$1\033[0m"
}

function show_info()
{
    echo -e "\033[32m$1\033[0m"
}

function cp_file()
{
    src_file=$1
    dst_file=$2

    if [ ! -f "${src_file}" ]; then
        show_error "${src_file} is not found"
        exit -1
    fi

    if [ ! -f "${dst_file}" ]; then
        cp ${src_file} ${dst_file}
        return
    fi

    src_md5=$(md5sum ${src_file} | cut -d' ' -f1)
    dst_md5=$(md5sum ${dst_file} | cut -d' ' -f1)
    if [ ${src_md5} != ${dst_md5} ]; then
        cp ${src_file} ${dst_file}
    fi
}

if [ -z "$1" ]; then
    src_dir="../../sm8250_Ali/aibox/src/non-hlos/test_device/"
else
    src_dir="$1"
fi

if [ ! -d "${src_dir}" ]; then
	show_error "${src_dir} is not found"
	exit -1
fi

if [ -z "$2" ]; then
    dst_dir="../../sm8250_Ali/self_data/all_flashed_images/"
else
    dst_dir="$2"
fi

if [ ! -d "${dst_dir}" ]; then
	mkdir ${dst_dir}
fi

cp ${src_dir}aop_proc/build/ms/bin/AAAAANAZO/aop.mbn ${dst_dir}

cp_file ${src_dir}boot_images/QcomPkg/SocPkg/8250/Bin/LAA/RELEASE/xbl.elf ${dst_dir}

cp ${src_dir}boot_images/QcomPkg/SocPkg/8250/Bin/LAA/RELEASE/xbl_config.elf ${dst_dir}

cp ${src_dir}boot_images/QcomPkg/SocPkg/8250/Bin/LAA/RELEASE/imagefv.elf ${dst_dir}

cp ${src_dir}boot_images/QcomPkg/Tools/binaries/logfs_ufs_8mb.bin ${dst_dir}

cp ${src_dir}boot_images/QcomPkg/SocPkg/8250/Bin/LAA/RELEASE/prog_firehose_ddr.elf ${dst_dir}

cp_file ${src_dir}trustzone_images/build/ms/bin/DARAANAA/tz.mbn ${dst_dir}

cp ${src_dir}trustzone_images/build/ms/bin/DARAANAA/hyp.mbn ${dst_dir}

cp ${src_dir}trustzone_images/build/ms/bin/DARAANAA/devcfg.mbn ${dst_dir}

cp ${src_dir}trustzone_images/build/ms/bin/DARAANAA/cmnlib64.mbn ${dst_dir}

cp ${src_dir}trustzone_images/build/ms/bin/DARAANAA/cmnlib.mbn ${dst_dir}

cp ${src_dir}qtee_tas/build/ms/bin/DARAANAA/featenabler.mbn ${dst_dir}

cp ${src_dir}qtee_tas/build/ms/bin/DARAANAA/uefi_sec.mbn ${dst_dir}

cp ${src_dir}qtee_tas/build/ms/bin/DARAANAA/km4.mbn ${dst_dir}

cp ${src_dir}spss_proc/release/crm/spunvm.bin ${dst_dir}

cp_file ${src_dir}apps_proc/poky/build/tmp-glibc/deploy/images/sm8250-edge/sm8250-sysfs.ext4 ${dst_dir}sm8250-sysfs.ext4

cp_file ${src_dir}apps_proc/poky/build/tmp-glibc/deploy/images/sm8250-edge/sm8250-systemrw.ext4 ${dst_dir}sm8250-systemrw.ext4

cp_file ${src_dir}apps_proc/poky/build/tmp-glibc/deploy/images/sm8250-edge/sm8250-cache.ext4 ${dst_dir}sm8250-cache.ext4

cp_file ${src_dir}apps_proc/poky/build/tmp-glibc/deploy/images/sm8250-edge/sm8250-persist.ext4 ${dst_dir} sm8250-persist.ext4

cp_file ${src_dir}apps_proc/poky/build/tmp-glibc/deploy/images/sm8250-edge/sm8250-usrfs.ext4 ${dst_dir}sm8250-usrfs.ext4

cp_file ${src_dir}apps_proc/poky/build/tmp-glibc/deploy/images/sm8250-edge/sm8250-boot.img ${dst_dir}sm8250-boot.img

cp ${src_dir}apps_proc/poky/build/tmp-glibc/deploy/images/sm8250-edge/abl.elf ${dst_dir}

cp_file ${src_dir}common/build/ufs/bin/asic/NON-HLOS.bin ${dst_dir}

cp ${src_dir}common/build/ufs/bin/BTFM.bin ${dst_dir}

cp_file ${src_dir}common/build/bin/dspso.bin ${dst_dir}

cp ${src_dir}common/core_qupv3fw/qupv3fw.elf ${dst_dir}

cp ${src_dir}common/build/bin/multi_image.mbn ${dst_dir}

cp ${src_dir}common/build/bin/apdp/apdp.mbn ${dst_dir}

cp ${src_dir}common/build/ufs/*.bin ${dst_dir}

cp ${src_dir}common/build/ufs/*.xml ${dst_dir}

cp ${src_dir}common/build/ufs/bin/asic/sparse_images/rawprogram_unsparse0.xml ${dst_dir}

cp ${src_dir}common/config/ufs/external/partition.xml ${dst_dir}

show_info "All flash images are synchronized"

