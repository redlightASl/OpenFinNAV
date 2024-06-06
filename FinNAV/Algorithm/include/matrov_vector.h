#pragma once
#include "Defines.h"


struct mr_Vector
{
    uint32_t size; //向量长度
    uint32_t stride; //向量中每个元素所占内存大小
    void* data; //内存数据块指针
    int32_t is_owner; //所有者标识，所有者拥有内存数据块的写入/释放权限
    enum
    {
        VecI32,
        VecF32
    }; //数据格式
};
typedef struct mr_Vector* mr_Vector_t;

//向量计算
#ifdef MATROV_STATIC_MEM
void mr_vec_init(uint32_t size, uint32_t stride, uint32_t* memblk, mr_Vector_t vp);
#else
void mr_vec_alloc(uint32_t size, uint32_t stride, mr_Vector_t vp);
void mr_vec_calloc(uint32_t size, uint32_t stride, mr_Vector_t vp);
void mr_vec_free(mr_Vector_t vp);
#endif

void mr_vec_set(mr_Vector_t vp, uint32_t i, void* num); //将v的第i+1个元素设置为num
void mr_vec_set_all(mr_Vector_t vp, void* num);
void mr_vec_set_zero(mr_Vector_t vp);
void mr_vec_set_basis(mr_Vector_t vp, uint32_t i); //将v的第i+1个元素设置为1，其余元素为0
void mr_vec_get(mr_Vector_t vp, uint32_t i, void* res); //获得v的第i+1个元素

//从v向量中的第offset+1个元素开始提取n个元素构建一个子向量
void mr_vec_slice(mr_Vector_t vp, uint32_t offset, uint32_t size, mr_Vector_t sub_vp);
void mr_vec_from_array(mr_Vector_t vp, void* array);
void mr_vec_to_array(mr_Vector_t vp, void* res_array);

void mr_vec_copy(mr_Vector_t vp_src, mr_Vector_t vp_dst);
struct mr_Vector mr_vec_clone(struct mr_Vector v);

void mr_vec_swap(mr_Vector_t vp, uint32_t i1, uint32_t i2); //元素互换
void mr_vec_reverse(mr_Vector_t vp); //倒序排列
void mr_vec_add(mr_Vector_t vp1, mr_Vector_t vp2, mr_Vector_t vp_res);
void mr_vec_sub(mr_Vector_t vp1, mr_Vector_t vp2, mr_Vector_t vp_res);
void mr_vec_mul(mr_Vector_t vp1, mr_Vector_t vp2, mr_Vector_t vp_res);
void mr_vec_div(mr_Vector_t vp1, mr_Vector_t vp2, mr_Vector_t vp_res);
void mr_vec_dot(mr_Vector_t vp1, mr_Vector_t vp2, void* num); //向量点积
void mr_vec_cross(mr_Vector_t vp1, mr_Vector_t vp2, mr_Vector_t vp_res); //向量叉积
void mr_vec_normalize(mr_Vector_t p); //归一化
void mr_vec_scale(mr_Vector_t vp, const fp32_t num);
void mr_vec_add_const(mr_Vector_t vp, const fp32_t num);
void* mr_vec_sum(mr_Vector_t vp); //所有元素求和
void* mr_vec_max(mr_Vector_t vp); //最大值
void* mr_vec_min(mr_Vector_t vp); //最小值
uint32_t mr_vec_max_index(mr_Vector_t vp); //最大值位置
uint32_t mr_vec_min_index(mr_Vector_t vp); //最小值位置
