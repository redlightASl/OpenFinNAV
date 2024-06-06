#pragma once
#include "Defines.h"

#define GET_BIT_N_VAL(data, n) (0x1 & (( *((data) + (n)/8) & (0x1 << ((n)%8)) ) >> ((n)%8)))

uint8_t SumCheck_calculate(const uint8_t* CacString, uint32_t CacStringSize, uint8_t sum_check_bit);
uint8_t SumCheck_check(uint8_t* CacString, uint32_t CacStringSize);
bool OddParity_calculate(uint8_t byte);
uint8_t OddParity_check(uint8_t* data, uint32_t length);
bool EvenParity_calculate(uint8_t byte);
uint8_t EvenParity_check(uint8_t* data, uint32_t length);
// uint8_t IdTest(uint8_t* String, uint8_t Method, uint8_t StringLength, uint8_t IdBitAddr);
