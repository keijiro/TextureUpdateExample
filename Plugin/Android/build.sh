#!/bin/sh

BIN_PATH="$ANDROID_NDK_PATH/toolchains/llvm/prebuilt/linux-x86_64/bin"

CC="$BIN_PATH/aarch64-linux-android28-clang"
STRIP="$BIN_PATH/aarch64-linux-android-strip"

CCFLAGS="-O2 -Wall -shared -rdynamic -fPIC"

$CC $CCFLAGS ../Plasma.c -lm -o libPlasma.so
$STRIP libPlasma.so
