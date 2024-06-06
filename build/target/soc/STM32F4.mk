######################################
# STM32F4xx Make file include --- port
######################################
# cpu
CPU := cortex-m4
MCU_CORE := ARM_CM4F
# fpu
FPU := fpv4-sp-d16
# float-abi
FLOAT-ABI := hard
# SoC
MCU := -mcpu=$(CPU) -march=armv7e-m -mthumb -mfpu=$(FPU) -mfloat-abi=$(FLOAT-ABI) -fsingle-precision-constant
# compiler prefix
COMPILER_TARGET := arm
COMPILER_OS := none
COMPILER_ABI := eabi
# PREFIX = arm-none-eabi-

#######################################
# SoC specifics --- port
#######################################
ifeq ($(TARGET_SOC),STM32F407xx)
DEVICE_DEFS := -DSTM32F40_41xxx
LD_SCRIPT = $(FINNAV_TARGET_LINKER_DIR)/STM32F407VETx_FLASH.ld
STARTUP_FILE = startup_stm32f407xx.s
CONFIG_MCU_FLASH_SIZE ?= 1024
else ifeq ($(TARGET_SOC),STM32F405xx)
DEVICE_DEFS :=
LD_SCRIPT = $(FINNAV_TARGET_LINKER_DIR)/STM32F405RGTx_FLASH.ld
STARTUP_FILE = startup_stm32f405xx.s
CONFIG_MCU_FLASH_SIZE ?= 512
else
$(call ERROR,FinNAV,Unknown MCU for STM32F4 target.)
endif

DEVICE_DEFS += -D$(TARGET_SOC) -DSTM32
ifeq ($(CONFIG_SOC_USE_FPU),y)
DEVICE_DEFS += -D_FPU_USED=1
endif
ifeq ($(CONFIG_SOC_USE_DSP),y)
DEVICE_DEFS += -DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING -DUNALIGNED_SUPPORT_DISABLE
endif

######################################
# Sources --- Do not change
######################################
SOC_DRIVER_SPEC := $(FINNAV_LIB_DIR)/main/$(TARGET_SOC_FAMILY)/Drivers

CORE_SUPPORT_INC := $(FINNAV_LIB_DIR)/main/CMSIS/Core/Include
BOOTLOADER_SRC := $(SOC_DRIVER_SPEC)/CMSIS/Device/ST/$(TARGET_SOC_FAMILY)xx/Source/Templates/$(COMPILER_CC)/$(STARTUP_FILE)
SOC_HEADER_SRC := $(SOC_DRIVER_SPEC)/CMSIS/Device/ST/$(TARGET_SOC_FAMILY)xx/Source/Templates/system_$(call lower,$(TARGET_SOC_FAMILY))xx.c

ifeq ($(TARGET_HAL), HAL)
SOC_HEADER_INC := $(SOC_DRIVER_SPEC)/CMSIS/Device/ST/$(TARGET_SOC_FAMILY)xx/Include
SOC_PERIPHERAL_LIB_INC := $(SOC_DRIVER_SPEC)/$(TARGET_SOC_FAMILY)xx_HAL_Driver/Inc
SOC_PERIPHERAL_LIB_DIR := $(SOC_DRIVER_SPEC)/$(TARGET_SOC_FAMILY)xx_HAL_Driver/Src
else ifeq ($(TARGET_HAL), STDPERIPH)
SOC_HEADER_INC := $(SOC_DRIVER_SPEC)/CMSIS/Device/ST/$(TARGET_SOC_FAMILY)xx/Include_SPL
SOC_PERIPHERAL_LIB_INC := $(SOC_DRIVER_SPEC)/$(TARGET_SOC_FAMILY)xx_StdPeriph_Driver/inc
SOC_PERIPHERAL_LIB_DIR := $(SOC_DRIVER_SPEC)/$(TARGET_SOC_FAMILY)xx_StdPeriph_Driver/src
else ifeq ($(TARGET_HAL), REGISTER)
SOC_HEADER_INC :=
SOC_PERIPHERAL_LIB_INC := 
SOC_PERIPHERAL_LIB_DIR := 
else
SOC_HEADER_INC :=
SOC_PERIPHERAL_LIB_INC := 
SOC_PERIPHERAL_LIB_DIR := 
endif
SOC_PERIPHERAL_LIB_SRC := $(wildcard $(SOC_PERIPHERAL_LIB_DIR)/*.c)

EXCLUDE_FILE := $(SOC_PERIPHERAL_LIB_DIR)/stm32f4xx_fmc.c
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

DSP_LIB_INC := $(FINNAV_LIB_DIR)/main/CMSIS/DSP/Include
DSP_LIB_DIR := $(FINNAV_LIB_DIR)/main/CMSIS/DSP/Source/BasicMathFunctions \
$(FINNAV_LIB_DIR)/main/CMSIS/DSP/Source/FilteringFunctions \
$(FINNAV_LIB_DIR)/main/CMSIS/DSP/Source/MatrixFunctions \
$(FINNAV_LIB_DIR)/main/CMSIS/DSP/Source/StatisticsFunctions \
$(FINNAV_LIB_DIR)/main/CMSIS/DSP/Source/SupportFunctions \
$(FINNAV_LIB_DIR)/main/CMSIS/DSP/Source/TransformFunctions \
$(FINNAV_LIB_DIR)/main/CMSIS/DSP/Source/BasicMathFunctions
DSP_LIB_SRC := $(wildcard $(DSP_LIB_DIR)/*.c)
DSP_LIB_STATIC := $(FINNAV_LIB_DIR)/main/CMSIS/DSP/Lib
DSP_LIB := arm_cortexM4lf.a

# *** included ***
