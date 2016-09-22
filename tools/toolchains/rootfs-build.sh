#!/bin/bash
# rootfs-build.sh
# v1.0

KERNEL_ARCHIVE=kernel.tar.gz
BUSYBOX_ARCHIVE=busybox.tar.gz
TOYBOX_ARCHIVE=toybox.tar.gz

NB_CPU=`grep -c ^processor /proc/cpuinfo`
export PARALLEL_BUILD_OPTS=-j$NB_CPU

set -e

if [ "$SUBMARINE_PROJECT_DIR" == "" ]; then
    echo -e "Must init project environment"
    echo -e "Must set env SUBMARINE_PROJECT_DIR variable"
    exit 1
fi

if [ "$SUBMARINE_SYSROOT_DIR" == "" ]; then
    echo -e "Must set env SUBMARINE_SYSROOT_DIR variable"
    exit 1
fi

if [ "$SUBMARINE_BUILD_DIR" == "" ]; then
    echo -e "Must set env SUBMARINE_BUILD_DIR variable"
    exit 1
fi

BASEDIR=$SUBMARINE_PROJECT_DIR
DL_DIR=$BASEDIR/dl
RFS_DIR=$SUBMARINE_BUILD_DIR/rootfs
IMG_DIR=$SUBMARINE_BUILD_DIR/images
SRC_DIR=$SUBMARINE_BUILD_DIR/toolchains/src
TGT_DIR=$SUBMARINE_BUILD_DIR/toolchains/target
INSTALL_PREFIX=$SUBMARINE_SYSROOT_DIR

function die {
	echo -e $1
	exit 1
}

# rootfs
cd $BASEDIR

mkdir -p $IMG_DIR || die "Unable to create images dir";

rm -rf $RFS_DIR
mkdir -p $RFS_DIR || die "Unable to create rootfs dir";

cd $RFS_DIR

tar --exclude=.empty -C $BASEDIR/configs/rootfs/ -cpf - . | tar -C $RFS_DIR -xf -

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

mksquashfs $RFS_DIR $IMG_DIR/hda.sqf -noappend -always-use-fragments
