#!/bin/bash 

export SUBMARINE_PROJECT_DIR=$PWD
export SUBMARINE_BUILD_DIR=$SUBMARINE_PROJECT_DIR/build
export SUBMARINE_SYSROOT_DIR=$SUBMARINE_BUILD_DIR/usr
export ARCH=i686
export TARGET=i686
export PATH=$SUBMARINE_SYSROOT_DIR/bin:$PATH
# export NB_CPUS=1