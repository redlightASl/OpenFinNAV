/**
 * @file Defines.h
 * @brief 进行各种基础数据类型的定义
 * @author RedlightASl (dddbbbdd@foxmail.com)
 * @version 1.0
 * @date 2021-09-13
 *
 * @copyright Copyright (c), 2009-2023, OurEDA Underwater Robot Team, DLUT.
 * This file is part of FinNAV LibROV.
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-09-13 <td>1.0     <td>wangh     <td>Content
 * </table>
 */
#pragma once
#include "fin_setup.h"
#include "fin_versions.h"
#include "fin_types.h"
#include "fin_utils.h"


#if defined ( __ARMCC_VERSION ) && ( __ARMCC_VERSION >= 6010050 )
/* new version of armcc */
#define __CLANG_ARM
#endif

#if defined( __CC_ARM ) || defined( __CLANG_ARM ) /* Keil MDK */
#ifdef LIBROV_PRINT_ALL_LOGS
#warning "Using MDK!"
#endif

#define MEM_ALIGN_32BYTES ALIGN_32BYTES
#define ROV_ATTRIB_SECTION(__section__) __attribute__((section(__section__)))
#define ROV_STABLE_MEMORY_SPACE(__ram_district__) __attribute__((section(__ram_district__)))
#define ROV_WEAK __attribute__((weak))
#define ROV_INLINE static __inline
#elif defined( __IAR_SYSTEMS_ICC__ )
#ifdef LIBROV_PRINT_ALL_LOGS
#pragma message("Using IAR!") /* IAR */
#endif

#define MEM_ALIGN_32BYTES ALIGN_32BYTES
#define ROV_ATTRIB_SECTION(__section__) __attribute__((section(__section__)))
#define ROV_STABLE_MEMORY_SPACE(__ram_district__) __attribute__((section(__ram_district__)))
#define ROV_WEAK __weak
#define ROV_INLINE static inline
#elif defined( __GNUC__ ) /* GCC */
#ifdef LIBROV_PRINT_ALL_LOGS
#pragma message("Using GCC!")
#endif

#define MEM_ALIGN_32BYTES ALIGN_32BYTES
#define ROV_ATTRIB_SECTION(__section__) __attribute__((section(__section__)))
#define ROV_STABLE_MEMORY_SPACE(__ram_district__) __attribute__((section(__ram_district__)))
#define ROV_WEAK __attribute__((weak))
#define ROV_INLINE static __inline
#else
#error FinNAV Do not supporte this toolchain!
#endif

ROV_INLINE void fin_interrupt_enable(void)
{
#if defined(CONFIG_TARGET_RTOS_FREERTOS)
    portENABLE_INTERRUPTS();
#elif defined(CONFIG_TARGET_RTOS_RTT)
    rt_hw_interrupt_enable();
#elif defined(CONFIG_TARGET_RTOS_LITEOS)
    LOS_IntUnLock();
else /* CONFIG_TARGET_RTOS_BAREMETAL */
    __enable_irq(); //HACK: for CMSIS only
#endif /* CONFIG_TARGET_RTOS_FREERTOS, CONFIG_TARGET_RTOS_RTT, CONFIG_TARGET_RTOS_LITEOS, CONFIG_TARGET_RTOS_BAREMETAL */
}

ROV_INLINE void fin_interrupt_disable(void)
{
#if defined(CONFIG_TARGET_RTOS_FREERTOS)
    portDISABLE_INTERRUPTS();
#elif defined(CONFIG_TARGET_RTOS_RTT)
    rt_hw_interrupt_disable();
#elif defined(CONFIG_TARGET_RTOS_LITEOS)
    LOS_IntLock();
else /* CONFIG_TARGET_RTOS_BAREMETAL */
    __disable_irq(); //HACK: for CMSIS only
#endif /* CONFIG_TARGET_RTOS_FREERTOS, CONFIG_TARGET_RTOS_RTT, CONFIG_TARGET_RTOS_LITEOS, CONFIG_TARGET_RTOS_BAREMETAL */
}

#include "fin_list.h"
#include "fin_assert.h"
#include "fin_panic.h"
