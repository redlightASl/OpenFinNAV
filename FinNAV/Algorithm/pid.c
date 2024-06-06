#include "pid.h"


// #ifdef ENABLE_PID
/**
 * @brief PID初始化
 * @param  Pid              PID对象
 * @param  mode             PID控制模式
 * @param  fb_gain          反馈增益
 * @param  st_init          初始采样时间
 * @param  kp_init          初始P参数
 * @param  ki_init          初始I参数
 * @param  kd_init          初始D参数
 * @param  err_min          误差限幅下限
 * @param  err_max          误差限幅上限
 * @param  int_sep          积分分离阈值
 * @param  int_decay        积分衰减
 * @param  int_min          积分限幅下限
 * @param  int_max          积分限幅上限
 * @param  dif_min          微分限幅下限
 * @param  dif_max          微分限幅上限
 * @param  output_min       输出限幅下限
 * @param  output_max       输出限幅上限
 * @param  bias             基础偏置值
 * @param  feedforward      前馈值
 */
void initPID(Classical_PID_t Pid, uint8_t mode,
    fp32_t fb_gain,
    fp32_t st_init,
    fp32_t kp_init,
    fp32_t ki_init,
    fp32_t kd_init,
    fp32_t err_min,
    fp32_t err_max,
    fp32_t int_sep,
    fp32_t int_decay,
    fp32_t int_min,
    fp32_t int_max,
    fp32_t dif_min,
    fp32_t dif_max,
    fp32_t output_min,
    fp32_t output_max,
    fp32_t bias,
    fp32_t feedforward
)
{
    Pid->mode |= mode;
    Pid->FeedBack_gain = fb_gain;
    Pid->sample_time = st_init;
    Pid->getPID_time = (ROV_VOID_POINTER)(0);
    Pid->Error = 0.0f;
    Pid->LastError = 0.0f;
#ifdef ENABLE_INCRETOR
    Pid->LastLastError = 0.0f;
#endif
    Pid->Output = 0.0f;
#ifdef FIXED_PID_PARAMETER
    Pid->Kp = PID_Kp / 1000.0f;
    Pid->Ki = PID_Ki / 1000.0f;
    Pid->Kd = PID_Kd / 1000.0f;
    Pid->FF = PID_FF;
    Pid->ErrorMinValue = PID_ERROR_MIN / 1000.0f;
    Pid->ErrorMaxValue = PID_ERROR_MAX / 1000.0f;
    Pid->IntSeperation = PID_INT_SEPERATION / 1000.0f;
    Pid->IntDecay = PID_INT_DECAY / 1000.0f;
    Pid->IntMinValue = PID_INT_MIN / 1000.0f;
    Pid->IntMaxValue = PID_INT_MAX / 1000.0f;
    Pid->DifMinValue = PID_DIFF_MIN / 1000.0f;
    Pid->DifMaxValue = PID_DIFF_MAX / 1000.0f;
    Pid->OutMinValue = PID_OUTPUT_MIN / 1000.0f;
    Pid->OutMaxValue = PID_OUTPUT_MAX / 1000.0f;
#else
    Pid->Kp = kp_init;
    Pid->Ki = ki_init;
    Pid->Kd = kd_init;
    Pid->FF = feedforward;
    Pid->ErrorMinValue = err_min;
    Pid->ErrorMaxValue = err_max;
    Pid->IntSeperation = int_sep;
    Pid->IntDecay = int_decay;
    Pid->IntMinValue = int_min;
    Pid->IntMaxValue = int_max;
    Pid->DifMinValue = dif_min;
    Pid->DifMaxValue = dif_max;
    Pid->OutMinValue = output_min;
    Pid->OutMaxValue = output_max;
#endif
}

/**
 * @brief 设置PID模式配置
 * @param  Pid              PID对象
 * @param  mode             PID模式
 */
void setPID_mode(Classical_PID_t Pid, uint8_t mode)
{
    Pid->mode |= mode;
}

/**
 * @brief 设置PID是否为定向PID
 * @param  Pid              PID对象
 * @param  is_orbit_pid     是否为定向PID
 */
void setPID_isorbit(Classical_PID_t Pid, uint8_t is_orbit_pid)
{
    Pid->is_orbit_pid = is_orbit_pid;
}

/**
 * @brief 设置PID目标值
 * @param  Pid              PID对象
 * @param  target           目标值
 */
void setPID_target(Classical_PID_t Pid, fp32_t target)
{
    Pid->Target = target;
}

/**
 * @brief 设置PID反馈值
 * @param  Pid              PID对象
 * @param  fb               反馈值
 */
