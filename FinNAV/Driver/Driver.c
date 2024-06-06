#include "Driver.h"


#ifdef LIBROV_USE_DRIVER
#ifndef BSP_CONFIG_FILE
#error "Modify BSP Configuration Header File!"
#else
#include BSP_CONFIG_FILE
#endif /* BSP_CONFIG_FILE */

#define drv_probe (dev->ops->probe)
#define drv_reset (dev->ops->reset)
#define drv_sleep (dev->ops->sleep)
#define drv_read (dev->ops->read)
#define drv_write (dev->ops->write)
#define drv_ioctl (dev->ops->ioctl)


//设备链表实例
static rov_list_t _dev_list_inst = ROV_LIST_INST_INIT(_dev_list_inst);

/**
 * @brief 外设初始化
 * @param  dev              外设对象
 * @param  type             外设类型
 * @param  flag             外设固有标志
 * @param  ops              外设驱动
 * @return rov_err_t ROV_PASS成功
 */
rov_err_t drv_device_attach(rov_dev_t* dev, dev_type_t type, uint8_t flag, dev_ops_t* ops)
{
    if (dev == NULL)
    {
        return ROV_PANIC;
    }
    if (type == DEV_TYPE_UNKNOWN)
    {
        return ROV_INVALID;
    }
    if (ops == NULL)
    {
        return ROV_INVALID;
    }

    rov_list_head_insert(&_dev_list_inst, &(dev->list)); //挂载到设备链表
    dev->type = type;
    dev->flag = flag;
    dev->ops = ops;
    return ROV_PASS;
}

/**
 * @brief 外设反初始化
 * @param  dev              外设对象
 * @return rov_err_t ROV_PASS成功
 */
rov_err_t drv_device_detach(rov_dev_t* dev)
{
    if (dev == NULL)
    {
        return ROV_PANIC;
    }

    dev->type = DEV_TYPE_EMPTY;
    dev->flag = DEV_FLAG_REMOVABLE;
    dev->ops = NULL;
    rov_list_remove(&(dev->list));
    return ROV_PASS;
}

/**
 * @brief 外设硬件实例映射
 * @param  dev              外设对象
 * @param  inst             硬件实例
 * @return rov_err_t ROV_PASS成功
 */
rov_err_t drv_device_regmap(rov_dev_t* dev, dev_instance_t inst)
{
    if (dev == NULL)
    {
        return ROV_PANIC;
    }
    if (inst == NULL)
    {
        return ROV_INVALID;
    }

    dev->inst = inst;
    return ROV_PASS;
}

/**
 * @brief 设备自检
 * @param  dev              外设对象
 * @return rov_err_t ROV_PASS成功
 */
rov_err_t drv_device_probe(rov_dev_t* dev)
{
    if (dev == NULL)
    {
        return ROV_PANIC;
    }
    rov_err_t ret = ROV_ERROR;

    if (drv_probe != NULL)
    {
        if (!(dev->flag & DEV_FLAG_ACTIVATED))
        {
            ret = drv_probe(dev);
            if (ret == ROV_PASS)
            {
                dev->flag |= DEV_FLAG_ACTIVATED;
            }
        }
    }
    return ret;
}

/**
 * @brief 设备复位
 * @param  dev              外设对象
 * @return rov_err_t ROV_PASS成功
 */
rov_err_t drv_device_reset(rov_dev_t* dev)
{
    if (dev == NULL)
    {
        return ROV_PANIC;
    }
    rov_err_t ret = ROV_ERROR;

    if (drv_reset != NULL)
    {
        ret = drv_reset(dev);
    }
    if (ret == ROV_PASS)
    {
        dev->flag = DEV_FLAG_SUSPENDED;
    }
    return ret;
}

/**
 * @brief 设备读取
 * @param  dev              外设对象
 * @param  rd_buffer        读缓冲区
 * @param  size             要读取数据长度
 * @return uint32_t 成功读取数据的字节数
 * @note 若返回0则写入失败
 */
uint32_t drv_device_read(rov_dev_t* dev, void* rd_buffer, const uint32_t size)
{
    if (dev == NULL)
    {
        return ROV_PANIC;
    }
    if (drv_read != NULL)
    {
        return drv_read(dev, rd_buffer, size);
    }
    return 0;
}

/**
 * @brief 设备写入
 * @param  dev              外设对象
 * @param  wr_buffer        写缓冲区
 * @param  size             要写入数据长度
 * @return uint32_t 成功写入的字节数
 * @note 若返回0则写入失败
 */
uint32_t drv_device_write(rov_dev_t* dev, const void* wr_buffer, const uint32_t size)
{
    if (dev == NULL)
    {
        return ROV_PANIC;
    }
    if (drv_write != NULL)
    {
        return drv_write(dev, wr_buffer, size);
    }
    return 0;
}

/**
 * @brief 设备综合控制
 * @param  dev              外设对象
 * @param  cmd              控制指令
 * @param  args             指令参数列表
 * @return rov_err_t ROV_PASS成功
 */
