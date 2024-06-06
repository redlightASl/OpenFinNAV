#include "motion.h"


/**
 * @brief 基本的运动控制函数
 * @param  motor     推进器控制数据
 * @param  target 姿态控制参数
 * @param  mode      模式控制参数
 * @note 基于经验公式
 *
 * +---+----------+----------+---+
 * |   |          |          |   |
 * | 0 |   +---+     +---+   | 1 |
 * |   |   |   |     |   |   |   |
 * +---+   | 1 |     | 2 |   +---+
 *     |   |   |     |   |   |
 *     |   +---+     +---+   |
 *     |                     |
 *     |                     |
 *     |   +---+     +---+   |
 *     |   |   |     |   |   |
 * +---+   | 0 |     | 3 |   +---+
 * |   |   |   |     |   |   |   |
 * | 3 |   +---+     +---+   | 2 |
 * |   |                     |   |
 * +---+---------------------+---+
 *
 */
void Motion_control(struct MachineAttitude target, enum ThrusterMode_e mode, MotorManager_t motor)
{
    uint8_t AFlag = 0;
    uint8_t BFlag = 0;
    uint8_t CFlag = 0;
    uint8_t DFlag = 0;
    uint8_t SFlag = 0;

    /* 水平推进器 */
#if defined(AXIS_2_HORIZENTAL) /* 二轴转向 */
    switch (mode)
    {
    case MIX_MODE:
        motor->HorizontalThruster[0] = PWM_MIDDLE_POSITION;
        motor->HorizontalThruster[1] = PWM_MIDDLE_POSITION;
        break;
    case SIDEPUSH_MODE:
    NOOP; //Unavailable
        break;
    case NORMAL_MODE:
        AFlag = (target.RotateNum > target.StraightNum);
        BFlag = ((target.RotateNum + target.StraightNum) > (2 * PWM_MIDDLE_POSITION));
        CFlag = (target.RotateNum > PWM_MIDDLE_POSITION);
        DFlag = (target.StraightNum > PWM_MIDDLE_POSITION);
        SFlag = AFlag * 8 + BFlag * 4 + CFlag * 2 + DFlag;
        switch (SFlag)
        {
        case 0:
        case 15:
            motor->HorizontalThruster[0] = (uint32_t)(target.RotateNum);
            motor->HorizontalThruster[1] = (uint32_t)((PWM_MIDDLE_POSITION - target.RotateNum
                + target.StraightNum));
            break;
        case 7:
        case 8:
            motor->HorizontalThruster[0] = (uint32_t)(target.StraightNum);
            motor->HorizontalThruster[1] = (uint32_t)((PWM_MIDDLE_POSITION - target.RotateNum
                + target.StraightNum));
            break;
        case 5:
        case 10:
            motor->HorizontalThruster[0] = (uint32_t)((target.RotateNum + target.StraightNum
                - PWM_MIDDLE_POSITION));
            motor->HorizontalThruster[1] = (uint32_t)(target.StraightNum);
            break;
        case 1:
        case 14:
            motor->HorizontalThruster[0] = (uint32_t)((target.RotateNum + target.StraightNum
                - PWM_MIDDLE_POSITION));
            motor->HorizontalThruster[1] = (uint32_t)(((2 * PWM_MIDDLE_POSITION) - target.RotateNum));
            break;
        }
        break;
    default:
        break;
    }
#elif defined(AXIS_4_HORIZENTAL) /* 四轴转向 */
    switch (mode)
    {
    case MIX_MODE:
        motor->HorizontalThruster[0] = PWM_MIDDLE_POSITION;
        motor->HorizontalThruster[1] = PWM_MIDDLE_POSITION;
        motor->HorizontalThruster[2] = PWM_MIDDLE_POSITION;
        motor->HorizontalThruster[3] = PWM_MIDDLE_POSITION;
        break;
    case SIDEPUSH_MODE:
        motor->HorizontalThruster[0] = (uint32_t)(target.RotateNum);
        motor->HorizontalThruster[1] = (uint32_t)((2 * PWM_MIDDLE_POSITION) - target.RotateNum);
        motor->HorizontalThruster[2] = (uint32_t)((2 * PWM_MIDDLE_POSITION) - target.RotateNum);
        motor->HorizontalThruster[3] = (uint32_t)(target.RotateNum);
        break;
    case NORMAL_MODE:
        AFlag = (target.RotateNum > target.StraightNum);
        BFlag = ((target.RotateNum + target.StraightNum) > (2 * PWM_MIDDLE_POSITION));
        CFlag = (target.RotateNum > PWM_MIDDLE_POSITION);
        DFlag = (target.StraightNum > PWM_MIDDLE_POSITION);
        SFlag = AFlag * 8 + BFlag * 4 + CFlag * 2 + DFlag;
        switch (SFlag)
        {
        case 0:
        case 15:
            motor->HorizontalThruster[0] = (uint32_t)(target.RotateNum);
            motor->HorizontalThruster[1] = (uint32_t)(target.RotateNum);
            motor->HorizontalThruster[2] = (uint32_t)((PWM_MIDDLE_POSITION - target.RotateNum
                + target.StraightNum));
            motor->HorizontalThruster[3] = (uint32_t)((PWM_MIDDLE_POSITION - target.RotateNum
                + target.StraightNum));
            break;
        case 7:
        case 8:
            motor->HorizontalThruster[0] = (uint32_t)(target.StraightNum);
            motor->HorizontalThruster[1] = (uint32_t)(target.StraightNum);
            motor->HorizontalThruster[2] = (uint32_t)((PWM_MIDDLE_POSITION - target.RotateNum
                + target.StraightNum));
            motor->HorizontalThruster[3] = (uint32_t)((PWM_MIDDLE_POSITION - target.RotateNum
                + target.StraightNum));
            break;
        case 5:
        case 10:
            motor->HorizontalThruster[0] = (uint32_t)((target.RotateNum + target.StraightNum
                - PWM_MIDDLE_POSITION));
            motor->HorizontalThruster[1] = (uint32_t)((target.RotateNum + target.StraightNum
                - PWM_MIDDLE_POSITION));
            motor->HorizontalThruster[2] = (uint32_t)(target.StraightNum);
            motor->HorizontalThruster[3] = (uint32_t)(target.StraightNum);
            break;
        case 1:
        case 14:
            motor->HorizontalThruster[0] = (uint32_t)((target.RotateNum + target.StraightNum
                - PWM_MIDDLE_POSITION));
            motor->HorizontalThruster[1] = (uint32_t)((target.RotateNum + target.StraightNum
                - PWM_MIDDLE_POSITION));
            motor->HorizontalThruster[2] = (uint32_t)(((2 * PWM_MIDDLE_POSITION) - target.RotateNum));
            motor->HorizontalThruster[3] = (uint32_t)(((2 * PWM_MIDDLE_POSITION) - target.RotateNum));
            break;
        }
        break;
    default:
        break;
    }
#endif /* AXIS_2_HORIZENTAL, AXIS_4_HORIZENTAL */

    /* 垂直推进器 */
#if defined(AXIS_1_VERTICAL) /* 单轴垂直 */
    switch (mode)
    {
    case MIX_MODE:
        NOOP; //Unavailable
        break;
    case PITCH_MODE:
        NOOP; //Unavailable
        break;
    case ROLL_MODE:
        NOOP; //Unavailable
        break;
    case VERTICAL_MODE:
        motor->VerticalThruster = (uint32_t)(target.VerticalNum);
        break;
    default:
        break;
    }
#elif defined(AXIS_2_VERTICAL) /* 二轴垂直 */
    switch (mode)
    {
    case MIX_MODE:
        NOOP; //Unavailable
        break;
    case PITCH_MODE:
        NOOP; //Unavailable
        break;
    case ROLL_MODE:
        motor->VerticalThruster[0] = (uint32_t)((2 * PWM_MIDDLE_POSITION) - target.VerticalNum);
        motor->VerticalThruster[1] = (uint32_t)(target.VerticalNum);
        break;
    case VERTICAL_MODE:
        motor->VerticalThruster[0] = (uint32_t)(target.VerticalNum);
        motor->VerticalThruster[1] = (uint32_t)(target.VerticalNum);
        break;
    default:
        break;
    }
#elif defined(AXIS_3_VERTICAL) /* 三轴垂直 */
    switch (mode)
    {
    case MIX_MODE:
        NOOP; //Unavailable
        break;
    case PITCH_MODE:
        NOOP; //Unavailable
        break;
    case ROLL_MODE:
        motor->VerticalThruster[0] = (uint32_t)((2 * PWM_MIDDLE_POSITION) - target.VerticalNum);
        motor->VerticalThruster[1] = (uint32_t)(target.VerticalNum);
        motor->VerticalThruster[2] = (uint32_t)(PWM_MIDDLE_POSITION);
        break;
    case VERTICAL_MODE:
        motor->VerticalThruster[0] = (uint32_t)(target.VerticalNum);
        motor->VerticalThruster[1] = (uint32_t)(target.VerticalNum);
        motor->VerticalThruster[2] = (uint32_t)(target.VerticalNum);
        break;
    default:
        break;
    }
#elif defined(AXIS_4_VERTICAL) /* 四轴垂直 */
    switch (mode)
    {
    case MIX_MODE:
        AFlag = (target.RotateNum > target.StraightNum);
        BFlag = ((target.RotateNum + target.StraightNum) > (2 * PWM_MIDDLE_POSITION));
        CFlag = (target.RotateNum > PWM_MIDDLE_POSITION);
        DFlag = (target.StraightNum > PWM_MIDDLE_POSITION);
        SFlag = AFlag * 8 + BFlag * 4 + CFlag * 2 + DFlag;
        switch (SFlag)
        {
        case 0:
        case 15:
            motor->VerticalThruster[0] = (uint32_t)(target.RotateNum);
            motor->VerticalThruster[1] = (uint32_t)(target.RotateNum);
            motor->VerticalThruster[2] = (uint32_t)(PWM_MIDDLE_POSITION - target.RotateNum + target.StraightNum);
            motor->VerticalThruster[3] = (uint32_t)(PWM_MIDDLE_POSITION - target.RotateNum + target.StraightNum);
            break;
        case 7:
        case 8:
            motor->VerticalThruster[0] = (uint32_t)(target.StraightNum);
            motor->VerticalThruster[1] = (uint32_t)(target.StraightNum);
            motor->VerticalThruster[2] = (uint32_t)(PWM_MIDDLE_POSITION - target.RotateNum + target.StraightNum);
            motor->VerticalThruster[3] = (uint32_t)(PWM_MIDDLE_POSITION - target.RotateNum + target.StraightNum);
            break;
        case 5:
        case 10:
            motor->VerticalThruster[0] = (uint32_t)(target.RotateNum + target.StraightNum - PWM_MIDDLE_POSITION);
            motor->VerticalThruster[1] = (uint32_t)(target.RotateNum + target.StraightNum - PWM_MIDDLE_POSITION);
            motor->VerticalThruster[2] = (uint32_t)(target.StraightNum);
            motor->VerticalThruster[3] = (uint32_t)(target.StraightNum);
            break;
        case 1:
        case 14:
            motor->VerticalThruster[0] = (uint32_t)(target.RotateNum + target.StraightNum - PWM_MIDDLE_POSITION);
            motor->VerticalThruster[1] = (uint32_t)(target.RotateNum + target.StraightNum - PWM_MIDDLE_POSITION);
            motor->VerticalThruster[2] = (uint32_t)((2 * PWM_MIDDLE_POSITION) - target.RotateNum);
            motor->VerticalThruster[3] = (uint32_t)((2 * PWM_MIDDLE_POSITION) - target.RotateNum);
            break;
        }
        break;
    case PITCH_MODE:
        motor->VerticalThruster[0] = (uint32_t)(target.VerticalNum);
        // motor->VerticalThruster[1] = (uint32_t)((2 * PWM_MIDDLE_POSITION) - target.VerticalNum);
        motor->VerticalThruster[1] = (uint32_t)(target.VerticalNum); //!
        // motor->VerticalThruster[2] = (uint32_t)(target.VerticalNum);
        motor->VerticalThruster[2] = (uint32_t)((2 * PWM_MIDDLE_POSITION) - target.VerticalNum); //!
        motor->VerticalThruster[3] = (uint32_t)((2 * PWM_MIDDLE_POSITION) - target.VerticalNum);
        break;
    case ROLL_MODE:
        // motor->VerticalThruster[0] = (uint32_t)(target.VerticalNum);
        // motor->VerticalThruster[1] = (uint32_t)(target.VerticalNum);
        // motor->VerticalThruster[2] = (uint32_t)((2 * PWM_MIDDLE_POSITION) - target.VerticalNum);
        // motor->VerticalThruster[3] = (uint32_t)((2 * PWM_MIDDLE_POSITION) - target.VerticalNum);
        // motor->VerticalThruster[0] = (uint32_t)(target.RollNum);
        motor->VerticalThruster[0] = (uint32_t)((2 * PWM_MIDDLE_POSITION) - target.RollNum); //!
        motor->VerticalThruster[1] = (uint32_t)(target.RollNum);
        // motor->VerticalThruster[2] = (uint32_t)((2 * PWM_MIDDLE_POSITION) - target.RollNum);
        motor->VerticalThruster[2] = (uint32_t)(target.RollNum); //!
        motor->VerticalThruster[3] = (uint32_t)((2 * PWM_MIDDLE_POSITION) - target.RollNum);
        break;
    case VERTICAL_MODE:
        motor->VerticalThruster[0] = (uint32_t)(target.VerticalNum);
        motor->VerticalThruster[1] = (uint32_t)(target.VerticalNum);
        motor->VerticalThruster[2] = (uint32_t)(target.VerticalNum);
        motor->VerticalThruster[3] = (uint32_t)(target.VerticalNum);
        break;
    default:
        break;
    }
#endif /* AXIS_1_VERTICAL, AXIS_2_VERTICAL, AXIS_3_VERTICAL, AXIS_4_VERTICAL */
}