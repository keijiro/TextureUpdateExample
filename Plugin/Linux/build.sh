#!/bin/sh

FLAGS="-O2 -Wall -shared -rdynamic -fPIC"

gcc $FLAGS ../Plasma.c -o libPlasma.so
