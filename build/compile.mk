include $(FINNAV_BUILD_DIR)/system.mk
include $(FINNAV_BUILD_DIR)/utils.mk

######################################
# build environment
######################################
# soc makefile
include $(FINNAV_TARGET_SOC_CONFIG_DIR)/$(TARGET_SOC_FAMILY).mk
# rtos makefile
include $(FINNAV_TARGET_RTOS_CONFIG_DIR)/$(TARGET_RTOS).mk

# fixed compiler makefile
include $(FINNAV_TARGET_TOOLCHAIN_CONFIG_DIR)/gcc.mk

#######################################
# Includes configuration
#######################################
# AS includes
AS_INCLUDES =

# menuconfig includes
ifneq ($(wildcard $(KCONFIG_AUTOHEADER)),)
MENUCONFIG_INC := $(FINNAV_BUILD_DIR)/target/kconfig
else
$(call ERROR,FinNAV,No valid menuconfig.h specified. Run `make menuconfig` first.)
endif
C_INCLUDES = -I$(MENUCONFIG_INC)

# HAL includes
C_INCLUDES += -I$(CORE_SUPPORT_INC) \
-I$(SOC_HEADER_INC) \
-I$(SOC_PERIPHERAL_LIB_INC) \
-I$($(TARGET_HAL)_CONF_INC)

ifeq ($(CONFIG_SOC_USE_DSP),y)
C_INCLUDES += -I$(DSP_LIB_INC)
endif

# Third Party Lib includes
ifeq ($(CONFIG_BSP_USE_FATFS),y)
C_INCLUDES += -I$(FINNAV_LIB_DIR)/main/Third_Party/FatFs/src
endif

# RTOS includes
C_INCLUDES += $(OS_INC) $(OS_BSP_INC)
ifneq ($(CMSIS_RTOS_VERSION),NO)
C_INCLUDES += $(CMSIS_RTOS_INC)
endif

# LibROV includes
ifeq ($(CONFIG_USE_FINNAV),y)
C_INCLUDES += $(LIBROV_INC)
endif

# Application includes
APP_INC := $(FINNAV_APP_DIR)/$(TARGET_APP)/Inc
C_INCLUDES += -I$(APP_INC)

#######################################
# Global Define configuration
#######################################
# macros for gcc
# AS defines
AS_DEFS := 

# C defines
C_DEFS := -DUSE_$(TARGET_HAL)_DRIVER $(DEVICE_DEFS) $(OS_DEFS)

ifneq ($(CONFIG_SOC_MAIN_OSC_VALUE),-1)
C_DEFS += -DHSE_VALUE=$(CONFIG_SOC_MAIN_OSC_VALUE)
endif
ifneq ($(CONFIG_SOC_INNER_OSC_VALUE),-1)
C_DEFS += -DHSI_VALUE=$(CONFIG_SOC_INNER_OSC_VALUE)
endif

ifneq ($(CMSIS_RTOS_VERSION),NO)
C_DEFS += -DCMSIS_device_header=\"$(call lower,$(TARGET_SOC_FAMILY))xx.h\"
endif

#######################################
# CFLAGS configuration
#######################################
ifneq ($(CONFIG_CFLAGS_CUSTOM),y)
CFLAGS = $(MCU) $(C_DEFS)
CFLAGS += -std=gnu11
# CFLAGS += -Wno-unused-parameter

# Compiler Not use libc
CFLAGS += $(CFLAGS_NO_LIBC)

# Compiler Debug Configuration
CFLAGS += $(CFLAGS_DEBUG)

# Compiler Optimization Configuration
CFLAGS += $(COMPILE_OPT)

# Other Compiler Functions
CFLAGS += -Wall -fdata-sections
CFLAGS += $(CFLAGS_SECTION_PER_FUNC)
CFLAGS += -u_printf_float
CFLAGS += -fgnu89-inline
else

endif

CFLAGS += $(C_INCLUDES)

#######################################
# ASFLAGS configuration
#######################################
ASFLAGS ?= $(CFLAGS)
ASFLAGS += $(OS_ASM_CFLAG)

#######################################
# CPPFLAGS configuration
#######################################
CPPFLAGS := $(CFLAGS)

#######################################
# TestBench FLAGS configuration
#######################################
TBFLAGS := -Wall -fdata-sections
TBFLAGS += -DNDEBUG
TBFLAGS += $(COMPILE_OPT)
TBFLAGS += $(CFLAGS_SECTION_PER_FUNC)

TBFLAGS += $(C_INCLUDES)

#######################################
# LDFLAGS
#######################################
# libraries
LIBDIR := -L $(FINNAV_OUT_DIR)

LIBS := -lc -lm -lnosys
LIBS += -l $(call lower,$(TARGET_HAL))

ifneq ($(TARGET_RTOS),Baremetal)
LIBS += -l $(call lower,$(TARGET_RTOS))
endif

ifeq ($(CONFIG_USE_FINNAV),y)
LIBS += -l rov
endif

ifeq ($(CONFIG_SOC_USE_DSP),y)
LIBDIR += -L$(DSP_LIB_STATIC)
LIBS += -l $(DSP_LIB)
endif

LDFLAGS := $(MCU) -specs=nano.specs $(LIBDIR) $(LIBS) -T$(LD_SCRIPT)
LDFLAGS += -Wl,--print-memory-usage
# LDFLAGS := $(MCU) $(LIBDIR) $(LIBS) -T$(LD_SCRIPT)

#######################################
# Functions
#######################################
include $(FINNAV_BUILD_DIR)/libtarget.mk

libtarget = $(eval $(call _libtarget))
add_sources = $(eval $(call _add_sources))
add_sources_cpp = $(eval $(call _add_sources_cpp))
# *** included ***
