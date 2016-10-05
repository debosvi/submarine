#!/bin/bash -x
# rootfs-build.sh
# v1.0

. `dirname $0`/basic-build.sh

cd $IMG_DIR

#qemu-system-i386 -m 128 -nographic -kernel ./vmlinuz -initrd $ROOTFS_INITRD.gz \
#    -net nic,model=e1000 -net tap,ifname=tap0,script=no,downscript=no \
#    -device kvaser_pci,canbus=canbus0,host=vcan0\
#    -append "panic=1 console=ttyS0 HOST=SUBMARINE"

INSTANCE=$1

if [ "$INSTANCE" == "" ]; then
	die "Usage: $0 <NB>"
fi

NB=$(echo 10+$INSTANCE | bc -l)

qemu-system-i386 -m 128 -nographic -kernel ./vmlinuz -initrd $ROOTFS_INITRD.gz \
    -net nic,model=e1000,macaddr=52:54:00:12:34:$NB -net socket,mcast=230.0.0.1:1234 \
    -append "panic=1 console=ttyS0 HOST=SUBMARINE EXPECTED_IP=10.0.2.$NB"
