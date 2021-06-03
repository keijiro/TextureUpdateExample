#!/bin/sh

FLAGS="-O2 -Wall -shared"

x86_64-w64-mingw32-gcc $FLAGS ../Plasma.c -o Plasma.dll

x86_64-w64-mingw32-strip Plasma.dll
