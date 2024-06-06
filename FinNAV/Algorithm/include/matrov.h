#pragma once
#include "Defines.h"


// \pi
#define CONST_PI 3.14159265358979323846264338328
// e
#define CONST_E 2.71828182845904523536028747135
// log_2(e)
#define CONST_LOG2E 1.44269504088896340735992468100
// log_{10}(e)
#define CONST_LOG10E 0.43429448190325182765112891892
// \frac{\pi}{2}
#define M_PI_2 1.57079632679489661923132169164
// \frac{\pi}{4}
#define M_PI_4 0.78539816339744830961566084582
// \frac{1}{\pi}
#define M_1_PI 0.31830988618379067153776752675
// ln(10)
#define M_LN10 2.30258509299404568401799145468
// ln(2)
#define M_LN2 0.69314718055994530941723212146
// ln(\pi)
#define M_LNPI 1.14472988584940017414342735135

#define M_RAD (CONST_PI / 180.0)

/**
 * @brief 检查是否为奇数
 * @param  x        数x
 */
#define ROV_IS_ODD(x) ((x) & 1)

/**
 * @brief 检查是否为偶数
 * @param  x        数x
 */
#define ROV_IS_EVEN(x) (!(ROV_IS_ODD(x)))

// #ifdef LIBROV_ENABLE_MATROV
#ifdef __GNUC__
/**
 * @brief 取较大值
 * @param  x        数x
 * @param  y        数y
 */
#define ROV_MAX(x, y) ({\
					typeof(x) _x = (x);\
					typeof(y) _y = (y);\
					(void)(&_x == &_y);\
					_x > _y ? _x : _y;\
					})

/**
 * @brief 取较小值
 * @param  x        数x
 * @param  y        数y
 */
#define ROV_MIN(x, y) ({\
					typeof(x) _x = (x);\
					typeof(y) _y = (y);\
					(void)(&_x == &_y);\
					_x < _y ? _x : _y;\
					})

/**
 * @brief 求绝对值
 * @param  x        数x
 */
#define ROV_ABS(x) ({\
                    typeof(x) _x = (x);\
                    _x > 0 ? _x : -_x;\
                    })

/**
 * @brief SIGN函数
 * @param  x        数x
 */
#define ROV_SIGN(x) ({\
                    typeof(x) _x = (x);\
                    _x >= 0 ? 1 : -1;\
                    })
#else
/**
 * @brief 取较大值
 * @param  x        数x
 * @param  y        数y
 */
#define ROV_MAX(x, y) ({\
                    (x) > (y) ? (x) : (y);\
                    })

/**
 * @brief 取较小值
 * @param  x        数x
 * @param  y        数y
 */
#define ROV_MIN(x, y) ({\
                    (x) < (y) ? (x) : (y);\
                    })

/**
 * @brief 求绝对值
 * @param  x        数x
 */
#define ROV_ABS(x) ({\
                    (x) > 0 ? (x) : -(x);\
                    })

/**
 * @brief SIGN函数
 * @param  x        数x
 */
#define ROV_SIGN(x) ({\
                    (x) >= 0 ? 1 : -1;\
                    })
#endif /* __GNUC__ */

//定义

//基本计算
int32_t mr_i32_exp(const int32_t num);
fp32_t mr_f32_exp(const fp32_t num);

int32_t gcd(int32_t num, int32_t denom); //betaflight gcd函数

bool mr_f32_eq(const fp32_t num1, const fp32_t num2);
bool mr_f32_greater(const fp32_t num1, const fp32_t num2);
bool mr_f32_less(const fp32_t num1, const fp32_t num2);

fp32_t mr_f32_atan(const fp32_t num);
fp32_t mr_f32_sqrt(const fp32_t num);
fp32_t mr_f32_rsqrt(const fp32_t num);

// #endif /* LIBROV_ENABLE_MATROV */
