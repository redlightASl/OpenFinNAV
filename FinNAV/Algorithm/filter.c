#include "filter.h"


/**
 * @brief 低通滤波器初始化
 * @param  Filter           滤波器对象
 * @param  Alpha            滤波器参数
 */
void initLPF(Filter_LPF_t Filter, const fp32_t Alpha)
{
    Filter->Alpha = Alpha;
    Filter->now_num = 0;
    Filter->last_num = 0;
}

/**
 * @brief 低通滤波器输入
 * @param  Filter           滤波器对象
 * @param  num              输入数据
 */
void inLPF(Filter_LPF_t Filter, const fp32_t* num)
{
    Filter->last_num = Filter->now_num;
    Filter->now_num = *num;
}

/**
 * @brief 低通滤波器输出
 * @param  Filter           滤波器对象
 * @param  num              输出数据
 */
void outLPF(Filter_LPF_t Filter, fp32_t* num)
{
    *num = (Filter->now_num * Filter->Alpha) + (Filter->last_num * (1 - Filter->Alpha));
}

struct Filter_AVG
{
    uint32_t avg_scale;
    fp32_t v_m;
    fp32_t v_m_last;
};
typedef struct Filter_AVG Filter_AVG_t;

fp32_t updateAVG(Filter_AVG_t Filter, const fp32_t* num)
{
    Filter.v_m = Filter.v_m_last + (*num - Filter.v_m_last) / Filter.avg_scale;
    Filter.v_m_last = Filter.v_m;
    //在这里要让avg_scale改变
    // Filter.avg_scale++;
    // if(Filter.avg_time > )
    // {

    // }
    return Filter.v_m;
}
#ifdef LIBROV_ENABLE_SMF
/**
 * @brief 滑动均值滤波初始化
 * @param  Filter           滤波器对象
 */
void initSMF(Filter_SMF_t Filter)
{
    for (uint8_t i = 0;i < MEANFILTER_SIZE;i++)
    {
        Filter->fifo[i] = 0.0f;
    }
    Filter->fifo_head = 0;
    Filter->filter_ready = 0;
    Filter->sum = 0;
}

/**
 * @brief 滑动均值滤波输入
 * @param  Filter           滤波器对象
 * @param  num              输入数据
 */
void inSMF(Filter_SMF_t Filter, const fp32_t* num)
{
    if (Filter->filter_ready == 0)
    {
        Filter->fifo[Filter->fifo_head] = *num;
        Filter->sum += Filter->fifo[Filter->fifo_head];

        if (Filter->fifo_head >= MEANFILTER_SIZE - 1) //data ready
        {
            Filter->filter_ready = 1;
            Filter->fifo_head = 0;
        }
        else
        {
            Filter->fifo_head++;
        }
    }
    else
    {
        Filter->sum -= Filter->fifo[Filter->fifo_head]; //remove old value
        Filter->fifo[Filter->fifo_head] = *num;
        Filter->sum += Filter->fifo[Filter->fifo_head];
        Filter->fifo_head++;
        if (Filter->fifo_head > MEANFILTER_SIZE - 1)
        {
            Filter->fifo_head = 0;
        }
    }
}

/**
 * @brief 滑动均值滤波输出
 * @param  Filter           滤波器对象
 * @param  num              输出数据
 */
void outSMF(Filter_SMF_t Filter, fp32_t* num)
{
    if (Filter->filter_ready == 0) //unstable output
    {
        *num = Filter->sum / (Filter->fifo_head + 1);
    }
    else //stable output
    {
        *num = Filter->sum / MEANFILTER_SIZE;
    }
}
#endif
/**
 * @brief 一阶互补滤波器初始化
 * @param  Filter           滤波器对象
 * @param  Alpha            滤波器参数
 */
void initCF(Filter_CF_t Filter, const fp32_t Alpha)
{
    Filter->Alpha = Alpha;
    Filter->A_num = 0.0f;
    Filter->B_num = 0.0f;
}

/**
 * @brief 一阶互补滤波器输入
 * @param  Filter           滤波器对象
 * @param  A_num            滤波数据A
 * @param  B_num            滤波数据B
 */
void inCF(Filter_CF_t Filter, const fp32_t* A_num, const fp32_t* B_num)
{
    Filter->A_last = Filter->A_num;
    Filter->A_num = *A_num;
    Filter->B_num = *B_num;
}

/**
 * @brief 一阶互补滤波器输出
 * @param  Filter           滤波器对象
 * @param  num              滤波结果输出
 */
void outCF(Filter_CF_t Filter, fp32_t* num)
{
    *num = (fp32_t)((Filter->Alpha * Filter->A_num) + (1 - Filter->Alpha) * (Filter->A_last + (Filter->B_num * 0.005f)));
}

//TODO: 巴特沃斯滤波
//TODO: IIR
