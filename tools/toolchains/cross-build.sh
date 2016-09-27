#!/bin/bash -x
# cross-build.sh
# v1.0

. `dirname $0`/basic-build.sh


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


# Downloads

download_archive http://ftp.gnu.org/gnu/binutils/$BINUTILS_ARCHIVE
download_archive http://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/$GCC_ARCHIVE
download_archive http://ftp.gnu.org/gnu/gdb/$GDB_ARCHIVE
download_archive http://www.mpfr.org/mpfr-current/$MPFR_ARCHIVE
download_archive http://ftp.gnu.org/gnu/gmp/$GMP_ARCHIVE
download_archive http://ftp.gnu.org/gnu/mpc/$MPC_ARCHIVE
download_archive http://isl.gforge.inria.fr/$ISL_ARCHIVE
download_archive https://github.com/openrisc/newlib/archive/$NEWLIB_ARCHIVE


# Automatically download GMP, MPC and MPFR. These will be placed into the right directories.
# You can also download these separately, and specify their locations as arguments to ./configure
cd $SRC_DIR/gcc-$GCC_VERSION
rm -rfv mpfr gmp mpc isl
ln -sfn $SRC_DIR/mpfr-$MPFR_VERSION mpfr
ln -sfn $SRC_DIR/gmp-$GMP_VERSION gmp
ln -sfn $SRC_DIR/mpc-$MPC_VERSION mpc
ln -sfn $SRC_DIR/isl-$ISL_VERSION isl
ln -sfn $SRC_DIR/newlib-$NEWLIB_VERSION newlib



# Binutils
cd $BASEDIR
mkdir -p $TGT_DIR/$CROSS_TARGET/binutils-$BINUTILS_VERSION
cd $TGT_DIR/$CROSS_TARGET/binutils-$BINUTILS_VERSION
if [ ! -f .configure ]; then
    $SRC_DIR/binutils-$BINUTILS_VERSION/configure --prefix=$INSTALL_PREFIX --target=$CROSS_TARGET --with-sysroot --disable-multilib --disable-nls --disable-shared --disable-werror
    if [ $? -eq 1 ]; then  
		echo -e "Binutils configure failed!" && exit 1
	fi
    touch .configure
fi
if [ ! -f .install ]; then
    make $PARALLEL_BUILD_OPTS
    if [ $? -eq 1 ]; then  
		echo -e "Binutils build failed!" && exit 1
    fi
    make install
    if [ $? -eq 1 ]; then  
		echo -e "Binutils install failed!" && exit 1
	fi
    touch .install
fi


# GCC
cd $BASEDIR
mkdir -p $TGT_DIR/$CROSS_TARGET/gcc-$GCC_VERSION
cd $TGT_DIR/$CROSS_TARGET/gcc-$GCC_VERSION
if [ ! -f .configure ]; then
    $SRC_DIR/gcc-$GCC_VERSION/configure --prefix=$INSTALL_PREFIX --target=$CROSS_TARGET \
		--enable-32bit --disable-64bit --enable-languages="c,c++" \
		--disable-multilib --disable-libssp --enable-threads=posix --disable-nls -disable-shared \
		--enable-checking=release --enable-lto --enable-version-specific-runtime-libs --without-headers
		
    if [ $? -eq 1 ]; then  
		echo -e "GCC configure failed!" && exit 1
    fi
    touch .configure
fi
if [ ! -f .install ]; then
    make $PARALLEL_BUILD_OPTS all-gcc
    if [ $? -eq 1 ]; then  
		echo -e "GCC build failed!" && exit 1
    fi
    make $PARALLEL_BUILD_OPTS all-target-libgcc
    if [ $? -eq 1 ]; then  
		echo -e "GCC libgcc build failed!" && exit 1
    fi
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

# newlib
#cd $BASEDIR
#mkdir -p $TGT_DIR/$CROSS_TARGET/newlib-$NEWLIB_VERSION
#cd $TGT_DIR/$CROSS_TARGET/newlib-$NEWLIB_VERSION
#if [ ! -f .configure ]; then
#    $SRC_DIR/newlib-$NEWLIB_VERSION/configure --prefix=$INSTALL_PREFIX --target=$CROSS_TARGET --enable-interwork --enable-multilib --disable-nls
#	if [ $? -eq 1 ]; then  
#		echo -e "newlib configure failed!" && exit 1
#    fi
#    touch .configure
#fi
#if [ ! -f .install ]; then
#    make $PARALLEL_BUILD_OPTS all
#	if [ $? -eq 1 ]; then  
#		echo -e "newlib build failed!" && exit 1
#    fi
#    make install
#	if [ $? -eq 1 ]; then  
#		echo -e "newlib install failed!" && exit 1
#    fi
#    touch .install
#fi
#

# GDB
cd $BASEDIR
mkdir -p $TGT_DIR/$CROSS_TARGET/gdb-$GDB_VERSION
cd $TGT_DIR/$CROSS_TARGET/gdb-$GDB_VERSION
if [ ! -f .configure ]; then
    $SRC_DIR/gdb-$GDB_VERSION/configure --prefix=$INSTALL_PREFIX --target=$CROSS_TARGET --disable-nls --disable-werror
	if [ $? -eq 1 ]; then  
		echo -e "GDB configure failed!" && exit 1
    fi
    touch .configure
fi
if [ ! -f .install ]; then
    make $PARALLEL_BUILD_OPTS
	if [ $? -eq 1 ]; then  
		echo -e "GDB build failed!" && exit 1
    fi
    make install
	if [ $? -eq 1 ]; then  
		echo -e "GDB install failed!" && exit 1
    fi
    touch .install
fi

