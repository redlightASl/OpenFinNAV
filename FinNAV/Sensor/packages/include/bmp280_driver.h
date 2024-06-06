#ifndef __BMP280_DRIVER_H_
#define __BMP280_DRIVER_H_
#include <stdint.h>
#include <stddef.h>

#include "spi.h"


/****************************************************************/
/*! @name       BMP280 Macros               */
/****************************************************************/

/*! @name Macro to disable double precision floating point compensation
 * @note Uncomment the following line to disable it
 */
#ifndef BMP280_DISABLE_DOUBLE_COMPENSATION

/* #define BMP280_DISABLE_DOUBLE_COMPENSATION */
#endif

/*! @name Macro to disable 64bit compensation
 * @note Uncomment the following line to disable it
 */
#ifndef BMP280_DISABLE_64BIT_COMPENSATION

/* #define BMP280_DISABLE_64BIT_COMPENSATION */
#endif

/*! @name Interface selection macros */
#define BMP280_SPI_INTF                      UINT8_C(0)
#define BMP280_I2C_INTF                      UINT8_C(1)

/*! @name Return codes */
/*! @name Success code*/
#define BMP280_OK                            INT8_C(0)
#define BMP280_BOND_WIRE_OK                  INT8_C(0)

/*! @name Error codes */
#define BMP280_E_NULL_PTR                    INT8_C(-1)
#define BMP280_E_DEV_NOT_FOUND               INT8_C(-2)
#define BMP280_E_INVALID_LEN                 INT8_C(-3)
#define BMP280_E_COMM_FAIL                   INT8_C(-4)
#define BMP280_E_INVALID_MODE                INT8_C(-5)
#define BMP280_E_BOND_WIRE                   INT8_C(-6)
#define BMP280_E_IMPLAUS_TEMP                INT8_C(-7)
#define BMP280_E_IMPLAUS_PRESS               INT8_C(-8)
#define BMP280_E_CAL_PARAM_RANGE             INT8_C(-9)
#define BMP280_E_UNCOMP_TEMP_RANGE           INT8_C(-10)
#define BMP280_E_UNCOMP_PRES_RANGE           INT8_C(-11)
#define BMP280_E_UNCOMP_TEMP_AND_PRESS_RANGE INT8_C(-12)
#define BMP280_E_UNCOMP_DATA_CALC            INT8_C(-13)
#define BMP280_E_32BIT_COMP_TEMP             INT8_C(-14)
#define BMP280_E_32BIT_COMP_PRESS            INT8_C(-15)
#define BMP280_E_64BIT_COMP_PRESS            INT8_C(-16)
#define BMP280_E_DOUBLE_COMP_TEMP            INT8_C(-17)
#define BMP280_E_DOUBLE_COMP_PRESS           INT8_C(-18)

/*! @name Chip IDs for samples and mass production parts */
#define BMP280_CHIP_ID1                      UINT8_C(0x56)
#define BMP280_CHIP_ID2                      UINT8_C(0x57)
#define BMP280_CHIP_ID3                      UINT8_C(0x58)

/*! @name I2C addresses */
#define BMP280_I2C_ADDR_PRIM                 UINT8_C(0x76)
#define BMP280_I2C_ADDR_SEC                  UINT8_C(0x77)

