#include "Driver.h"
#include "drv_uart.h"


#ifdef LIBROV_ENABLE_DRIVER_UART
dev_instance_t uart_inst[UART_DEV_MAX_NUM];

void drv_uart_init(drv_uart_t* drv)
{
    for (uint8_t i = 0;i < UART_DEV_MAX_NUM;i++)
    {
        drv->device[i].dev_ctrl.probe = bsp_uart_probe;
        drv->device[i].dev_ctrl.read = bsp_uart_read;
        drv->device[i].dev_ctrl.write = bsp_uart_write;
        drv->device[i].dev_ctrl.ioctl = bsp_uart_ioctl;

        drv_device_regmap(&drv->device[i], &uart_inst[i]);
        drv_device_create(&drv->device[i], i, DEV_UART);
        drv_device_irq_hook(&drv->device[i], 0, (ROV_VOID_POINTER)0);
    }
}

void drv_uart_read(drv_uart_t* drv, uint32_t obj, uint8_t* rd_buffer, uint32_t size)
{
    drv->device[obj].dev_ctrl.read(&(drv->device[obj]), rd_buffer, size);
}

void drv_uart_write(drv_uart_t* drv, uint32_t obj, uint8_t* wr_buffer, uint32_t size)
{
    drv->device[obj].dev_ctrl.write(&(drv->device[obj]), wr_buffer, size);
}

void drv_uart_set_baudrate(drv_uart_t* drv, uint32_t obj, uint32_t baudrate)
{
    drv->device[obj].dev_ctrl.ioctl(&(drv->device[obj]), UART_IOCTL_SET_BAUDRATE, baudrate);
}

void drv_uart_set_databits(drv_uart_t* drv, uint32_t obj, uint8_t databits)
{
    drv->device[obj].dev_ctrl.ioctl(&(drv->device[obj]), UART_IOCTL_SET_DATA_BITS, databits);
}

void drv_uart_set_stopbit(drv_uart_t* drv, uint32_t obj, uint8_t stopbit)
{
    drv->device[obj].dev_ctrl.ioctl(&(drv->device[obj]), UART_IOCTL_SET_STOP_BITS, stopbit);
}

void drv_uart_set_parity(drv_uart_t* drv, uint32_t obj, uint8_t parity)
{
    drv->device[obj].dev_ctrl.ioctl(&(drv->device[obj]), UART_IOCTL_SET_PARITY, parity);
}

void drv_uart_set_flow(drv_uart_t* drv, uint32_t obj, uint8_t flow_control)
{
    drv->device[obj].dev_ctrl.ioctl(&(drv->device[obj]), UART_IOCTL_SET_FLOW_CONTROL, flow_control);
}

void drv_uart_set_tx_timeout(drv_uart_t* drv, uint32_t obj, uint8_t tx_timeout)
{
    drv->device[obj].dev_ctrl.ioctl(&(drv->device[obj]), UART_IOCTL_SET_TX_TIMEOUT, tx_timeout);
}

void drv_uart_set_rx_timeout(drv_uart_t* drv, uint32_t obj, uint8_t rx_timeout)
{
    drv->device[obj].dev_ctrl.ioctl(&(drv->device[obj]), UART_IOCTL_SET_RX_TIMEOUT, rx_timeout);
}

void drv_uart_find(drv_uart_t* drv, UART_DEV_INSTANCE* inst, uint8_t* obj)
{
    *obj = drv_device_find_obj(drv->device, UART_DEV_MAX_NUM, (ROV_VOID_POINTER)inst);
}
#endif
