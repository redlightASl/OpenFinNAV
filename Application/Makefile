include $(FINNAV_BUILD_DIR)/compile.mk


######################################
# Inner Variables
######################################
TARGET := $(call lower,$(TARGET_APP))
BUILD_DIR := $(FINNAV_OUT_DIR)/$(TARGET)_build
LIB_TARGET := $(FINNAV_OUT_DIR)/lib$(TARGET).a

# ASM sources Config
ASM_SOURCES =

# C sources Config
APP_DIR := $(FINNAV_APP_DIR)/$(TARGET_APP)/Src
APP_SRC := $(wildcard $(APP_DIR)/*.c)

C_SOURCES = \
$(OS_BSP_SRC) \
$(BSP_SRC) \
$(APP_SRC)

# Linker Flags
# LDFLAGS += -Xlinker --gc-sections -Wl,-Map=$(FINNAV_OUT_DIR)/$(TARGET).map -Xlinker --cref
LDFLAGS += -Wl,-Map=$(FINNAV_OUT_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

$(call add_sources)
#######################################
# Target
#######################################
.DEFAULT_GOAL = all
all: build

build: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
	@$(call INFO,App,build application: $(TARGET))
	$(V1)cp $(BUILD_DIR)/$(TARGET).elf $(FINNAV_OUT_DIR)/../finnav.elf
	$(V1)cp $(BUILD_DIR)/$(TARGET).hex $(FINNAV_OUT_DIR)/../finnav.hex
	$(V1)cp $(BUILD_DIR)/$(TARGET).bin $(FINNAV_OUT_DIR)/../finnav.bin

$(BUILD_DIR)/$(TARGET).elf: $($(TARGET)_OBJS)
	$(V0)$(CC) $^ $(LDFLAGS) -o $@
	$(V0)$(SZ) $@

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(V0)$(HEX) $< $@

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(V0)$(BIN) $< $@

$(call libtarget)
# *** EOF ***
