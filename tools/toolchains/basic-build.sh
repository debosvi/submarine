#!/bin/bash
# basic-build.sh
# v1.0


if [ -z $NB_CPUS ]; then 
	NB_CPUS=`grep -c ^processor /proc/cpuinfo`
fi

export PARALLEL_BUILD_OPTS=-j$NB_CPUS

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


## default i686
CROSS_ARCH=${ARCH:-i686}
CROSS_TARGET=${TARGET:-i686}
CROSS_COMPILE=$CROSS_TARGET-

## local vars
BASEDIR=$SUBMARINE_PROJECT_DIR
DL_DIR=$BASEDIR/dl
SRC_DIR=$SUBMARINE_BUILD_DIR/toolchains/src
TGT_DIR=$SUBMARINE_BUILD_DIR/toolchains/target
RFS_DIR=$SUBMARINE_BUILD_DIR/rootfs
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
    archive=
    
    if [ ! -f $DL_DIR/.dl_$name ]; then
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
        fi
        
        if [ $archive ]; then
            mkdir -p $DL_DIR
            echo -e "Download $archive"
            wget -c $url/$archive -O $DL_DIR/$archive || die "Unable to download $archive"
        fi
        touch $DL_DIR/.dl_$name
    fi
        
    extract_archive $archive
}