void setPID_feedback(Classical_PID_t Pid, fp32_t fb)
{
    Pid->FeedBack = fb * Pid->FeedBack_gain;
}

/**
 * @brief 设置PID反馈增益
 * @param  Pid              PID对象
 * @param  fbg              反馈增益
 */
void setPID_fbgain(Classical_PID_t Pid, fp32_t fbg)
{
    Pid->FeedBack_gain = fbg;
}

/**
 * @brief 设置PID时间触发回调函数
 * @param  Pid              PID对象
 * @param  cb               时间触发回调函数
 */
void setPID_time_callback(Classical_PID_t Pid, const pid_time_cb_t cb)
{
    Pid->getPID_time = cb;
}

/**
 * @brief 清空PID历史数据
 * @param  Pid              PID对象
 */
void clearPID_data(Classical_PID_t Pid)
{
    Pid->last_time = 0;
    Pid->now_time = 0;
    Pid->Error = 0.0f;
    Pid->LastError = 0.0f;
#ifdef ENABLE_INCRETOR
    Pid->LastLastError = 0.0f;
#endif
    Pid->DeltaIntegral = 0.0f;
    Pid->DeltaDifference = 0.0f;
}

#ifdef PID_EXTENSION_LPF
/**
 * @brief 设置PID的低通滤波器参数
 * @param  Pid              PID对象
 * @param  err_a            误差LPF参数
 * @param  diff_a           差分LPF参数
 */
void setPID_lpf(Classical_PID_t Pid, fp32_t err_a, fp32_t diff_a)
{
    Pid->Error_Alpha = err_a;
    Pid->Diff_Alpha = diff_a;
}
#endif

/**
 * @brief 设置PID参数
 * @param  Pid              PID对象
 * @param  Kp               比例P参数
 * @param  Ki               积分I参数
 * @param  Kd               微分D参数
 * @param  Ts               控制间隔ms
 */
void setPID_param(Classical_PID_t Pid, fp32_t Kp, fp32_t Ki, fp32_t Kd, uint64_t Ts)
{
    Pid->Kp = Kp;
    Pid->Ki = Ki;
    Pid->Kd = Kd;
    if (Ts > 0)
    {
        Pid->sample_time = Ts;
    }
}

/**
 * @brief 设置PID积分衰减
 * @param  Pid              PID对象
 * @param  IntDecay         积分衰减值
 */
void setPID_IntDecay(Classical_PID_t Pid, fp32_t IntDecay)
{
    Pid->IntDecay = IntDecay;
}

/**
 * @brief 设置PID前馈值
 * @param  Pid              PID对象
 * @param  FF               前馈值
 */
void setPID_FF(Classical_PID_t Pid, fp32_t FF)
{
    Pid->FF = FF;
}

/**
 * @brief 设置PID偏置值
 * @param  Pid              PID对象
 * @param  bias             基础偏置值
 */
void setPID_Bias(Classical_PID_t Pid, fp32_t bias)
{
    Pid->Bias = bias;
}

/**
 * @brief 获取PID输出
 * @param  Pid              PID对象
 * @return fp32_t PID输出
 */
fp32_t getPID_output(Classical_PID_t Pid)
{
    return Pid->Output;
}

#ifdef ENABLE_INCRETOR
/**
 * @brief 计算增量式PID
 * @param  Pid              PID对象
 * @return fp32_t 若为增量式PID，输出结果；若不为增量式PID，输出ROV_FALSE
 */
fp32_t calculatePID_incretor(Classical_PID_t Pid)
{
    if (Pid->mode & PID_INCRETOR)
    {
        Pid->Error = Pid->Target - Pid->FeedBack; //calculate err(t)

        Pid->Output = Pid->Kp * (Pid->Error - Pid->LastError) + Pid->Ki * Pid->Error * Pid->sample_time
            + Pid->Kd * (Pid->Error - (2 * (Pid->LastError)) + Pid->LastLastError) / Pid->sample_time; //PID

        //restrict output
        RestrictValue(Pid->Output, Pid->OutMinValue, Pid->OutMaxValue);

        Pid->LastLastError = Pid->LastError; //load err_2(t)
        Pid->LastError = Pid->Error; //load err_1(t)

        return Pid->Output;
    }
    return (fp32_t)ROV_FALSE;
}
#endif

/**
 * @brief 计算位置式PID
 * @param  Pid              PID对象
 * @return fp32_t 若为位置式PID，输出结果；若不为位置式PID，输出ROV_FALSE
 */
