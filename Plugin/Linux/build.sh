gcc -Wall \
    -O2 -fPIC -Wl,--gc-sections \
    -I../Unity \
    ../Plasma.cpp \
    -shared -o libPlasma.so
