#include "LagencyLink.h"

#ifdef USE_LAGENCY
#include "Algorithm.h"


void Lagency_Command_Decode(LagencyCtrlFrame_t* data, LagencyAlgorithmFrame_t* pid_orbit, LagencyAlgorithmFrame_t* pid_hover, uint8_t* DataFrame, uint8_t DataFrame_size)
{
    if (DataFrame_size == LAGENCY_COMMAND_LENGTH)
    {
        if ((DataFrame[0] == COMMAND_FRAME_HEAD) && (DataFrame[LAGENCY_COMMAND_LENGTH - 1] == COMMAND_FRAME_END)) //head & tail
        {
            //NOTE: 下面这部分代码是针对OurEDA-S2S设计的协议
            // data->FrameHead = DataFrame[0];
            // data->Attitude.StraightNum = (DataFrame[1] << 8) | DataFrame[2];
            // data->Attitude.RotateNum = (DataFrame[3] << 8) | DataFrame[4];
            // data->Attitude.VerticalNum = (DataFrame[5] << 8) | DataFrame[6];
            // data->Light.L1 = (DataFrame[7] << 8) | DataFrame[8];
            // data->Pan.TH1 = (DataFrame[9] << 8) | DataFrame[10];
            // data->MachineArmA.pwm1 = (DataFrame[11] << 8) | DataFrame[12];
            // data->Mode.PitchMode = DataFrame[13];
            // data->Mode.RollMode = DataFrame[13];
            // data->Mode.SidePushMode = DataFrame[13];
            // data->Validation = DataFrame[14];
            // data->FrameEnd = DataFrame[15];
            //NOTE: 下面这部分代码是兼容OurEDA-S2L的协议
            data->FrameHead = DataFrame[0];
            data->Attitude.StraightNum = (DataFrame[2] << 8) | DataFrame[1];
            data->Attitude.RotateNum = (DataFrame[4] << 8) | DataFrame[3];
            data->Attitude.VerticalNum = (DataFrame[6] << 8) | DataFrame[5];
            data->Attitude.RollNum = (DataFrame[8] << 8) | DataFrame[7];
            data->Light.L1 = (DataFrame[10] << 8) | DataFrame[9];
            data->Pan.TH1 = (DataFrame[12] << 8) | DataFrame[11];
            data->MachineArmA.pwm1 = (DataFrame[14] << 8) | DataFrame[13];
            data->MachineArmA.pwm2 = (DataFrame[16] << 8) | DataFrame[15];
            data->Mode.SidePushMode = DataFrame[17];
            data->Auto.OrbitMode = DataFrame[18];
            data->Auto.HoverMode = DataFrame[19];
            data->Mode.SecureMode = DataFrame[20]; //推进模式复用为救援模式
            data->Mode.PitchMode = (DataFrame[21] == 0x01) ? 1 : 0;
            data->Mode.RollMode = (DataFrame[21] == 0x02) ? 1 : 0;
            data->Mode.AuxMode = (DataFrame[21] == 0x03) ? 1 : 0;
            data->FrameEnd = DataFrame[22];
            //NOTE: 下面这部分代码是大端序
            // data->FrameHead = DataFrame[0];
            // data->Attitude.StraightNum = (DataFrame[1] << 8) | DataFrame[2];
            // data->Attitude.RotateNum = (DataFrame[3] << 8) | DataFrame[4];
            // data->Attitude.VerticalNum = (DataFrame[5] << 8) | DataFrame[6];
            // data->Attitude.RollNum = (DataFrame[7] << 8) | DataFrame[8];
            // data->Light.L1 = (DataFrame[9] << 8) | DataFrame[10];
            // data->Pan.TH1 = (DataFrame[11] << 8) | DataFrame[12];
            // data->MachineArmA.pwm1 = (DataFrame[13] << 8) | DataFrame[14];
            // data->MachineArmA.pwm2 = (DataFrame[15] << 8) | DataFrame[16];
            // data->Mode.SidePushMode = DataFrame[17];
            // data->Auto.OrbitMode = DataFrame[18];
            // data->Auto.HoverMode = DataFrame[19];
            // //?data = DataFrame[20];推进模式无用
            // data->Mode.PitchMode = (DataFrame[21] == 0x01) ? 1 : 0;
            // data->Mode.RollMode = (DataFrame[21] == 0x02) ? 1 : 0;
            // data->Mode.AuxMode = (DataFrame[21] == 0x03) ? 1 : 0;
            // data->FrameEnd = DataFrame[22];
        }
        // else if ((DataFrame[0] == ORBIT_PID_FRAME_HEAD) && (DataFrame[15] == PID_FRAME_END)) //orbit PID config mode
        // {
        //     pid_orbit->Kp = (fp32_t)(((fp32_t)(((int32_t)DataFrame[1] << 24)
        //         | ((int32_t)DataFrame[2] << 16) | ((int32_t)DataFrame[3] << 8)
        //         | ((int32_t)DataFrame[4]))) / 1000);
        //     pid_orbit->Ki = (fp32_t)(((fp32_t)(((int32_t)DataFrame[5] << 24)
        //         | ((int32_t)DataFrame[6] << 16) | ((int32_t)DataFrame[7] << 8)
        //         | ((int32_t)DataFrame[8]))) / 1000);
        //     pid_orbit->Kd = (fp32_t)(((fp32_t)(((int32_t)DataFrame[9] << 24)
        //         | ((int32_t)DataFrame[10] << 16) | ((int32_t)DataFrame[11] << 8)
        //         | ((int32_t)DataFrame[12]))) / 1000);
        //     pid_orbit->FrameEnd = DataFrame[15];
        // }
        // else if ((DataFrame[0] == HOVER_PID_FRAME_HEAD) && (DataFrame[15] == PID_FRAME_END)) //hover PID config mode
        // {
        //     pid_hover->Kp = (fp32_t)(((fp32_t)(((int32_t)DataFrame[1] << 24)
        //         | ((int32_t)DataFrame[2] << 16) | ((int32_t)DataFrame[3] << 8)
        //         | ((int32_t)DataFrame[4]))) / 1000);
        //     pid_hover->Ki = (fp32_t)(((fp32_t)(((int32_t)DataFrame[5] << 24)
        //         | ((int32_t)DataFrame[6] << 16) | ((int32_t)DataFrame[7] << 8)
        //         | ((int32_t)DataFrame[8]))) / 1000);
        //     pid_hover->Kd = (fp32_t)(((fp32_t)(((int32_t)DataFrame[9] << 24)
        //         | ((int32_t)DataFrame[10] << 16) | ((int32_t)DataFrame[11] << 8)
        //         | ((int32_t)DataFrame[12]))) / 1000);
        //     pid_hover->FrameEnd = DataFrame[15];
        // }
    }
}

