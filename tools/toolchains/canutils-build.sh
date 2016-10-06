#!/bin/bash
# canutils-build.sh
# v1.0

. `dirname $0`/basic-build.sh

CANUTILS_VERSION=master
CANUTILS_NAME=can-utils-$CANUTILS_VERSION

# Downloads
download_archive https://github.com/linux-can/can-utils/archive $CANUTILS_NAME

# can-utils
cd $BASEDIR

mkdir -p $TGT_DIR/$CROSS_TARGET/$CANUTILS_NAME/{build,rootfs}
cd $TGT_DIR/$CROSS_TARGET/$CANUTILS_NAME/build

DEFAULT_MAKE_OPTS="$PARALLEL_BUILD_OPTS"

pushd $SRC_DIR/$CANUTILS_NAME
if [ ! -f configure ]; then
    ./autogen.sh || die "Unable to generate configure file for can-utils";
fi
popd

if [ ! -f .configure ]; then
    $SRC_DIR/$CANUTILS_NAME/configure --host=$CROSS_ARCH --disable-shared --prefix=$TGT_DIR/$CROSS_TARGET/$CANUTILS_NAME/rootfs || die "Unable to configure can-utils";
    touch .configure
fi

if [ ! -f .build ]; then
    make $DEFAULT_MAKE_OPTS all || die "Unable to build can-utils image";
    touch .build
fi

if [ ! -f .install ]; then
    rm -rf $TGT_DIR/$CROSS_TARGET/$CANUTILS_NAME/rootfs || die "Unable to clean can-utils rootfs";
    mkdir $TGT_DIR/$CROSS_TARGET/$CANUTILS_NAME/rootfs || die "Unable to create can-utils rootfs base";
    make $DEFAULT_MAKE_OPTS install-strip || die "Unable to install can-utils image";
    touch .install
fi

if [ ! -f .archive ]; then
    archive=$SUBMARINE_BUILD_DIR/can-utils.tar.gz
    rm -rf $archive
    tar -C $TGT_DIR/$CROSS_TARGET/$CANUTILS_NAME/ -cjf $archive rootfs || die "Unable to archive can-utils install tree";
    touch .archive
fi

