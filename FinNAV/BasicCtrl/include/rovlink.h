/**
 * @file rovlink.h
 * @brief RovLink通用API
 * @author RedlightASl (dddbbbdd@foxmail.com)
 * @version 1.0
 * @date 2023-05-24
 * 
 * @copyright Copyright (c) 2023 RedlightASl
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date    <th>Version  <th>Author     <th>Description
 * <tr><td>2023-05-24  <td>1.0      <td>RedlightASl   <td>Content
 * </table>
 */
#pragma once
#include "Defines.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifdef LIBROV_USE_ROVLINK
// #define STD_FRAME_LENGTH 10
// #define INN_FRAME_LENGTH 8
// #define PAYLOAD_LENGTH 6

/* Operation Codes */
// Enum: RovDeviceType [1] {6 values}
// enum RovDeviceType {
//   NONE = 0,
//   POWER_CAB = 1,
//   CONTROL_CAB = 2,
//   COMM_CAB = 3,
//   MAIN_CAB = 4,
//   HOST = 5,
// };

// // Enum: RovlinkFrameType [1] {51 values}
// enum RovlinkFrameType {
//   SENSOR_NONE = 0,
//   SENSOR_CAB_TEMP_HUMID_PRESS = 1,
//   SENSOR_WATER_TEMP_DEPTH_PRESS = 2,
//   SENSOR_ACCELERATION = 3,
//   SENSOR_ANGULAR_VELOCITY = 4,
//   SENSOR_EULER_ANGLE = 5,
//   SENSOR_MAGNETIC_FIELD = 6,
//   SENSOR_HEIGHT_SONAR = 7,
//   SENSOR_DISTANCE_SONAR = 8,
//   EXDATA_LEAKAGE = 16,
//   EXDATA_KEEP_ALIVE = 17,
//   CONTROL_PROPELLER_A = 33,
//   CONTROL_PROPELLER_B = 34,
//   CONTROL_PROPELLER_C = 35,
//   CONTROL_PROPELLER_D = 36,
//   CONTROL_LIGHT_A = 37,
//   CONTROL_LIGHT_B = 38,
//   CONTROL_PTZ = 39,
//   CONTROL_SERVO_A = 40,
//   CONTROL_SERVO_B = 41,
//   CONTROL_SERVO_C = 42,
//   CONTROL_POSTURE = 43,
//   HOST_CAMARA = 49,
//   ALGORITHM_PID_KP = 65,
//   ALGORITHM_PID_KI = 66,
//   ALGORITHM_PID_KD = 67,
//   COMPONENT_PROPELLER = 81,
//   COMPONENT_LIGHT = 82,
//   COMPONENT_PTZ = 83,
//   COMPONENT_SERVO_A = 84,
//   COMPONENT_SERVO_B = 85,
//   EXCOMPONENT_RELAY = 97,
//   EXCOMPONENT_RESCUE = 98,
//   MODE_MODE_A = 113,
//   MODE_MODE_B = 114,
//   EXCONTROL_CLAMP = 129,
//   EXCONTROL_ARM_A = 130,
//   EXCONTROL_ARM_B = 131,
//   EXCONTROL_ARM_C = 132,
//   BETTERY_VOLTAGE = 160,
//   BETTERY_CURRENT_GAIN = 161,
//   BETTERY_CURRENT_BIAS = 162,
//   BETTERY_CURRENT = 163,
//   BETTERY_REMAIN = 164,
//   CURRENT_PROPELLER_A = 176,
//   CURRENT_PROPELLER_B = 177,
//   CURRENT_PROPELLER_C = 178,
//   CURRENT_PROPELLER_D = 179,
//   CURRENT_PTZ = 180,
//   CURRENT_SERVO_A = 181,
//   CURRENT_SERVO_B = 182,
// };

// // Struct: RovlinkFrame [8] {6 fields}
// struct RovlinkFrame {
//   // [0, 1) NormalField: RovlinkFrameType opcode[1]
//   enum RovlinkFrameType opcode;
//   // [1, 1#1) NormalField: bool sensor[#1]
//   bool sensor;
//   // [1#1, 1#2) NormalField: bool valid[#1]
//   bool valid;
//   // [1#2, 1#4) VoidField: void [#2]
//   // [1#4, 2) NormalField: RovDeviceType device[#4]
//   enum RovDeviceType device;
//   // [2, 8) NormalField: uint8<6> payload[6]
//   uint8_t payload[6];
// };

