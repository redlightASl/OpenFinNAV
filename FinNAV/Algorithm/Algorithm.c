#include "Algorithm.h"
#include <math.h>


/**
 * @brief 调转两数
 * @param  m                m
 * @param  n                n
 */
void swap_i32(int32_t* m, int32_t* n)
{
    *m = (*m) ^ (*n);
    *n = (*m) ^ (*n);
    *m = (*m) ^ (*n);
}

/**
 * @brief 根据当前IMU航向角计算航向保持所需的航向误差值
 * @param  yaw_feedback     当前IMU反馈航向角
 * @param  yaw_target       目标航向角
 * @return uint16_t 相对于目标航向角的误差值
 */
uint16_t absolute_yaw(uint16_t yaw_feedback, uint16_t yaw_target)
{
    uint16_t yaw_absolute = (yaw_feedback + (180 - yaw_target) + 360) % 360 - (180 - yaw_target);
    return yaw_absolute;
}
