######################################
# <Target SoC> Make file include
######################################
# cpu
CPU :=
MCU_CORE :=
# fpu
FPU :=
# float-abi
FLOAT-ABI :=
# SoC
MCU := -mcpu=$(CPU) -mthumb -mfpu=$(FPU) -mfloat-abi=$(FLOAT-ABI) -fsingle-precision-constant
# compiler prefix
COMPILER_TARGET := arm
COMPILER_OS := none
COMPILER_ABI := eabi
# PREFIX = arm-none-eabi-

#######################################
# SoC specifics --- port
#######################################
ifeq ($(TARGET_SOC),STM32H750xx)
DEVICE_DEFS := -DSTM32H750xx
LD_SCRIPT = $(FINNAV_TARGET_LINKER_DIR)/STM32H750VBTx_FLASH.ld
STARTUP_FILE = startup_stm32h750xx.s
CONFIG_MCU_FLASH_SIZE ?= 512
else
$(call ERROR,FinNAV,Unknown MCU for STM32H7 target.)
endif

DEVICE_DEFS += -DSTM32
ifeq ($(CONFIG_SOC_USE_FPU),y)
DEVICE_DEFS += -D_FPU_USED
endif
ifeq ($(CONFIG_SOC_USE_DSP),y)
DEVICE_DEFS +=
endif

######################################
# Sources --- Do not change
######################################
SOC_DRIVER_SPEC := $(FINNAV_LIB_DIR)/main/$(TARGET_SOC_FAMILY)/Drivers

CORE_SUPPORT_INC := $(FINNAV_LIB_DIR)/main/CMSIS/Core/Include
BOOTLOADER_SRC := $(SOC_DRIVER_SPEC)/CMSIS/Device/ST/$(TARGET_SOC_FAMILY)xx/Source/Templates/$(COMPILER_CC)/$(STARTUP_FILE)
SOC_HEADER_SRC := $(SOC_DRIVER_SPEC)/CMSIS/Device/ST/$(TARGET_SOC_FAMILY)xx/Source/Templates/system_stm32f4xx.c

ifeq ($(TARGET_HAL), HAL)
SOC_HEADER_INC := $(SOC_DRIVER_SPEC)/CMSIS/Device/ST/$(TARGET_SOC_FAMILY)xx/Include
SOC_PERIPHERAL_LIB_INC := $(SOC_DRIVER_SPEC)/$(TARGET_SOC_FAMILY)xx_HAL_Driver/Inc
SOC_PERIPHERAL_LIB_DIR := $(SOC_DRIVER_SPEC)/$(TARGET_SOC_FAMILY)xx_HAL_Driver/Src
else
SOC_HEADER_INC :=
SOC_PERIPHERAL_LIB_INC := 
SOC_PERIPHERAL_LIB_DIR := 
endif
SOC_PERIPHERAL_LIB_SRC := $(wildcard $(SOC_PERIPHERAL_LIB_DIR)/*.c)
EXCLUDE_FILE :=
SOC_PERIPHERAL_LIB_SRC := $(filter-out $(EXCLUDE_FILE),$(SOC_PERIPHERAL_LIB_SRC))

$(TARGET_HAL)_CONF_INC := $(FINNAV_BSP_DIR)/BSP_$(TARGET_BSP)/Core/Inc
BSP_DIR := $(FINNAV_BSP_DIR)/BSP_$(TARGET_BSP)/Core/Src
BSP_SRC := $(wildcard $(BSP_DIR)/*.c)

ifeq ($(CONFIG_BSP_USE_FATFS),y)
BSP_SRC += $(wildcard $(FINNAV_BSP_DIR)/BSP_$(TARGET_BSP)/FATFS/Target/*.c)
BSP_SRC += $(wildcard $(FINNAV_BSP_DIR)/BSP_$(TARGET_BSP)/FATFS/App/*.c)
$(TARGET_HAL)_CONF_INC += -I$(FINNAV_BSP_DIR)/BSP_$(TARGET_BSP)/FATFS/Target
$(TARGET_HAL)_CONF_INC += -I$(FINNAV_BSP_DIR)/BSP_$(TARGET_BSP)/FATFS/App
endif

DSP_LIB_INC :=
DSP_LIB_DIR :=
DSP_LIB_SRC :=
DSP_LIB_BIN :=
DSP_LIB :=

# *** included ***
