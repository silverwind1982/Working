#!/bin/bash

function show_error()
{
    echo -e "\033[31m$1\033[0m"
}

function show_info()
{
    echo -e "\033[32m$1\033[0m"
}

if [ ! -z "$1" ]; then
    slot="$1"
fi

if [ -z "$2" ]; then
    src_dir="../../../../sm8250_Ali/self_data/all_flashed_images/"
else
    src_dir="$2"
fi

if [ ! -d "${src_dir}" ]; then
    show_error "${src_dir} is not found"
    exit -1
fi


partitions_a="persist system_a systemrw cache userdata
              xbl_a xbl_config_a ddr aop_a tz_a
              hyp_a modem_a bluetooth_a abl_a dsp_a
              keymaster_a boot_a cmnlib_a cmnlib64_a devcfg_a
              qupfw_a uefisecapp_a multiimgoem_a featenabler_a imagefv_a
              apdp spunvm logfs"

images_a=("sm8250-persist.ext4" "sm8250-sysfs.ext4" "sm8250-systemrw.ext4" "sm8250-cache.ext4" "sm8250-usrfs.ext4"
          "xbl.elf" "xbl_config.elf" "zeros_5sectors.bin" "aop.mbn" "tz.mbn"
          "hyp.mbn" "NON-HLOS.bin" "BTFM.bin" "abl.elf" "dspso.bin"
          "km4.mbn" "sm8250-boot.img" "cmnlib.mbn" "cmnlib64.mbn" "devcfg.mbn"
          "qupv3fw.elf" "uefi_sec.mbn" "multi_image.mbn" "featenabler.mbn" "imagefv.elf"
          "apdp.mbn" "spunvm.bin" "logfs_ufs_8mb.bin")


partitions_b="system_b xbl_b xbl_config_b aop_b tz_b
              hyp_b modem_b bluetooth_b abl_b dsp_b
              keymaster_b boot_b cmnlib_b cmnlib64_b devcfg_b
              qupfw_b uefisecapp_b multiimgoem_b featenabler_b imagefv_b"

images_b=("sm8250-sysfs.ext4" "xbl.elf" "xbl_config.elf" "aop.mbn" "tz.mbn"
          "hyp.mbn" "NON-HLOS.bin" "BTFM.bin" "abl.elf" "dspso.bin"
          "km4.mbn" "sm8250-boot.img" "cmnlib.mbn" "cmnlib64.mbn" "devcfg.mbn"
          "qupv3fw.elf" "uefi_sec.mbn" "multi_image.mbn" "featenabler.mbn" "imagefv.elf")


if [ ${slot} == "a" ] || [ -z ${slot} ]; then
i=0
for partition in ${partitions_a}; do
    if [ ! -f "${src_dir}${images_a[$i]}" ]; then
        show_error "${src_dir}${images_a[$i]} not found"
        exit -1
    fi
    fastboot flash ${partition} ${src_dir}${images_a[$i]}
    result=$?
    if [ $result != 0 ]; then
        show_error "fastboot flash ${partition} ${src_dir}${images_a[$i]} error"
        exit -1
    fi
    let "++i"
done

show_info "All partition A images are flashed"

fi


if [ ${slot} == "b" ] || [ -z ${slot} ]; then
i=0
for partition in ${partitions_b}; do
    if [ ! -f "${src_dir}${images_b[$i]}" ]; then
        show_error "${src_dir}${images_b[$i]} not found"
        exit -1
    fi
    fastboot flash ${partition} ${src_dir}${images_b[$i]}
    result=$?
    if [ $result != 0 ]; then
        show_error "fastboot flash ${partition} ${src_dir}${images_b[$i]} error"
        exit -1
    fi
    let "++i"
done

show_info "All partition B images are flashed"

fi