/*! @name Calibration parameter register addresses*/
#define BMP280_DIG_T1_LSB_ADDR               UINT8_C(0x88)
#define BMP280_DIG_T1_MSB_ADDR               UINT8_C(0x89)
#define BMP280_DIG_T2_LSB_ADDR               UINT8_C(0x8A)
#define BMP280_DIG_T2_MSB_ADDR               UINT8_C(0x8B)
#define BMP280_DIG_T3_LSB_ADDR               UINT8_C(0x8C)
#define BMP280_DIG_T3_MSB_ADDR               UINT8_C(0x8D)
#define BMP280_DIG_P1_LSB_ADDR               UINT8_C(0x8E)
#define BMP280_DIG_P1_MSB_ADDR               UINT8_C(0x8F)
#define BMP280_DIG_P2_LSB_ADDR               UINT8_C(0x90)
#define BMP280_DIG_P2_MSB_ADDR               UINT8_C(0x91)
#define BMP280_DIG_P3_LSB_ADDR               UINT8_C(0x92)
#define BMP280_DIG_P3_MSB_ADDR               UINT8_C(0x93)
#define BMP280_DIG_P4_LSB_ADDR               UINT8_C(0x94)
#define BMP280_DIG_P4_MSB_ADDR               UINT8_C(0x95)
#define BMP280_DIG_P5_LSB_ADDR               UINT8_C(0x96)
#define BMP280_DIG_P5_MSB_ADDR               UINT8_C(0x97)
#define BMP280_DIG_P6_LSB_ADDR               UINT8_C(0x98)
#define BMP280_DIG_P6_MSB_ADDR               UINT8_C(0x99)
#define BMP280_DIG_P7_LSB_ADDR               UINT8_C(0x9A)
#define BMP280_DIG_P7_MSB_ADDR               UINT8_C(0x9B)
#define BMP280_DIG_P8_LSB_ADDR               UINT8_C(0x9C)
#define BMP280_DIG_P8_MSB_ADDR               UINT8_C(0x9D)
#define BMP280_DIG_P9_LSB_ADDR               UINT8_C(0x9E)
#define BMP280_DIG_P9_MSB_ADDR               UINT8_C(0x9F)

/*! @name Other registers */
#define BMP280_CHIP_ID_ADDR                  UINT8_C(0xD0)
#define BMP280_SOFT_RESET_ADDR               UINT8_C(0xE0)
#define BMP280_STATUS_ADDR                   UINT8_C(0xF3)
#define BMP280_CTRL_MEAS_ADDR                UINT8_C(0xF4)
#define BMP280_CONFIG_ADDR                   UINT8_C(0xF5)
#define BMP280_PRES_MSB_ADDR                 UINT8_C(0xF7)
#define BMP280_PRES_LSB_ADDR                 UINT8_C(0xF8)
#define BMP280_PRES_XLSB_ADDR                UINT8_C(0xF9)
#define BMP280_TEMP_MSB_ADDR                 UINT8_C(0xFA)
#define BMP280_TEMP_LSB_ADDR                 UINT8_C(0xFB)
#define BMP280_TEMP_XLSB_ADDR                UINT8_C(0xFC)

/*! @name Power modes */
#define BMP280_SLEEP_MODE                    UINT8_C(0x00)
#define BMP280_FORCED_MODE                   UINT8_C(0x01)
#define BMP280_NORMAL_MODE                   UINT8_C(0x03)

/*! @name Soft reset command */
#define BMP280_SOFT_RESET_CMD                UINT8_C(0xB6)

/*! @name ODR options */
#define BMP280_ODR_0_5_MS                    UINT8_C(0x00)
#define BMP280_ODR_62_5_MS                   UINT8_C(0x01)
#define BMP280_ODR_125_MS                    UINT8_C(0x02)
#define BMP280_ODR_250_MS                    UINT8_C(0x03)
#define BMP280_ODR_500_MS                    UINT8_C(0x04)
#define BMP280_ODR_1000_MS                   UINT8_C(0x05)
#define BMP280_ODR_2000_MS                   UINT8_C(0x06)
#define BMP280_ODR_4000_MS                   UINT8_C(0x07)

/*! @name Over-sampling macros */
#define BMP280_OS_NONE                       UINT8_C(0x00)
#define BMP280_OS_1X                         UINT8_C(0x01)
#define BMP280_OS_2X                         UINT8_C(0x02)
#define BMP280_OS_4X                         UINT8_C(0x03)
#define BMP280_OS_8X                         UINT8_C(0x04)
#define BMP280_OS_16X                        UINT8_C(0x05)

/*! @name Filter coefficient macros */
#define BMP280_FILTER_OFF                    UINT8_C(0x00)
#define BMP280_FILTER_COEFF_2                UINT8_C(0x01)
#define BMP280_FILTER_COEFF_4                UINT8_C(0x02)
#define BMP280_FILTER_COEFF_8                UINT8_C(0x03)
#define BMP280_FILTER_COEFF_16               UINT8_C(0x04)

