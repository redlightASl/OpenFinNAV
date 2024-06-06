#include "ladrc.h"


/**
 * @note 根据经验 ts在0.2~0.3之间 W0与Wc选定后从小到大整定b0
 * ---------------------------------------------------
 *               LADRC default参数表
 * ---------------------------------------------------
 * ---------------------------------------------------
 *     ts	|	h	|	r	|   wc   |   w0  |	b0
 * ---------------------------------------------------
 *     0.1	|	h	|	r	|  100   |  400  |	b0
 * ---------------------------------------------------
 *    0.157|	h	|	r	|   64   |  224~255  |	b0
 * ---------------------------------------------------
 *    0.158|	h	|	r	|   63   |  253  |	b0
 * ---------------------------------------------------
 *    0.159|	h	|	r	|   63   |  252  |	b0
 * ---------------------------------------------------
 *     0.16|	h	|	r	|   63   |  250  |	b0
 * ---------------------------------------------------
 *     0.17|	h	|	r	|   59   |  235  |	b0
 * ---------------------------------------------------
 *     0.18|	h	|	r	|   56   |  222  |	b0
 * ---------------------------------------------------
 *     0.2	|	h	|	r	|   50   |  200  |	b0
 * ---------------------------------------------------
 *     0.21|	h	|	r	|   48   |  190  |	b0
 * ---------------------------------------------------
 *     0.22|	h	|	r	|   45   |  182  |	b0
 * ---------------------------------------------------
 *     0.23|	h	|	r	|   43   |  174  |	b0
 * ---------------------------------------------------
 *     0.24|	h	|	r	|   42   |  167  |	b0
 * ---------------------------------------------------
 *     0.25|	h	|	r	|   40   |  160  |	b0
 * ---------------------------------------------------
 *     0.26|	h	|	r	|   38   |  154  |	b0
 * ---------------------------------------------------
 *     0.27|	h	|	r	|   37   |  148 |	b0
 * ---------------------------------------------------
 *     0.28|	h	|	r	|   36   |  144  |	b0
 * ---------------------------------------------------
 *     0.29|	h	|	r	|   34   |  138  |	b0
 * ---------------------------------------------------
 *     0.3	|	h	|	r	|   33   |  133  |	b0
 * ---------------------------------------------------
 *     0.4	|	h	|	r	|   25   |  100  |	b0
 * ---------------------------------------------------
 *     0.5	|	h	|	r	|   20   |   80  |	b0
 * ---------------------------------------------------
 * ---------------------------------------------------
 */
#ifdef LIBROV_ENABLE_LADRC
// LADRC初始参考值
static LADRC_UNIT_t LADRC_UNIT =
{
    //h     r    wc   w0   b0
    {0.005, 20,  100, 400, 0.5},
    {0.001, 20,  33,  133, 8},
    {0.005, 100, 20,  80,  0.5},
    {0.005, 100, 14,  57,  0.5},
    {0.005, 100, 50,  10,  1}
};

/**
 * @brief 设置LADRC参数矩阵
 * @param  unit             LADRC参数矩阵
 */
void setLADRC_param(const LADRC_UNIT_t unit)
{
    for (uint8_t i = 0;i < 5;i++)
    {
        for (uint8_t j = 0;j < 5;j++)
        {
            LADRC_UNIT[i][j] = unit[i][j];
        }
    }
}

/**
 * @brief LADRC初始化
 * @param  ladrc      LADRC对象
 */
void initLADRC(Modern_Ladrc_t ladrc)
{
    ladrc->h = LADRC_UNIT[1][0]; //定时时间及时间步长
    ladrc->r = LADRC_UNIT[1][1]; //跟踪速度参数
    ladrc->wc = LADRC_UNIT[1][2]; //观测器带宽
    ladrc->w0 = LADRC_UNIT[1][3]; //状态误差反馈率带宽
    ladrc->b0 = LADRC_UNIT[1][4]; //系统参数
    ladrc->z1 = 0; //观测器输出1
    ladrc->z2 = 0; //观测器输出2
    ladrc->z3 = 0; //观测器输出3
}

/**
 * @brief LADRC跟踪微分部分
 * @param  ladrc            LADRC对象
 * @param  exp              期望值
 * @note 输入期望值跟踪微分
 */
static void update_LADRC_TD(Modern_Ladrc_t ladrc, const fp32_t *exp)
{
    fp32_t fh = ((-1 * (ladrc->r)) * (ladrc->r) * ((ladrc->v1) - (*exp))) - (2 * (ladrc->r) * (ladrc->v2));
    ladrc->v1 += ladrc->v2 * ladrc->h;
    ladrc->v2 += fh * ladrc->h;
}

/**
 * @brief LADRC线性状态观测器
 * @param  ladrc            LADRC对象
 * @param  fb               反馈值
 */
static void update_LADRC_ESO(Modern_Ladrc_t ladrc, fp32_t *fb)
{
    fp32_t beta_01 = 3 * ladrc->w0;
    fp32_t beta_02 = 3 * ladrc->w0 * ladrc->w0;
    fp32_t beta_03 = ladrc->w0 * ladrc->w0 * ladrc->w0;
    fp32_t e = ladrc->z1 - (*fb);

    ladrc->z1 += (ladrc->z2 - beta_01 * e) * ladrc->h;
    ladrc->z2 += (ladrc->z3 - beta_02 * e + ladrc->b0 * ladrc->u) * ladrc->h;
    ladrc->z3 += (-1 * beta_03) * e * ladrc->h;
}

/**
 * @brief LADRC线性控制率
 * @param  ladrc            LADRC对象
 * @note 可选Kd = 3wc作为补偿量
 */
static void update_LADRC_LF(Modern_Ladrc_t ladrc)
{
    fp32_t Kp = ladrc->wc * ladrc->wc;
    fp32_t Kd = 2 * ladrc->wc; //kd = 2wc
    fp32_t e1 = ladrc->v1 - ladrc->z1;
    fp32_t e2 = ladrc->v2 - ladrc->z2;
    fp32_t u0 = Kp * e1 + Kd * e2;
    ladrc->u = (u0 - ladrc->z3) / (ladrc->b0);
    if (ladrc->u > 2000) //Output restriction
    {
        ladrc->u = 2000;
    }
    else if (ladrc->u < -2000)
    {
        ladrc->u = -2000;
    }
}

/**
 * @brief LADRC控制函数
 * @param  ladrc            LADRC对象
 * @param  exp              期望值
 * @param  feedback         反馈值
 * @note 将其置于任务循环中即可
 */
void updateLADRC(Modern_Ladrc_t ladrc, const fp32_t *exp, const fp32_t *feedback)
{
    update_LADRC_TD(ladrc, exp);
    update_LADRC_ESO(ladrc, feedback);
    update_LADRC_LF(ladrc);
}

/**
 * @brief 获取LADRC输出
 * @param  ladrc            LADRC对象
 * @return fp32_t 输出值
 */
fp32_t getLADRC_output(Modern_Ladrc_t ladrc)
{
    return ladrc->u;
}
#endif
