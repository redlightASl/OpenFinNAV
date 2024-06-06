#!/bin/bash
echo "Script for downloading openocd Source"
cd ../../Toolchain

if [ ! -d "openocd" ]; then
    echo "Downloading openocd"
    git clone https://git.code.sf.net/p/openocd/code openocd
    if [ $? -ne 0 ]; then
        echo "Failed to clone openocd Source"
        exit 1
    else
        echo "openocd cloned successfully"
    fi
    cd ./openocd
    git submodule update
    ./bootstrap
    ./configure --enable-maintainer-mode --enable-ftdi --prefix=.
    make -j
    make install
else
    echo "openocd already exists"
fi
echo "Script for downloading openocd End"
