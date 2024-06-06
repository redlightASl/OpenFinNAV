include $(FINNAV_BUILD_DIR)/compile.mk


######################################
# Inner Variables
######################################
TARGET := rov
BUILD_DIR := $(FINNAV_OUT_DIR)/$(TARGET)_build
ifeq ($(CONFIG_USE_FINNAV),y)
LIB_TARGET := $(FINNAV_OUT_DIR)/lib$(TARGET).a
else
LIB_TARGET :=
endif

#TODO
LIBROV_MODULE_INC := \
-I$(FINNAV_LIBROV_DIR)/Include\
-I$(FINNAV_LIBROV_DIR)/Algorithm/include \
-I$(FINNAV_LIBROV_DIR)/Base/include \
-I$(FINNAV_LIBROV_DIR)/BasicCtrl/include \
-I$(FINNAV_LIBROV_DIR)/Display/include \
-I$(FINNAV_LIBROV_DIR)/Driver/include \
-I$(FINNAV_LIBROV_DIR)/Runtime/include \
-I$(FINNAV_LIBROV_DIR)/Sensor/include \
-I$(FINNAV_LIBROV_DIR)/Sensor/packages/include \
-I$(FINNAV_LIBROV_DIR)/Thread/include
ifeq ($(LIBROV_USE_DRIVER),y)
LIBROV_MODULE_INC += -I$(FINNAV_BSP_DIR)/BSP_$(TARGET_BSP)/Port/Inc
endif
LIBROV_INC = $(LIBROV_MODULE_INC)


LIBROV_ALGORITHM_DIR := $(FINNAV_LIBROV_DIR)/Algorithm
LIBROV_BASE_DIR := $(FINNAV_LIBROV_DIR)/Base
LIBROV_BASICCTRL_DIR := $(FINNAV_LIBROV_DIR)/BasicCtrl
LIBROV_DISPLAY_DIR := $(FINNAV_LIBROV_DIR)/Display
LIBROV_DRIVER_DIR := $(FINNAV_LIBROV_DIR)/Driver
LIBROV_RUNTIME_DIR := $(FINNAV_LIBROV_DIR)/Runtime
LIBROV_SENSOR_DIR := $(FINNAV_LIBROV_DIR)/Sensor
LIBROV_THREAD_DIR := $(FINNAV_LIBROV_DIR)/Thread
LIBROV_PORT_DIR := $(FINNAV_BSP_DIR)/BSP_$(TARGET_BSP)/Port/Src

LIBROV_ALGORITHM_SRC := $(wildcard $(LIBROV_ALGORITHM_DIR)/*.c)
LIBROV_BASE_SRC := $(wildcard $(LIBROV_BASE_DIR)/*.c)
LIBROV_BASICCTRL_SRC := $(wildcard $(LIBROV_BASICCTRL_DIR)/*.c)
LIBROV_DISPLAY_SRC := $(wildcard $(LIBROV_DISPLAY_DIR)/*.c)
LIBROV_DRIVER_SRC := $(wildcard $(LIBROV_DRIVER_DIR)/*.c)
LIBROV_RUNTIME_SRC := $(wildcard $(LIBROV_RUNTIME_DIR)/*.c)
LIBROV_SENSOR_SRC := $(wildcard $(LIBROV_SENSOR_DIR)/*.c)
LIBROV_THREAD_SRC := $(wildcard $(LIBROV_THREAD_DIR)/*.c)
LIBROV_PORT_SRC := $(wildcard $(LIBROV_PORT_DIR)/*.c)

# ASM sources Config
ASM_SOURCES = 

# C sources Config
ifeq ($(CONFIG_USE_FINNAV),y)
C_SOURCES = \
$(LIBROV_ALGORITHM_SRC) \
$(LIBROV_BASE_SRC) \
$(LIBROV_BASICCTRL_SRC) \
$(LIBROV_DISPLAY_SRC) \
$(LIBROV_DRIVER_SRC) \
$(LIBROV_RUNTIME_SRC) \
$(LIBROV_SENSOR_SRC) \
$(LIBROV_THREAD_SRC)
ifeq ($(LIBROV_USE_DRIVER),y)
C_SOURCES += $(LIBROV_PORT_SRC)
endif
else
C_SOURCES =
endif

$(call add_sources)
#######################################
# Target
#######################################
.DEFAULT_GOAL = all
all: build

build: $(LIB_TARGET)
	$(V1)$(call INFO,LibROV,build FinNAV Middleware as static library!)

$(call libtarget)
# *** EOF ***
