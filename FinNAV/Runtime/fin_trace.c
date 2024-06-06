#include "fin_trace.h"

#ifdef LIBROV_USE_TRACE


VOID LOS_BackTrace(VOID)
{
#ifdef LOSCFG_BACKTRACE
    LosTaskCB *runTask = OsCurrTaskGet();
    PrintExcInfo("runTask->taskName = %s\n""runTask->taskId = %u\n",
        runTask->taskName, runTask->taskId);
    ArchBackTrace();
#endif
}





void rov_panic(const int8_t *fmt, ...)
{
#ifdef LIBROV_USE_PANIC
    va_list ap;
    va_start(ap, fmt);
    // UartVprintf(fmt, ap);
    va_end(ap);
    rov_arch_panic();
#endif /* LIBROV_USE_PANIC */
} //采用汇编在进入hardfault前保存寄存器参数


// static void do_process_exception(exc_context_t *exc_buff_addr)
// {
//     g_exc_info.type = (uint16_t)(exc_buff_addr->mcause);
//     g_exc_info.context = exc_buff_addr;
//     exc_info_display(&g_exc_info);
// }

// void exc_info_display(const exc_info_t *exc)
// {
//     if (exc == NULL) {
//         return;
//     }
//     PRINT("**************Exception Information************** \n");
//     PRINT("uwExcType = 0x%x\n", exc->type);

//     PRINT("mepc       = 0x%x\n", exc->context->task_context.mepc);
//     PRINT("mstatus    = 0x%x\n", exc->context->task_context.mstatus);
//     PRINT("mtval      = 0x%x\n", exc->context->mtval);
//     PRINT("mcause     = 0x%x\n", exc->context->mcause);
//     PRINT("ccause     = 0x%x\n", exc->context->ccause);
// #if CORE == WIFI
//     PRINT("cxcptsc    = 0x%x\n", read_custom_csr(CXCPTSC));
// #endif
//     PRINT("ra         = 0x%x\n", exc->context->task_context.ra);
//     PRINT("sp         = 0x%x\n", exc->context->task_context.sp);
//     PRINT("gp         = 0x%x\n", exc->context->gp);
//     PRINT("tp         = 0x%x\n", exc->context->task_context.tp);
//     PRINT("t0         = 0x%x\n", exc->context->task_context.t0);
//     PRINT("t1         = 0x%x\n", exc->context->task_context.t1);
//     PRINT("t2         = 0x%x\n", exc->context->task_context.t2);
//     PRINT("s0         = 0x%x\n", exc->context->task_context.s0);
//     PRINT("s1         = 0x%x\n", exc->context->task_context.s1);
//     PRINT("a0         = 0x%x\n", exc->context->task_context.a0);
//     PRINT("a1         = 0x%x\n", exc->context->task_context.a1);
//     PRINT("a2         = 0x%x\n", exc->context->task_context.a2);
//     PRINT("a3         = 0x%x\n", exc->context->task_context.a3);
//     PRINT("a4         = 0x%x\n", exc->context->task_context.a4);
//     PRINT("a5         = 0x%x\n", exc->context->task_context.a5);
//     PRINT("a6         = 0x%x\n", exc->context->task_context.a6);
//     PRINT("a7         = 0x%x\n", exc->context->task_context.a7);
//     PRINT("s2         = 0x%x\n", exc->context->task_context.s2);
//     PRINT("s3         = 0x%x\n", exc->context->task_context.s3);
//     PRINT("s4         = 0x%x\n", exc->context->task_context.s4);
//     PRINT("s5         = 0x%x\n", exc->context->task_context.s5);
//     PRINT("s6         = 0x%x\n", exc->context->task_context.s6);
//     PRINT("s7         = 0x%x\n", exc->context->task_context.s7);
//     PRINT("s8         = 0x%x\n", exc->context->task_context.s8);
//     PRINT("s9         = 0x%x\n", exc->context->task_context.s9);
//     PRINT("s10        = 0x%x\n", exc->context->task_context.s10);
//     PRINT("s11        = 0x%x\n", exc->context->task_context.s11);
//     PRINT("t3         = 0x%x\n", exc->context->task_context.t3);
//     PRINT("t4         = 0x%x\n", exc->context->task_context.t4);
//     PRINT("t5         = 0x%x\n", exc->context->task_context.t5);
//     PRINT("t6         = 0x%x\n", exc->context->task_context.t6);

//     PRINT("**************Exception Information end************** \n");
//     return;
// }

#endif /* LIBROV_USE_TRACE */
