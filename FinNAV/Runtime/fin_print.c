#include "fin_print.h"




// #ifdef LIBROV_CONSOLE_UART
// #if (CONSOLE_DEV_NUMBER > 12)
// #error "Please define a valid CONSOLE_UART between 1 to 12!"
// #endif

// #include <stdarg.h>

// int8_t rov_print(const char* format, ...)
// {
//     uint16_t len;
//     int8_t SEND_STATUS;
//     va_list args;
//     uint8_t _buffer[DEBUG_UART_SIZE];

//     va_start(args, format);
//     len = vsnprintf((char*)_buffer, sizeof(_buffer) + 1, (char*)format, args);
//     va_end(args);
//     drv_uart_write(&sys_drv_uart, CONSOLE_DEV_NUMBER, _buffer, len);
//     //memset(dma_printf_buffer, 0, DEBUG_UART_DMA_SIZE);
//     return SEND_STATUS;
// }

#ifdef LIBROV_USE_STDIO
#include <stdio.h>
/* re-direct printf() */
#if defined (__CC_ARM) /* ARMCC */
#pragma import(__use_no_semihosting)
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *p)
PUTCHAR_PROTOTYPE;
#elif defined (__GNUC__) /* GNUC */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
PUTCHAR_PROTOTYPE;
ROV_WEAK int _write(int file, char *ptr, int len)
{
    int DataIdx;
    for (DataIdx = 0; DataIdx < len; DataIdx++)
    {
        __io_putchar(*ptr++);
    }
    return len;
}
#else /* others */
struct __FILE
{
    int handle;
};
FILE __stdout;

int fputc(int ch, FILE* stream)
{
    while ((USART1->ISR & 0X40) == 0);
    USART1->TDR = (uint8_t)ch;
    return ch;
}
#endif

//define _sys_exit to avoid semihosting
void _sys_exit(int x)
{
    x = x;
}

void _ttywrch(int ch)
{
    ch = ch;
}

// #ifdef UART_DEV_TX_USE_DMA
// ROV_WEAK PUTCHAR_PROTOTYPE
// {
//     drv_uart_write(&sys_drv_uart, CONSOLE_DEV_NUMBER, (uint8_t*)&ch, 1);
    
//     return ch;
// }
// #else
// ROV_WEAK PUTCHAR_PROTOTYPE
// {
//     drv_uart_write(&sys_drv_uart, CONSOLE_DEV_NUMBER, (uint8_t*)&ch, 1);
//     return ch;
// }
// #endif

// #if defined ENABLE_STDIO_DMA
// PUTCHAR_PROTOTYPE
// {
//     HAL_UART_Transmit_DMA(&CONSOLE_UART_INSTANCE, (uint8_t*)&ch, 1);
//     while (!(__HAL_UART_GET_FLAG(&CONSOLE_UART_INSTANCE, UART_FLAG_TC))) {}
//     return ch;
// }
// #elif defined ENABLE_STDIO_IT
// PUTCHAR_PROTOTYPE
// {
//     HAL_UART_Transmit_IT(&CONSOLE_UART_INSTANCE, (uint8_t*)&ch, 1);
//     while (!(__HAL_UART_GET_FLAG(&CONSOLE_UART_INSTANCE, UART_FLAG_TC))) {}
//     return ch;
// }
// #elif defined ENABLE_STDIO_POLLING
#else
putcf stdout_putf;
void *stdout_putp;

// print bf, padded from left to at least n characters.
// padding is zero ('0') if z!=0, space (' ') otherwise
static int putchw(void *putp, putcf putf, int n, char z, char *bf)
{
    int written = 0;
    char fc = z ? '0' : ' ';
    char ch;
    char *p = bf;
    while (*p++ && n > 0)
        n--;
    while (n-- > 0) {
        putf(putp, fc); written++;
    }
    while ((ch = *bf++)) {
        putf(putp, ch); written++;
    }
    return written;
}

// retrun number of bytes written
int tfp_format(void *putp, putcf putf, const char *fmt, va_list va)
{
    char bf[12];
    int written = 0;
    char ch;

    while ((ch = *(fmt++))) {
        if (ch != '%') {
            putf(putp, ch); written++;
        } else {
            char lz = 0;
#ifdef  REQUIRE_PRINTF_LONG_SUPPORT
            char lng = 0;
#endif
            int w = 0;
            ch = *(fmt++);
            if (ch == '0') {
                ch = *(fmt++);
                lz = 1;
            }
            if (ch >= '0' && ch <= '9') {
                ch = a2i(ch, &fmt, 10, &w);
            }
#ifdef  REQUIRE_PRINTF_LONG_SUPPORT
            if (ch == 'l') {
                ch = *(fmt++);
                lng = 1;
            }
#endif
            switch (ch) {
            case 0:
                goto abort;
            case 'u':{
#ifdef  REQUIRE_PRINTF_LONG_SUPPORT
                    if (lng)
                        uli2a(va_arg(va, unsigned long int), 10, 0, bf);
                    else
#endif
                        ui2a(va_arg(va, unsigned int), 10, 0, bf);
                    written += putchw(putp, putf, w, lz, bf);
                    break;
                }
            case 'd':{
#ifdef  REQUIRE_PRINTF_LONG_SUPPORT
                    if (lng)
                        li2a(va_arg(va, unsigned long int), bf);
                    else
#endif
                        i2a(va_arg(va, int), bf);
                    written += putchw(putp, putf, w, lz, bf);
                    break;
                }
            case 'x':
            case 'X':
#ifdef  REQUIRE_PRINTF_LONG_SUPPORT
                if (lng)
                    uli2a(va_arg(va, unsigned long int), 16, (ch == 'X'), bf);
                else
#endif
                    ui2a(va_arg(va, unsigned int), 16, (ch == 'X'), bf);
                written += putchw(putp, putf, w, lz, bf);
                break;
            case 'c':
                putf(putp, (char) (va_arg(va, int))); written++;
                break;
            case 's':
                written += putchw(putp, putf, w, 0, va_arg(va, char *));
                break;
            case '%':
                putf(putp, ch); written++;
                break;
            case 'n':
                *va_arg(va, int*) = written;
                break;
            default:
                break;
            }
        }
    }
abort:
    return written;
}

void init_printf(void *putp, void (*putf) (void *, char))
{
    stdout_putf = putf;
    stdout_putp = putp;
}

static void putcp(void *p, char c)
{
    *(*((char **) p))++ = c;
}

int tfp_sprintf(char *s, const char *fmt, ...)
{
    va_list va;

    va_start(va, fmt);
    int written = tfp_format(&s, putcp, fmt, va);
    putcp(&s, 0);
    va_end(va);
    return written;
}
#endif /* LIBROV_USE_STDIO */

// #endif /* LIBROV_CONSOLE_UART */