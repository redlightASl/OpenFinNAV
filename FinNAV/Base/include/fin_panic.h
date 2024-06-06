/**
 * @file fin_panic.h
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

#ifdef LIBROV_USE_PANIC
ROV_INLINE void rov_arch_panic(void)
{
#if defined(CONFIG_TARGET_RTOS_FREERTOS)
    fin_interrupt_disable();
    while (1) {}
#elif defined(CONFIG_TARGET_RTOS_RTT)
    rt_hw_cpu_shutdown();
#elif defined(CONFIG_TARGET_RTOS_LITEOS)
    ArchHaltCpu();
else /* CONFIG_TARGET_RTOS_BAREMETAL */
    fin_interrupt_disable();
    while (1) {}
#endif /* CONFIG_TARGET_RTOS_FREERTOS, CONFIG_TARGET_RTOS_RTT, CONFIG_TARGET_RTOS_LITEOS, CONFIG_TARGET_RTOS_BAREMETAL */
}
#endif /* LIBROV_USE_PANIC */
