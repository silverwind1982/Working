#! /bin/sh

umount /AliDisk

mkfs.ext4 -F /dev/disk/by-partlabel/alidata

