#!/bin/bash -x
# toybox-build.sh
# v1.0
TOYBOX_VERSION=0.7.1
TOYBOX_NAME=toybox-$TOYBOX_VERSION
TOYBOX_ARCHIVE=$TOYBOX_NAME.tar.gz

NB_CPU=`grep -c ^processor /proc/cpuinfo`
# export PARALLEL_BUILD_OPTS=-j$NB_CPU

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
RFS_DIR=$SUBMARINE_BUILD_DIR/rootfs
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
    archive=`basename $1`
    url=`echo $1 | sed -e "s/^\(.*\)\/.*$/\1/g"`
    ver=`echo $1 | cut -d"-" -f2-`
    if [ ! -f $DL_DIR/$archive ]; then
        mkdir -p $DL_DIR
	echo -e "Download $archive"
        wget --spider -q $1 &&
			wget -c $1 -O $DL_DIR/$archive || 
			wget -c $url/v$ver -O $DL_DIR/$archive || exit 1
    fi
    extract_archive $archive
}

# Downloads

download_archive https://www.landley.net/toybox/downloads/$TOYBOX_ARCHIVE

## for qemu i686
ARCH=i686
TARGET=i686-pc-linux
## for qemu PIC32
# TARGET=mipsel-elf32

# toybox
cd $BASEDIR
mkdir -p $TGT_DIR/$TARGET/$TOYBOX_NAME/{build,rootfs}

cd $TGT_DIR/$TARGET/$TOYBOX_NAME/build
if [ ! -f .configure ]; then
    cp -av $BASEDIR/configs/toybox.config $SRC_DIR/$TOYBOX_NAME/.config || die "Unable to place default config";
    make $PARALLEL_BUILD_OPTS -C $SRC_DIR/$TOYBOX_NAME oldconfig  || die "Unable to initiate toybox";
    touch .configure
fi
if [ ! -f .build ]; then
    CFLAGS="--static" make $PARALLEL_BUILD_OPTS -C $SRC_DIR/$TOYBOX_NAME  toybox|| die "Unable to build toybox image";
    touch .build
fi
if [ ! -f .install ]; then
    rm -rf $TGT_DIR/$TARGET/$TOYBOX_NAME/rootfs || die "Unable to clean toybox rootfs";
    
    mkdir $TGT_DIR/$TARGET/$TOYBOX_NAME/rootfs || die "Unable to create toybox rootfs base";
    make $PARALLEL_BUILD_OPTS -C $SRC_DIR/$TOYBOX_NAME PREFIX=$TGT_DIR/$TARGET/$TOYBOX_NAME/rootfs install || die "Unable to install toybox image";
    touch .install
fi
if [ ! -f .archive ]; then
    archive=$SUBMARINE_BUILD_DIR/toybox.tar.gz
    rm -rf $archive
    tar -C $TGT_DIR/$TARGET/$TOYBOX_NAME/ -cjf $archive rootfs || die "Unable to archive toybox install tree";
    touch .archive
fi

