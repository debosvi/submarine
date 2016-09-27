#!/bin/bash
# kernel_headers-build.sh
# v1.0

. `dirname $0`/basic-build.sh

KERNEL_BRANCH=v4.x
KERNEL_VERSION=4.3
KERNEL_NAME=linux-$KERNEL_VERSION

# Downloads
download_archive https://www.kernel.org/pub/linux/kernel/$KERNEL_BRANCH $KERNEL_NAME

# kernel
cd $BASEDIR

mkdir -p $TGT_DIR/$CROSS_TARGET/$KERNEL_NAME
cd $TGT_DIR/$CROSS_TARGET/$KERNEL_NAME

if [ ! -f .configure ]; then
    cp -av $BASEDIR/configs/kernel.config $PWD/.config || die "Unable to place default config";
    make ARCH=$CROSS_ARCH CROSS_COMPILE=$CROSS_COMPILE $PARALLEL_BUILD_OPTS -C $SRC_DIR/$KERNEL_NAME O=$PWD oldconfig  || die "Unable to initiate kernel";
    touch .configure
fi

if [ ! -f .install ]; then
    make INSTALL_HDR_PATH=$SUBMARINE_SYSROOT_DIR headers_install || die "Unable to install kernel headers";
    touch .install
fi

