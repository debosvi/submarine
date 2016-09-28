#!/bin/bash -x
# kernel-build.sh
# v1.0

. `dirname $0`/basic-build.sh

KERNEL_BRANCH=v4.x
KERNEL_VERSION=4.3
KERNEL_NAME=linux-$KERNEL_VERSION


# Downloads

download_archive https://www.kernel.org/pub/linux/kernel/$KERNEL_BRANCH $KERNEL_NAME

# kernel
cd $BASEDIR

mkdir -p $TGT_DIR/$CROSS_TARGET/$KERNEL_NAME/{build,rootfs}
cd $TGT_DIR/$CROSS_TARGET/$KERNEL_NAME/build

DEFAULT_MAKE_OPTS="ARCH=x86 CROSS_COMPILE=$CROSS_COMPILE $PARALLEL_BUILD_OPTS"

if [ ! -f .configure ]; then
    cp -av $BASEDIR/configs/kernel.config $PWD/.config || die "Unable to place default config";
    make $DEFAULT_MAKE_OPTS -C $SRC_DIR/$KERNEL_NAME O=$PWD oldconfig  || die "Unable to initiate kernel";
    touch .configure
fi
if [ ! -f .build ]; then
    make $DEFAULT_MAKE_OPTS bzImage || die "Unable to build kernel image";
    make $DEFAULT_MAKE_OPTS modules || die "Unable to build kernel modules";
    touch .build
fi
if [ ! -f .install ]; then
    rm -rf $TGT_DIR/$CROSS_TARGET/$KERNEL_NAME/rootfs || die "Unable to clean kernel rootfs";
    
    mkdir $TGT_DIR/$CROSS_TARGET/$KERNEL_NAME/rootfs || die "Unable to create kernel rootfs base";
    make $DEFAULT_MAKE_OPTS INSTALL_PATH=$TGT_DIR/$CROSS_TARGET/$KERNEL_NAME/rootfs install || die "Unable to install kernel image";
    make $DEFAULT_MAKE_OPTS INSTALL_MOD_PATH=$TGT_DIR/$CROSS_TARGET/$KERNEL_NAME/rootfs modules_install || die "Unable to install kernel modules";
    rm -rfv $TGT_DIR/$CROSS_TARGET/$KERNEL_NAME/rootfs/lib/modules/$KERNEL_VERSION.0/{source,build} || die "Unable to clean build install modules tree";
    touch .install
fi

if [ ! -f .archive ]; then
    archive=$SUBMARINE_BUILD_DIR/kernel.tar.gz
    rm -rf $archive
    tar -C $TGT_DIR/$CROSS_TARGET/$KERNEL_NAME/ -cjf $archive rootfs || die "Unable to archive kernel install tree";
    touch .archive
fi

