#pragma once
#include "Defines.h"

#ifdef USE_LAGENCY
#include "motion.h"

#define COMMAND_FRAME_HEAD 0x25
#define COMMAND_FRAME_END 0x21
#define REPORT_FRAME_HEAD 0x25
#define REPORT_FRAME_END 0xFF
#define ORBIT_PID_FRAME_HEAD 0x23
#define HOVER_PID_FRAME_HEAD 0x27
#define PID_FRAME_END 0x26

struct ThrusterGroupA
{
    uint16_t A1;
    uint16_t A2;
    uint16_t A3;
};
typedef struct ThrusterGroupA ThrusterGroupA_t;

struct LightGroupA
{
    uint16_t L1;
    uint16_t L2;
    uint16_t L3;
};
typedef struct LightGroupA LightGroupA_t;

struct LightGroupB
{
    uint16_t L4;
    uint16_t L5;
    uint16_t L6;
};
typedef struct LightGroupB LightGroupB_t;

struct PanGroup
{
    uint16_t TH1;
    uint16_t TH2;
    uint16_t TH3;
};
typedef struct PanGroup PanGroup_t;

struct ServoGroupA
{
    uint16_t pwm1;
    uint16_t pwm2;
    uint16_t pwm3;
};
typedef struct ServoGroupA ServoGroupA_t;

struct ServoGroupB
{
    uint16_t pwm4;
    uint16_t pwm5;
    uint16_t pwm6;
};
typedef struct ServoGroupB ServoGroupB_t;

struct ServoGroupC
{
    uint16_t pwm7;
    uint16_t pwm8;
    uint16_t pwm9;
};
typedef struct ServoGroupC ServoGroupC_t;

struct PeripheralEnable
{
    uint8_t Laser;
    uint8_t Manipulate;
    uint8_t MachanicalArm;
    uint8_t Sonar;
    uint8_t Thruster;
    uint8_t CameraPan;
};
typedef struct PeripheralEnable PeripheralEnable_t;

struct ModeSwitch
{
    uint8_t SidePushMode;
    uint8_t PitchMode;
    uint8_t RollMode;
    uint8_t AuxMode;
    uint8_t SecureMode;
    uint8_t ModuleMode;
};
typedef struct ModeSwitch ModeSwitch_t;

struct AutoModeSwitch
{
    uint8_t OrbitMode;
    uint8_t HoverMode;
    uint8_t SelfStableMode;
    uint8_t AutoPlanMode;
    uint8_t AutoExeMode;
    uint8_t ObstacleAvoidMode;
};
typedef struct AutoModeSwitch AutoModeSwitch_t;

struct LagencyCabinData
{
    uint16_t CarbinTemperature;
    uint16_t CarbinHumidity;
    uint32_t CarbinBarometric;
    uint16_t CarbinIllumination;
};
typedef struct LagencyCabinData LagencyCabinData_t;

struct LagencyBatteryData
{
    uint16_t Voltage;
};
typedef struct LagencyBatteryData LagencyBatteryData_t;

struct LagencyIMUData
{
    uint16_t Acceleration[3]; //accx accy accz
    uint16_t AngularSpeed[3]; //gyrx gyry gyrz
};
typedef struct LagencyIMUData LagencyIMUData_t;

struct LagencyAHRSData
{
    LagencyIMUData_t IMU;
    uint16_t EulerAngle[3]; //pitch roll yaw
    uint16_t Quaternion[4]; //w x y z
    uint16_t MagneticValue[3]; //mx my mz
};
typedef struct LagencyAHRSData LagencyAHRSData_t;

struct LagencySonarData
{
    uint32_t SonarHeight;
    uint32_t SonarDistance;
    uint16_t Confidence;
};
typedef struct LagencySonarData LagencySonarData_t;

struct LagencyWaterBodyData
{
    uint16_t WaterSalinity;
    uint16_t WaterTemperature;
    uint16_t WaterPressure;
    uint16_t WaterDepth;
};
typedef struct LagencyWaterBodyData LagencyWaterBodyData_t;

struct LagencyCtrlFrame
{
    uint8_t FrameHead; //帧头起始位 0x25
    struct MachineAttitude Attitude; //机器人姿态
    LightGroupA_t Light; //灯光
    PanGroup_t Pan; //云台
    ServoGroupA_t MachineArmA; //机械臂组A
    ServoGroupB_t MachineArmB; //机械臂组B
    ServoGroupC_t Conveyor; //传送带
    enum ThrusterMode_e Mode; //模式
    AutoModeSwitch_t Auto; //智能模式
    uint8_t Validation; //验证位
    uint8_t FrameEnd; //帧尾结束位 0x21
};
typedef struct LagencyCtrlFrame LagencyCtrlFrame_t;

struct LagencyReportFrame
{
    uint8_t FrameHead; //帧头起始位 0x25
    uint8_t CabinState; //舱内状态
    LagencyCabinData_t CabinData; //舱内传感器
    LagencyBatteryData_t BatteryData; //电池状态
    LagencyAHRSData_t AHRSData; //AHRS数据
    LagencySonarData_t SonarData; //声呐数据
    LagencyWaterBodyData_t WaterBodyData; //水体数据
    uint8_t Validation; //验证位
    uint8_t FrameEnd; //帧尾结束位 0xFF
    uint8_t FrameEnd_repeat; //帧尾结束位重复 0xFF
};
typedef struct LagencyReportFrame LagencyReportFrame_t;

typedef uint8_t LagencyDataFrame_t[LAGENCY_REPORT_LENGTH]; //旧版数据帧
typedef uint8_t LagencyCommandFrame_t[LAGENCY_COMMAND_LENGTH]; //旧版控制帧

struct LagencyAlgorithmFrame
{
    uint8_t FrameHead; //帧头起始位
    fp32_t Kp;
    fp32_t Ki;
    fp32_t Kd;
    uint8_t Validation; //验证位
    uint8_t FrameEnd; //帧尾结束位重复 0x26
};
typedef struct LagencyAlgorithmFrame LagencyAlgorithmFrame_t;

struct PwmVal
{
    struct MotorManager Thrusters; //姿态推进器
    vuint32_t LightServo; //灯光
    vuint32_t PanServo; //云台
    vuint32_t ClampServo; //夹爪
    vuint32_t ArmServo; //机械臂
};
typedef struct PwmVal PwmVal_t;

void Lagency_Command_Decode(LagencyCtrlFrame_t* data, LagencyAlgorithmFrame_t* pid_orbit, LagencyAlgorithmFrame_t* pid_hover, uint8_t* DataFrame, uint8_t DataFrame_size);
void Lagency_Report_Encode(uint8_t* DataFrame, LagencyReportFrame_t* data);
#endif /* USE_LAGENCY */
