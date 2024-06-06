#include "matrov_matrix.h"

// #ifdef ENABLE_MATROV
// #ifdef MATRIX_STATIC_MEM
// /**
//  * @brief 静态初始化矩阵
//  * @param  mat              待初始化矩阵
//  * @param  memblk           矩阵内存区
//  * @param  row              行数
//  * @param  col              列数
//  * @return uint8_t ROV_TRUE 成功
//  */
// uint8_t mr_init(MatR_t mat, uint8_t** memblk, uint32_t row, uint32_t col)
// {
//     if (memblk == NULL) //null memory
//     {
//         return ROV_FALSE;
//     }

//     mat->element = memblk;
//     mat->row = row;
//     mat->col = col;

//     return ROV_TRUE;
// }
// #else
// /**
//  * @brief 动态创建矩阵
//  * @param  mat              待创建矩阵
//  * @param  row              行数
//  * @param  col              列数
//  * @return uint8_t ROV_TRUE 成功
//  */
// uint8_t mr_create(MatR_t mat, uint32_t row, uint32_t col)
// {
//     mat->element = (float_t**)rov_malloc(row * sizeof(float_t*));
//     if (mat->element == NULL)//malloc fail
//     {
//         return ROV_FALSE;
//     }

//     for (uint32_t i = 0; i < row; i++)
//     {
//         mat->element[i] = (float_t*)rov_malloc(col * sizeof(float_t));
//         if (mat->element[i] == NULL) //malloc fail
//         {
//             for (uint32_t j = 0; j < i; j++)
//             {
//                 rov_mfree(mat->element[j]);
//             }
//             rov_mfree(mat->element);
//             return ROV_FALSE;
//         }
//     }

//     mat->row = row;
//     mat->col = col;

//     return ROV_TRUE;
// }

// /**
//  * @brief 动态释放矩阵
//  * @param  mat              待释放矩阵
//  * @return uint8_t ROV_TRUE 成功
//  */
// uint8_t mr_delete(MatR_t mat)
// {
//     for (uint32_t i = 0; i < mat->row; i++)
//     {
//         rov_mfree(mat->element[i]);
//     }
//     rov_mfree(mat->element);
//     return ROV_TRUE;
// }
// #endif 

// /**
//  * @brief 生成零矩阵/空矩阵
//  * @param  mat              矩阵对象
//  * @return uint8_t ROV_TRUE 成功
//  */
// uint8_t mr_generate_zeros(MatR_t mat)
// {
//     for (uint32_t i = 0; i < mat->row; i++)
//     {
//         for (uint32_t j = 0; j < mat->col; j++)
//         {
//             mat->element[i][j] = 0.0f;
//         }
//     }
//     return ROV_TRUE;
// }

// /**
//  * @brief 生成全1矩阵
//  * @param  mat              矩阵对象
//  * @return uint8_t ROV_TRUE 成功
//  */
// uint8_t mr_generate_one(MatR_t mat)
// {
//     for (uint32_t i = 0; i < mat->row; i++)
//     {
//         for (uint32_t j = 0; j < mat->col; j++)
//         {
//             mat->element[i][j] = 1.0f;
//         }
//     }
//     return ROV_TRUE;
// }

// /**
//  * @brief 生成对角矩阵
//  * @param  mat              矩阵对象
//  * @return uint8_t ROV_TRUE 成功
//  */
// uint8_t mr_generate_eye(MatR_t mat)
// {
//     for (uint32_t i = 0; i < mat->row; i++)
//     {
//         for (uint32_t j = 0; j < mat->col; j++)
//         {
//             if (i == j)
//             {
//                 mat->element[i][j] = 1.0f;
//             }
//             else
//             {
//                 mat->element[i][j] = 0.0f;
//             }
//         }
//     }
//     return ROV_TRUE;
// }

// /**
//  * @brief 矩阵求和
//  * @param  mat_m            矩阵m
//  * @param  mat_n            矩阵n
//  * @param  mat_res          矩阵和
//  * @return uint8_t ROV_TRUE 成功
//  */
// uint8_t mr_add(MatR_t mat_m, MatR_t mat_n, MatR_t mat_res)
// {
//     if ((mat_m->row != mat_n->row) || (mat_m->col != mat_n->col))
//     {
//         return ROV_FALSE;
//     }

