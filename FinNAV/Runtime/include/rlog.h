/**
 * @file rlog.h
 * @brief 系统LOG实现
 * @author RedlightASl (dddbbbdd@foxmail.com)
 * @version 1.0
 * @date 2023-05-24
 * 
 * @copyright Copyright (c) 2023 RedlightASl
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date    <th>Version  <th>Author     <th>Description
 * <tr><td>2023-05-24  <td>1.0      <td>RedlightASl   <td>Content
 * </table>
 */
#pragma once
#include "Defines.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LIBROV_ENABLE_RLOG
#ifndef RLOG_MAX_LENGTH
#define RLOG_MAX_LENGTH 64
#endif

#ifndef RLOG_MAX_COMMITOR
#define RLOG_MAX_COMMITOR 4
#endif

enum rlog_level_enum
{
    RLOG_DEBUG=1,
    RLOG_INFO,
    RLOG_WARNING,
    RLOG_ERROR
};
typedef enum rlog_level rlog_level_enum;

#define DEBUG_LEVEL RLOG_LOG
#define RLOG_INIT() Rlog_init()
#define RLOG_COMMIT(a, b) Rlog_commit(a, b)
#define RLOG_UNCOMMIT(a) Rlog_uncommit(a)
#define RLOG_LEVEL_NAME(a) Rlog_level_name(a)
#define RLOG(...) rov_printf(__VA_ARGS__)
#define RLOG_DEBUG(...) rov_printf(RLOG_DEBUG, __VA_ARGS__)
#define RLOG_INFO(...) rov_printf(RLOG_INFO, __VA_ARGS__)
#define RLOG_WARNING(...) rov_printf(RLOG_WARNING, __VA_ARGS__)
#define RLOG_ERROR(...) rov_printf(RLOG_ERROR, __VA_ARGS__)


typedef void (*rlog_entry_t)(rlog_level_enum log_level, char *m);

void Rlog_init(void);
uint8_t Rlog_commit(rlog_entry_t entry, rlog_level_enum log_level);
uint8_t Rlog_uncommit(rlog_entry_t entry);
const char *Rlog_level_name(rlog_level_enum log_level);
uint32_t rov_printf(rlog_level_enum log_level, const char *format, ...);
#ifdef LIBROV_USE_STDIO
void rlog_create(rlog_level_enum log_level);
#endif /* LIBROV_USE_STDIO */
#else
#define RLOG_INIT() do {} while(0)
#define RLOG_COMMIT(a, b) do {} while(0)
#define RLOG_UNCOMMIT(a) do {} while(0)
#define RLOG_LEVEL_NAME(a) do {} while(0)
#define RLOG(s, f, ...) do {} while(0)
#define RLOG_DEBUG(f, ...) do {} while(0)
#define RLOG_INFO(f, ...) do {} while(0)
#define RLOG_WARNING(f, ...) do {} while(0)
#define RLOG_ERROR(f, ...) do {} while(0)
#endif /* LIBROV_ENABLE_RLOG */

#ifdef __cplusplus
}
#endif
