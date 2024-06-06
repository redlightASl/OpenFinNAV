#!/bin/bash
echo "Script for downloading RT-Thread Kernel"
cd ../../Kernel

if [ ! -d "RTT/.git" ]; then
    git clone https://gitee.com/rtthread/rt-thread.git RTT
    if [ $? -ne 0 ]; then
        echo "Failed to clone RT-Thread Kernel"
        exit 1
    else
        echo "RT-Thread Kernel cloned successfully"
    fi
else
    echo "RTT already exists"
fi

echo "Script for downloading RT-Thread End"
