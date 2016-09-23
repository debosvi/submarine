#!/bin/bash
# kernel-build.sh
# v1.0

KERNEL_VERSION=4.3
KERNEL_NAME=linux-$KERNEL_VERSION
KERNEL_ARCHIVE=$KERNEL_NAME.tar.xz

NB_CPU=`grep -c ^processor /proc/cpuinfo`
export PARALLEL_BUILD_OPTS=-j$NB_CPU

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

download_archive https://www.kernel.org/pub/linux/kernel/v4.x/$KERNEL_ARCHIVE

## default i686
CROSS_TARGET=${CROSS_TARGET:-i686}
CROSS_COMPILE=$CROSS_TARGET-

# kernel
cd $BASEDIR
mkdir -p $TGT_DIR/$CROSS_TARGET/$KERNEL_NAME/{build,rootfs}

cd $TGT_DIR/$CROSS_TARGET/$KERNEL_NAME/build
if [ ! -f .configure ]; then
    cp -av $BASEDIR/configs/kernel.config $PWD/.config || die "Unable to place default config";
    make CROSS_COMPILE=$CROSS_COMPILE $PARALLEL_BUILD_OPTS -C $SRC_DIR/$KERNEL_NAME O=$PWD oldconfig  || die "Unable to initiate kernel";
    touch .configure
fi
if [ ! -f .build ]; then
    make CROSS_COMPILE=$CROSS_COMPILE $PARALLEL_BUILD_OPTS bzImage || die "Unable to build kernel image";
    make CROSS_COMPILE=$CROSS_COMPILE $PARALLEL_BUILD_OPTS modules || die "Unable to build kernel modules";
    touch .build
fi
if [ ! -f .install ]; then
    rm -rf $TGT_DIR/$CROSS_TARGET/$KERNEL_NAME/rootfs || die "Unable to clean kernel rootfs";
    
    mkdir $TGT_DIR/$CROSS_TARGET/$KERNEL_NAME/rootfs || die "Unable to create kernel rootfs base";
    make CROSS_COMPILE=$CROSS_COMPILE INSTALL_PATH=$TGT_DIR/$CROSS_TARGET/$KERNEL_NAME/rootfs install || die "Unable to install kernel image";
    make CROSS_COMPILE=$CROSS_COMPILE INSTALL_MOD_PATH=$TGT_DIR/$CROSS_TARGET/$KERNEL_NAME/rootfs modules_install || die "Unable to install kernel modules";
    rm -rfv $TGT_DIR/$CROSS_TARGET/$KERNEL_NAME/rootfs/lib/modules/$KERNEL_VERSION.0/{source,build} || die "Unable to clean build install modules tree";
    touch .install
fi
if [ ! -f .archive ]; then
    archive=$SUBMARINE_BUILD_DIR/kernel.tar.gz
    rm -rf $archive
    tar -C $TGT_DIR/$CROSS_TARGET/$KERNEL_NAME/ -cjf $archive rootfs || die "Unable to archive kernel install tree";
    touch .archive
fi