// // Struct: RovlinkFullFrame [10] {9 fields}
// struct RovlinkFullFrame {
//   // [0, 1) NormalField: uint8 header[1]
//   uint8_t header;
//   // [virtual] EmbeddedField: RovlinkFrame [8]
//   // [1, 2) NormalField: RovlinkFrameType opcode[1]
//   enum RovlinkFrameType opcode;
//   // [2, 2#1) NormalField: bool sensor[#1]
//   bool sensor;
//   // [2#1, 2#2) NormalField: bool valid[#1]
//   bool valid;
//   // [2#2, 2#4) VoidField: void [#2]
//   // [2#4, 3) NormalField: RovDeviceType device[#4]
//   enum RovDeviceType device;
//   // [3, 9) NormalField: uint8<6> payload[6]
//   uint8_t payload[6];
//   // [9, 10) NormalField: uint8 crc[1]
//   uint8_t crc;
// };

/* !DEPRECATED
//Normal Data
#define OPCODE_NOP 0x00
#define OPCODE_CARBIN_TEMP_HUMI 0x01
#define OPCODE_WATER_TEMP_DEPTH 0x02
#define OPCODE_ACC_VAL 0x03
#define OPCODE_GYR_VAL 0x04
#define OPCODE_EUL_VAL 0x05
#define OPCODE_MAG_VAL 0x06
#define OPCODE_HEIGHT_SONAR 0x07
#define OPCODE_FRONT_SONAR 0x08
#define OPCODE_CIR_SONAR 0x09
#define OPCODE_SCAN_SONAR 0x0A
#define OPCODE_QUATERNION 0x0B
#define OPCODE_WATERBODY 0x0C
//Special Data
#define OPCODE_WATER_WARNING 0x10
#define OPCODE_ROV_ID ROV_ID

#define OPCODE_OTA_START 0x1E
#define OPCODE_OTA_DATAF 0x1F
//Commands
#define OPCODE_THRUSTER_A 0x21
#define OPCODE_THRUSTER_B 0x22
#define OPCODE_THRUSTER_C 0x23
#define OPCODE_THRUSTER_D 0x24
#define OPCODE_LIGHT_A 0x25
#define OPCODE_LIGHT_B 0x26
#define OPCODE_PAN 0x27
#define OPCODE_SERVO_A 0x28
#define OPCODE_SERVO_B 0x29
#define OPCODE_SERVO_C 0x2A
#define OPCODE_ATTITUDE 0x2B
#define OPCODE_MOVEMENT 0x2B
#define OPCODE_ANGLE 0x2B
//Reserved
#define OPCODE_CAMERA 0x31
//Basic Algorithm
#define OPCODE_PID_KP 0x41
#define OPCODE_PID_KI 0x42
#define OPCODE_PID_KD 0x43
//Hardware Status
#define OPCODE_THRUSTER_STATUS 0x51
#define OPCODE_LIGHT_STATUS 0x52
#define OPCODE_PAN_STATUS 0x53
#define OPCODE_SERVO_A_STATUS 0x54
#define OPCODE_SERVO_B_STATUS 0x55
//Special Hardware Peripheral
#define OPCODE_PERIPHERAL_ENABLE 0x61
#define OPCODE_RESCURE_MODULE 0x62
//Mode Switch and Auxiliary
#define OPCODE_MODE_SWITCH_A 0x71
#define OPCODE_MODE_SWITCH_B 0x71
#define OPCODE_MODE_SWITCH_C 0x71
//Peripheral Control Command
#define OPCODE_CONTROL_CLAMP 0x81
#define OPCODE_CONTROL_MACHINE_ARM_1 0x82
#define OPCODE_CONTROL_MACHINE_ARM_2 0x83
#define OPCODE_CONTROL_MACHINE_ARM_3 0x84
//Battery Data
#define OPCODE_BATTERY_VOLTAGE 0xA0
#define OPCODE_BATTERY_CURRENT_GAIN 0xA1
#define OPCODE_BATTERY_CURRENT_DIFF 0xA2
#define OPCODE_BATTERY_CURRENT_OUTP 0xA3
#define OPCODE_BATTERY_CAPCITY 0xA4
//Current Monitor
#define OPCODE_CURRENT_THRUSTER_A 0xB1
#define OPCODE_CURRENT_THRUSTER_B 0xB2
#define OPCODE_CURRENT_THRUSTER_C 0xB3
#define OPCODE_CURRENT_THRUSTER_D 0xB4
#define OPCODE_CURRENT_LIGHT_A 0xB5
#define OPCODE_CURRENT_LIGHT_B 0xB6
#define OPCODE_CURRENT_PAN 0xB7
#define OPCODE_CURRENT_SERVO_A 0xB8
#define OPCODE_CURRENT_SERVO_B 0xB9
#define OPCODE_CURRENT_SERVO_C 0xBA

typedef enum Identify {
    P_ID=0x10 >> 4, //动力舱ID
    S_ID=0x20 >> 4, //控制舱ID
    C_ID=0x30 >> 4, //通讯仓ID
    M_ID=0x40 >> 4, //主控仓ID
    U_ID=0x50 >> 4 //上位机ID
} Identify_enum;

typedef enum DataLengthCode {
    MULTI_DATA=0x00 >> 2, //8 uint8_t
    SINGLE_DATA=0x04 >> 2, //uint32 or uint48_t
    DOUBLE_DATA=0x08 >> 2, //uint32+uint16
    TRIPLE_DATA=0x0C >> 2 //uint16+uint16+uint16
} DLC_enum;

typedef enum Valid {
    FRAME_END_CHECK_ENABLE = 0x02 >> 1, //帧尾校验位使能
    FRAME_END_CHECK_DISABLE = 0x00 >> 1 //帧尾校验位失能
} Valid_enum;

typedef enum Sensor {
    SENSOR_RUNNING = 0x01, //当前传感器正常运行
    SENSOR_DAMAGED = 0x00 //当前传感器损坏
} Sensor_enum;

struct Characode
{
    uint8_t Identify: 4; //设备ID
    uint8_t DLC: 2; //指令特征指示位
    uint8_t Valid: 1; //检验有效位
    uint8_t Sensor: 1; //传感器有效位
};
typedef struct Characode Characode_t;

struct RovData
{
    uint8_t Opcode; //数据类型
    Characode_t Characode; //特征指示
    uint8_t Payload[PAYLOAD_LENGTH]; //数据位
};
typedef struct RovData RovData_t;

struct RovData_Package
{
    uint8_t FrameHead; //帧头0xFD
    RovData_t DataBody; //数据
    uint8_t FrameEnd; //帧尾CRC校验
};
typedef struct RovData_Package RovData_Package_t;

typedef uint8_t StdDataFrame_t[STD_FRAME_LENGTH]; //标准数据帧-串口协议
typedef uint8_t InnDataFrame_t[INN_FRAME_LENGTH]; //标准数据帧-CAN协议
typedef uint8_t Payload_t[PAYLOAD_LENGTH]; //原始数据

struct GeneralData_multiple
{
    uint8_t data_8bit[6];
};
typedef struct GeneralData_multiple GeneralData_multiple_t;

union GeneralData_single
{
    uint32_t data_32bit;
    uint64_t data_48bit;
};
typedef union GeneralData_single GeneralData_single_t; //! union

struct GeneralData_double
{
    uint32_t data_32bit;
    uint16_t data_16bit;
};
typedef struct GeneralData_double GeneralData_double_t;

struct GeneralData_triple
{
    uint16_t data_16bit[3];
};
typedef struct GeneralData_triple GeneralData_triple_t;

union GeneralData
{
    GeneralData_multiple_t multiple_data;
    GeneralData_single_t single_data;
    GeneralData_double_t double_data;
    GeneralData_triple_t triple_data;
};
typedef union GeneralData GeneralData_t; //! union

void FrameData_Encode(RovData_t* data, const uint8_t* payload, const uint8_t opcode, const Characode_t* characode);
void FrameData_Decode(uint8_t* payload, uint8_t* opcode, Characode_t* characode, const RovData_t* data);
void FrameData_Package(RovData_Package_t* package, const RovData_t* data);
uint8_t FrameData_Depackage(RovData_t* data, const RovData_Package_t* package);
void FrameData_StdPackage2Frame(uint8_t* DataFrame, const RovData_Package_t* package);
uint8_t FrameData_Frame2StdPackage(RovData_Package_t* package, const uint8_t* DataFrame, uint8_t DataFrame_size);
void FrameData_InnPackage2Frame(uint8_t* DataFrame, const RovData_t* data);
uint8_t FrameData_Frame2InnPackage(RovData_t* data, const uint8_t* DataFrame, uint8_t DataFrame_size);

void Payload_CommonDecode(ROV_VOID_POINTER raw_data, const Characode_t* characode, const uint8_t* payload);
void Payload_MultipleDecode(GeneralData_multiple_t* raw_data, const uint8_t* payload);
void Payload_SingleDecode(GeneralData_single_t* raw_data, const uint8_t* payload);
void Payload_DoubleDecode(GeneralData_double_t* raw_data, const uint8_t* payload);
void Payload_TripleDecode(GeneralData_triple_t* raw_data, const uint8_t* payload);
void Payload_CommonEncode(uint8_t* payload, const Characode_t* characode, const ROV_VOID_POINTER raw_data);
void Payload_MultipleEncode(uint8_t* payload, const GeneralData_multiple_t* raw_data);
void Payload_SingleEncode(uint8_t* payload, const GeneralData_single_t* raw_data);
void Payload_DoubleEncode(uint8_t* payload, const GeneralData_double_t* raw_data);
void Payload_TripleEncode(uint8_t* payload, const GeneralData_triple_t* raw_data);
*/

#include "gen_rovlink.h"

#endif /* LIBROV_USE_ROVLINK */
#ifdef __cplusplus
}
#endif
