/**
 * @file fin_assert.h
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

#ifdef LIBROV_USE_ASSERT

#ifdef LIBROV_USE_KPRINT
#define rov_assert(expr) do { \
    if ((uint64_t)(expr) == 0) { \
        rov_kprintf("ASSERT FAILED AT %s, %s, %d!\r\n", __FILE__, __FUNCTION__, __LINE__); \
        fin_interrupt_disable(); \
        while (1) {} \
    } \
} while(0)
#else
#define rov_assert(expr) do { \
    if ((uint64_t)(expr) == 0) { \
        fin_interrupt_disable(); \
        while (1) {} \
    } \
} while(0)
#endif /* LIBROV_USE_KPRINT */

#else
#define rov_assert(expr)
#endif /* LIBROV_USE_ASSERT */
