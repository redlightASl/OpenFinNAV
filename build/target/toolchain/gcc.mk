######################################
# Compiler Configuration Make file include
######################################
ifneq ($(CONFIG_COMPILER_CUSTOM),y)

CROSS_COMPILE ?= $(COMPILER_TARGET)-$(COMPILER_OS)-$(COMPILER_ABI)-

ifeq ($(CONFIG_BUILTIN_TOOLCHAIN),y)
ifneq ($(wildcard $(FINNAV_TOOLCHAIN_DIR)/gcc),)
ifeq ($(OSFAMILY),linux)
GCC_PATH := $(FINNAV_TOOLCHAIN_DIR)/gcc/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi/bin
ifeq ($(wildcard $(FINNAV_TOOLCHAIN_DIR)/gcc/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi),)
$(call ERROR,gcc.mk,Builtin Toolchain <arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi> Not Found. Run `make gcc-prepare` first.)
endif
else
GCC_PATH := $(FINNAV_TOOLCHAIN_DIR)/gcc/arm-gnu-toolchain-13.2.Rel1-mingw-w64-i686-arm-none-eabi/bin
ifeq ($(wildcard $(FINNAV_TOOLCHAIN_DIR)/gcc/arm-gnu-toolchain-13.2.Rel1-mingw-w64-i686-arm-none-eabi),)
$(call ERROR,gcc.mk,Builtin Toolchain <arm-gnu-toolchain-13.2.Rel1-mingw-w64-i686-arm-none-eabi> Not Found. Run `make gcc-prepare` first.)
endif
endif
else
$(call ERROR,gcc.mk,Builtin Toolchain Not Found. Run `make gcc-prepare` first.)
endif
endif

ifdef GCC_PATH
CC := $(GCC_PATH)/$(CROSS_COMPILE)gcc
CXX := $(GCC_PATH)/$(CROSS_COMPILE)g++
AS := $(GCC_PATH)/$(CROSS_COMPILE)gcc -x assembler-with-cpp
AR := $(GCC_PATH)/$(CROSS_COMPILE)ar
OBJCOPY := $(GCC_PATH)/$(CROSS_COMPILE)objcopy
SZ := $(GCC_PATH)/$(CROSS_COMPILE)size
else
CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
AS := $(CROSS_COMPILE)gcc -x assembler-with-cpp
AR := $(CROSS_COMPILE)ar
OBJCOPY := $(CROSS_COMPILE)objcopy
SZ := $(CROSS_COMPILE)size
endif
HEX := $(OBJCOPY) -O ihex
BIN := $(OBJCOPY) -O binary -S

ifeq ($(CONFIG_COMPILE_DEBUG),y)
CFLAGS_DEBUG := -g -gdwarf-2 -D_DEBUG
else
CFLAGS_DEBUG := -DNDEBUG
endif

ifeq ($(CONFIG_COMPILE_ONE_SECTION_PER_FUNC),y)
CFLAGS_SECTION_PER_FUNC := -ffunction-sections
endif

ifeq ($(CONFIG_COMPILE_NO_LIBC),y)
CFLAGS_NO_LIBC := -nostdlib
CFLAGS_NO_LIBC += -specs=nosys.specs
CFLAGS_NO_LIBC += -ffreestanding
endif

endif

$(call INFO,gcc.mk,C Compiler: $(CC).)
$(call INFO,gcc.mk,C++ Compiler: $(CXX).)
$(call INFO,gcc.mk,Assembler: $(AS).)
# *** included ***
