#!/bin/bash

lspci > lspci.new

diff lspci.new lspci.orig

if [ $? -eq 0 ]; then
        echo "lspci is correct"
else
        echo "lspci is abnormal, stop reboot for debug"
        lspci
        exit 1
fi

echo "sleep 10 secs before reboot"
sleep 10
reboot
