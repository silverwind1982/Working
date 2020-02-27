# This include forces the generation of a /usr userdata partition
# image file and propagates the /usr part of the filesystem
# over to it.
DEPLOY_DIR_IMAGE_EMMC    ?= "${DEPLOY_DIR_IMAGE}"
DEPLOY_DIR_IMAGE_NAND    ?= "${DEPLOY_DIR_IMAGE}"
USR_IMAGE_BASENAME       ?= "${MACHINE}-usrfs"
USR_IMAGE_ROOTFS         ?= "${TMPDIR}/rootfs/${USR_IMAGE_BASENAME}"
OUTPUT_FILE_ALI_EXT4     ?= "${DEPLOY_DIR_IMAGE_EMMC}/${ALIDATAIMAGE_TARGET}"
OUTPUT_FILE_EXT4         ?= "${DEPLOY_DIR_IMAGE_EMMC}/${USERDATAIMAGE_TARGET}"
OUTPUT_FILE_USR_UBIFS    ?= "${DEPLOY_DIR_IMAGE_NAND}/${USR_IMAGE_BASENAME}.ubifs"
OUTPUT_FILE_FINAL_UBI    ?= "${DEPLOY_DIR_IMAGE_NAND}/${MACHINE}-sysfs.ubi"
OUTPUT_FILE_SYSTEM_UBIFS ?= "${DEPLOY_DIR_IMAGE_NAND}/${IMAGE_LINK_NAME}.ubifs"
UBINIZE_CFG              ?= "${DEPLOY_DIR_IMAGE_NAND}/ubinize_system_userdata.cfg"

# Ensure SELinux file context variable is defined
SELINUX_FILE_CONTEXTS    ?= ""

BASEPRODUCT = "${@d.getVar('PRODUCT', False)}"

ROOTFS_POSTPROCESS_COMMAND_prepend = "clean_usr_rootfs; purge_rootfs; symlink_modules; sync_hostfs;"

# Generating alidata image in EXT4
IMAGE_PREPROCESS_COMMAND_append  = " create_archive_ali_img; "
IMAGE_PREPROCESS_COMMAND_append = "${@bb.utils.contains('IMAGE_FSTYPES','ext4',' create_ali_ext4_img;','', d)}"

# Generating userdata image in EXT4
IMAGE_PREPROCESS_COMMAND_append  = " create_archive_usr_img; "
IMAGE_PREPROCESS_COMMAND_append = "${@bb.utils.contains('IMAGE_FSTYPES','ext4',' create_usr_ext4_img;','', d)}"

# Generating single UBI device to be mounted on system partition
# It Contains three UBI volumes for system, userdata and cache
IMAGE_PREPROCESS_COMMAND_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'nand-boot', 'create_ubi_img;', '', d)} "

IMAGE_PREPROCESS_COMMAND_remove = " ${@bb.utils.contains('DISTRO_FEATURES', 'nand-squashfs', 'create_ubi_img;', '', d)} "

# Root image is created now
clean_usr_rootfs() {
   rm -rf ${USR_IMAGE_ROOTFS}
   mkdir -p ${USR_IMAGE_ROOTFS}
}

# Remove unwanted headers and sources copied into rootfs
purge_rootfs() {
    rm -rf ${IMAGE_ROOTFS}/usr/include
    rm -rf ${IMAGE_ROOTFS}/usr/src
    rm -rf ${IMAGE_ROOTFS}/src
}

rename_img() {
   cp ${DEPLOY_DIR_IMAGE}/${IMAGE_LINK_NAME}.ext4 ${DEPLOY_DIR_IMAGE}/${SYSTEMIMAGE_TARGET}
}

