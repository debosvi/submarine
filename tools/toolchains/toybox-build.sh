#!/bin/bash -x
# toybox-build.sh
# v1.0

. `dirname $0`/basic-build.sh

TOYBOX_VERSION=0.7.1
TOYBOX_NAME=toybox-$TOYBOX_VERSION

# Downloads
download_archive https://www.landley.net/toybox/downloads $TOYBOX_NAME

# toybox
cd $BASEDIR

mkdir -p $TGT_DIR/$CROSS_TARGET/$TOYBOX_NAME/{build,rootfs}
cd $TGT_DIR/$CROSS_TARGET/$TOYBOX_NAME/build

DEFAULT_MAKE_OPTS="ARCH=$CROSS_ARCH CROSS_COMPILE=$CROSS_COMPILE $PARALLEL_BUILD_OPTS"

if [ ! -f .configure ]; then
    cp -av $BASEDIR/configs/toybox.config $SRC_DIR/$TOYBOX_NAME/.config || die "Unable to place default config";
    make $DEFAULT_MAKE_OPTS -C $SRC_DIR/$TOYBOX_NAME oldconfig  || die "Unable to initiate toybox";
    touch .configure
fi
if [ ! -f .build ]; then
    CFLAGS="--static" make $DEFAULT_MAKE_OPTS -C $SRC_DIR/$TOYBOX_NAME  toybox|| die "Unable to build toybox image";
    touch .build
fi
if [ ! -f .install ]; then
    rm -rf $TGT_DIR/$CROSS_TARGET/$TOYBOX_NAME/rootfs || die "Unable to clean toybox rootfs";
    
    mkdir $TGT_DIR/$CROSS_TARGET/$TOYBOX_NAME/rootfs || die "Unable to create toybox rootfs base";
    make $DEFAULT_MAKE_OPTS -C $SRC_DIR/$TOYBOX_NAME PREFIX=$TGT_DIR/$CROSS_TARGET/$TOYBOX_NAME/rootfs install || die "Unable to install toybox image";
    touch .install
fi
if [ ! -f .archive ]; then
    archive=$SUBMARINE_BUILD_DIR/toybox.tar.gz
    rm -rf $archive
    tar -C $TGT_DIR/$CROSS_TARGET/$TOYBOX_NAME/ -cjf $archive rootfs || die "Unable to archive toybox install tree";
    touch .archive
fi

