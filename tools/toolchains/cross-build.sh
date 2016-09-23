#!/bin/bash -x
# cross-build.sh
# v1.0

ABORIGINAL_VERSION=1.4.5
ABORIGINAL_NAME=aboriginal-$ABORIGINAL_VERSION

NB_CPU=`grep -c ^processor /proc/cpuinfo`
#export PARALLEL_BUILD_OPTS=-j$NB_CPU
export PARALLEL_BUILD_OPTS=-j2

set -e

if [ "$SUBMARINE_PROJECT_DIR" == "" ]; then
    echo -e "Must init project environment"
    echo -e "Must set env SUBMARINE_PROJECT_DIR variable"
    exit 1
fi

if [ "$SUBMARINE_SYSROOT_DIR" == "" ]; then
    echo -e "Must set env SUBMARINE_SYSROOT_DIR variable"
    exit 1
fi

if [ "$SUBMARINE_BUILD_DIR" == "" ]; then
    echo -e "Must set env SUBMARINE_BUILD_DIR variable"
    exit 1
fi

BASEDIR=$SUBMARINE_PROJECT_DIR
DL_DIR=$BASEDIR/dl
SRC_DIR=$SUBMARINE_BUILD_DIR/toolchains/src
TGT_DIR=$SUBMARINE_BUILD_DIR/toolchains/target
INSTALL_PREFIX=$SUBMARINE_SYSROOT_DIR

function die {
	echo -e $1
	exit 1
} 

function extract_archive {
	dir=`echo $1  | sed -e "s/^\(.*\)\.tar.*$/\1/g"`
   if [ ! -d $SRC_DIR/$dir ]; then
		mkdir -p $SRC_DIR
		echo -e "Extract $dir"
		tar -xf $DL_DIR/$1 -C $SRC_DIR
	fi
}

function download_archive {
	url=$1
	name=$2
	ver=`echo $name | cut -d"-" -f2-`
	if wget --spider -q $url/$name.tar.xz; then 
		archive=$name.tar.xz
	elif wget --spider -q $url/v$ver.tar.xz; then 
		archive=v$ver.tar.xz
	elif wget --spider -q $url/$name.tar.bz2; then 
		archive=$name.tar.bz2
	elif wget --spider -q $url/v$ver.tar.bz2; then 
		archive=v$ver.tar.bz2
	elif wget --spider -q $url/$name.tar.gz; then 
		archive=$name.tar.gz
	elif wget --spider -q $url/v$ver.tar.gz; then 
		archive=v$ver.tar.gz
	else
		die "No archive to be found!!"
	fi
	if [ ! -f $DL_DIR/.dl_$name ]; then
		mkdir -p $DL_DIR
		echo -e "Download $name"
		
		wget -q -c $url/$archive -O $DL_DIR/$archive || die "No archive downloaded!!"
		touch $DL_DIR/.dl_$name
	fi
	extract_archive $archive
}

# Downloads

download_archive http://landley.net/aboriginal/downloads $ABORIGINAL_NAME

## default i686
CROSS_TARGET=${CROSS_TARGET:-i686}

# Binutils
# cd $BASEDIR
cd $SRC_DIR/$ABORIGINAL_NAME
if [ ! -f .build ]; then
	cp -av $BASEDIR/configs/aboriginal.config config
 	./download.sh $CROSS_TARGET || die "Aboriginal toolchain download failed!"
	./host-tools.sh || die "Aboriginal toolchain host tools build failed!"
	./simple-cross-compiler.sh $CROSS_TARGET || die "Aboriginal toolchain build failed!"
	touch .build
fi

if [ ! -f $SUBMARINE_SYSROOT_DIR/.install ]; then
	mkdir $SUBMARINE_SYSROOT_DIR
	tar -xf build/simple-cross-compiler-$CROSS_TARGET.tar.gz -C $SUBMARINE_SYSROOT_DIR --strip-components=1 || die "Aboriginal not ready to use!"
	touch $SUBMARINE_SYSROOT_DIR/.install
fi
