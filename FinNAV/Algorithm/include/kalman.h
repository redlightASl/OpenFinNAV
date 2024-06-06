#pragma once
#include "Defines.h"


// union KalmanType
// {
//     float KT_FP32;
//     KT_MAT_t KT_MAT;
// };
// typedef union KalmanType KalmanType_t;

// struct Algorithm_Kalman
// {
//     KalmanType_t* X; //先验状态估计

//     KalmanType_t* A; //状态矩阵
//     KalmanType_t* B; //输入矩阵
//     KalmanType_t* H; //观测矩阵

//     KalmanType_t* P; //先验状态估计误差协方差
//     /**
//      * @brief Q增大，动态响应变快，收敛稳定性变差
//      */
//     KalmanType_t* Q; //过程噪声协方差
//     /**
//      * @brief R增大，动态响应变慢，收敛稳定性变好
//      * @note 应按3σ原则取目标数据的(3σ)^2作为R
//      */
//     KalmanType_t* R; //测量噪声协方差
//     KalmanType_t* K; //卡尔曼增益
// };
// typedef struct Algorithm_Kalman* Algorithm_Kalman_t; /* 一维卡尔曼滤波控制ADT */

// typedef float_t KT_MAT[2][2];
// //TODO: 高阶卡尔曼滤波
// //TODO: 扩展卡尔曼滤波
// //TODO: 史密斯预估

// void initKalman(Algorithm_Kalman_t Kalman, const float_t P, const float_t Q, const float_t R);
// void setKalman_initialX(Algorithm_Kalman_t Kalman, const float_t X);
// void setKalman_P(Algorithm_Kalman_t Kalman, const float_t P);
// void inKalman(Algorithm_Kalman_t Kalman, float_t* num);
// void outKalman(Algorithm_Kalman_t Kalman, float_t* num);
