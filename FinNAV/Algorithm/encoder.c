#include "encoder.h"


/**
 * @brief 加和校验
 * @param  rx_data          待校验数据
 * @param  data_size        待校验数据长度
 * @param  sum_check_bit    校验位
 * @return uint8_t 加和运算结果
 */
uint8_t SumCheck_calculate(const uint8_t* CacString, uint32_t CacStringSize, uint8_t sum_check_bit)
{
    uint8_t sum = 0;
    for (uint32_t i = 0; i < CacStringSize; i++)
    {
        sum += CacString[i];
    }
    return sum;
}

uint8_t SumCheck_check(uint8_t* CacString, uint32_t CacStringSize)
{

}

bool OddParity_calculate(uint8_t byte)
{
    bool parity = false;
    for (uint8_t i = 0; i < 8; i++)
    {
        parity = !parity; // further XOR
        if ((byte & (1u << i)) != 0)
        {
            parity = !parity;
        }
    }
    return parity;
}

uint8_t OddParity_check(uint8_t* data, uint32_t length)
{
    for (uint32_t i = 0; i < length; i++)
    {

    }
}

bool EvenParity_calculate(uint8_t byte)
{
    bool parity = false;
    for (uint8_t i = 0; i < 8; i++)
    {
        if ((byte & (1u << i)) != 0)
        {
            parity = !parity;
        }
    }
    return parity;
}

uint8_t EvenParity_check(uint8_t* data, uint32_t length)
{
    for (int i = 0; i < length; ++i)
    {
    }
}

// /**
//  * @brief 奇偶运算
//  * @param  CacString        待校验数据
//  * @param  CacStringSize    待校验数据长度
//  * @return uint8_t 奇偶运算结果
//  */
// static uint8_t ParityCalculate(uint8_t* CacString, uint8_t CacStringSize)
// {
//     uint8_t CacResult = 0;
//     for (uint8_t i = 0; i < CacStringSize; i++)
//     {
//         CacResult += GET_BIT_N_VAL((CacString), i);
//     }
//     if (CacResult % 2 == 0)
//     {
//         return ROV_TRUE;
//     }
//     else
//     {
//         return ROV_FALSE;
//     }
// }

// /**
//  * @brief 校验位检查
//  * @param  String           待校验的数据
//  * @param  Method           校验算法
//  * @param  StringLength     数据长度
//  * @param  IdBitAddr        校验位偏移量
//  * @return u8 正确为1；错误为0，如果不开启校验默认为1
//  */
// uint8_t IdTest(uint8_t* String, uint8_t Method, uint8_t StringLength, uint8_t IdBitAddr)
// {
//     switch (Method)
//     {
//     case SUM: //加和校验
//         if (SumCheck(String, StringLength, String[IdBitAddr]))
//         {
//             return ROV_TRUE;
//         }
//         break;
//     case CRC8: //CRC8校验
//         if (*(String + IdBitAddr) == Crc8Caculate(String, StringLength))
//         {
//             return ROV_TRUE;
//         }
//         break;
//     case PARITY: //奇校验
//         if (*(String + IdBitAddr) == XorCaculate(String, StringLength))
//         {
//             return ROV_TRUE;
//         }
//         break;
//     case CRC32: //CRC32校验
//         if (*(String + IdBitAddr) == Crc32Caculate(String, StringLength))
//         {
//             return ROV_TRUE;
//         }
//         break;
//     default:
//         return 0;
//         break;
//     }
//     return ROV_FALSE;
// }
