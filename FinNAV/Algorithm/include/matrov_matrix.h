#pragma once
#include "Defines.h"
#include "matrov_vector.h"


/**
 * @brief 得到矩阵r行c列的某个元素
 * @param  m      矩阵
 * @param  r      行数
 * @param  c      列数
 */
#define MAT_ELEMENT(m, r, c) ((m).pData[(r) * (mat).col + (c)])

struct mr_Mat
{
    uint32_t col; //矩阵列数
    uint32_t row; //矩阵行数
    uint32_t tda; //矩阵每列元素数
    void* data; //内存数据块指针
    bool is_owner; //所有者标识，所有者拥有内存数据块的写入/释放权限
    enum
    {
        MatI32,
        MatF32
    }; //数据格式
};
typedef struct mr_Mat* mr_Mat_t;


//矩阵计算
#ifdef MATROV_STATIC_MEM
void mr_mat_init(uint32_t row, uint32_t col, uint32_t** memblk, mr_Mat_t mp);
#else
void mr_mat_alloc(const uint32_t row, const uint32_t col, mr_Mat_t mp);
void mr_mat_calloc(const uint32_t row, const uint32_t col, mr_Mat_t mp);
void mr_mat_free(mr_Mat_t mp);
#endif

void mr_mat_gen(mr_Mat_t mp, void* num_array);
void mr_mat_gen_zeros(mr_Mat_t mp);
void mr_mat_gen_all(mr_Mat_t mp, void *num);
void mr_mat_gen_one(mr_Mat_t mp);
void mr_mat_gen_eye(mr_Mat_t mp, void *num);

void mr_mat_slice(mr_Mat_t mp, const uint32_t tda, mr_Vector_t *vps_res);
void mr_mat_from_array(fp32_t* array, const uint32_t row, const uint32_t col, mr_Mat_t mp_res);
void mr_mat_from_array2d(fp32_t* array, const uint32_t row, const uint32_t col, const uint32_t tda, mr_Mat_t mp_res);
void mr_mat_from_vec(mr_Vector_t vp, mr_Mat_t mp_res);

void mr_mat_copy(mr_Mat_t mp_src, mr_Mat_t mp_dst);
struct mr_Mat mr_mat_clone(struct mr_Mat m);
void mr_mat_get_row(mr_Mat_t mp, uint32_t col, mr_Vector_t *vps_res);
void mr_mat_get_col(mr_Mat_t mp, uint32_t row, mr_Vector_t *vps_res);

void mr_mat_transpose(mr_Mat_t mp);
void mr_mat_add(mr_Mat_t mp1, mr_Mat_t mp2, mr_Mat_t mp_res);
void mr_mat_sub(mr_Mat_t mp1, mr_Mat_t mp2, mr_Mat_t mp_res);
void mr_mat_scale(mr_Mat_t mp1, const fp32_t num, mr_Mat_t mp_res);
void mr_mat_add_const(mr_Mat_t mp1, const fp32_t num, mr_Mat_t mp_res);
void mr_mat_mul_elements(mr_Mat_t mp1, mr_Mat_t mp2, mr_Mat_t mp_res);
void mr_mat_mul_dot(mr_Mat_t mp1, mr_Mat_t mp2, mr_Mat_t mp_res);
void mr_mat_mul_cross(mr_Mat_t mp1, mr_Mat_t mp2, mr_Mat_t mp_res);
void mr_mat_div_elements(mr_Mat_t mp1, mr_Mat_t mp2, mr_Mat_t mp_res);
void* mr_mat_sum_diagonal(mr_Mat_t mp);
void* mr_mat_trace(mr_Mat_t mp);
