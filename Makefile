TARGET := FinNAV
export LIBROV_VERSION := 4
export LIBROV_SUBVERSION := 5

######################################
# Export Variables
######################################
# Root path
export FINNAV_ROOT_DIR := $(CURDIR)
# Application path
export FINNAV_APP_DIR := $(FINNAV_ROOT_DIR)/Application
# BSP path
export FINNAV_BSP_DIR := $(FINNAV_ROOT_DIR)/Boards
# Build path
export FINNAV_BUILD_DIR := $(FINNAV_ROOT_DIR)/build
# Doc path
export FINNAV_DOC_DIR := $(FINNAV_ROOT_DIR)/Doc
# FinNAV path
export FINNAV_LIBROV_DIR := $(FINNAV_ROOT_DIR)/FinNAV
# RTOS Kernel path
export FINNAV_KERNEL_DIR := $(FINNAV_ROOT_DIR)/Kernel
export RTT_DIR := $(FINNAV_KERNEL_DIR)/RTT
# FinNAV Lib path
export FINNAV_LIB_DIR := $(FINNAV_ROOT_DIR)/Lib
# Testbench path
export FINNAV_TB_DIR := $(FINNAV_ROOT_DIR)/Testbench
# Toolchain path
export FINNAV_TOOLCHAIN_DIR := $(FINNAV_ROOT_DIR)/Toolchain

# SDK configuration file path
export FINNAV_SDK_CONFIG_DIR := $(FINNAV_BUILD_DIR)/configs
# SDK compatable path for Keil MDK
export FINNAV_SDK_COMPAT_KEIL_DIR := $(FINNAV_BUILD_DIR)/MDK-ARM

# Target Link-file path
export FINNAV_TARGET_LINKER_DIR := $(FINNAV_BUILD_DIR)/target/linker
# Target RTOS configuation file path
export FINNAV_TARGET_RTOS_CONFIG_DIR := $(FINNAV_BUILD_DIR)/target/rtos
# Target SoC configuration file path
export FINNAV_TARGET_SOC_CONFIG_DIR := $(FINNAV_BUILD_DIR)/target/soc
# Target Compiler configuration file path
export FINNAV_TARGET_TOOLCHAIN_CONFIG_DIR := $(FINNAV_BUILD_DIR)/target/toolchain

include $(FINNAV_BUILD_DIR)/system.mk
######################################
# Kconfig&Kbuild Variables
######################################
# # Kconfig auto-generated header path
# export KCONFIG_AUTOHEADER := $(FINNAV_BUILD_DIR)/target/kconfig/menuconfig.h
# # NO CONFIG_ prefix!
# export CONFIG_ :=
# # Kconfig menu file
# KCONFIG_MENU := $(FINNAV_BUILD_DIR)/kconfig/Kconfig
# Kconfig auto-generated header path
export KCONFIG_AUTOHEADER ?= $(FINNAV_BUILD_DIR)/target/kconfig/menuconfig.h
# NO CONFIG_ prefix!
export CONFIG_ ?=
# Kconfig menu file
KCONFIG_MENU ?= $(FINNAV_BUILD_DIR)/kconfig/Kconfig

# Kconfig source path and mconf command
ifeq ($(OSFAMILY), windows)
export KCONFIG_PATH := $(FINNAV_TOOLCHAIN_DIR)/kconfig-python/kconfig
KCONFIG_MCONF_CMD := $(MAKE) -C $(KCONFIG_PATH) menuconfig
else ifeq ($(OSFAMILY), linux)
export KCONFIG_PATH := $(FINNAV_TOOLCHAIN_DIR)/kconfig
KCONFIG_MCONF_CMD := $(MAKE) -C $(KCONFIG_PATH) KBUILD_KCONFIG=$(KCONFIG_MENU) menuconfig
endif

# Kconfig mconf path #!Unused
KCONFIG_MCONF_EXE := $(FINNAV_TOOLCHAIN_DIR)/kconfig/kconfig/mconf
# Kconfig conf path #!Unused
KCONFIG_CONF_EXE := $(FINNAV_TOOLCHAIN_DIR)/kconfig/kconfig/conf