/*! @name SPI 3-Wire macros */
#define BMP280_SPI3_WIRE_ENABLE              UINT8_C(1)
#define BMP280_SPI3_WIRE_DISABLE             UINT8_C(0)

/*! @name Measurement status */
#define BMP280_MEAS_DONE                     UINT8_C(0)
#define BMP280_MEAS_ONGOING                  UINT8_C(1)

/*! @name Image update */
#define BMP280_IM_UPDATE_DONE                UINT8_C(0)
#define BMP280_IM_UPDATE_ONGOING             UINT8_C(1)

/*! @name Position and mask macros */
#define BMP280_STATUS_IM_UPDATE_POS          UINT8_C(0)
#define BMP280_STATUS_IM_UPDATE_MASK         UINT8_C(0x01)
#define BMP280_STATUS_MEAS_POS               UINT8_C(3)
#define BMP280_STATUS_MEAS_MASK              UINT8_C(0x08)
#define BMP280_OS_TEMP_POS                   UINT8_C(5)
#define BMP280_OS_TEMP_MASK                  UINT8_C(0xE0)
#define BMP280_OS_PRES_POS                   UINT8_C(2)
#define BMP280_OS_PRES_MASK                  UINT8_C(0x1C)
#define BMP280_POWER_MODE_POS                UINT8_C(0)
#define BMP280_POWER_MODE_MASK               UINT8_C(0x03)
#define BMP280_STANDBY_DURN_POS              UINT8_C(5)
#define BMP280_STANDBY_DURN_MASK             UINT8_C(0xE0)
#define BMP280_FILTER_POS                    UINT8_C(2)
#define BMP280_FILTER_MASK                   UINT8_C(0x1C)
#define BMP280_SPI3_ENABLE_POS               UINT8_C(0)
#define BMP280_SPI3_ENABLE_MASK              UINT8_C(0x01)

/*! @name Calibration parameters' relative position */
#define BMP280_DIG_T1_LSB_POS                UINT8_C(0)
#define BMP280_DIG_T1_MSB_POS                UINT8_C(1)
#define BMP280_DIG_T2_LSB_POS                UINT8_C(2)
#define BMP280_DIG_T2_MSB_POS                UINT8_C(3)
#define BMP280_DIG_T3_LSB_POS                UINT8_C(4)
#define BMP280_DIG_T3_MSB_POS                UINT8_C(5)
#define BMP280_DIG_P1_LSB_POS                UINT8_C(6)
#define BMP280_DIG_P1_MSB_POS                UINT8_C(7)
#define BMP280_DIG_P2_LSB_POS                UINT8_C(8)
#define BMP280_DIG_P2_MSB_POS                UINT8_C(9)
#define BMP280_DIG_P3_LSB_POS                UINT8_C(10)
#define BMP280_DIG_P3_MSB_POS                UINT8_C(11)
#define BMP280_DIG_P4_LSB_POS                UINT8_C(12)
#define BMP280_DIG_P4_MSB_POS                UINT8_C(13)
#define BMP280_DIG_P5_LSB_POS                UINT8_C(14)
#define BMP280_DIG_P5_MSB_POS                UINT8_C(15)
#define BMP280_DIG_P6_LSB_POS                UINT8_C(16)
#define BMP280_DIG_P6_MSB_POS                UINT8_C(17)
#define BMP280_DIG_P7_LSB_POS                UINT8_C(18)
#define BMP280_DIG_P7_MSB_POS                UINT8_C(19)
#define BMP280_DIG_P8_LSB_POS                UINT8_C(20)
#define BMP280_DIG_P8_MSB_POS                UINT8_C(21)
#define BMP280_DIG_P9_LSB_POS                UINT8_C(22)
#define BMP280_DIG_P9_MSB_POS                UINT8_C(23)
#define BMP280_CALIB_DATA_SIZE               UINT8_C(24)

/*! @name Bit-slicing macros */
#define BMP280_GET_BITS(bitname, x)                    ((x & bitname##_MASK) \
                                                        >> bitname##_POS)
