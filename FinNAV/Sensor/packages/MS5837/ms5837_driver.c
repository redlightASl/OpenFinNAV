#include "ms5837_driver.h"
#include "ms5837_driver.h"
#include <stdio.h>



struct MS5837_values_t MS5837_values;
struct MS5837_t MS5837;

static void I2C_send(uint8_t addr, I2C_HandleTypeDef* i2c_channel) {
    HAL_I2C_Master_Transmit(i2c_channel, MS5837_ADDR << 1, &addr, 1, 100);
}

static int8_t I2C_read8(uint8_t addr, I2C_HandleTypeDef* i2c_channel) {
    uint8_t data = 0;
    HAL_I2C_Master_Transmit(i2c_channel, MS5837_ADDR << 1, &addr, 1, 100);
    HAL_Delay(20);
    // osDelay(20);
    HAL_I2C_Master_Receive(i2c_channel, MS5837_ADDR << 1, &data, 1, 100);
    return data;
}

static int16_t I2C_read16(uint8_t addr, I2C_HandleTypeDef* i2c_channel) {
    uint8_t dataArr[2] = { 0,0 };
    HAL_I2C_Master_Transmit(i2c_channel, MS5837_ADDR << 1, &addr, 1, 100);
    HAL_Delay(20);
    // osDelay(20);
    HAL_I2C_Master_Receive(i2c_channel, MS5837_ADDR << 1, dataArr, 2, 100);
    uint16_t data = (dataArr[0] << 8) | dataArr[1];
    return data;
}

static int32_t I2C_read32(uint8_t addr, I2C_HandleTypeDef* i2c_channel) {
    uint8_t dataArr[4] = { 0,0,0,0 };
    HAL_I2C_Master_Transmit(i2c_channel, MS5837_ADDR << 1, &addr, 1, 100);
    HAL_Delay(20);
    // osDelay(20);
    HAL_I2C_Master_Receive(i2c_channel, MS5837_ADDR << 1, dataArr, 4, 100);
    uint32_t data = (dataArr[0] << 24) | (dataArr[1] << 16) | (dataArr[2] << 8) | dataArr[3];
    return data;
}

static uint8_t crc4(uint16_t n_prom[]) {
    uint16_t n_rem = 0;

    n_prom[0] = ((n_prom[0]) & 0x0FFF);
    n_prom[7] = 0;

    for (uint8_t i = 0; i < 16; i++) {
        if (i % 2 == 1) {
            n_rem ^= (uint16_t)((n_prom[i >> 1]) & 0x00FF);
        }
        else {
            n_rem ^= (uint16_t)(n_prom[i >> 1] >> 8);
        }
        for (uint8_t n_bit = 8; n_bit > 0; n_bit--) {
            if (n_rem & 0x8000) {
                n_rem = (n_rem << 1) ^ 0x3000;
            }
            else {
                n_rem = (n_rem << 1);
            }
        }
    }

    n_rem = ((n_rem >> 12) & 0x000F);

    return n_rem ^ 0x00;
}

