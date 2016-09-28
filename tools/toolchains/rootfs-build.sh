#!/bin/bash
# rootfs-build.sh
# v1.0

. `dirname $0`/basic-build.sh

KERNEL_ARCHIVE=kernel.tar.gz
BUSYBOX_ARCHIVE=busybox.tar.gz
TOYBOX_ARCHIVE=toybox.tar.gz

# rootfs
cd $BASEDIR

# prepare output dirs
mkdir -p $IMG_DIR || die "Unable to create images dir";
rm -rf $RFS_DIR
mkdir -p $RFS_DIR || die "Unable to create rootfs dir";

# get cross compiler
$(dirname $0)/cross-build.sh

# build components
$(dirname $0)/busybox-build.sh
$(dirname $0)/toybox-build.sh
$(dirname $0)/kernel-build.sh

cd $RFS_DIR

# copy skeleton with tar
tar --exclude=.empty -C $BASEDIR/configs/rootfs/ -cpf - . | tar -C $RFS_DIR -xf -

# extract built archives rootfs (busybox, toybox, kernel)
if [ -f $SUBMARINE_BUILD_DIR/$KERNEL_ARCHIVE ]; then
    tar -xf $SUBMARINE_BUILD_DIR/$KERNEL_ARCHIVE --strip-components=1 rootfs/lib || die "Unable to extract kernel modules";
    IMG=$(tar -tf $SUBMARINE_BUILD_DIR/$KERNEL_ARCHIVE | grep vmlinuz | xargs basename)
    tar -C $IMG_DIR -xf $SUBMARINE_BUILD_DIR/$KERNEL_ARCHIVE --strip-components=1 rootfs/$IMG || die "Unable to extract kernel image";
    mv $IMG_DIR/$IMG $IMG_DIR/vmlinuz
fi

if [ -f $SUBMARINE_BUILD_DIR/$BUSYBOX_ARCHIVE ]; then
    tar --exclude=linuxrc -xf $SUBMARINE_BUILD_DIR/$BUSYBOX_ARCHIVE --strip-components=1 || die "Unable to extract busybox built archive";
fi

if [ -f $SUBMARINE_BUILD_DIR/$TOYBOX_ARCHIVE ]; then
    tar -xf $SUBMARINE_BUILD_DIR/$TOYBOX_ARCHIVE --strip-components=1 || die "Unable to extract toybox built archive";
fi

# create initramfs
cd $RFS_DIR
find . | cpio --create --'format=newc' | gzip  > $IMG_DIR/$ROOTFS_INITRD.gz

# mksquashfs $RFS_DIR $IMG_DIR/hda.sqf -noappend -always-use-fragments



