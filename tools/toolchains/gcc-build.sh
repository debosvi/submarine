#!/bin/bash -x
# cross-build.sh
# v1.0

. `dirname $0`/basic-build.sh


GCC_VERSION=6.2.0
MPFR_VERSION=3.1.5
GMP_VERSION=6.1.1
MPC_VERSION=1.0.3
ISL_VERSION=0.17
NEWLIB_VERSION=2.4.0

GCC_NAME=gcc-$GCC_VERSION
MPFR_NAME=mpfr-$MPFR_VERSION
GMP_NAME=gmp-$GMP_VERSION
MPC_NAME=mpc-$MPC_VERSION
ISL_NAME=isl-$ISL_VERSION
NEWLIB_NAME=newlib-$NEWLIB_VERSION


# Downloads

download_archive http://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION $GCC_NAME
download_archive http://www.mpfr.org/mpfr-current $MPFR_NAME
download_archive http://ftp.gnu.org/gnu/gmp $GMP_NAME
download_archive http://ftp.gnu.org/gnu/mpc $MPC_NAME
download_archive http://isl.gforge.inria.fr $ISL_NAME
download_archive https://github.com/openrisc/newlib/archive $NEWLIB_NAME


# Automatically download GMP, MPC and MPFR. These will be placed into the right directories.
# You can also download these separately, and specify their locations as arguments to ./configure
cd $SRC_DIR/gcc-$GCC_VERSION
rm -rfv mpfr gmp mpc isl newlib
ln -sfn $SRC_DIR/$MPFR_NAME mpfr
ln -sfn $SRC_DIR/$GMP_NAME gmp
ln -sfn $SRC_DIR/$MPC_NAME mpc
ln -sfn $SRC_DIR/$ISL_NAME isl
ln -sfn $SRC_DIR/$NEWLIB_NAME newlib


# GCC
cd $BASEDIR
mkdir -p $TGT_DIR/$CROSS_TARGET/$GCC_NAME
cd $TGT_DIR/$CROSS_TARGET/$GCC_NAME
if [ ! -f .configure ]; then
    $SRC_DIR/$GCC_NAME/configure --prefix=$INSTALL_PREFIX --target=$CROSS_TARGET \
        --enable-languages="c,c++" \
        --enable-threads=posix --disable-nls \
        --without-headers
    
    if [ $? -eq 1 ]; then  
        echo -e "GCC configure failed!" && exit 1
    fi
    touch .configure
fi

if [ ! -f .build ]; then
    make $PARALLEL_BUILD_OPTS all-gcc
    if [ $? -eq 1 ]; then  
        echo -e "GCC build failed!" && exit 1
    fi
    make $PARALLEL_BUILD_OPTS all-target-libgcc
    if [ $? -eq 1 ]; then  
        echo -e "GCC libgcc build failed!" && exit 1
    fi
    touch .build
fi
if [ ! -f .install ]; then
    make install-gcc
    if [ $? -eq 1 ]; then  
        echo -e "GCC install failed!" && exit 1
    fi
    make install-target-libgcc
    if [ $? -eq 1 ]; then  
        echo -e "GCC libgcc install failed!" && exit 1
    fi
    touch .install
fi
