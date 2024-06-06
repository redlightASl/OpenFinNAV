#!/bin/bash
echo "Script for downloading FreeRTOS Kernel"
cd ../../Kernel

if [ ! -d "FreeRTOS/.git" ]; then
    git clone https://github.com/FreeRTOS/FreeRTOS-Kernel FreeRTOS
    if [ $? -ne 0 ]; then
        echo "Failed to clone FreeRTOS Kernel"
        exit 1
    else
        echo "FreeRTOS Kernel cloned successfully"
    fi
else
    echo "FreeRTOS already exists"
fi

echo "Script for downloading FreeRTOS Kernel End"
