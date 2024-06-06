#pragma once
#include "Defines.h"


#ifdef LIBROV_ENABLE_MEMCTRL
#if defined(CONFIG_TARGET_RTOS_FREERTOS)
#define rov_malloc pvPortMalloc
#define rov_mfree vPortFree
#elif defined(CONFIG_TARGET_RTOS_RTT)
#define rov_malloc rt_malloc
#define rov_mfree rt_free
#elif defined(CONFIG_TARGET_RTOS_LITEOS)
#define rov_malloc malloc
#define rov_mfree free
#else /* CONFIG_TARGET_RTOS_BAREMETAL */
//TODO
#endif /* CONFIG_TARGET_RTOS_FREERTOS, CONFIG_TARGET_RTOS_RTT, CONFIG_TARGET_RTOS_LITEOS, CONFIG_TARGET_RTOS_BAREMETAL */
#else
#include "stdlib.h"
#define rov_malloc malloc
#define rov_mfree free
#endif /* LIBROV_ENABLE_MEMCTRL */
