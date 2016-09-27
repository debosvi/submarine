#!/bin/bash
# binutils-build.sh
# v1.0

. `dirname $0`/basic-build.sh


BINUTILS_VERSION=2.27
BINUTILS_NAME=binutils-$BINUTILS_VERSION

# Downloads
download_archive http://ftp.gnu.org/gnu/binutils $BINUTILS_NAME

# Binutils
cd $BASEDIR

mkdir -p $TGT_DIR/$CROSS_TARGET/$BINUTILS_NAME
cd $TGT_DIR/$CROSS_TARGET/$BINUTILS_NAME

if [ ! -f .configure ]; then
    $SRC_DIR/$BINUTILS_NAME/configure --prefix=$INSTALL_PREFIX --target=$CROSS_TARGET --with-sysroot --disable-multilib --disable-nls --disable-shared --disable-werror
    if [ $? -eq 1 ]; then  
        echo -e "Binutils configure failed!" && exit 1
    fi  
    touch .configure
fi

if [ ! -f .build ]; then
    make $PARALLEL_BUILD_OPTS
    if [ $? -eq 1 ]; then  
        echo -e "Binutils build failed!" && exit 1
    fi
    touch .build
fi

if [ ! -f .install ]; then
    make install
    if [ $? -eq 1 ]; then  
        echo -e "Binutils install failed!" && exit 1
    fi
    touch .install
fi
