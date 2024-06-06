#pragma once
#include "Defines.h"


#ifdef LIBROV_HANDLE_INTERRUPT

typedef void (*fin_irq_cb)(int32_t irq, ROV_VOID_POINTER arg);

struct fin_irq
{
    int32_t irqno; //IRQ number
    fin_irq_cb callback; //IRQ Callback Function
    ROV_VOID_POINTER args; //IRQ Callback Arguments
};
typedef struct fin_irq fin_irq_t;

void fin_interrupt_init(void);
void fin_interrupt_register(int32_t irq, fin_irq_cb callback, ROV_VOID_POINTER args);
#endif /* LIBROV_HANDLE_INTERRUPT */
