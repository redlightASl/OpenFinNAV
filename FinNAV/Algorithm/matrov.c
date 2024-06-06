#include "matrov.h"

/**
 * @brief 快速计算平方根倒数
 * @param  num           计算值
 * @return fp32_t 计算值的平方根的倒数(\frac{1}{sqrt{num}})
 */
fp32_t mr_f32_rsqrt(const fp32_t num)
{
    int32_t i = 0;
    fp32_t x2 = 0.0f;
    fp32_t y = 0.0f;
    const fp32_t threehalfs = 1.5f;
    x2 = num * 0.5F;
    y = num;
    i = *(int32_t*)&y; // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1); // what the fuck?
    y = *(fp32_t*)&i;
    y = y * (threehalfs - (x2 * y * y)); // 1st iteration
    y = y * (threehalfs - (x2 * y * y)); // 2nd iteration, this can be removed
    return y;
}
