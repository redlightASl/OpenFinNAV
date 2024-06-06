#include "gy26_driver.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"


// uint8_t dev_id; //Device ID
// uint8_t dev_type; //Device Type
// dev_instance_t dev_instance; //Device Registers
// dev_irq_t dev_irq; //Device IRQ Handler

// int8_t gy26_sense(struct rov_dev* device, ROV_VOID_POINTER sensor_data);
// int8_t gy26_sleep(struct rov_dev* device, uint32_t time);



// int8_t gy26_init(struct rov_dev* device)
// {
//     device->dev_id = 1;
//     device->dev_type = 1;
//     // device->dev_instance;
//     device->dev_irq.irq = -1;
//     device->dev_irq.cb_function = (void*)(0);

//     // device->read = gy26_read;
//     // device->write = gy26_write;
//     device->sense = gy26_sense;

//     return ROV_TRUE; 
// }



// int8_t gy26_sleep(struct rov_dev* device, uint32_t time)
// {

// }


// int8_t gy26_read(struct rov_dev* device, uint8_t* rd_buffer, uint32_t size)
// {

//     HAL_I2C_Mem_Write(&hi2c2, DEVICE_ADDR, 0x00, I2C_MEMADD_SIZE_8BIT, &tx_data, 1, 100);
//     HAL_I2C_Mem_Read(&hi2c2, DEVICE_ADDR, 0X01, I2C_MEMADD_SIZE_8BIT, &dev.mag_h, 2, 1000);

// }

// int8_t gy26_write(struct rov_dev* device, uint8_t* wr_buffer, uint32_t size)
// {
//     HAL_I2C_Mem_Write(&hi2c2, DEVICE_ADDR, 0x00, I2C_MEMADD_SIZE_8BIT, &tx_data, 1, 100);
// }

// int8_t gy26_sense(struct rov_dev* device, ROV_VOID_POINTER sensor_data)
// {
//     uint8_t tx_data = 0x31;
//     gy26_driver_t dev;
//     gy26_driver_t* sensor_data_p = (gy26_driver_t*)sensor_data;

//     HAL_I2C_Mem_Write(&hi2c2, DEVICE_ADDR, 0x00, I2C_MEMADD_SIZE_8BIT, &tx_data, 1, 1);
//     HAL_I2C_Mem_Read(&hi2c2, DEVICE_ADDR, 0X01, I2C_MEMADD_SIZE_8BIT, &dev.mag_h, 1, 1);
//     HAL_I2C_Mem_Read(&hi2c2, DEVICE_ADDR, 0X02, I2C_MEMADD_SIZE_8BIT, &dev.mag_l, 1, 1);
//     dev.mag_data = (uint16_t)(((uint16_t)dev.mag_h << 8) | ((uint16_t)dev.mag_l));

//     // tx_data = 0x35;
//     // HAL_I2C_Mem_Write(&hi2c2, DEVICE_ADDR, 0x00, I2C_MEMADD_SIZE_8BIT, &tx_data, 1, 100);
//     // HAL_I2C_Mem_Read(&hi2c2, DEVICE_ADDR, 0X05, I2C_MEMADD_SIZE_8BIT, &dev.temp_h, 1, 1000);
//     // HAL_I2C_Mem_Read(&hi2c2, DEVICE_ADDR, 0X06, I2C_MEMADD_SIZE_8BIT, &dev.temp_l, 1, 1000);
//     // dev.temp_data = (uint16_t)(((uint16_t)dev.temp_h << 8) | ((uint16_t)dev.temp_l));

//     *sensor_data_p = dev;
// }


void read_mag(gy26_driver_t* dev)
{
    uint8_t tx_data = 0x31;
    uint8_t mag_h = 0x00;
    uint8_t mag_l = 0x00;
    HAL_I2C_Mem_Write(&hi2c1, DEVICE_ADDR, 0x00, I2C_MEMADD_SIZE_8BIT, &tx_data, 1, 100);
    // HAL_Delay(10);
    osDelay(10);
    HAL_I2C_Mem_Read(&hi2c1, DEVICE_ADDR, 0X01, I2C_MEMADD_SIZE_8BIT, &mag_h, 1, 100);
    // HAL_Delay(10);
    osDelay(10);
    HAL_I2C_Mem_Read(&hi2c1, DEVICE_ADDR, 0X02, I2C_MEMADD_SIZE_8BIT, &mag_l, 1, 100);
    dev->mag_data = (uint16_t)(((uint16_t)mag_h << 8) | ((uint16_t)mag_l));
}

void read_temp(gy26_driver_t* dev)
{
    uint8_t tx_data = 0x35;
    uint8_t temp_h = 0x00;
    uint8_t temp_l = 0x00;
    HAL_I2C_Mem_Write(&hi2c1, DEVICE_ADDR, 0x00, I2C_MEMADD_SIZE_8BIT, &tx_data, 1, 100);
    // HAL_Delay(10);
    osDelay(10);
    HAL_I2C_Mem_Read(&hi2c1, DEVICE_ADDR, 0X05, I2C_MEMADD_SIZE_8BIT, &temp_h, 1, 1000);
    // HAL_Delay(10);
    osDelay(10);
    HAL_I2C_Mem_Read(&hi2c1, DEVICE_ADDR, 0X06, I2C_MEMADD_SIZE_8BIT, &temp_l, 1, 1000);
    dev->temp_data = (uint16_t)(((uint16_t)temp_h << 8) | ((uint16_t)temp_l));
}
