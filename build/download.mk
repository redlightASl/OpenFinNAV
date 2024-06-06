######################################
# OpenOCD Config
######################################
OPENOCD ?= openocd

ifeq ($(CONFIG_OPENOCD_PATH),)
CONFIG_OPENOCD_PATH := $(FINNAV_TOOLCHAIN_DIR)/openocd/share/openocd
endif
ifeq ($(CONFIG_DEBUGGER_INTERFACE),)
CONFIG_DEBUGGER_INTERFACE := cmsis-dap
endif

OPENOCD_SCRIPTS_PATH := $(CONFIG_OPENOCD_PATH)/scripts
FLASH_TARGET := $(call addsuffix,x,$(call lower,$(TARGET_SOC_FAMILY)))

CONFIG_BOOTLOADER_BASE_ADDRESS ?= 0x08000000
CONFIG_MCU_FLASH_SIZE ?= 0x00040000
CONFIG_MULTIBOOT_MEM_ADDR ?= 0x08100000

ifeq ($(CONFIG_OPENOCD_FLASH_HEX),y)
FLASH_HEX := $(FINNAV_BUILD_DIR)/out/finnav.hex
FLASH_CMD := "flash write_image erase $(FLASH_HEX)"
else ifeq ($(CONFIG_OPENOCD_FLASH_ELF),y)
FLASH_ELF := $(FINNAV_BUILD_DIR)/out/finnav.elf
FLASH_CMD := "flash write_image erase $(FLASH_ELF)"
else ifeq ($(CONFIG_OPENOCD_FLASH_BIN),y)
FLASH_BIN := $(FINNAV_BUILD_DIR)/out/finnav.bin
FLASH_CMD := "flash write_image erase $(FLASH_BIN) $(CONFIG_BOOTLOADER_BASE_ADDRESS)"
else
endif

INTERFACE_CFG = "$(OPENOCD_SCRIPTS_PATH)/interface/$(CONFIG_DEBUGGER_INTERFACE).cfg"
TARGET_CFG = "$(OPENOCD_SCRIPTS_PATH)/target/$(FLASH_TARGET).cfg"

OPENOCD_BASE_CMD = $(OPENOCD) -f $(INTERFACE_CFG) -f $(TARGET_CFG)

OPENOCD_CMD_FLASH := $(OPENOCD_BASE_CMD) -c init \
-c "adapter speed $(CONFIG_OPENOCD_FLASH_SPEED)" \
-c "reset halt" \
-c $(FLASH_CMD) \
-c "reset run" \
-c shutdown

OPENOCD_DBG_FLASH := $(OPENOCD_BASE_CMD) \
& arm-none-eabi-gdb $(FLASH_ELF) -ex "target remote localhost:3333" -ex "load"

OPENOCD_ERASE_FLASH := $(OPENOCD_BASE_CMD) -c init \
-c "adapter speed $(CONFIG_OPENOCD_FLASH_SPEED)" \
-c halt \
-c "reset halt" \
-c "flash erase_address ${CONFIG_BOOTLOADER_BASE_ADDRESS} ${CONFIG_MCU_FLASH_SIZE}" \
-c shutdown

OPENOCD_DUMP_FLASH := $(OPENOCD_BASE_CMD) -c init \
-c "adapter speed $(CONFIG_OPENOCD_FLASH_SPEED)" \
-c halt \
-c "reset halt" \
-c "dump_image $(FINNAV_BUILD_DIR)/out/image_dump.bin ${CONFIG_BOOTLOADER_BASE_ADDRESS} ${CONFIG_MCU_FLASH_SIZE}" \
-c shutdown
# *** included ***
