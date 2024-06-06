#!/bin/sh

if [[ $(pwd) == *"build/script"* ]]; then
    echo "Excute this file in the root of the project"
    exit 1
fi

make clean
make build
