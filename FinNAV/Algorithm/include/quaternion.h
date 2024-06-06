#pragma once
#include "Defines.h"

#ifdef LIBROV_ENABLE_QUATERNION
#include "matrov_base.h"
struct quaternion
{
    fp32_t w;
    fp32_t x;
    fp32_t y;
    fp32_t z;
};
typedef struct quaternion quaternion_t;

void alg_quat_set(quaternion_t* q, fp32_t w, fp32_t x, fp32_t y, fp32_t z);
void alg_quat_get(const quaternion_t* q, fp32_t* w, fp32_t* x, fp32_t* y, fp32_t* z);
void alg_quat_copy(quaternion_t* q, const quaternion_t* src);
bool alg_quat_eq(const quaternion_t* q1, const quaternion_t* q2);
void alg_quat_add(quaternion_t* q, const quaternion_t* q1, const quaternion_t* q2);
void alg_quat_sub(quaternion_t* q, const quaternion_t* q1, const quaternion_t* q2);
void alg_quat_mul(quaternion_t* q, const quaternion_t* q1, const quaternion_t* q2);
void alg_quat_div(quaternion_t* q, const quaternion_t* q1, const quaternion_t* q2);
void alg_quat_conj(quaternion_t* q, const quaternion_t* q1);
void alg_quat_norm(quaternion_t* q, const quaternion_t* q1);
void alg_quat_inv(quaternion_t* q, const quaternion_t* q1);

void alg_quat_to_euler(quaternion_t* q, fp32_t* roll, fp32_t* pitch, fp32_t* yaw);
void alg_quat_from_euler(quaternion_t* q, fp32_t roll, fp32_t pitch, fp32_t yaw);

void alg_quat_rotate(quaternion_t* q, const quaternion_t* q1, const quaternion_t* q2);
void alg_quat_slerp(quaternion_t* q, const quaternion_t* q1, const quaternion_t* q2, fp32_t t);

#endif /* LIBROV_ENABLE_QUATERNION */