//     for (uint32_t i = 0; i < mat_m->row; i++)
//     {
//         for (uint32_t j = 0; j < mat_m->col; j++)
//         {
//             mat_res->element[i][j] = mat_m->element[i][j] + mat_n->element[i][j];
//         }
//     }
//     return ROV_TRUE;
// }

// /**
//  * @brief 矩阵点乘
//  * @param  mat_m            矩阵m
//  * @param  mat_n            矩阵n
//  * @param  mat_res          矩阵点乘积
//  * @return uint8_t ROV_TRUE 成功
//  */
// uint8_t mr_mul(MatR_t mat_m, MatR_t mat_n, MatR_t mat_res)
// {
//     float_t temp = 0.0f;
//     if (mat_m->col != mat_n->row)
//     {
//         return ROV_FALSE;
//     }

//     for (uint32_t i = 0; i < mat_res->row; i++)
//     {
//         for (uint32_t j = 0; j < mat_res->col; j++)
//         {
//             temp = 0.0f;
//             for (uint32_t k = 0; k < mat_m->col; k++)
//             {
//                 temp += mat_m->element[i][k] * mat_n->element[k][j];
//             }
//             mat_res->element[i][j] = temp;
//         }
//     }
//     return ROV_TRUE;
// }

// /**
//  * @brief 矩阵转置
//  * @param  mat              原矩阵
//  * @param  mat_res          转置矩阵
//  * @return uint8_t ROV_TRUE 成功
//  */
// uint8_t mr_tr(MatR_t mat, MatR_t mat_res)
// {
//     if ((mat_res->col != mat->row) || (mat_res->row != mat->col))
//     {
//         return ROV_FALSE;
//     }

//     for (uint32_t i = 0; i < mat_res->row; i++)
//     {
//         for (uint32_t j = 0; j < mat_res->col; j++)
//         {
//             mat_res->element[i][j] = mat->element[j][i];
//         }
//     }
//     return ROV_TRUE;
// }

// /**
//  * @brief 矩阵置换
//  * @param  list
//  * @param  k
//  * @param  m
//  * @param  p
//  * @param  mat
//  * @param  det
//  */
// static void mr_permutate(int32_t list[], int32_t k, int32_t m, int32_t* p, MatR_t mat, float_t* det)
// {
//     uint32_t i = 0;
//     if (k > m)
//     {
//         float_t res = mat->element[0][list[0]];
//         for (i = 1; i < mat->row; i++)
//         {
//             res *= mat->element[i][list[i]];
//         }
//         if (*p % 2) //odd or even
//         {
//             *det -= res; //odd is negative
//         }
//         else
//         {
//             *det += res; //even is positive
//         }
//     }
//     else
//     {
//         mr_permutate(list, k + 1, m, p, mat, det);
//         for (i = k + 1; i <= m; i++)
//         {
//             swap(&list[k], &list[i]);
//             *p += 1;
//             mr_permutate(list, k + 1, m, p, mat, det);
//             swap(&list[k], &list[i]);
//             *p -= 1;
//         }
//     }
// }

// /**
//  * @brief 矩阵求行列式
//  * @param  mat              原矩阵
//  * @param  result           行列式值
//  * @return uint8_t ROV_TRUE 成功
//  */
// uint8_t mr_det(MatR_t mat, float_t* result)
// {
//     int32_t plarity = 0;

//     if (mat->col != mat->row) //square matrix
//     {
//         return ROV_FALSE;
//     }

//     int32_t* list = (int32_t*)rov_malloc(sizeof(int32_t) * mat->col);
//     if (list == NULL)
//     {
//         return ROV_FALSE;
//     }

//     for (uint32_t i = 0; i < mat->col; i++)
//     {
//         list[i] = i;
//     }

//     mr_permutate(list, 0, mat->row - 1, &plarity, mat, result);
//     rov_mfree(list);
//     return ROV_TRUE;
// }

// #endif