######################################
# SDK Global CONF File
######################################
# Kconfig default global config file name
KCONFIG_FILE_DEFCONFIG := $(FINNAV_SDK_CONFIG_DIR)/FinNAV_defconfig
SAVE = FinNAV_defconfig

# .last_conf保存了当前使用的配置文件，如果没有传入命令行参数$(CONF)，则使用默认配置文件
ifeq ("$(origin CONF)", "command line")
$(shell echo CONF=$(CONF) > .last_conf; cp $(FINNAV_BUILD_DIR)/configs/$(CONF) $(FINNAV_BUILD_DIR)/target/kconfig/.config)
else
$(shell [ -f .last_conf ] || ( echo CONF=$(KCONFIG_FILE_DEFCONFIG) > .last_conf ) )
endif
# CONF=xxx
include .last_conf

######################################
# specific includes
######################################
# common utils
include $(FINNAV_BUILD_DIR)/utils.mk
# parse .config file
include $(FINNAV_BUILD_DIR)/parse.mk
# setup verbosity level
include $(FINNAV_BUILD_DIR)/build_verbosity.mk

# Target full name
export FINNAV_TARGET := $(TARGET)_$(TARGET_SOC_FAMILY)_$(TARGET_RTOS)_$(TARGET_HAL)_v$(LIBROV_VERSION).$(LIBROV_SUBVERSION)

# Output path
export FINNAV_OUT_DIR := $(FINNAV_BUILD_DIR)/out/$(FINNAV_TARGET)

# openocd download specific includes
include $(FINNAV_BUILD_DIR)/download.mk

#######################################
# Environment Info Log
#######################################
$(call INFO,FinNAV,Target SoC Family: $(TARGET_SOC_FAMILY).)
$(call INFO,FinNAV,Target SoC: $(TARGET_SOC), Makefile: $(FINNAV_TARGET_SOC_CONFIG_DIR)/$(TARGET_SOC_FAMILY).mk.)
$(call INFO,FinNAV,Target RTOS: $(TARGET_RTOS), Makefile: $(FINNAV_TARGET_RTOS_CONFIG_DIR)/$(TARGET_RTOS).mk.)
$(call INFO,FinNAV,Target Lib: $(TARGET_HAL).)
#######################################
# Target
#######################################
.DEFAULT_GOAL = all
all: clean build

build: app

force:
	$(V1)$(call INFO,=============DBG=============,Debug Logs!)
	$(V1)$(call INFO,TARGET_HAL,$(TARGET_HAL))
	$(V1)$(call INFO,TARGET_RTOS,$(TARGET_RTOS))
	$(V1)$(call INFO,TARGET_SOC_FAMILY,$(TARGET_SOC_FAMILY))
	$(V1)$(call INFO,TARGET_SOC,$(TARGET_SOC))
	$(V1)$(call INFO,CONF,$(CONF))
	$(V1)$(call INFO,FINNAV_GLOBAL_CONFIG,$(FINNAV_GLOBAL_CONFIG))
	$(V1)$(call INFO,OPENOCD_CMD_FLASH,$(OPENOCD_CMD_FLASH))
	$(V1)$(call INFO,=============DBG=============,Debug Logs!)

# 编译芯片原厂驱动静态库
lib:
	$(V1)$(call INFO,FinNAV,compile peripheral libs!)
	$(MAKE) -C $(FINNAV_LIB_DIR)/main

# 删除驱动库
cleanlib:
	$(V1)$(call INFO,FinNAV,clean peripheral libs!)
	$(MAKE) -C $(FINNAV_LIB_DIR)/main clean

# 编译嵌入式操作系统内核静态库
kernel:
	$(V1)$(call INFO,FinNAV,compile rtos kernel!)
	$(MAKE) -C $(FINNAV_KERNEL_DIR)

# 删除嵌入式操作系统内核静态库
cleankernel:
	$(V1)$(call INFO,FinNAV,clean rtos kernel!)
	$(MAKE) -C $(FINNAV_KERNEL_DIR) clean

