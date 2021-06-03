#!/bin/sh

FLAGS="-O2 -Wall -shared -rdynamic -fPIC"

gcc -target x86_64-apple-macos10.12 $FLAGS ../Plasma.c -o x86_64.so
gcc -target  arm64-apple-macos10.12 $FLAGS ../Plasma.c -o arm64.so

lipo -create -output Plasma.bundle x86_64.so arm64.so
