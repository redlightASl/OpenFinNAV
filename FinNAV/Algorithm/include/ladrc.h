#pragma once
#include "Defines.h"


#ifdef LIBROV_ENABLE_LADRC
    typedef fp32_t LADRC_UNIT_t[5][5];

    struct Modern_Ladrc
    {
        fp32_t v1; //最速输出值1
        fp32_t v2; //最速输出值2
        fp32_t r; //速度因子
        fp32_t h; //积分步长
        fp32_t wc; //控制器带宽
        fp32_t w0; //观测器带宽
        fp32_t b0; //系统参数
        fp32_t z1; //观测器输出1
        fp32_t z2; //观测器输出2
        fp32_t z3; //观测器输出3
        fp32_t u; //LADRC控制器输出
    };
    typedef struct Modern_Ladrc* Modern_Ladrc_t; /* LADRC控制ADT */

    /*
    wu = 2*3.1415/Pu;
    ku = 4*h/3.1415*a;
    wc = 2.3997wu - 0.4731;
    w0 = 0.7332wu + 3.5070;
    b0 = 3.6105wu + 4.8823;
    */
    struct Modern_Auto_Tuning
    {
        float Pu; //继电实验输出周期
        float a; //继电实验输出幅值
        float h; //指令输出幅值
        float Wu; //系统临界频率
        float Kp; //系统临界幅值
    };
    typedef struct Modern_Auto_Tuning* Modern_AutoTuning_t;

    void setLADRC_param(const LADRC_UNIT_t unit);
    void initLADRC(Modern_Ladrc_t ladrc);
    void updateLADRC(Modern_Ladrc_t ladrc, const fp32_t* exp, const fp32_t* feedback);
    fp32_t getLADRC_output(Modern_Ladrc_t ladrc);
#endif

