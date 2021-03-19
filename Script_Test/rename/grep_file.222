#! /bin/bash
set -e

KERNEL_CMDLINE="./cmdline"

if $(grep -q "androidboot.slot_suffix=_a" ${KERNEL_CMDLINE}); then
  echo "Found search_string. a"
elif $(grep -q "androidboot.slot_suffix=_b" ${KERNEL_CMDLINE}); then
  echo "Found search_string. b"
else
  echo "Incorrect slot was detected in ${KERNEL_CMDLINE}."
fi


exit 0
