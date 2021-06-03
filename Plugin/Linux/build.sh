gcc -Wall \
    -O2 -rdynamic -fPIC -Wl,--gc-sections \
    -I../Unity \
    ../Plasma.c \
    -shared -o libPlasma.so
