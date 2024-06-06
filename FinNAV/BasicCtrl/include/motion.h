#pragma once
#include "Defines.h"


enum ThrusterMode_e
{
    NORMAL_MODE = 0, //旋转转向
    SIDEPUSH_MODE = 1, //侧推平移
    PITCH_MODE = 2, //俯仰艏摇
    ROLL_MODE = 3, //横滚横摇
    VERTICAL_MODE = 4, //垂直运动
    MIX_MODE = 5, //全向运动
}; /* 推进器模式 */

/* Basic Controller */
struct MachineAttitude
{
    uint16_t StraightNum;
    uint16_t RotateNum;
    uint16_t VerticalNum;
    uint16_t RollNum;
};
typedef struct MachineAttitude *MachineAttitude_t;

struct MachineMovement
{
    uint16_t StraightDist;
    uint16_t ShiftDist;
    uint16_t VerticalDist;
};
typedef struct MachineMovement *MachineMovement_t;

struct MachineAngle
{
    uint16_t PitchAngle;
    uint16_t RollAngle;
    uint16_t YawAngle;
};
typedef struct MachineAngle *MachineAngle_t;


/* Hardware Map */
struct MotorManager
{
    //水平方向推进器
#if defined(AXIS_2_HORIZENTAL)
    uint32_t HorizontalThruster[2];
#elif defined(AXIS_4_HORIZENTAL)
    uint32_t HorizontalThruster[4];
#endif

#if defined(AXIS_1_VERTICAL)
    uint32_t VerticalThruster; //垂直方向推进器
#elif defined(AXIS_2_VERTICAL)
    uint32_t VerticalThruster[2]; //垂直方向推进器
#elif defined(AXIS_3_VERTICAL)
    uint32_t VerticalThruster[3]; //垂直方向推进器
#elif defined(AXIS_4_VERTICAL)
    uint32_t VerticalThruster[4]; //垂直方向推进器
#endif
};
typedef struct MotorManager *MotorManager_t;

void Motion_control(struct MachineAttitude target, enum ThrusterMode_e mode_switch, MotorManager_t motor);

void Motion_distance_loop(struct MachineMovement target, MotorManager_t motor);
void Motion_angle_loop(struct MachineAngle target, MotorManager_t motor);