symlink_modules() {
   LIB_MODULES="${IMAGE_ROOTFS}/lib/modules"
   USR_LIB_MODULES="${IMAGE_ROOTFS}/usr/lib/modules"

   DATA_DIR="${IMAGE_ROOTFS}/data"
   CONFIG_DIR="${DATA_DIR}/configs"
   LOGS_DIR="${DATA_DIR}/logs"

   if [ ! -d ${DATA_DIR} ]; then
       mkdir ${DATA_DIR}
   fi
   if [ ! -d ${CONFIG_DIR} ]; then
       mkdir ${CONFIG_DIR}
   fi
   if [ ! -d ${LOGS_DIR} ]; then
      mkdir ${LOGS_DIR}
   fi

   mv ${DATA_DIR}/* ${USR_IMAGE_ROOTFS}

   mkdir -p ${LIB_MODULES}
   mv ${LIB_MODULES} ${USR_LIB_MODULES}
   ln -sf /usr/lib/modules ${IMAGE_ROOTFS}/lib
}

sync_hostfs() {
   /bin/sync
}

create_usr_yaffs2_img() {
   mkyaffs2image ${USR_IMAGE_ROOTFS} ${OUTPUT_FILE_YAFFS}
   chmod 644 ${OUTPUT_FILE_YAFFS}
}

create_rootfs_config() {
    # stat all the files in rootfs and emit only the
    # <filename, uid, gid, mode(in hex)>
    cd ${IMAGE_ROOTFS} && \
        find . ! -path . -exec stat {} \
        --printf="%n %u %g %f\n" \; > ${DEPLOY_DIR_IMAGE}/system.canned.fsconfig \
        && cd -

    # remove the leading "./"
    sed -i 's#^\.\/##' ${DEPLOY_DIR_IMAGE}/system.canned.fsconfig
}

create_ubi_img() {
   if [ "${BASEPRODUCT}" == "robot" ] || [ "${BASEPRODUCT}" == "robot-rome" ]; then
       create_ubinize_config
       mkdir ${DEPLOY_DIR_IMAGE}/${MACHINE}.rootfs.ubi
       tar -cvzf ${DEPLOY_DIR_IMAGE}/${MACHINE}.rootfs.ubi.tgz -C ${IMAGE_ROOTFS} .
       tar -xvzf ${DEPLOY_DIR_IMAGE}/${MACHINE}.rootfs.ubi.tgz -C ${DEPLOY_DIR_IMAGE}/${MACHINE}.rootfs.ubi/
       sed -i -e 's:SELINUX=enforcing:SELINUX=disabled:' ${DEPLOY_DIR_IMAGE}/${MACHINE}.rootfs.ubi/etc/selinux/config
       mkfs.ubifs -r ${DEPLOY_DIR_IMAGE}/${MACHINE}.rootfs.ubi/  -o ${OUTPUT_FILE_SYSTEM_UBIFS} ${MKUBIFS_ARGS}
       mkfs.ubifs -r ${USR_IMAGE_ROOTFS} -o ${OUTPUT_FILE_USR_UBIFS} ${MKUBIFS_ARGS}
       ubinize -o ${OUTPUT_FILE_FINAL_UBI} ${UBINIZE_ARGS} ${UBINIZE_CFG}
       chmod 644 ${OUTPUT_FILE_FINAL_UBI}
       rm -rf ${DEPLOY_DIR_IMAGE}/${MACHINE}.rootfs.ubi
       rm -rf ${DEPLOY_DIR_IMAGE}/${MACHINE}.rootfs.ubi.tgz
   else
       # For selinux options in mkfs.ubifs
       IMAGE_UBIFS_SELINUX_OPTIONS="${@bb.utils.contains('DISTRO_FEATURES', 'selinux', '--selinux=${SELINUX_FILE_CONTEXTS}', '', d)}"

       # Nand targets use file-based OTA upgrade which needs to
       # correctly assign uid/gid/mode to the upgraded files.
       # Since we are running inside the fakeroot/pseudo environment,
       # we get a snapshot of  <filename, uid, gid, mode> mapping
       # here, which can then be fed to the canned-fs_config utility.
       create_rootfs_config

       create_ubinize_config
       mkfs.ubifs -r ${IMAGE_ROOTFS} ${IMAGE_UBIFS_SELINUX_OPTIONS} -o ${OUTPUT_FILE_SYSTEM_UBIFS} ${MKUBIFS_ARGS}
       mkfs.ubifs -r ${USR_IMAGE_ROOTFS} -o ${OUTPUT_FILE_USR_UBIFS} ${MKUBIFS_ARGS}
       ubinize -o ${OUTPUT_FILE_FINAL_UBI} ${UBINIZE_ARGS} ${UBINIZE_CFG}
       chmod 644 ${OUTPUT_FILE_FINAL_UBI}
   fi
}

create_archive_usr_img() {
   if [[ "${DISTRO_FEATURES}" =~ .*systemd.* ]] && [[ "${DISTRO_FEATURES}" =~ .*userfs-factory-reset.* ]]; then
       tar -zcvf ${IMAGE_ROOTFS}${sysconfdir}/${MACHINE}.usrfs.tar.gz -C ${USR_IMAGE_ROOTFS} .
   fi
}

create_ali_ext4_img() {
       mkdir -p ${DEPLOY_DIR_IMAGE_EMMC}
       make_ext4fs ${USRFS_FSCONFIG} ${MAKEEXT4_MOUNT_OPT} -s -l ${ALIDATA_SIZE_EXT4} ${OUTPUT_FILE_ALI_EXT4} ${USR_IMAGE_ROOTFS}
       chmod 644 ${OUTPUT_FILE_ALI_EXT4}
}

create_usr_ext4_img() {
       mkdir -p ${DEPLOY_DIR_IMAGE_EMMC}
       make_ext4fs ${USRFS_FSCONFIG} ${MAKEEXT4_MOUNT_OPT} -s -l ${USERDATA_SIZE_EXT4} ${OUTPUT_FILE_EXT4} ${USR_IMAGE_ROOTFS}
       chmod 644 ${OUTPUT_FILE_EXT4}
}

create_ubinize_config() {
   echo \[sysfs_volume\] > "${UBINIZE_CFG}"
   echo mode=ubi >> "${UBINIZE_CFG}"
   echo image="${OUTPUT_FILE_SYSTEM_UBIFS}" >> "${UBINIZE_CFG}"
   echo vol_id=0 >> "${UBINIZE_CFG}"
   echo vol_type=dynamic >> "${UBINIZE_CFG}"
   echo vol_name=rootfs >> "${UBINIZE_CFG}"
   echo vol_size="${SYSTEM_VOLUME_SIZE}" >> "${UBINIZE_CFG}"

   echo \[usrfs_volume\] >> "${UBINIZE_CFG}"
   echo mode=ubi >> "${UBINIZE_CFG}"
   echo image="${OUTPUT_FILE_USR_UBIFS}" >> "${UBINIZE_CFG}"
   echo vol_id=1 >> "${UBINIZE_CFG}"
   echo vol_type=dynamic >> "${UBINIZE_CFG}"
   echo vol_name=usrfs >> "${UBINIZE_CFG}"
   echo vol_flags = autoresize >> "${UBINIZE_CFG}"

   echo \[cache_volume\] >> "${UBINIZE_CFG}"
   echo mode=ubi >> "${UBINIZE_CFG}"
   echo vol_id=2 >> "${UBINIZE_CFG}"
   echo vol_type=dynamic >> "${UBINIZE_CFG}"
   echo vol_name=cachefs >> "${UBINIZE_CFG}"
   echo vol_size="${CACHE_VOLUME_SIZE}" >> "${UBINIZE_CFG}"

   echo \[systemrw_volume\] >> "${UBINIZE_CFG}"
   echo mode=ubi >> "${UBINIZE_CFG}"
   echo vol_id=3 >> "${UBINIZE_CFG}"
   echo vol_type=dynamic >> "${UBINIZE_CFG}"
   echo vol_name=systemrw >> "${UBINIZE_CFG}"
   echo vol_size="${SYSTEMRW_VOLUME_SIZE}" >> "${UBINIZE_CFG}"

   if [[ "${DISTRO_FEATURES}" =~ .*persist-volume.* ]]; then
    echo \[persist_volume\] >> "${UBINIZE_CFG}"
    echo mode=ubi >> "${UBINIZE_CFG}"
    if [[ "${DISTRO_FEATURES}" =~ .*persist-image.* ]]; then
      echo image="${OUTPUT_FILE_PERSIST_UBIFS}" >> "${UBINIZE_CFG}"
    fi
    echo vol_id=4 >> "${UBINIZE_CFG}"
    echo vol_type=dynamic >> "${UBINIZE_CFG}"
    echo vol_name=persist >> "${UBINIZE_CFG}"
    echo vol_size="${PERSIST_VOLUME_SIZE}" >> "${UBINIZE_CFG}"
   fi
}