#define BMP280_SET_BITS(regvar, bitname, val)          ((regvar & \
                                                         ~bitname##_MASK) | ((val << bitname##_POS) & bitname##_MASK))
#define BMP280_SET_BITS_POS_0(reg_data, bitname, data) ((reg_data & \
                                                         ~(bitname##_MASK)) | (data & bitname##_MASK))
#define BMP280_GET_BITS_POS_0(bitname, reg_data)       (reg_data & \
                                                        (bitname##_MASK))

/*! @brief Macros holding the minimum and maximum for trimming values */

#define BMP280_ST_DIG_T1_MIN UINT16_C(19000)
#define BMP280_ST_DIG_T1_MAX UINT16_C(35000)
#define BMP280_ST_DIG_T2_MIN UINT16_C(22000)
#define BMP280_ST_DIG_T2_MAX UINT16_C(30000)
#define BMP280_ST_DIG_T3_MIN INT16_C(-3000)
#define BMP280_ST_DIG_T3_MAX INT16_C(-1000)
#define BMP280_ST_DIG_P1_MIN UINT16_C(30000)
#define BMP280_ST_DIG_P1_MAX UINT16_C(42000)
#define BMP280_ST_DIG_P2_MIN INT16_C(-12970)
#define BMP280_ST_DIG_P2_MAX INT16_C(-8000)
#define BMP280_ST_DIG_P3_MIN INT16_C(-5000)
#define BMP280_ST_DIG_P3_MAX UINT16_C(8000)
#define BMP280_ST_DIG_P4_MIN INT16_C(-10000)
#define BMP280_ST_DIG_P4_MAX UINT16_C(18000)
#define BMP280_ST_DIG_P5_MIN INT16_C(-500)
#define BMP280_ST_DIG_P5_MAX UINT16_C(1100)
#define BMP280_ST_DIG_P6_MIN INT16_C(-1000)
#define BMP280_ST_DIG_P6_MAX UINT16_C(1000)
#define BMP280_ST_DIG_P7_MIN INT16_C(-32768)
#define BMP280_ST_DIG_P7_MAX UINT16_C(32767)
#define BMP280_ST_DIG_P8_MIN INT16_C(-30000)
#define BMP280_ST_DIG_P8_MAX UINT16_C(10000)
#define BMP280_ST_DIG_P9_MIN INT16_C(-10000)
#define BMP280_ST_DIG_P9_MAX UINT16_C(30000)

#define BMP280_GET_BITSLICE(regvar, bitname) \
    ((regvar & bitname##__MSK) >> bitname##__POS)

/*! @brief Macros to read out API revision number */
/*Register holding custom trimming values */
#define BMP280_ST_TRIMCUSTOM_REG             UINT8_C(0x87)
#define BMP280_ST_TRIMCUSTOM_REG_APIREV__POS UINT8_C(1)
#define BMP280_ST_TRIMCUSTOM_REG_APIREV__MSK UINT8_C(0x06)
#define BMP280_ST_TRIMCUSTOM_REG_APIREV__LEN UINT8_C(2)
#define BMP280_ST_TRIMCUSTOM_REG_APIREV__REG BMP280_ST_TRIMCUSTOM_REG

/* highest API revision supported is revision 0. */
#define BMP280_ST_MAX_APIREVISION            UINT8_C(0x00)

/*! @brief Macros holding the minimum and maximum for trimming values */
/* 0x00000 is minimum output value */
#define BMP280_ST_ADC_T_MIN                  INT32_C(0x00000)

/* 0xFFFF0 is maximum 20-bit output value without over sampling */
#define BMP280_ST_ADC_T_MAX                  INT32_C(0xFFFF0)

/* 0x00000 is minimum output value */
#define BMP280_ST_ADC_P_MIN                  INT32_C(0x00000)

/* 0xFFFF0 is maximum 20-bit output value without over sampling */
#define BMP280_ST_ADC_P_MAX                  INT32_C(0xFFFF0)

/*! @name Function pointer type definitions */
typedef int8_t (*bmp280_com_fptr_t)(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len);
typedef void (*bmp280_delay_fptr_t)(uint32_t period);

/*! @name Calibration parameters' structure */
struct bmp280_calib_param
{
    uint16_t dig_t1;
    int16_t dig_t2;
    int16_t dig_t3;
    uint16_t dig_p1;
    int16_t dig_p2;
    int16_t dig_p3;
    int16_t dig_p4;
    int16_t dig_p5;
    int16_t dig_p6;
    int16_t dig_p7;
    int16_t dig_p8;
    int16_t dig_p9;
    int32_t t_fine;
};

/*! @name Sensor configuration structure */
struct bmp280_config
{
    uint8_t os_temp;
    uint8_t os_pres;
    uint8_t odr;
    uint8_t filter;
    uint8_t spi3w_en;
};

/*! @name Sensor status structure */
struct bmp280_status
{
    uint8_t measuring;
    uint8_t im_update;
};

/*! @name Uncompensated data structure */
struct bmp280_uncomp_data
{
    int32_t uncomp_temp;
    uint32_t uncomp_press;
};

/*! @name API device structure */
struct bmp280_dev
{
    uint8_t chip_id;
    uint8_t dev_id;
    uint8_t intf;
    bmp280_com_fptr_t read;
    bmp280_com_fptr_t write;
    bmp280_delay_fptr_t delay_ms;
    struct bmp280_calib_param calib_param;
    struct bmp280_config conf;
};













/* Port */
int8_t spi_reg_write(uint8_t cs, uint8_t reg_addr, uint8_t* reg_data, uint16_t length);
int8_t spi_reg_read(uint8_t cs, uint8_t reg_addr, uint8_t* reg_data, uint16_t length);
void print_rslt(const char api_name[], int8_t rslt);












/*!
 * @brief This API reads the data from the given register address of the
 * sensor.
 *
 * @param[in] reg_addr : Register address from where the data to be read
 * @param[out] reg_data : Pointer to data buffer to store the read data.
 * @param[in] len : No of bytes of data to be read.
 * @param[in] dev : Structure instance of bmp280_dev.
 *
 * @return Result of API execution
 * @retval Zero for Success, non-zero otherwise.
 */
int8_t bmp280_get_regs(uint8_t reg_addr, uint8_t *reg_data, uint8_t len, const struct bmp280_dev *dev);

/*!
 * @brief This API writes the given data to the register addresses
 * of the sensor.
 *
 * @param[in] reg_addr : Register address from where the data to be written.
 * @param[in] reg_data : Pointer to data buffer which is to be written
 * in the sensor.
 * @param[in] len : No of bytes of data to write..
 * @param[in] dev : Structure instance of bmp280_dev.
 *
 * @return Result of API execution
 * @retval Zero for Success, non-zero otherwise.
 */
int8_t bmp280_set_regs(uint8_t *reg_addr, const uint8_t *reg_data, uint8_t len, const struct bmp280_dev *dev);

/*!
 * @brief This API triggers the soft reset of the sensor.
 *
 * @param[in] dev : Structure instance of bmp280_dev.
 *
 * @return Result of API execution
 * @retval Zero for Success, non-zero otherwise..
 */
int8_t bmp280_soft_reset(const struct bmp280_dev *dev);

/*!
 *  @brief This API is the entry point.
 *  It reads the chip-id and calibration data from the sensor.
 *
 *  @param[in,out] dev : Structure instance of bmp280_dev
 *
 *  @return Result of API execution
 *  @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t bmp280_init(struct bmp280_dev *dev);

/*!
 * @brief This API reads the data from the ctrl_meas register and config
 * register. It gives the currently set temperature and pressure over-sampling
 * configuration, power mode configuration, sleep duration and
 * IIR filter coefficient.
 *
 * @param[out] conf : Current configuration of the bmp280
 * conf.osrs_t, conf.osrs_p = BMP280_OS_NONE, BMP280_OS_1X,
 *     BMP280_OS_2X, BMP280_OS_4X, BMP280_OS_8X, BMP280_OS_16X
 * conf.odr = BMP280_ODR_0_5_MS, BMP280_ODR_62_5_MS, BMP280_ODR_125_MS,
 *     BMP280_ODR_250_MS, BMP280_ODR_500_MS, BMP280_ODR_1000_MS,
 *     BMP280_ODR_2000_MS, BMP280_ODR_4000_MS
 * conf.filter = BMP280_FILTER_OFF, BMP280_FILTER_COEFF_2,
 *     BMP280_FILTER_COEFF_4, BMP280_FILTER_COEFF_8, BMP280_FILTER_COEFF_16
 * conf.spi3w_en = BMP280_SPI3_WIRE_ENABLE, BMP280_SPI3_WIRE_DISABLE
 * @param[in] dev : Structure instance of bmp280_dev
 *
 * @return Result of API execution
 * @retval Zero for Success, non-zero otherwise.
 */
int8_t bmp280_get_config(struct bmp280_config *conf, struct bmp280_dev *dev);

/*!
 * @brief This API writes the data to the ctrl_meas register and config register.
 * It sets the temperature and pressure over-sampling configuration,
 * power mode configuration, sleep duration and IIR filter coefficient.
 *
 * @param[in] conf : Desired configuration to the bmp280
 * conf.osrs_t, conf.osrs_p = BMP280_OS_NONE, BMP280_OS_1X,
 *     BMP280_OS_2X, BMP280_OS_4X, BMP280_OS_8X, BMP280_OS_16X
 * conf.odr = BMP280_ODR_0_5_MS, BMP280_ODR_62_5_MS, BMP280_ODR_125_MS,
 *     BMP280_ODR_250_MS, BMP280_ODR_500_MS, BMP280_ODR_1000_MS,
 *     BMP280_ODR_2000_MS, BMP280_ODR_4000_MS
 * conf.filter = BMP280_FILTER_OFF, BMP280_FILTER_COEFF_2,
 *     BMP280_FILTER_COEFF_4, BMP280_FILTER_COEFF_8, BMP280_FILTER_COEFF_16
 * conf.spi3w_en = BMP280_SPI3_WIRE_ENABLE, BMP280_SPI3_WIRE_DISABLE
 * @param[in] dev : Structure instance of bmp280_dev
 *
 * @return Result of API execution
 * @retval Zero for Success, non-zero otherwise.
 */
int8_t bmp280_set_config(const struct bmp280_config *conf, struct bmp280_dev *dev);

/*!
 * @brief This API reads the status register
 *
 * @param[out] status : Status of the sensor
 * status.measuring = BMP280_MEAS_DONE, BMP280_MEAS_ONGOING
 * status.im_update = BMP280_IM_UPDATE_DONE, BMP280_IM_UPDATE_ONGOING
 * @param[in] dev : structure instance of bmp280_dev
 *
 * @return Result of API execution
 * @retval Zero for Success, non-zero otherwise.
 */
int8_t bmp280_get_status(struct bmp280_status *status, const struct bmp280_dev *dev);

/*!
 * @brief This API reads the power mode.
 *
 * @param[out] mode : BMP280_SLEEP_MODE, BMP280_NORMAL_MODE,
 *     BMP280_FORCED_MODE
 * @param[in] dev : Structure instance of bmp280_dev
 *
 * @return Result of API execution
 * @retval Zero for Success, non-zero otherwise.
 */
int8_t bmp280_get_power_mode(uint8_t *mode, const struct bmp280_dev *dev);

/*!
 * @brief This API writes the power mode.
 *
 * @param[out] mode : BMP280_SLEEP_MODE, BMP280_NORMAL_MODE,
 *     BMP280_FORCED_MODE
 * @param[in] dev : Structure instance of bmp280_dev
 *
 * @return Result of API execution
 * @retval Zero for Success, non-zero otherwise.
 */
int8_t bmp280_set_power_mode(uint8_t mode, struct bmp280_dev *dev);

/*!
 * @brief This API reads the temperature and pressure data registers.
 * It gives the raw temperature and pressure data.
 *
 * @param[in] uncomp_data : Structure instance of bmp280_uncomp_data
 * @param[in] dev : Structure instance of bmp280_dev
 *
 * @return Result of API execution
 * @retval Zero for Success, non-zero otherwise.
 */
int8_t bmp280_get_uncomp_data(struct bmp280_uncomp_data *uncomp_data, const struct bmp280_dev *dev);

/*!
 * @brief This API is used to get the compensated temperature from
 * uncompensated temperature. This API uses 32 bit integers.
 * Temperature in degC, resolution is 0.01 DegC. output value of
 * "5123" equals 51.23 degree Celsius
 *
 * @param[out] comp_temp : 32 bit compensated temperature
 * @param[in] uncomp_temp : Raw temperature values from the sensor
 * @param[in] dev : Structure instance of bmp280_dev
 *
 * @return Result of API execution
 * @retval Zero for Success, non-zero otherwise.
 */
int8_t bmp280_get_comp_temp_32bit(int32_t *comp_temp, int32_t uncomp_temp, struct bmp280_dev *dev);

/*!
 * @brief This API is used to get the compensated pressure from
 * uncompensated pressure. This API uses 32 bit integers.
 * Pressure in Pa as unsigned 32 bit integer
 * output value of "96386" equals 96386 Pa = 963.86 hPa
 *
 * @param[out] comp_pres : 32 bit compensated pressure
 * @param[in] uncomp_pres : Raw pressure values from the sensor
 * @param[in] dev : structure instance of bmp280_dev
 *
 * @return Result of API execution
 * @retval Zero for Success, non-zero otherwise.
 */
int8_t bmp280_get_comp_pres_32bit(uint32_t *comp_pres, uint32_t uncomp_pres, const struct bmp280_dev *dev);

#ifndef BMP280_DISABLE_64BIT_COMPENSATION

/*!
 * @brief This API is used to get the compensated pressure from
 * uncompensated pressure. This API uses 64 bit integers.
 * Pressure in Pa as unsigned 32 bit integer in Q24.8 format
 * (24 integer bits and 8 fractional bits). Output value of "24674867"
 * represents 24674867/256 = 96386.2 Pa = 963.862 hPa
 *
 * @param[out] pressure : compensated pressure
 * @param[in] uncomp_pres : Raw pressure values from the sensor
 * @param[in] dev : Structure instance of bmp280_dev
 *
 * @return Result of API execution
 * @retval Zero for Success, non-zero otherwise.
 */
int8_t bmp280_get_comp_pres_64bit(uint32_t *pressure, uint32_t uncomp_pres, const struct bmp280_dev *dev);

#endif /* BMP280_DISABLE_64BIT_COMPENSATION */

#ifndef BMP280_DISABLE_DOUBLE_COMPENSATION

/*!
 * @brief This API is used to get the compensated temperature from
 * uncompensated temperature. This API uses double floating precision.
 * Temperature in degree Celsius , double precision. output value
 * of "51.23" equals 51.23 degC.
 *
 * @param[out] temperature : compensated temperature
 * @param[in] uncomp_temp : Raw temperature values from the sensor
 * @param[in] dev : Structure instance of bmp280_dev
 *
 * @return Result of API execution
 * @retval Zero for Success, non-zero otherwise.
 */
int8_t bmp280_get_comp_temp_double(double *temperature, int32_t uncomp_temp, struct bmp280_dev *dev);

/*!
 * @brief This API is used to get the compensated pressure from
 * uncompensated pressure. This API uses double floating precision.
 * Pressure in Pa as double. Output value of "96386.2"
 * equals 96386.2 Pa = 963.862 hPa
 *
 * @param[out] pressure : compensated pressure
 * @param[in] uncomp_pres : Raw pressure values from the sensor
 * @param[in] dev : Structure instance of bmp280_dev
 *
 * @return Result of API execution
 * @retval Zero for Success, non-zero otherwise.
 */
int8_t bmp280_get_comp_pres_double(double *pressure, uint32_t uncomp_pres, const struct bmp280_dev *dev);

#endif /* BMP280_DISABLE_DOUBLE_COMPENSATION */

/*!
 * @brief This API computes the measurement time in milliseconds for the
 * active configuration
 *
 * @param[in] dev : Structure instance of bmp280_dev
 *
 * @return Measurement time for the active configuration in milliseconds
 */
uint8_t bmp280_compute_meas_time(const struct bmp280_dev *dev);

#endif
