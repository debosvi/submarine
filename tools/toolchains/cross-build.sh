#!/bin/bash -x
# cross-build.sh
# v1.0

. `dirname $0`/basic-build.sh

COMPILER_NAME=cross-compiler-$CROSS_ARCH

# Downloads
download_archive http://landley.net/aboriginal/downloads/binaries $COMPILER_NAME

ln -sfn $SRC_DIR/$COMPILER_NAME $SUBMARINE_SYSROOT_DIR