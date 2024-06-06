/**
 * @file fin_types.h
 * @brief
 * @author RedlightASl (dddbbbdd@foxmail.com)
 * @version 1.0
 * @date 2024-04-01
 *
 * @copyright Copyright (c), 2009-2023, OurEDA Underwater Robot Team, DLUT.
 * This file is part of FinNAV LibROV.
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date    <th>Version  <th>Author     <th>Description
 * <tr><td>2024-04-01  <td>1.0      <td>RedlightASl   <td>Content
 * </table>
 */
#pragma once

#if defined (CONFIG_TARGET_RTOS_RTT) /* Use RT-Thread */
typedef unsigned char uint8_t; /**< unsigned 8bit integer type */
typedef unsigned short uint16_t; /**< unsigned 16bit integer type */
typedef unsigned int uint32_t; /**< unsigned 32bit integer type */
typedef unsigned long long uint64_t; /**< unsigned 64bit integer type */
typedef signed char int8_t; /**< signed 8bit integer type */
typedef signed short int16_t; /**< signed 16bit integer type */
typedef signed int int32_t; /**< signed 32bit integer type */
typedef signed long long int64_t; /**< signed 64bit integer type */
typedef unsigned long size_t;
typedef signed long ssize_t;
typedef unsigned int uintptr_t;

#define ROV_TRUE RT_EOK /* RT_EOK == 0 */ /**< no error */
#define ROV_FALSE RT_ERROR /* RT_ERROR == 1*/ /**< generic error */
#elif defined (CONFIG_TARGET_RTOS_FREERTOS) /* Use FreeRTOS */
#include <stddef.h>
#include <stdint.h>
#define ROV_TRUE 1 /**< no error */
#define ROV_FALSE 0 /**< generic error */
#elif defined (CONFIG_TARGET_RTOS_LITEOS) /* Use LiteOS */
//TODO
#else /* Use Baremetal */
#include <stddef.h>
#include <stdint.h>
#define ROV_TRUE 1 /**< no error */
#define ROV_FALSE 0 /**< generic error */
#endif /* CONFIG_TARGET_RTOS_RTT, CONFIG_TARGET_RTOS_FREERTOS, CONFIG_TARGET_RTOS_LITEOS, CONFIG_TARGET_RTOS_BAREMETAL */
typedef float fp32_t; /**< signed 32bit float type */
typedef double fp64_t; /**< signed 64bit float type */

typedef void* ROV_VOID_POINTER;

#define HW_REG_WO volatile /* write only register */
#define HW_REG_RO volatile const /* read only register */
#define HW_REG_WR volatile /* read-write register */

typedef volatile unsigned char vuint8_t; /**<  8bit IO__ integer type */
typedef volatile unsigned short vuint16_t; /**< 16bit IO__ integer type */
typedef volatile unsigned int vuint32_t; /**< 32bit IO__ integer type */

#ifdef LIBROV_USE_STDBOOL
#include <stdbool.h>
#else
#define bool _Bool
#define true 1
#define false 0
#endif

#define UINT8_T_MAX 0xff /**< Maxium number of uint8_t */
#define UINT16_T_MAX 0xffff /**< Maxium number of uint16_t */
#define UINT32_T_MAX 0xffffffff /**< Maxium number of uint32_t */

typedef void (*pFunc)(void);
#define IS_VALID_FUNCTION_ADDR(addr) ((void*)(addr) != NULL && ((uintptr_t)(addr) & 1) == 0)
#define JUMPTO_FORCE(_addr) do { \
    if(IS_VALID_FUNCTION_ADDR(_addr) == 1) { \
        pFunc addr = (pFunc)(*((volatile unsigned int*)(_addr))); \
        addr(); \
    } \
} while(0)

/* ROV Error State Flags */
#define ROV_PASS    0 /**< no error */
#define ROV_ERROR   1 /**< generic error */
#define ROV_TIMEOUT 2 /**< timeout error */
#define ROV_BUSY    3 /**< resource busy */
#define ROV_FULL    4 /**< resource full */
#define ROV_EMPTY   5 /**< resource empty */
#define ROV_INVALID 6 /**< invalid argument */
#define ROV_MEMOUT  7 /**< out of memory */
#define ROV_PANIC   8 /**< finnav panic */
typedef uint8_t rov_err_t;
