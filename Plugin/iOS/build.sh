#!/bin/sh

SYSROOT=`xcrun --sdk iphoneos --show-sdk-path`
FLAGS="-O2 -Wall --sysroot $SYSROOT -isysroot $SYSROOT -fembed-bitcode"

gcc $FLAGS -c ../Plasma.c

ar -crv libPlasma.a Plasma.o
