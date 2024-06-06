#pragma once
#include "Defines.h"


/**
 * @brief 一阶低通滤波LPF
 */
struct Filter_LPF
{
    fp32_t Alpha; //滤波参数 0~1
    fp32_t now_num; //反馈值
    fp32_t last_num; //上次值
};
typedef struct Filter_LPF* Filter_LPF_t;

#ifdef LIBROV_ENABLE_SMF
/**
 * @brief 滑动均值滤波SMF
 */
struct Filter_SMF
{
    fp32_t fifo[MEANFILTER_SIZE]; //滑动滤波FIFO
    uint32_t fifo_head; //FIFO头指针
    int8_t filter_ready; //FIFO尾指针
    fp32_t sum; //输出值
};
typedef struct Filter_SMF* Filter_SMF_t;
#endif

/**
 * @brief 一阶互补滤波CF
 */
struct Filter_CF
{
    fp32_t Alpha; //滤波参数 0~1
    fp32_t A_num; //输入量A
    fp32_t A_last; //输入量A上次值
    fp32_t B_num; //输入量B
};
typedef struct Filter_CF* Filter_CF_t;

/**
 * @brief 巴特沃斯滤波器BWF
 */
struct Filter_BWF
{
    fp32_t a;
};
typedef struct Filter_BWF* Filter_BWF_t;

void initLPF(Filter_LPF_t Filter, const fp32_t Alpha);
void inLPF(Filter_LPF_t Filter, const fp32_t* num);
void outLPF(Filter_LPF_t Filter, fp32_t* num);
#ifdef LIBROV_ENABLE_SMF
void initSMF(Filter_SMF_t Filter);
void inSMF(Filter_SMF_t Filter, const fp32_t* num);
void outSMF(Filter_SMF_t Filter, fp32_t* num);
#endif
void initCF(Filter_CF_t Filter, const fp32_t Alpha);
void inCF(Filter_CF_t Filter, const fp32_t* A_num, const fp32_t* B_num);
void outCF(Filter_CF_t Filter, fp32_t* num);

//TODO: 巴特沃斯滤波 
//TODO: IIR

