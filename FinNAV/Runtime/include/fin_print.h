#pragma once
#include "Defines.h"
#include <stdarg.h>
#include <stdlib.h>

typedef void (*putcf) (void *, char);
extern putcf stdout_putf;
extern void *stdout_putp;

void init_printf(void *putp, void (*putf) (void *, char));
int tfp_sprintf(char *s, const char *fmt, ...);
int tfp_format(void *putp, void (*putf) (void *, char), const char *fmt, va_list va);