include $(FINNAV_BUILD_DIR)/compile.mk


######################################
# Inner Variables
######################################
TARGET := $(call lower,$(TARGET_RTOS))
BUILD_DIR := $(FINNAV_OUT_DIR)/$(TARGET)_build
LIB_TARGET := $(FINNAV_OUT_DIR)/lib$(TARGET).a

# ASM sources Config
ASM_SOURCES = \
$(OS_ASM)

# C sources Config
C_SOURCES = \
$(CMSIS_RTOS_SRC) \
$(OS_SRC)

$(call add_sources)
#######################################
# Target
#######################################
.DEFAULT_GOAL = all
all: build_$(TARGET_RTOS)

prepare_Baremetal: $(BUILD_DIR)
	$(V1)$(call INFO,Kernel,nothing to prepare!)

prepare_FreeRTOS: $(BUILD_DIR)
	$(V1)$(call INFO,Kernel,prepare for OS: FreeRTOS!)

prepare_LiteOS: $(BUILD_DIR)
	$(V1)$(call INFO,Kernel,prepare for OS: LiteOS!)
	git clone https://gitee.com/LiteOS/LiteOS.git LiteOS;

prepare_RTT: $(BUILD_DIR)
	$(V1)$(call INFO,Kernel,prepare for OS: RT-Thread!)

.PHONY: prepare_Baremetal prepare_FreeRTOS prepare_LiteOS prepare_RTT

build_Baremetal: prepare_Baremetal
	$(V1)$(call INFO,Kernel,TODO!)

build_FreeRTOS: $(LIB_TARGET) prepare_FreeRTOS
	$(V1)$(call INFO,Kernel,build FreeRTOS as static library!)

build_LiteOS:
	$(V1)$(call INFO,Kernel,TODO!)

build_RTT: $(LIB_TARGET) prepare_RTT
	$(V1)$(call INFO,Kernel,build RT-Thread as static library!)

.PHONY: build_Baremetal build_FreeRTOS build_LiteOS build_RTT

$(call libtarget)
# *** EOF ***
