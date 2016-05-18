#!/bin/bash

SCRIPTPATH=`dirname $0`
cd $SCRIPTPATH

QEMU_PATH=${QEMU_PATH:=qemu-2.5.0}
ML=${ML:=magic-lantern}
# copy and consume parameters, leave the remainder as arguments to qemu
CAM=$1
VER=$2
shift
shift
ML_PATH=../${ML}/platform/${CAM}.${VER}

make -C $QEMU_PATH || exit
make -C $ML_PATH || exit
make qemu-helper.bin -C $ML_PATH || exit
cp $ML_PATH/autoexec.bin .
cp $ML_PATH/qemu-helper.bin .
cp $ML_PATH/magiclantern .
cp $ML_PATH/${CAM}_${VER}.sym sdcard/ML/MODULES/${CAM}_${VER}.SYM

$QEMU_PATH/arm-softmmu/qemu-system-arm -M ML-${CAM} $*
