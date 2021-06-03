#!/bin/sh

FLAGS="-O2 -Wall -shared -rdynamic -fPIC -std=c++11"

g++ -target x86_64-apple-macos10.12 $FLAGS ../Plasma.cpp -o x86_64.so
g++ -target  arm64-apple-macos10.12 $FLAGS ../Plasma.cpp -o arm64.so

lipo -create -output Plasma.bundle x86_64.so arm64.so