fp32_t calculatePID_position(Classical_PID_t Pid)
{
    if (Pid->getPID_time != (ROV_VOID_POINTER)(0))
    {
        Pid->now_time = Pid->getPID_time();
    }
    else
    {
        Pid->now_time = 1; //did not setup callback function, default Ts=1
    }

    Pid->sample_time = (uint64_t)(Pid->now_time) - (uint64_t)(Pid->last_time);
    Pid->Error = Pid->Target - Pid->FeedBack; //calculate err(t)=e(t)-r(t)

#ifdef PID_EXTENSION_ORBIT
    /*
     * extension judgement for orbit mode
     * check if yaw change between 0 and 360
     */
    if (Pid->is_orbit_pid)
    {
        if ((Pid->Error > 180) || (Pid->Error < -180)) //abs(Pid->Error) > 180
        {
            if (Pid->FeedBack > 180) //from 0 to 360
            {
                Pid->Error += 360;
            }
            else //from 360 to 0
            {
                Pid->Error -= 360;
            }
        }
    }
#endif
#ifdef PID_EXTENSION_LPF
    if (Pid->mode & PID_ERROR_LPF) //use LPF to filter Error noise
    {
        Pid->Error_LPF = Pid->Error_LPF + ((Pid->Error_Alpha) * (Pid->Error - Pid->Error_LPF));
        Pid->Error = Pid->Error_LPF;
    }
#endif
    //restrict error
    if (Pid->mode & PID_LIMIT_ERROR)
    {
        RestrictValue(Pid->Error, Pid->ErrorMinValue, Pid->ErrorMaxValue);
    }

#ifdef PID_IN_PD_MODE
    Pid->DeltaIntegral = 0.0f;
#else
    //calculate integration
    if (Pid->mode & PID_INT_SEPERATION) //integral seperation
    {
        if ((ABS(Pid->Error)) < Pid->IntSeperation)
        {
            Pid->DeltaIntegral += Pid->Error * Pid->sample_time; // Pid->DeltaIntegral += Pid->Error;
        }
        else
        {
            Pid->DeltaIntegral += Pid->IntDecay; //integration decay
        }
    }
    else
    {
        Pid->DeltaIntegral += Pid->Error * Pid->sample_time; // Pid->DeltaIntegral += Pid->Error;
    }

    //restrict integration
    RestrictValue(Pid->DeltaIntegral, Pid->IntMinValue, Pid->IntMaxValue);
#endif

    Pid->DeltaDifference = 0.0f;

    //calculate difference
    Pid->DeltaDifference = (Pid->Error - Pid->LastError) / (Pid->sample_time);
#ifdef PID_EXTENSION_LPF
    if (Pid->mode & PID_LPF) //use LPF to inhibit Diff noise
    {
        Pid->Diff_LPF = Pid->Diff_LPF + (Pid->Diff_Alpha) * (Pid->DeltaDifference - Pid->Diff_LPF);
        Pid->DeltaDifference = Pid->Diff_LPF;
    }
#else
    //TODO: 添加微分环节基于积分反馈环的噪声抑制功能
#endif
    //restrict difference
    RestrictValue(Pid->DeltaDifference, Pid->DifMinValue, Pid->DifMaxValue);

    //PID Calculation
    Pid->Output = Pid->Kp * Pid->Error + Pid->Ki * Pid->DeltaIntegral + Pid->Kd * Pid->DeltaDifference;
    Pid->Output += Pid->Bias; //Bias Count in

    if (Pid->mode & PID_FEED_FORWARD) //feed forward
    {
        Pid->Output += Pid->FF;
    }

    //restrict output
    RestrictValue(Pid->Output, Pid->OutMinValue, Pid->OutMaxValue);

    //load err_1(t)
    Pid->LastError = Pid->Error;
    Pid->last_time = Pid->now_time;

    return Pid->Output;
}

/**
 * @brief 计算串级PID
 * @param  Pid              串级PID对象
 * @return fp32_t 串级PID输出
 */
fp32_t calculatePID_cascade(Classical_CascadePID_t Pid)
{
    fp32_t o = 0.0f;
    setPID_target(&(Pid->outer), Pid->Target);
    setPID_feedback(&(Pid->outer), Pid->Feedback);
    calculatePID_position(&(Pid->outer)); //outer PID calculation
    o = getPID_output(&(Pid->outer));
    setPID_target(&(Pid->inner), o);
    setPID_feedback(&(Pid->inner), Pid->dFeedback);
    calculatePID_position(&(Pid->inner)); //inner PID calculation
    Pid->Output = getPID_output(&(Pid->inner));
    return Pid->Output;
}

// #endif /* ENABLE_PID */
