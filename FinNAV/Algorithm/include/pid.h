#pragma once
#include "Defines.h"


/* PID */
// #ifdef ENABLE_PID
enum pid_method_e
{
    PID_INCRETOR = 0x01,
    PID_LIMIT_ERROR = 0x02,
    PID_INT_SEPERATION = 0x04,
    PID_FEED_FORWARD = 0x10,
    PID_LPF = 0x20,
    PID_ERROR_LPF = 0x40,
};


typedef uint64_t(*pid_time_cb_t)(void);
struct Classical_PID
{
    uint8_t mode; //PID模式设置
    uint8_t is_orbit_pid; //定向PID标志

    fp32_t Target; //目标值
    fp32_t FeedBack; //反馈值
    fp32_t FeedBack_gain; //反馈增益

    uint64_t sample_time; //采样时间
    uint64_t last_time; //上次计算时间
    uint64_t now_time; //当前时间
    pid_time_cb_t getPID_time; //获取系统时钟回调函数

    fp32_t Error; //误差
    fp32_t LastError; //上次误差
#ifdef ENABLE_INCRETOR
    fp32_t LastLastError; //上上次误差
#endif
    fp32_t DeltaIntegral; //误差的积分
    fp32_t DeltaDifference; //误差的差分
#ifdef PID_EXTENSION_LPF
    fp32_t Error_LPF;
    fp32_t Error_Alpha;
    fp32_t Diff_LPF;
    fp32_t Diff_Alpha;
#endif
    fp32_t Kp; //PID参数p
    fp32_t Ki; //PID参数i
    fp32_t Kd; //PID参数d

    fp32_t ErrorMinValue; //误差限幅下限
    fp32_t ErrorMaxValue; //误差限幅上限
    fp32_t IntMinValue; //积分限幅下限
    fp32_t IntMaxValue; //积分限幅上限
    fp32_t IntSeperation; //积分分离阈值
    fp32_t IntDecay; //积分衰减
    fp32_t DifMinValue; //微分限幅下限
    fp32_t DifMaxValue; //微分限幅上限
    fp32_t OutMinValue; //输出限幅下限
    fp32_t OutMaxValue; //输出限幅上限
    fp32_t FF; //前馈值
    fp32_t Bias; //基础偏置值
    fp32_t Output; //输出值
};
typedef struct Classical_PID* Classical_PID_t; /* PID控制ADT */

struct Classical_CascadePID
{
    fp32_t Target;
    fp32_t Feedback;
    fp32_t dFeedback;
    struct Classical_PID inner;
    struct Classical_PID outer;
    fp32_t Output;
};
typedef struct Classical_CascadePID* Classical_CascadePID_t; /* 串级PID控制ADT */


void initPID(Classical_PID_t Pid, uint8_t mode, fp32_t fb_gain, fp32_t st_init, fp32_t kp_init,
    fp32_t ki_init, fp32_t kd_init, fp32_t err_min, fp32_t err_max, fp32_t int_sep, fp32_t int_decay,
    fp32_t int_min, fp32_t int_max, fp32_t dif_min, fp32_t dif_max, fp32_t output_min, fp32_t output_max,
    fp32_t bias, fp32_t feedforward
);
void setPID_mode(Classical_PID_t Pid, uint8_t mode);
void setPID_isorbit(Classical_PID_t Pid, uint8_t is_orbit_pid);
void setPID_target(Classical_PID_t Pid, fp32_t target);
void setPID_feedback(Classical_PID_t Pid, fp32_t fb);
void setPID_fbgain(Classical_PID_t Pid, fp32_t fbg);
void setPID_time_callback(Classical_PID_t Pid, const pid_time_cb_t cb);
void clearPID_data(Classical_PID_t Pid);
#ifdef PID_EXTENSION_LPF
void setPID_lpf(Classical_PID_t Pid, fp32_t err_a, fp32_t diff_a);
#endif
void setPID_param(Classical_PID_t Pid, fp32_t Kp, fp32_t Ki, fp32_t Kd, uint64_t Ts);
void setPID_IntDecay(Classical_PID_t Pid, fp32_t IntDecay);
void setPID_FF(Classical_PID_t Pid, fp32_t FF);
void setPID_Bias(Classical_PID_t Pid, fp32_t bias);
fp32_t getPID_output(Classical_PID_t Pid);
#ifdef ENABLE_INCRETOR
fp32_t calculatePID_incretor(Classical_PID_t Pid);
#endif
fp32_t calculatePID_position(Classical_PID_t Pid);
fp32_t calculatePID_cascade(Classical_CascadePID_t Pid);
#ifdef ENABLE_FUZZY_PID
//TODO: 模糊PID
#endif
// #endif /* ENABLE_PID */