rov_err_t drv_device_ioctl(rov_dev_t* dev, const int32_t cmd, void* args)
{
    if (dev == NULL)
    {
        return ROV_PANIC;
    }
    if (args == NULL)
    {
        return drv_ioctl(dev, cmd, args);
    }
    return ROV_PASS;
}

/**
 * @brief 按设备类型返回外设对象
 * @param  id               设备类型
 * @return rov_dev_t* 外设对象
 */
rov_dev_t* drv_device_find_from_type(dev_type_t type)
{
    if (type == DEV_TYPE_UNKNOWN)
    {
        return ROV_INVALID;
    }

    rov_dev_t* dev_res = NULL;
    struct rov_list_node* node = NULL;

    ROV_LIST_FOR_EACH(node, &_dev_list_inst)
    {
        dev_res = ROV_LIST_ENTRY(node, struct rov_dev, list);
        if (dev_res->id == id)
        {
            return dev_res;
        }
    }
    return NULL;
}

/**
 * @brief 按外设实例返回外设对象
 * @param  inst             外设对象
 * @return rov_dev_t* 外设对象
 */
rov_dev_t* drv_device_find_from_inst(dev_instance_t inst)
{
    if (inst == NULL)
    {
        return ROV_INVALID;
    }

    rov_dev_t* dev_res = NULL;
    struct rov_list_node* node = NULL;

    ROV_LIST_FOR_EACH(node, &_dev_list_inst)
    {
        dev_res = ROV_LIST_ENTRY(node, struct rov_dev, list);
        if (dev_res->inst == inst)
        {
            return dev_res;
        }
    }
    return NULL;
}

/**
 * @brief 获得设备ID
 * @param  dev              外设对象
 * @return uint8_t 设备ID
 */
uint8_t drv_device_get_id(rov_dev_t* dev)
{
    if (dev == NULL)
    {
        return 0;
    }
    return dev->id;
}

/**
 * @brief 获得设备类型
 * @param  dev              外设对象
 * @return dev_type_t 设备类型
 */
dev_type_t drv_device_get_type(rov_dev_t* dev)
{
    if (dev == NULL)
    {
        return DEV_TYPE_UNKNOWN;
    }
    return dev->type;
}

/**
 * @brief 获得设备实例
 * @param  dev              外设对象
 * @return dev_instance_t 设备实例
 */
dev_instance_t drv_device_get_inst(rov_dev_t* dev)
{
    if (dev == NULL)
    {
        return NULL;
    }
    return dev->inst;
}


#ifdef LIBROV_HANDLE_INTERRUPT
/**
 * @brief 绑定中断对象到外设
 * @param  dev              外设对象
 * @param  irq              中断对象
 * @return rov_err_t ROV_PASS成功
 */
rov_err_t drv_device_irq_hook(rov_dev_t* dev, fin_irq_t* irq)
{
    rov_assert(dev != NULL);
    rov_assert(irq != NULL);
    NOOP;
}
#endif /* LIBROV_HANDLE_INTERRUPT */


void drv_soc_init(void)
{
    /* Instruction Cache Enable */
#ifdef CONFIG_SOC_USE_ICACHE
#endif
/* Data Cache Enable */
#ifdef CONFIG_SOC_USE_DCACHE
#endif
/* DSP Enable */
#ifdef LIBROV_ENABLE_DRIVER_DSP
#endif
/* Peripheral Driver Enable */
#ifdef LIBROV_ENABLE_DRIVER_GPIO

#endif
#ifdef LIBROV_ENABLE_DRIVER_UART

#endif
#ifdef LIBROV_ENABLE_DRIVER_DMA
#endif
#ifdef LIBROV_ENABLE_DRIVER_ADC
#endif
#ifdef LIBROV_ENABLE_DRIVER_DAC
#endif
#ifdef LIBROV_ENABLE_DRIVER_PWM
#endif
#ifdef LIBROV_ENABLE_DRIVER_HWTIM
#endif
#ifdef LIBROV_ENABLE_DRIVER_RTC
#endif
#ifdef LIBROV_ENABLE_DRIVER_WDG
#endif
#ifdef LIBROV_ENABLE_DRIVER_I2C
#endif
#ifdef LIBROV_ENABLE_DRIVER_I2C_SOFT
#endif
#ifdef LIBROV_ENABLE_DRIVER_SPI
#endif
#ifdef LIBROV_ENABLE_DRIVER_CAN
#endif
#ifdef LIBROV_ENABLE_DRIVER_CANFD
#endif
#ifdef LIBROV_ENABLE_DRIVER_ONCHIP_FLASH
#endif
#ifdef LIBROV_ENABLE_DRIVER_SDIO
#endif
#ifdef LIBROV_ENABLE_DRIVER_PARALLEL
#endif
#ifdef LIBROV_ENABLE_DRIVER_ETH
#endif
#ifdef LIBROV_ENABLE_DRIVER_FPGA
#endif
}


void drv_linkcom_init(void)
{
    NOOP;
}

void drv_console_init(void)
{
    NOOP;
}

ROV_WEAK void drv_board_init(void)
{
    extern void drv_soc_init(void);

    drv_soc_init(); //SoC Startup
    drv_linkcom_init(); //LinkCOM Initialization
    drv_console_init(); //Console Initialization
}

#endif
