#!/bin/bash
echo "Script for downloading GNU Toolchain"
cd ../../Toolchain

if [ ! -d "gcc" ]; then
    echo "Downloading Toolchain"
    mkdir -p gcc
    cd gcc
    if [[ "$1" = "linux" ]]; then
        echo "Linux Host"
        wget -c https://developer.arm.com/-/media/Files/downloads/gnu/13.2.rel1/binrel/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz
        xz -d "arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz"
        tar -xvf "arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar"
    elif [[ "$1" = "windows" ]]; then
        echo "Windows Host"
        wget -c https://developer.arm.com/-/media/Files/downloads/gnu/13.2.rel1/binrel/arm-gnu-toolchain-13.2.rel1-mingw-w64-i686-arm-none-eabi.zip
        unzip "arm-gnu-toolchain-13.2.rel1-mingw-w64-i686-arm-none-eabi.zip"
    else
        echo "Unknown Host"
    fi
else
    echo "Toolchain already exists"
fi

echo "Script for downloading GNU Toolchain End"
