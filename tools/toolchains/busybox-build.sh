#!/bin/bash -x
# busybox-build.sh
# v1.0

. `dirname $0`/basic-build.sh

BUSYBOX_VERSION=1.25.0
BUSYBOX_NAME=busybox-$BUSYBOX_VERSION

# Downloads
download_archive https://busybox.net/downloads $BUSYBOX_NAME

# busybox
cd $BASEDIR

mkdir -p $TGT_DIR/$CROSS_TARGET/$BUSYBOX_NAME/{build,rootfs}
cd $TGT_DIR/$CROSS_TARGET/$BUSYBOX_NAME/build

DEFAULT_MAKE_OPTS="ARCH=$CROSS_ARCH CROSS_COMPILE=$CROSS_COMPILE $PARALLEL_BUILD_OPTS"

if [ ! -f .configure ]; then
    cp -av $BASEDIR/configs/busybox.config $PWD/.config || die "Unable to place default config";
    make $DEFAULT_MAKE_OPTS -C $SRC_DIR/$BUSYBOX_NAME O=$PWD oldconfig  || die "Unable to initiate busybox";
    touch .configure
fi

if [ ! -f .build ]; then
    make $DEFAULT_MAKE_OPTS all || die "Unable to build busybox image";
    touch .build
fi

if [ ! -f .install ]; then
    rm -rf $TGT_DIR/$CROSS_TARGET/$BUSYBOX_NAME/rootfs || die "Unable to clean busybox rootfs";
    
    mkdir $TGT_DIR/$CROSS_TARGET/$BUSYBOX_NAME/rootfs || die "Unable to create busybox rootfs base";
    make $DEFAULT_MAKE_OPTS CONFIG_PREFIX=$TGT_DIR/$CROSS_TARGET/$BUSYBOX_NAME/rootfs install || die "Unable to install busybox image";
    touch .install
fi

if [ ! -f .archive ]; then
    archive=$SUBMARINE_BUILD_DIR/busybox.tar.gz
    rm -rf $archive
    tar -C $TGT_DIR/$CROSS_TARGET/$BUSYBOX_NAME/ -cjf $archive rootfs || die "Unable to archive busybox install tree";
    touch .archive
fi

