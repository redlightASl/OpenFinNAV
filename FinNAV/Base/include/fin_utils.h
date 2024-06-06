/**
 * @file fin_utils.h
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

#define NOOP do {} while (0)

#define ARRAYLEN(x) (sizeof(x) / sizeof((x)[0]))
#define ARRAYEND(x) (&(x)[ARRAYLEN(x)])

#define CONST_CAST(type, value) ((type)(value))

/* Unused function */
#ifdef __GNUC__
#define UNUSED_FUNCTION(x) __attribute__((__unused__)) UNUSED_ ## x
#else
#define UNUSED_FUNCTION(x) UNUSED_ ## x
#endif
/* Unused variables and parameters */
#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

#if ( __GNUC__ ) > 6
#define FALLTHROUGH ;__attribute__ ((fallthrough))
#else
#define FALLTHROUGH do {} while(0)
#endif


