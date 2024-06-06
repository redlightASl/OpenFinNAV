######################################
# RT-Thread Make file include
######################################

# RTOS support
OS_INC := \
-I$(FINNAV_KERNEL_DIR)/RTT/include \
-I$(FINNAV_KERNEL_DIR)/RTT/libcpu/arm/common \
-I$(FINNAV_KERNEL_DIR)/RTT/libcpu/arm/cortex-m7 \
-I$(FINNAV_KERNEL_DIR)/CMSIS_RTOS/RTT

# $(FINNAV_KERNEL_DIR)/RTT/components/legacy

OS_SRC := \
$(FINNAV_KERNEL_DIR)/RTT/src/clock.c \
$(FINNAV_KERNEL_DIR)/RTT/src/components.c \
$(FINNAV_KERNEL_DIR)/RTT/src/cpu.c \
$(FINNAV_KERNEL_DIR)/RTT/src/idle.c \
$(FINNAV_KERNEL_DIR)/RTT/src/ipc.c \
$(FINNAV_KERNEL_DIR)/RTT/src/irq.c \
$(FINNAV_KERNEL_DIR)/RTT/src/kservice.c \
$(FINNAV_KERNEL_DIR)/RTT/src/mem.c \
$(FINNAV_KERNEL_DIR)/RTT/src/memheap.c \
$(FINNAV_KERNEL_DIR)/RTT/src/mempool.c \
$(FINNAV_KERNEL_DIR)/RTT/src/object.c \
$(FINNAV_KERNEL_DIR)/RTT/src/scheduler_up.c \
$(FINNAV_KERNEL_DIR)/RTT/src/signal.c \
$(FINNAV_KERNEL_DIR)/RTT/src/slab.c \
$(FINNAV_KERNEL_DIR)/RTT/src/thread.c \
$(FINNAV_KERNEL_DIR)/RTT/src/timer.c \
$(FINNAV_KERNEL_DIR)/RTT/libcpu/arm/common/atomic_arm.c \
$(FINNAV_KERNEL_DIR)/RTT/libcpu/arm/common/div0.c \
$(FINNAV_KERNEL_DIR)/RTT/libcpu/arm/common/showmem.c \
$(FINNAV_KERNEL_DIR)/RTT/libcpu/arm/$(CPU)/cpuport.c

# $(FINNAV_KERNEL_DIR)/RTT/libcpu/arm/$(CPU)/mpu.c
# $(FINNAV_KERNEL_DIR)/RTT/src/scheduler_mp.c

OS_ASM := $(FINNAV_KERNEL_DIR)/RTT/libcpu/arm/$(CPU)/context_gcc.S

OS_BSP_INC := -I$(FINNAV_BSP_DIR)/BSP_$(TARGET_BSP)/Drivers
OS_BSP_DIR := $(FINNAV_BSP_DIR)/BSP_$(TARGET_BSP)/Drivers
OS_BSP_SRC := $(wildcard $(OS_BSP_DIR)/*.c)

# Correct RTT assembly command
OS_ASM_CFLAG := -Xassembler -mimplicit-it=thumb

OS_DEFS := -DSOC_FAMILY_STM32 -DSOC_SERIES_$(TARGET_SOC_FAMILY)

# Change link file and startup file to fit memory layout of RT-Thread
LD_SCRIPT_PATH := $(dir $(LD_SCRIPT))
LD_SCRIPT_NAME := $(notdir $(LD_SCRIPT))
LD_SCRIPT_SUFFIX := $(suffix $(LD_SCRIPT_NAME))
LD_SCRIPT := $(LD_SCRIPT_PATH)$(addsuffix _RTT, $(basename $(LD_SCRIPT_NAME)))$(LD_SCRIPT_SUFFIX)

BOOTLOADER_SRC_PATH := $(dir $(BOOTLOADER_SRC))
BOOTLOADER_SRC_NAME := $(notdir $(BOOTLOADER_SRC))
BOOTLOADER_SRC_SUFFIX := $(suffix $(BOOTLOADER_SRC_NAME))
BOOTLOADER_SRC := $(BOOTLOADER_SRC_PATH)$(addsuffix _RTT, $(basename $(BOOTLOADER_SRC_NAME)))$(BOOTLOADER_SRC_SUFFIX)

# CMSIS-RTOS support
ifeq ($(CMSIS_RTOS_VERSION),V1)
CMSIS_RTOS_INC :=
CMSIS_RTOS_SRC :=
else ifeq ($(CMSIS_RTOS_VERSION),V2)
CMSIS_RTOS_INC :=
CMSIS_RTOS_SRC :=
else ifeq ($(CMSIS_RTOS_VERSION),NO)
CMSIS_RTOS_INC :=
CMSIS_RTOS_SRC :=
endif
# *** included ***