# 编译FinNAV中间件(LibROV)静态库
librov:
	$(V1)$(call INFO,FinNAV,compile FinNAV middleware!)
	$(MAKE) -C $(FINNAV_LIBROV_DIR)

# 删除FinNAV中间件(LibROV)静态库
cleanlibrov:
	$(V1)$(call INFO,FinNAV,clean FinNAV middleware!)
	$(MAKE) -C $(FINNAV_LIBROV_DIR) clean

# 编译应用程序
app: lib kernel librov
	$(V1)$(call INFO,FinNAV,compile application!)
	$(MAKE) -C $(FINNAV_APP_DIR)

# 删除应用程序
cleanapp:
	$(V1)$(call INFO,FinNAV,clean application!)
	$(MAKE) -C $(FINNAV_APP_DIR) clean

.PHONY: all build force lib kernel librov app cleanlib cleankernel cleanlibrov cleanapp

# 编译单元测试库
lib_test:
	$(V1)$(call INFO,FinNAV,compile unit test libs!)
	$(MAKE) -C $(FINNAV_LIB_DIR)/test build_gtest

# 运行单元测试
run_ut:
	$(V1)$(call INFO,FinNAV,run unit test!)
	$(MAKE) -C $(FINNAV_LIB_DIR)/test unittest

# 运行测试向量
run_tb:
	$(V1)$(call INFO,FinNAV,run testbench target!)
	$(MAKE) -C $(FINNAV_TB_DIR)
	$(V1)echo ""
	$(V1)echo "/////////////////////////////////////////////////"
	$(V1)echo "// P P P         A          S S S S    S S S S //"
	$(V1)echo "// P     P      A A       S          S         //"
	$(V1)echo "// P     P     A   A      S          S         //"
	$(V1)echo "// P P P      A     A       S S S      S S S   //"
	$(V1)echo "// P         A A A A A            S          S //"
	$(V1)echo "// P        A         A           S          S //"
	$(V1)echo "// P       A           A  S S S S    S S S S   //"
	$(V1)echo "/////////////////////////////////////////////////"
	$(V1)echo ""

.PHONY: lib_test run_ut run_tb

# 配置条件编译
menuconfig:
	$(V1)$(call INFO,Kconfig,execute mconf on $(OSFAMILY)!)
	$(KCONFIG_MCONF_CMD)

# 保存当前配置为默认配置
saveconfig:
	$(V1)$(call INFO,Kconfig,save last .config as $(SAVE)!)
	$(V1)cp $(FINNAV_GLOBAL_CONFIG) $(FINNAV_SDK_CONFIG_DIR)/$(SAVE)

# 删除mconf工具链
delmconf:
	$(V1)$(call INFO,Kconfig,delete mconf!)
	$(MAKE) -C $(KCONFIG_PATH) clean

# 清除全局配置文件
cleanconfig:
	$(V1)$(call INFO,Kconfig,reset Kconfig config!)
	$(V0)rm -rf $(FINNAV_BUILD_DIR)/target/kconfig/.config
	$(V0)rm -rf $(FINNAV_BUILD_DIR)/target/kconfig/.config.old
	$(V0)rm -rf $(FINNAV_BUILD_DIR)/target/kconfig/include
	$(V0)rm -rf $(FINNAV_ROOT_DIR)/.last_conf

.PHONY: menuconfig saveconfig delmconf cleanconfig

freertos-prepare:
	$(V1)$(call INFO,Kernel,setup FreeRTOS!)
	$(V1)cd $(FINNAV_BUILD_DIR)/script; ./download_freertos.sh;

liteos-prepare:
	$(V1)$(call INFO,Kernel,setup LiteOS!)
	$(V1)cd $(FINNAV_BUILD_DIR)/script; ./download_liteos.sh;

rtt-prepare:
	$(V1)$(call INFO,Kernel,setup RT-Thread!)
	$(V1)cd $(FINNAV_BUILD_DIR)/script; ./download_rtt.sh;

