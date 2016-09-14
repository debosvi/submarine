#!/bin/bash
# i686-elf-tools.sh
# v1.0

BINUTILS_VERSION=2.27
GCC_VERSION=6.2.0
GDB_VERSION=7.11
MPFR_VERSION=3.1.4
GMP_VERSION=6.1.1
MPC_VERSION=1.0.3
ISL_VERSION=0.17
NEWLIB_VERSION=2.4.0

BINUTILS_ARCHIVE=binutils-$BINUTILS_VERSION.tar.bz2
GCC_ARCHIVE=gcc-$GCC_VERSION.tar.bz2
GDB_ARCHIVE=gdb-$GDB_VERSION.tar.gz
MPFR_ARCHIVE=mpfr-$MPFR_VERSION.tar.bz2
GMP_ARCHIVE=gmp-$GMP_VERSION.tar.bz2
MPC_ARCHIVE=mpc-$MPC_VERSION.tar.gz
ISL_ARCHIVE=isl-$ISL_VERSION.tar.gz
NEWLIB_ARCHIVE=newlib-$NEWLIB_VERSION.tar.gz

set -e

BASEDIR=$PWD
DL_DIR=$BASEDIR/dl
SRC_DIR=$BASEDIR/src
TGT_DIR=$BASEDIR/target

# MXE

export PATH=$HOME/usr/bin:$PATH

# cd $BASEDIR
# git clone https://github.com/mxe/mxe.git
# cd mxe
# make gcc

function extract_archive {
    dir=`echo $1  | sed -e "s/^\(.*\)\.tar.*$/\1/g"`
    if [ ! -d $SRC_DIR/$dir ]; then
        mkdir -p $SRC_DIR
        tar -xvf $DL_DIR/$1 -C $SRC_DIR
    fi
}

function download_archive {
    archive=`basename $1`
    if [ ! -f $DL_DIR/$archive ]; then
        mkdir -p $DL_DIR
        wget -c $1 -O $DL_DIR/$archive
    fi
    extract_archive $archive
}

# Downloads

download_archive http://ftp.gnu.org/gnu/binutils/$BINUTILS_ARCHIVE
download_archive http://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/$GCC_ARCHIVE
download_archive http://ftp.gnu.org/gnu/gdb/$GDB_ARCHIVE
download_archive http://www.mpfr.org/mpfr-current/$MPFR_ARCHIVE
download_archive http://ftp.gnu.org/gnu/gmp/$GMP_ARCHIVE
download_archive http://ftp.gnu.org/gnu/mpc/$MPC_ARCHIVE
download_archive http://isl.gforge.inria.fr/$ISL_ARCHIVE
download_archive ftp://sourceware.org/pub/newlib/$NEWLIB_ARCHIVE


# Automatically download GMP, MPC and MPFR. These will be placed into the right directories.
# You can also download these separately, and specify their locations as arguments to ./configure
cd $SRC_DIR/gcc-$GCC_VERSION
rm -rfv mpfr gmp mpc isl
ln -sfn $SRC_DIR/mpfr-$MPFR_VERSION mpfr
ln -sfn $SRC_DIR/gmp-$GMP_VERSION gmp
ln -sfn $SRC_DIR/mpc-$MPC_VERSION mpc
ln -sfn $SRC_DIR/isl-$ISL_VERSION isl

TARGET=i686-elf

# Binutils
cd $BASEDIR
mkdir -p $TGT_DIR/$TARGET/binutils-$BINUTILS_VERSION
cd $TGT_DIR/$TARGET/binutils-$BINUTILS_VERSION
if [ ! -f .configure ]; then
    $SRC_DIR/binutils-$BINUTILS_VERSION/configure --prefix=$HOME/usr --target=$TARGET --with-sysroot --enable-interwork --enable-multilib --disable-nls --disable-werror
    touch .configure
fi
if [ ! -f .install ]; then
    make && make install
    touch .install
fi


# GCC
cd $BASEDIR
mkdir -p $TGT_DIR/$TARGET/gcc-$GCC_VERSION
cd $TGT_DIR/$TARGET/gcc-$GCC_VERSION
if [ ! -f .configure ]; then
    $SRC_DIR/gcc-$GCC_VERSION/configure --prefix=$HOME/usr --target=$TARGET --enable-interwork --enable-multilib --disable-nls --enable-languages=c,c++ --without-headers
    touch .configure
fi
if [ ! -f .install ]; then
    make all-gcc && make all-target-libgcc && make install-gcc && make install-target-libgcc
    touch .install
fi

# newlib
cd $BASEDIR
mkdir -p $TGT_DIR/$TARGET/newlib-$NEWLIB_VERSION
cd $TGT_DIR/$TARGET/newlib-$NEWLIB_VERSION
if [ ! -f .configure ]; then
    $SRC_DIR/newlib-$NEWLIB_VERSION/configure --prefix=$HOME/usr --target=$TARGET --enable-interwork --enable-multilib --disable-nls
    touch .configure
fi
if [ ! -f .install ]; then
    make all && make install
    touch .install
fi


# GDB
cd $BASEDIR
mkdir -p $TGT_DIR/$TARGET/gdb-$GDB_VERSION
cd $TGT_DIR/$TARGET/gdb-$GDB_VERSION
if [ ! -f .configure ]; then
    $SRC_DIR/gdb-$GDB_VERSION/configure --prefix=$HOME/usr --target=$TARGET --disable-nls --disable-werror
    touch .configure
fi
if [ ! -f .install ]; then
    make && make install
    touch .install
fi

