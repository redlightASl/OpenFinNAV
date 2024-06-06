#!/bin/bash
echo "Script for downloading LiteOS Kernel"
cd ../../Kernel

if [ ! -d "LiteOS/.git" ]; then
    git clone https://gitee.com/LiteOS/LiteOS.git LiteOS
    if [ $? -ne 0 ]; then
        echo "Failed to clone LiteOS Kernel"
        exit 1
    else
        echo "LiteOS Kernel cloned successfully"
    fi
else
    echo "LiteOS already exists"
fi

echo "Script for downloading LiteOS Kernel End"
