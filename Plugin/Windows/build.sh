#!/bin/sh
x86_64-w64-mingw32-gcc -O2 -Wall -shared ../Plasma.c -o Plasma.dll
x86_64-w64-mingw32-strip Plasma.dll
