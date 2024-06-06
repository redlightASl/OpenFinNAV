/**
 * @file Algorithm.h
 * @brief 提供常用的软件和控制算法
 * @author RedlightASl (dddbbbdd@foxmail.com)
 * @version 1.0
 * @date 2021-09-13
 *
 * @copyright Copyright (c) 2021  RedlightASl
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-09-13 <td>1.0     <td>wangh     <td>Content
 * </table>
 */
#pragma once
#include "Defines.h"

#ifdef __cplusplus
extern "C"
{
#endif


/**
 * @brief 区间映射
 * @param  x        输入值
 * @param  a        较大值
 * @param  b        较小值
 */
#define ROV_RANGE(x, a, b) (ROV_MIN((ROV_MAX((x), (a))), (b)))

/**
 * @brief 将输入uint32数据拆分出最高8位
 * @param  _raw        输入数据
 */
#define SPLIT_UINT32_8HH(_raw) \
        ((uint8_t)((((uint32_t)(_raw)) & (0xFF000000)) >> (24U)))

/**
 * @brief 将输入uint32数据拆分出次高8位
 * @param  _raw        输入数据
 */
#define SPLIT_UINT32_8HL(_raw) \
        ((uint8_t)((((uint32_t)(_raw)) & (0x00FF0000)) >> (16U)))

/**
 * @brief 将输入uint32数据拆分出次低8位
 * @param  _raw        输入数据
 */
#define SPLIT_UINT32_8LH(_raw) \
        ((uint8_t)((((uint32_t)(_raw)) & (0x0000FF00)) >> (8U)))

/**
 * @brief 将输入uint32数据拆分出最低8位
 * @param  _raw        输入数据
 */
#define SPLIT_UINT32_8LL(_raw) \
        ((uint8_t)(((uint32_t)(_raw)) & (0x000000FF)))

/**
 * @brief 将输入uint16数据拆分出高8位
 * @param  _raw        输入数据
 */
#define SPLIT_UINT16_8H(_raw) \
        ((uint8_t)((((uint16_t)(_raw)) & (0xFF00)) >> (8U)))

/**
 * @brief 将输入uint16数据拆分出低8位
 * @param  _raw        输入数据
 */
#define SPLIT_UINT16_8L(_raw) \
        ((uint8_t)(((uint16_t)(_raw)) & (0x00FF)))

/**
 * @brief 将输入地址按大端序组合成uint16数据
 * @param  _raw        输入地址(字节对齐)
 */
#define COMBINE_UINT16(_raw) \
    ((uint16_t)((((uint16_t)(*(&(_raw) + 0))) << (8U)) | ((uint16_t)(*(&(_raw) + 1)))))

/**
 * @brief 将输入地址按大端序组合成uint32数据
 * @param  _raw        输入地址(字节对齐)
 */
#define COMBINE_UINT32(_raw) \
    (((uint32_t)(((uint32_t)(*(&(_raw) + 0))) << (24U))) | \
    ((uint32_t)(((uint32_t)(*(&(_raw) + 1))) << (16U))) | \
    ((uint32_t)(((uint32_t)(*(&(_raw) + 2))) << (8U))) | \
    ((uint16_t)(*(&(_raw) + 3))))

/**
 * @brief 检查PWM控制数据是否正确
 * @param  pwm_value        待检查的PWM控制数据
 * @param  top_value        上限
 * @param  bottom_value     下限
 * @return u8 1正确；0错误
 */
#define CheckPwmValue(pwm_value, bottom_value, top_value) ((((pwm_value) <= (top_value))\
                                                        &&((pwm_value) >= (bottom_value)))?\
                                                        (1):(0))

/**
 * @brief PWM控制数据限幅
 * @param  pwm_value        要限幅的PWM控制数据
 * @param  top_value        上限
 * @param  bottom_value     下限
 */
#define RestrictPwmValue(pwm_value, bottom_value, top_value) (pwm_value)=((pwm_value)>=(bottom_value))?\
        (((pwm_value)<=(top_value))?(pwm_value):(top_value)):(bottom_value)
//TODO 更名为Limit

/**
 * @brief PWM控制数据死区
 * @param  pwm_value        要设置死区的PWM控制数据
 * @param  min_value        死区下限
 * @param  max_value        死区上限
 * @param  lock_value       死区值
 */
#define Lock(pwm_value, min_value, max_value, lock_value) pwm_value=((pwm_value)<=(max_value))?\
        (((pwm_value)>=(min_value))?(lock_value):(pwm_value)):(pwm_value)
//TODO 更名为Lock

/**
 * @brief 数据限幅
 * @param  x        要限幅的数据
 * @param  min      下限
 * @param  max      上限
 */
#define Clip(x, min, max) (x) = (((x) <= (min)) ?\
        (min) : (((x) >= (max)) ? (max) : (x)))
//TODO 更名为Clip

#define RestrictDeltaValue(x, dl, y) (y) += (RestrictValue(((x) - (y)), -dl, dl))
//TODO 更名为DeltaClip


/**
 * @brief 将一个数据从某个区间映射到另一个目标区间
 * @param origin_data 原始数据
 * @param origin_bottom 原始数据下限
 * @param origin_top 原始数据上限
 * @param tatget_bottom 目标数据下限
 * @param target_top 目标数据上限
 * @return 目标区间上的数据值
 */
#define MAP(origin_data,origin_bottom,origin_top,tatget_bottom,target_top) \
            (((origin_data) - (origin_bottom)) * \
            ((target_top) - (tatget_bottom)) / \
            ((origin_top) - (origin_bottom))) + \
            (tatget_bottom)

// #define range_to_180deg(a) ((a) > 180 ? (a - 360) : ((a) < -180 ? (a + 360) : (a)))
// double yaw = (eulerData.Yaw + (180 - headingPID.TargetValue) + 360) % 360 - (180 - headingPID.TargetValue);

void swap_i32(int32_t* m, int32_t* n);
uint16_t absolute_yaw(uint16_t yaw_feedback, uint16_t yaw_target);

#ifdef __cplusplus
    }
#endif
