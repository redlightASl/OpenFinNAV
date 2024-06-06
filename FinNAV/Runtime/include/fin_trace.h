#pragma once
#include "Defines.h"

#ifdef LIBROV_USE_TRACE

struct rov_backtrace_frame{
    uint32_t pc;
    uint32_t fp;
};
typedef struct rov_backtrace_frame rov_trace_frame_t;

typedef rov_trace_info_t;

typedef thread_context_t;


rov_err_e rov_backtrace_get_frame(rov_trace_frame_t *frame);
rov_err_e rov_backtrace_collect_info(rov_trace_info_t *info);
void rov_backtrace_print(const rov_trace_info_t *info);

void get_stack_size(uint32_t sp, uint16_t *stack_size)
void set_stack_info(rov_trace_info_t **exc_info_save, uint32_t sp)
void set_context_info(const thread_context_t *task_context, rov_trace_info_t **exc_info_save)

//用于输出当前内存调试信息
void rov_mem_dump(uint32_t addr, size_t size);

//用于线程陷入
rov_err_e rov_trap(thread_context_t *context);

void rov_panic(const int8_t *fmt, ...);

#endif /* LIBROV_USE_TRACE */
