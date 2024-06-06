#include "matrov_base.h"

// /**
//  * @brief 二维向量计算欧氏距离
//  * @param  vec              二维向量
//  * @return float_t 欧氏距离
//  */
// inline float_t fin_vp2_distance(const Point2d_t vec)
// {
//     return sqrt(vec->x * vec->x + vec->y * vec->y);
// }

// /**
//  * @brief 二维向量归一化
//  * @param  vec              原始二维向量
//  * @param  res              归一化向量
//  */
// void fin_vp2_normalize(const Point2d_t vec, Point2d_t res)
// {
//     float_t rsqrt_num = fin_rsqrt(vec->x * vec->x + vec->y * vec->y);
//     res->x = vec->x * rsqrt_num;
//     res->y = vec->y * rsqrt_num;
// }

// /**
//  * @brief 二维向量点积
//  * @param  vec_m            二维向量m
//  * @param  vec_n            二维向量n
//  * @return float_t m .* n
//  */
// inline float_t fin_vp2_dot_product(const Point2d_t vec_m, const Point2d_t vec_n)
// {
//     return vec_m->x * vec_n->x + vec_m->y * vec_n->y;
// }

// /**
//  * @brief 三维向量欧氏距离
//  * @param  vec              三维向量
//  * @return float_t 欧氏距离
//  */
// inline float_t fin_vp3_distance(const Point3d_t vec)
// {
//     return sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
// }

// /**
//  * @brief 三维向量归一化
//  * @param  vec              原始三维向量
//  * @param  res              归一化向量
//  */
// void fin_vp3_normalize(const Point3d_t vec, Point3d_t res)
// {
//     float_t rsqrt_num = fin_rsqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
//     res->x = vec->x * rsqrt_num;
//     res->y = vec->y * rsqrt_num;
//     res->z = vec->z * rsqrt_num;
// }

// /**
//  * @brief 三维向量点积
//  * @param  vec_m            三维向量m
//  * @param  vec_n            三维向量n
//  * @return float_t m .* n
//  */
// inline float_t fin_vp3_dot_product(const Point3d_t vec_m, const Point3d_t vec_n)
// {
//     return vec_m->x * vec_n->x + vec_m->y * vec_n->y + vec_m->z * vec_n->z;
// }

// /**
//  * @brief 三维向量叉积
//  * @param  vec_m            三维向量m
//  * @param  vec_n            三维向量n
//  * @param  vec_res          三维向量叉积 m x n
//  */
// void fin_vp3_cross_product(const Point3d_t vec_m, const Point3d_t vec_n, Point3d_t vec_res)
// {
//     vec_res->x = vec_m->y * vec_n->z - vec_m->z * vec_n->y;
//     vec_res->y = vec_m->z * vec_n->x - vec_m->x * vec_n->z;
//     vec_res->z = vec_m->x * vec_n->y - vec_m->y * vec_n->x;
// }
