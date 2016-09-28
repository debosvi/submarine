#!/bin/bash
# rootfs-build.sh
# v1.0

. `dirname $0`/basic-build.sh

cd $IMG_DIR

qemu-system-i386 -m 128 -nographic -kernel ./vmlinuz -initrd $ROOTFS_INITRD.gz \
    -net nic,model=e1000 -net user \
    -append "panic=1 console=ttyS0 HOST=SUBMARINE"
