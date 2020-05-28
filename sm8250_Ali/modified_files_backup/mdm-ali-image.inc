# This include forces the generation of a /AliDisk alidata partition image file

DEPLOY_DIR_IMAGE_EMMC ?= "${DEPLOY_DIR_IMAGE}"
OUTPUT_ALIDATA_FILE_EXT4 = "${DEPLOY_DIR_IMAGE_EMMC}/${ALIDATAIMAGE_TARGET}"

# Generating alidata image in EXT4 format

IMAGE_PREPROCESS_COMMAND_append = "${@bb.utils.contains('IMAGE_FSTYPES','ext4',' create_alidata_ext4_img; ','', d)}"

create_alidata_ext4_img() {
        mkdir -p ${DEPLOY_DIR_IMAGE_EMMC}
        make_ext4fs -s -l ${ALIDATA_SIZE_EXT4} ${OUTPUT_ALIDATA_FILE_EXT4}
        chmod 644 ${OUTPUT_ALIDATA_FILE_EXT4}
}
