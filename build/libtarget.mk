######################################
# External Variables
######################################
# TARGET
# LIB_TARGET
# BUILD_DIR
# C_SOURCES
# ASM_SOURCES
# CFLAGS
######################################

######################################
# Function Defination
######################################
# 将.c .s .S文件列表转换成.o文件列表
define _add_sources
$$(TARGET)_OBJS = $$(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $$(sort $(dir $(C_SOURCES)))
$$(TARGET)_OBJS += $$(addprefix $(BUILD_DIR)/,$(notdir $(patsubst %.s,%.o,$(patsubst %.S,%.o,$(ASM_SOURCES)))))
vpath %.s $$(sort $(dir $(ASM_SOURCES)))
vpath %.S $$(sort $(dir $(ASM_SOURCES)))
endef

# 将.cpp文件列表转换成.o文件列表
define _add_sources_cpp
$$(TARGET)_OBJS = $$(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $$(sort $(dir $(CPP_SOURCES)))
endef

# 生成编译目标
define _libtarget
$$(LIB_TARGET): $$($(TARGET)_OBJS)
	$$(V0)$$(AR) -rcs $$@ $$^

$$(BUILD_DIR)/%.o: %.c Makefile | $$(BUILD_DIR)
	$$(V0)$$(CC) $$(CFLAGS) -MMD -MP -MF $$(@:%.o=%.d) -Wa,-adhlns=$$(BUILD_DIR)/$$(notdir $$(<:.c=.lst)) -c $$< -o $$@

$$(BUILD_DIR)/%.o: %.s Makefile | $$(BUILD_DIR)
	$$(V0)$$(AS) $$(ASFLAGS) -c $$< -o $$@

$$(BUILD_DIR)/%.o: %.S Makefile | $$(BUILD_DIR)
	$$(V0)$$(AS) $$(ASFLAGS) -c $$< -o $$@

$$(BUILD_DIR):
	$$(V1)mkdir -p $$@

clean:
	$$(V0)rm -rf $$(BUILD_DIR)

.PHONY: all build clean
-include $$(wildcard $(BUILD_DIR)/*.d)
endef
# *** included ***
