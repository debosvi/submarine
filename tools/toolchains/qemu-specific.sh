#!/bin/bash -x
# qemu-build.sh
# v1.0

. `dirname $0`/basic-build.sh

QEMU_VERSION=2.7.0
QEMU_NAME=qemu-$QEMU_VERSION

# Downloads
download_archive https://github.com/qemu/qemu/archive $QEMU_NAME

# kernel
cd $BASEDIR

mkdir -p $TGT_DIR/$CROSS_TARGET/$QEMU_NAME/build

DEFAULT_MAKE_OPTS="$PARALLEL_BUILD_OPTS"

cd $SRC_DIR/$QEMU_NAME 
if [ ! -f .patch ]; then
    patch -p1 -d. < $CONFIGS_DIR/can_pci.diff || die "Unable to patch qemu";
    touch .patch
fi

cd $TGT_DIR/$CROSS_TARGET/$QEMU_NAME/build
if [ ! -f .configure ]; then
    $SRC_DIR/$QEMU_NAME/configure --prefix=$INSTALL_PREFIX --target-list=i386-softmmu,i386-linux-user --enable-sdl   || die "Unable to configure qemu";
    touch .configure
fi

if [ ! -f .build ]; then
    make $DEFAULT_MAKE_OPTS || die "Unable to build qemu";
    touch .build
fi

if [ ! -f .install ]; then
    make $DEFAULT_MAKE_OPTS install || die "Unable to install qemu";
    touch .install
fi