# 配置gcc工具链
gcc-prepare:
	$(V1)$(call INFO,Toolchain,setup GCC!)
	$(V1)cd $(FINNAV_BUILD_DIR)/script; ./download_toolchain.sh $(OSFAMILY);

# 配置OpenOCD工具链
openocd-prepare:
	$(V1)$(call INFO,OpenOCD,setup OpenOCD!)
	$(V1)cd $(FINNAV_BUILD_DIR)/script; ./download_openocd.sh;

.PHONY: freertos-prepare liteos-prepare rtt-prepare gcc-prepare openocd-prepare

# 烧录可执行文件
flash:
	$(V1)$(call INFO,OpenOCD,flash target!)
	$(V0)$(OPENOCD_CMD_FLASH)

# 执行调试
debug:
	$(V1)$(call INFO,OpenOCD,debug target!)
	$(V0)$(OPENOCD_DBG_FLASH)

# 擦除Flash
erase:
	$(V1)$(call INFO,OpenOCD,erase target!)
	$(V0)$(OPENOCD_ERASE_FLASH)

# 读取Flash
dump_img:
	$(V1)$(call INFO,OpenOCD,dump image of target!)
	$(V0)$(OPENOCD_DUMP_FLASH)

.PHONY: flash debug erase dump_img

# 生成API Doxygen文档
gen_doc:
	$(V1)$(call INFO,Doxygen,generate Doxygen API Files target!)
	$(MAKE) -C $(FINNAV_DOC_DIR) doxygen

# 清除API Doxygen文档
clean_doc:
	$(V1)$(call INFO,Doxygen,clean Doxygen API Files target!)
	$(MAKE) -C $(FINNAV_DOC_DIR) clean

# 输出版本信息
sdkversion:
	$(V1)$(call INFO,FinNAV,print SDK version information target!)
	$(V1)echo ""
	$(V1)echo "=============================================================="
	$(V1)echo "FinNAV SDK version: beta$(LIBROV_VERSION).$(LIBROV_SUBVERSION)"
	$(V1)echo "LibROV-$(LIBROV_VERSION).0"
	$(V1)echo "=============================================================="
	$(V1)echo ""

# 输出帮助信息
help:
	$(V1)$(call INFO,FinNAV,print help information target!)
	$(V1)echo ""
	$(V1)echo "========================================================================="
	$(V1)echo "Makefile for FinNAV-v$(LIBROV_VERSION).$(LIBROV_SUBVERSION) SDK"
	$(V1)echo "Powered by LibROV and CoralReef"
	$(V1)echo "Copyright (c), 2009-2024, OurEDA Underwater Robot Team, DLUT."
	$(V1)echo ""
	$(V1)echo "Usage:"
	$(V1)echo "        make [CONF=<config_file>] [V=<verbosity>] [OPTIONS=\"<options>\"]"
	$(V1)echo ""
	$(V1)echo "        Use Kconfig toolchain to configure the build first:"
	$(V1)echo "                make menuconfig"
	$(V1)echo "        Or pass a config file in build/configs to make:"
	$(V1)echo "                make CONF=FinNAV_f407_defconfig"
	$(V1)echo ""
	$(V1)echo "Options:"
	$(V1)echo "        CONF=<config_file>   Config file to use"
	$(V1)echo "        SAVE=<config_file>   Save Config file as"
	$(V1)echo "        V=<verbosity>        Verbosity level 0 or 1"
	$(V1)echo "========================================================================="
	$(V1)echo ""

# 清除当前工程输出
clean:
	$(V1)$(call INFO,FinNAV,clean current target!)
	$(V0)rm -rf $(FINNAV_OUT_DIR)
	$(V0)rm -rf $(FINNAV_BUILD_DIR)/out/finnav.*

# 清除所有输出和配置
cleanall:
	$(V1)$(call INFO,FinNAV,clean all target!)
	$(V0)rm -rf $(FINNAV_BUILD_DIR)/out/*

.PHONY: gen_doc clean_doc help clean cleanall
# *** EOF ***