static void calculate() {

    int32_t dT = 0;
    int64_t SENS = 0;
    int64_t OFF = 0;
    int32_t SENSi = 0;
    int32_t OFFi = 0;
    int32_t Ti = 0;
    int64_t OFF2 = 0;
    int64_t SENS2 = 0;

    dT = MS5837_values.D2 - (uint32_t)MS5837_values.C[5] * 256l;
    if (MS5837.model) {
        SENS = (int64_t)MS5837_values.C[1] * 65536l + ((int64_t)MS5837_values.C[3] * dT) / 128l;
        OFF = (int64_t)MS5837_values.C[2] * 131072l + ((int64_t)MS5837_values.C[4] * dT) / 64l;
        MS5837_values.P = (MS5837_values.D1 * SENS / (2097152l) - OFF) / (32768l);
    }
    else {
        SENS = (int64_t)MS5837_values.C[1] * 32768l + ((int64_t)MS5837_values.C[3] * dT) / 256l;
        OFF = (int64_t)MS5837_values.C[2] * 65536l + ((int64_t)MS5837_values.C[4] * dT) / 128l;
        MS5837_values.P = (MS5837_values.D1 * SENS / (2097152l) - OFF) / (8192l);
    }

    MS5837_values.TEMP = 2000l + (int64_t)dT * MS5837_values.C[6] / 8388608LL;

    if (MS5837.model) {
        if ((MS5837_values.TEMP / 100) < 20) {
            Ti = (11 * (int64_t)dT * (int64_t)dT) / (34359738368LL);
            OFFi = (31 * (MS5837_values.TEMP - 2000) * (MS5837_values.TEMP - 2000)) / 8;
            SENSi = (63 * (MS5837_values.TEMP - 2000) * (MS5837_values.TEMP - 2000)) / 32;
        }
    }
    else {
        if ((MS5837_values.TEMP / 100) < 20) {
            Ti = (3 * (int64_t)dT * (int64_t)dT) / (8589934592LL);
            OFFi = (3 * (MS5837_values.TEMP - 2000) * (MS5837_values.TEMP - 2000)) / 2;
            SENSi = (5 * (MS5837_values.TEMP - 2000) * (MS5837_values.TEMP - 2000)) / 8;
            if ((MS5837_values.TEMP / 100) < -15) {
                OFFi = OFFi + 7 * (MS5837_values.TEMP + 1500l) * (MS5837_values.TEMP + 1500l);
                SENSi = SENSi + 4 * (MS5837_values.TEMP + 1500l) * (MS5837_values.TEMP + 1500l);
            }
        }
        else if ((MS5837_values.TEMP / 100) >= 20) {
            Ti = 2 * (dT * dT) / (137438953472LL);
            OFFi = (1 * (MS5837_values.TEMP - 2000) * (MS5837_values.TEMP - 2000)) / 16;
            SENSi = 0;
        }
    }

    OFF2 = OFF - OFFi;
    SENS2 = SENS - SENSi;

    if (MS5837.model) {
        MS5837_values.TEMP = (MS5837_values.TEMP - Ti);
        MS5837_values.P = (((MS5837_values.D1 * SENS2) / 2097152l - OFF2) / 32768l) / 100;
    }
    else {
        MS5837_values.TEMP = (MS5837_values.TEMP - Ti);
        MS5837_values.P = (((MS5837_values.D1 * SENS2) / 2097152l - OFF2) / 8192l) / 10;
    }

    MS5837.temperture = MS5837_values.TEMP / 100.0f;
    MS5837.pressure = MS5837_values.P * 1.0f;
#ifdef Pa
    MS5837.pressure = MS5837_values.P * 100.0f;
#endif
#ifdef bar
    MS5837.pressure = MS5837_values.P * 0.001f;
#endif

}

uint8_t MS5837_init(I2C_HandleTypeDef* i2c_channel) {
    MS5837.fluidDensity = 1029;
    MS5837.model = MS5837_30BA;

    I2C_send(MS5837_RESET, i2c_channel);
    HAL_Delay(10);
    // osDelay(20);

    for (uint8_t i = 0; i < 7; i++) {
        MS5837_values.C[i] = I2C_read16(MS5837_PROM_READ + (i * 2), i2c_channel);
        HAL_Delay(20);
        // osDelay(20);
    }
    uint8_t crcRead = MS5837_values.C[0] >> 12;
    uint8_t crcCalculated = crc4(MS5837_values.C);

    if (crcCalculated == crcRead) {
        return 1;
    }

    return 0;
}

void MS5837_read(I2C_HandleTypeDef* i2c_channel) {
    I2C_send(MS5837_CONVERT_D1_8192, i2c_channel);
    HAL_Delay(20);
    // osDelay(20);

    MS5837_values.D1 = I2C_read32(MS5837_ADC_READ, i2c_channel);
    MS5837_values.D1 = MS5837_values.D1 >> 8;
    HAL_Delay(20);
    // osDelay(20);
    I2C_send(MS5837_CONVERT_D2_8192, i2c_channel);
    HAL_Delay(20);
    // osDelay(20);

    MS5837_values.D2 = I2C_read32(MS5837_ADC_READ, i2c_channel);
    MS5837_values.D2 = MS5837_values.D2 >> 8;

    calculate();
}

float MS5837_get_depth(void) {
    return (MS5837.pressure * 100.0f - 101300.0f) / (MS5837.fluidDensity * 9.80665f);
}

float MS5837_get_pressure(void) {
    return MS5837.pressure;
}

float MS5837_get_temperature(void) {
    return 	MS5837.temperture;
}
