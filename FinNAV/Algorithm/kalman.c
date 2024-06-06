#include "kalman.h"


// void initKalman(Algorithm_Kalman_t Kalman, const float_t P, const float_t Q, const float_t R)
// {
//     Kalman->X = 0.0f;
//     Kalman->A = 1.0f;
//     Kalman->H = 1.0f;
//     Kalman->P = P;
//     Kalman->Q = Q;
//     Kalman->R = R;
//     Kalman->K_gain = 0.0f;
// }

// void setKalman_initialX(Algorithm_Kalman_t Kalman, const float_t X)
// {
//     Kalman->X = X;
// }

// void setKalman_P(Algorithm_Kalman_t Kalman, const float_t P)
// {
//     Kalman->P = P;
// }

// void inKalman(Algorithm_Kalman_t Kalman, float_t* num)
// {
//     // Predict
//     Kalman->X = Kalman->A * Kalman->X + Kalman->B;
//     Kalman->P = Kalman->A * Kalman->A * Kalman->P + Kalman->Q;
//     //Measure Update
//     Kalman->K = (Kalman->P * Kalman->H) / (Kalman->P * Kalman->H * Kalman->H + Kalman->R);
//     Kalman->X = Kalman->X + (Kalman->K * ((*num) - Kalman->H * Kalman->X));
//     Kalman->P = (1 - Kalman->K * Kalman->H) * Kalman->P;
// }

// void outKalman(Algorithm_Kalman_t Kalman, float_t* num)
// {
//     *num = Kalman->X;
// }

// //TODO: 高阶卡尔曼滤波
// // KalmanFilter(float _dt,float _speed_error,float _acc_error){
// // 			dt = _dt;
// // 			Q_mat[0] = _speed_error*_speed_error;
// // 			Q_mat[3] = _acc_error*_acc_error;
// // 			R_mat[0] = _speed_error*_speed_error;
// // 			R_mat[3] = _acc_error*_acc_error;
// // 		}


// /**
//  * @brief 卡尔曼滤波初始化
//  * @param  Kalman           卡尔曼滤波对象
//  * @param  P                P矩阵
//  * @param  R                R矩阵
//  * @param  Q                Q矩阵
//  */
// void InitKalman(Algorithm_Kalman_t Kalman, const float_t dt, const float_t _speed_error, const float_t _acc_error)
// {
//     Kalman->dt = dt;
//     Kalman->Q_mat[0] =
// }

// /**
//  * @brief 卡尔曼滤波计算
//  * @param  Kalman           卡尔曼滤波对象
//  * @param  original_value   原始值
//  * @return float_t 滤波输出值
//  */
// float_t KalmanFilter(Algorithm_Kalman_t Kalman, float_t original_value)
// {
//     float_t p_mid = 0.0;
//     float_t kg = 0.0;
//     float_t p_now = 0.0;

//     p_mid = Kalman->Last_P + Kalman->Measure_Q;
//     kg = p_mid / (p_mid + Kalman->Process_R);

//     Kalman->x_now = Kalman->x_last + kg * (original_value - Kalman->x_last); //最优值估计
//     p_now = (1 - kg) * p_mid; //最优值对应的协方差

//     Kalman->Last_P = p_now;
//     Kalman->x_last = Kalman->x_now;

//     return Kalman->x_now;
// }

//TODO: EKF