void Lagency_Report_Encode(uint8_t* DataFrame, LagencyReportFrame_t* data)
{
    //NOTE: 下面这部分代码是针对OurEDA-S2S设计的协议
    // DataFrame[0] = data->FrameHead;
    // DataFrame[1] = data->CabinState;
    // DataFrame[2] = SPLIT_UINT16_8H(data->CabinData.CarbinTemperature);
    // DataFrame[3] = SPLIT_UINT16_8L(data->CabinData.CarbinTemperature);
    // DataFrame[4] = SPLIT_UINT32_8HH(data->CabinData.CarbinBarometric);
    // DataFrame[5] = SPLIT_UINT32_8HL(data->CabinData.CarbinBarometric);
    // DataFrame[6] = SPLIT_UINT32_8LH(data->CabinData.CarbinBarometric);
    // DataFrame[7] = SPLIT_UINT32_8LL(data->CabinData.CarbinBarometric);
    // DataFrame[8] = SPLIT_UINT16_8H(data->CabinData.CarbinHumidity);
    // DataFrame[9] = SPLIT_UINT16_8L(data->CabinData.CarbinHumidity);
    // DataFrame[10] = SPLIT_UINT16_8H(data->AHRSData.IMU.Acceleration[0]);
    // DataFrame[11] = SPLIT_UINT16_8L(data->AHRSData.IMU.Acceleration[0]);
    // DataFrame[12] = SPLIT_UINT16_8H(data->AHRSData.IMU.Acceleration[1]);
    // DataFrame[13] = SPLIT_UINT16_8L(data->AHRSData.IMU.Acceleration[1]);
    // DataFrame[14] = SPLIT_UINT16_8H(data->AHRSData.IMU.Acceleration[2]);
    // DataFrame[15] = SPLIT_UINT16_8L(data->AHRSData.IMU.Acceleration[2]);
    // DataFrame[16] = SPLIT_UINT16_8H(data->AHRSData.IMU.AngularSpeed[0]);
    // DataFrame[17] = SPLIT_UINT16_8L(data->AHRSData.IMU.AngularSpeed[0]);
    // DataFrame[18] = SPLIT_UINT16_8H(data->AHRSData.IMU.AngularSpeed[1]);
    // DataFrame[19] = SPLIT_UINT16_8L(data->AHRSData.IMU.AngularSpeed[1]);
    // DataFrame[20] = SPLIT_UINT16_8H(data->AHRSData.IMU.AngularSpeed[2]);
    // DataFrame[21] = SPLIT_UINT16_8L(data->AHRSData.IMU.AngularSpeed[2]);
    // DataFrame[22] = SPLIT_UINT16_8H(data->AHRSData.EulerAngle[0]);
    // DataFrame[23] = SPLIT_UINT16_8L(data->AHRSData.EulerAngle[0]);
    // DataFrame[24] = SPLIT_UINT16_8H(data->AHRSData.EulerAngle[1]);
    // DataFrame[25] = SPLIT_UINT16_8L(data->AHRSData.EulerAngle[1]);
    // DataFrame[26] = SPLIT_UINT16_8H(data->AHRSData.EulerAngle[2]);
    // DataFrame[27] = SPLIT_UINT16_8L(data->AHRSData.EulerAngle[2]);
    // DataFrame[28] = SPLIT_UINT16_8H(data->AHRSData.MagneticValue[0]);
    // DataFrame[29] = SPLIT_UINT16_8L(data->AHRSData.MagneticValue[0]);
    // DataFrame[30] = SPLIT_UINT16_8H(data->AHRSData.MagneticValue[1]);
    // DataFrame[31] = SPLIT_UINT16_8L(data->AHRSData.MagneticValue[1]);
    // DataFrame[32] = SPLIT_UINT16_8H(data->AHRSData.MagneticValue[2]);
    // DataFrame[33] = SPLIT_UINT16_8L(data->AHRSData.MagneticValue[2]);
    // DataFrame[34] = SPLIT_UINT32_8HH(data->SonarData.SonarHeight);
    // DataFrame[35] = SPLIT_UINT32_8HL(data->SonarData.SonarHeight);
    // DataFrame[36] = SPLIT_UINT32_8LH(data->SonarData.SonarHeight);
    // DataFrame[37] = SPLIT_UINT32_8LL(data->SonarData.SonarHeight);
    // DataFrame[38] = SPLIT_UINT32_8LL(data->SonarData.Confidence);
    // DataFrame[39] = SPLIT_UINT32_8LL(data->SonarData.Confidence);
    // DataFrame[40] = SPLIT_UINT16_8H(data->WaterBodyData.WaterTemperature);
    // DataFrame[41] = SPLIT_UINT16_8L(data->WaterBodyData.WaterTemperature);
    // DataFrame[42] = SPLIT_UINT16_8H(data->WaterBodyData.WaterDepth);
    // DataFrame[43] = SPLIT_UINT16_8L(data->WaterBodyData.WaterDepth);
    // DataFrame[44] = data->Validation;
    // DataFrame[45] = data->FrameEnd;
    // DataFrame[46] = data->FrameEnd_repeat;
    //NOTE: 下面这部分代码是兼容OurEDA-S2L的协议
    DataFrame[0] = data->FrameHead;
    DataFrame[1] = data->CabinState; //?状态位
    DataFrame[2] = data->BatteryData.Voltage;
    DataFrame[3] = data->CabinState; //?仓位漏水指示
    DataFrame[4] = SPLIT_UINT16_8L(data->AHRSData.IMU.Acceleration[0]);
    DataFrame[5] = SPLIT_UINT16_8H(data->AHRSData.IMU.Acceleration[0]);
    DataFrame[6] = SPLIT_UINT16_8L(data->AHRSData.IMU.Acceleration[1]);
    DataFrame[7] = SPLIT_UINT16_8H(data->AHRSData.IMU.Acceleration[1]);
    DataFrame[8] = SPLIT_UINT16_8L(data->AHRSData.IMU.Acceleration[2]);
    DataFrame[9] = SPLIT_UINT16_8H(data->AHRSData.IMU.Acceleration[2]);
    DataFrame[10] = SPLIT_UINT16_8L(data->AHRSData.IMU.AngularSpeed[0]);
    DataFrame[11] = SPLIT_UINT16_8H(data->AHRSData.IMU.AngularSpeed[0]);
    DataFrame[12] = SPLIT_UINT16_8L(data->AHRSData.IMU.AngularSpeed[1]);
    DataFrame[13] = SPLIT_UINT16_8H(data->AHRSData.IMU.AngularSpeed[1]);
    DataFrame[14] = SPLIT_UINT16_8L(data->AHRSData.IMU.AngularSpeed[2]);
    DataFrame[15] = SPLIT_UINT16_8H(data->AHRSData.IMU.AngularSpeed[2]);
    DataFrame[16] = SPLIT_UINT16_8L(data->AHRSData.EulerAngle[0]);
    DataFrame[17] = SPLIT_UINT16_8H(data->AHRSData.EulerAngle[0]);
    DataFrame[18] = SPLIT_UINT16_8L(data->AHRSData.EulerAngle[1]);
    DataFrame[19] = SPLIT_UINT16_8H(data->AHRSData.EulerAngle[1]);
    DataFrame[20] = SPLIT_UINT16_8L(data->AHRSData.EulerAngle[2]);
    DataFrame[21] = SPLIT_UINT16_8H(data->AHRSData.EulerAngle[2]);
    DataFrame[22] = SPLIT_UINT16_8L(data->AHRSData.MagneticValue[0]);
    DataFrame[23] = SPLIT_UINT16_8H(data->AHRSData.MagneticValue[0]);
    DataFrame[24] = SPLIT_UINT16_8L(data->AHRSData.MagneticValue[1]);
    DataFrame[25] = SPLIT_UINT16_8H(data->AHRSData.MagneticValue[1]);
    DataFrame[26] = SPLIT_UINT16_8L(data->AHRSData.MagneticValue[2]);
    DataFrame[27] = SPLIT_UINT16_8H(data->AHRSData.MagneticValue[2]);
    DataFrame[28] = SPLIT_UINT16_8L(data->CabinData.CarbinTemperature);
    DataFrame[29] = SPLIT_UINT16_8H(data->CabinData.CarbinTemperature);
    DataFrame[30] = SPLIT_UINT16_8L(data->WaterBodyData.WaterTemperature);
    DataFrame[31] = SPLIT_UINT16_8H(data->WaterBodyData.WaterTemperature);
    DataFrame[32] = SPLIT_UINT16_8L(data->WaterBodyData.WaterDepth);
    DataFrame[33] = SPLIT_UINT16_8H(data->WaterBodyData.WaterDepth);
    DataFrame[34] = data->Validation;
    DataFrame[35] = data->FrameEnd;
    DataFrame[36] = data->FrameEnd_repeat;
}
#endif
