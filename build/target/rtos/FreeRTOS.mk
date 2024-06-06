######################################
# FreeRTOS Make file include
######################################
# Core Version Compatible 
ifeq ($(MCU_CORE),ARM_CM7)
CORE_VERSION_DIR := $(MCU_CORE)/r0p1
else
CORE_VERSION_DIR := $(MCU_CORE)
endif

ifeq ($(RTOS_MEM_POOL_TYPE),)
$(error "Variable RTOS_MEM_POOL_TYPE not found!")
endif

ifeq ($(CORE_VERSION_DIR),)
$(error "Variable CORE_VERSION_DIR not found!")
endif

# RTOS support
OS_INC := \
-I$(FINNAV_KERNEL_DIR)/FreeRTOS/include \
-I$(FINNAV_KERNEL_DIR)/FreeRTOS/portable/GCC/$(CORE_VERSION_DIR) \
-I$(FINNAV_KERNEL_DIR)/CMSIS_RTOS/FreeRTOS

OS_SRC := \
$(FINNAV_KERNEL_DIR)/FreeRTOS/croutine.c \
$(FINNAV_KERNEL_DIR)/FreeRTOS/event_groups.c \
$(FINNAV_KERNEL_DIR)/FreeRTOS/list.c \
$(FINNAV_KERNEL_DIR)/FreeRTOS/queue.c \
$(FINNAV_KERNEL_DIR)/FreeRTOS/stream_buffer.c \
$(FINNAV_KERNEL_DIR)/FreeRTOS/tasks.c \
$(FINNAV_KERNEL_DIR)/FreeRTOS/timers.c \
$(FINNAV_KERNEL_DIR)/FreeRTOS/portable/MemMang/$(RTOS_MEM_POOL_TYPE).c \
$(FINNAV_KERNEL_DIR)/FreeRTOS/portable/GCC/$(CORE_VERSION_DIR)/port.c

OS_ASM :=
OS_BSP_INC :=
OS_BSP_DIR :=
OS_BSP_SRC :=
OS_ASM_CFLAG :=
OS_DEFS :=

# CMSIS-RTOS support
ifeq ($(CMSIS_RTOS_VERSION),V1)
CMSIS_RTOS_INC := -I$(FINNAV_KERNEL_DIR)/CMSIS_RTOS/V1
CMSIS_RTOS_SRC := $(FINNAV_KERNEL_DIR)/CMSIS_RTOS/V1/cmsis_os.c
else ifeq ($(CMSIS_RTOS_VERSION),V2)
CMSIS_RTOS_INC := -I$(FINNAV_KERNEL_DIR)/CMSIS_RTOS/V2
CMSIS_RTOS_SRC := $(FINNAV_KERNEL_DIR)/CMSIS_RTOS/V2/cmsis_os2.c
else ifeq ($(CMSIS_RTOS_VERSION),NO)
CMSIS_RTOS_INC :=
CMSIS_RTOS_SRC :=
endif
# *** included ***
