#pragma once
#include "Defines.h"

// enum CheckAlgType {
//     CRC8 = 1,
//     SUMCHECK,
//     PARITY,
//     ODD
// };


extern uint8_t crc8_lut[256];
/**
 * @brief 查表计算CRC8
 */
#define Crc8Caculate(CRC, C) \
    (((CRC) = (crc8_lut[((CRC) ^ (C))])) & (0xFF))

void Crc8_init_LUT(void);

