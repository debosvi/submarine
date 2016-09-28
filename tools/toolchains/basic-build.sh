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
RFS_DIR=$SUBMARINE_BUILD_DIR/ramfs
HDA_DIR=$SUBMARINE_BUILD_DIR/rootfs
IMG_DIR=$SUBMARINE_BUILD_DIR/images
INSTALL_PREFIX=$SUBMARINE_SYSROOT_DIR

ROOTFS_INITRD=rootfs.cpio

function die {
    echo -e $1
    exit 1
}

function extract_archive {
    name=$1
    archive=`cat $DL_DIR/.dl_$name`
    ext=`echo $archive | cut -d. -f2-`
    if [ ! -d $SRC_DIR/$name ]; then
        mkdir -p $SRC_DIR
        echo -e "Extract $name"
        if [ "$ext" == "zip" ]; then
            unzip -o $DL_DIR/$archive -d $SRC_DIR
        else
            tar -xf $DL_DIR/$archive -C $SRC_DIR
        fi
    fi
}

function download_archive {
    url=$1
    name=$2
    ver=`echo $name | cut -d"-" -f2-`
    archive=
    output=
    
    if [ ! -f $DL_DIR/.dl_$name ]; then
        if wget --spider -q $url/$name.tar.xz; then
            archive=$name.tar.xz
            output=$name.tar.xz
        elif wget --spider -q $url/v$ver.tar.xz; then
            archive=v$ver.tar.xz
            output=$name.tar.xz
        elif wget --spider -q $url/$name.tar.bz2; then
            archive=$name.tar.bz2
            output=$name.tar.bz2
        elif wget --spider -q $url/v$ver.tar.bz2; then
            archive=v$ver.tar.bz2
            output=$name.tar.bz2
        elif wget --spider -q $url/$name.tar.gz; then
            archive=$name.tar.gz
            output=$name.tar.gz
        elif wget --spider -q $url/v$ver.tar.gz; then
            archive=v$ver.tar.gz
            output=$name.tar.gz
        elif wget --spider -q $url/master.zip; then
            archive=master.zip
            output=$name.zip
        fi
        
        if [ $archive ]; then
            mkdir -p $DL_DIR
            echo -e "Download $archive"
            wget -c $url/$archive -O $DL_DIR/$output || die "Unable to download $archive"
            echo $output > $DL_DIR/.dl_$name
        fi
        
    else
        archive=$(cat $DL_DIR/.dl_$name)
    fi
        
    extract_archive $name
}
