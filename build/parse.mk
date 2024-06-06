#######################################
# Include .config File
#######################################
ifneq ($(wildcard $(FINNAV_BUILD_DIR)/target/kconfig/.config),)
FINNAV_GLOBAL_CONFIG := $(FINNAV_BUILD_DIR)/target/kconfig/.config
else
FINNAV_GLOBAL_CONFIG := $(CONF)
endif
$(call INFO,parse.mk,Using $(FINNAV_GLOBAL_CONFIG) as config.)
# FinNAV SDK Global Configuration includes
-include $(FINNAV_GLOBAL_CONFIG)


# check CONFIG_XXX
ifeq ($(CONFIG_TARGET_APP),)
$(call WARNING,parse.mk,No CONFIG_TARGET_APP specified.)
endif
ifeq ($(CONFIG_TARGET_SOC),)
$(call WARNING,parse.mk,No CONFIG_TARGET_SOC specified.)
endif
ifeq ($(CONFIG_TARGET_BSP),)
$(call WARNING,parse.mk,No CONFIG_TARGET_BSP specified.)
endif


#######################################
# Parse .config File
#######################################
# Compile Target Config
export TARGET_APP := $(call qstrip,$(CONFIG_TARGET_APP))
export TARGET_SOC := $(call qstrip,$(CONFIG_TARGET_SOC))
export TARGET_BSP := $(call qstrip,$(CONFIG_TARGET_BSP))
export CONFIG_USE_FINNAV

ifneq ($(CONFIG_COMPILER_CUSTOM),y)
export CONFIG_BUILTIN_TOOLCHAIN
export CONFIG_COMPILE_DEBUG
export CONFIG_COMPILE_ONE_SECTION_PER_FUNC
export CONFIG_COMPILE_NO_LIBC

ifneq ($(filter $(CONFIG_COMPILE_OPT),"-O0" "-O1" "-O2" "-O3" "-Os" "-Og" "-Ofast" "-Oz"),)
	ifeq ($(CONFIG_COMPILE_DEBUG),y) # Debug Mode
		export COMPILE_OPT := -O0
	endif
else
	$(call WARNING,parse.mk,CONFIG_COMPILE_OPT is $(CONFIG_COMPILE_OPT). It must be one of "-O0", "-O1", "-O2", "-O3", "-Os", "-Og", "-Ofast" or "-Oz".)
	export COMPILE_OPT := $(call qstrip,$(CONFIG_COMPILE_OPT))
endif

ifeq ($(CONFIG_COMPILER_GCC),y)
export COMPILER_CC := gcc
else ifeq ($(CONFIG_COMPILER_ARMCC),y)
export COMPILER_CC := arm
endif

else
export CONFIG_CFLAGS_CUSTOM
endif

ifeq ($(CONFIG_TARGET_SOC_FAMILY_STM32F4),y)
export TARGET_SOC_FAMILY := STM32F4
else ifeq ($(CONFIG_TARGET_SOC_FAMILY_STM32H7),y)
export TARGET_SOC_FAMILY := STM32H7
else ifeq ($(CONFIG_TARGET_SOC_FAMILY_STM32G4),y)
export TARGET_SOC_FAMILY := STM32G4
else
$(call WARNING,parse.mk,No CONFIG_TARGET_SOC_FAMILY specified.)
endif

ifeq ($(CONFIG_TARGET_HAL_HAL),y)
export TARGET_HAL := HAL
else ifeq ($(CONFIG_TARGET_HAL_STDPERIPH),y)
export TARGET_HAL := STDPERIPH
else ifeq ($(CONFIG_TARGET_HAL_REGISTER),y)
export TARGET_HAL := REGISTER
else
$(call WARNING,parse.mk,No CONFIG_TARGET_HAL specified.)
endif

ifeq ($(CONFIG_TARGET_RTOS_BAREMETAL),y)
export TARGET_RTOS := Baremetal
else ifeq ($(CONFIG_TARGET_RTOS_FREERTOS),y)
export TARGET_RTOS := FreeRTOS
else ifeq ($(CONFIG_TARGET_RTOS_LITEOS),y)
export TARGET_RTOS := LiteOS
else ifeq ($(CONFIG_TARGET_RTOS_RTT),y)
export TARGET_RTOS := RTT
else
$(call WARNING,parse.mk,No CONFIG_TARGET_RTOS specified.)
endif

ifeq ($(CONFIG_CMSIS_RTOS_VERSION_V1),y)
export CMSIS_RTOS_VERSION := V1
else ifeq ($(CONFIG_CMSIS_RTOS_VERSION_V2),y)
export CMSIS_RTOS_VERSION := V2
else ifeq ($(CONFIG_CMSIS_RTOS_VERSION_NO),y)
export CMSIS_RTOS_VERSION := NO
else
$(call WARNING,parse.mk,No CONFIG_CMSIS_RTOS_VERSION specified.)
endif

# BSP Config
export RTOS_MEM_POOL_TYPE := $(call qstrip,$(CONFIG_RTOS_MEM_POOL_TYPE))
export CONFIG_SOC_USE_FPU
export CONFIG_SOC_USE_DSP
export CONFIG_SOC_USE_MPU
export CONFIG_SOC_USE_ICACHE
export CONFIG_SOC_USE_DCACHE
export CONFIG_SOC_MAIN_OSC_VALUE
export CONFIG_SOC_INNER_OSC_VALUE
export CONFIG_BSP_USE_USB_OTG_FS
export CONFIG_BSP_USE_USB_OTG_HS
export CONFIG_BSP_USE_FATFS
export CONFIG_BSP_USE_LWIP
export CONFIG_BSP_USE_MBEDTLS
export CONFIG_BSP_USE_OPENAMP

# Memory Config
export CONFIG_EXSBOOT
export CONFIG_RAM_BASED
export CONFIG_CUSTOM_DEFAULTS_EXTENDED
export CONFIG_MCU_FLASH_SIZE
export CONFIG_BOOTLOADER_BASE_ADDRESS
export CONFIG_MULTIBOOT_MEM_ADDR

# OpenOCD Config without export
CONFIG_OPENOCD_PATH := $(call qstrip,$(CONFIG_OPENOCD_PATH))
CONFIG_DEBUGGER_INTERFACE := $(call qstrip,$(CONFIG_DEBUGGER_INTERFACE))

# FinNAV Config
export LIBROV_USE_DRIVER
#TODO: Sensor Component need review
export LIBROV_USE_SENSOR

# *** included ***
