include $(FINNAV_BUILD_DIR)/compile.mk


######################################
# Inner Variables
######################################
TARGET := $(call lower,$(TARGET_HAL))
BUILD_DIR := $(FINNAV_OUT_DIR)/$(TARGET)_build
LIB_TARGET := $(FINNAV_OUT_DIR)/lib$(TARGET).a

# ThirdParty Library
ifeq ($(CONFIG_BSP_USE_FATFS),y)
FATFS_LIB_DIR := $(FINNAV_LIB_DIR)/main/Third_Party/FatFs/src
else
FATFS_LIB_DIR :=
endif
FATFS_LIB_SRC := $(wildcard $(FATFS_LIB_DIR)/*.c)

THIRD_PARTY_LIB_SRC :=
THIRD_PARTY_LIB_SRC += $(FATFS_LIB_SRC)

# ASM sources Config
ASM_SOURCES = $(BOOTLOADER_SRC)

# C sources Config
C_SOURCES = \
$(SOC_HEADER_SRC) \
$(SOC_PERIPHERAL_LIB_SRC) \
$(THIRD_PARTY_LIB_SRC)

$(call add_sources)
#######################################
# Target
#######################################
.DEFAULT_GOAL = all
all: build

build: $(LIB_TARGET)
	$(V1)$(call INFO,Lib,build static library: $(TARGET))
	$(V0)$(call INFO,Lib,=========== Success! ===========)

$(call libtarget)
# *** EOF ***
