#include "crc.h"


// /**
//  * @brief 异或运算
//  * @param  CacString        待校验数据
//  * @param  CacStringSize    待校验数据长度
//  * @return uint8_t 异或运算值
//  */
// static uint8_t XorCaculate(uint8_t* CacString, uint8_t CacStringSize)
// {
//     uint8_t CacResult = CacString[0];
//     for (uint8_t i = 1; i < CacStringSize; ++i)
//     {
//         CacResult ^= CacString[i];
//     }
//     return CacResult;
// }

uint8_t crc8_lut[256];

/**
 * @brief construct CRC8 Look-Up-Table
 */
void Crc8_init_LUT(void)
{
    uint8_t crc = 0;
    for (uint16_t i = 0; i < 256; i++)
    {
        crc = i;
        for (uint8_t j = 0; j < 8; j++)
        {
            crc = (crc << 1) ^ ((crc & 0x80) ? 0x07 : 0);
        }
        crc8_lut[i] = crc & 0xFF;
    }
}

// uint8_t Crc8_calculate(uint8_t byte)
// {

// }

/**
 * @brief CRC8校验
 * @param  CacString        待校验数据
 * @param  CacStringSize    待校验数据长度
 * @return uint8_t CRC8运算值
 */
static uint8_t Crc8_check(uint8_t* CacString, uint32_t CacStringSize)
{
    const uint16_t CRC8_POLY = 0x0107; // X^8+X^2+X^1+1
    uint8_t CacResult = 0;
    for (uint32_t num = CacStringSize; num > 0; num--)
    {
        CacResult = CacResult ^ (*CacString++ << 8);
        for (uint8_t i = 0; i < 8; i++)
        {
            if (CacResult & 0x8000)
            {
                CacResult = (CacResult << 1) ^ CRC8_POLY;
            }
            else
            {
                CacResult <<= 1;
            }
        }
        CacResult &= 0xFFFF;
    }
    return CacResult;
}

// /**
//  * @brief 硬件CRC32
//  * @param  CacString        待校验数据
//  * @param  CacStringSize    待校验数据长度
//  * @return uint32_t CRC32运算值
//  */
// static uint32_t Crc32_check(uint8_t* CacString, uint32_t CacStringSize)
// {
//     uint8_t CacResult = 0;
//     CacResult = (uint8_t)(HAL_CRC_Calculate(&hcrc, CacString, CacStringSize) & 0x000000FF); //取最低位
//     return CacResult;
// }

/**
 * @brief CRC32校验
 * @param  CacString        待校验数据
 * @param  CacStringSize    待校验数据长度
 * @return uint8_t CRC32运算值
 * @note 与STM32的硬件CRC结果一致
 */
static uint32_t Crc32_check(uint8_t* CacString, uint32_t CacStringSize)
{
    const uint32_t CRC32_POLY = 0x04C11DB7;
    uint32_t CacResult = 0xFFFFFFFF;
    uint32_t xbit = 0;

    for (uint32_t num = 0; num < CacStringSize; num++)
    {
        xbit = 0x80000000;
        for (uint32_t bits = 0; bits < 32; bits++)
        {
            if (CacResult & 0x80000000)
            {
                CacResult <<= 1;
                CacResult ^= CRC32_POLY;
            }
            else
            {
                CacResult <<= 1;
            }

            if (CacString[num] & xbit)
            {
                CacResult ^= CRC32_POLY;
            }
            xbit >>= 1;
        }
    }
    return CacResult;
}

// uint32_t Crc32_calculate(uint8_t byte)
// {

// }
