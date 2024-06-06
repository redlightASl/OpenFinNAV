#include "rovlink.h"


#ifdef LIBROV_USE_ROVLINK
#include "Algorithm.h"

// /**
//  * @brief 原始数据包编码为内部总线数据包
//  * @param  data             内部总线数据包输出
//  * @param  payload          原始数据包
//  * @param  opcode           数据类型
//  * @param  characode        舱位指示
//  */
// void FrameData_Encode(RovData_t* data, const uint8_t* payload, const uint8_t opcode, const Characode_t* characode)
// {
//     data->Characode = *characode;
//     data->Opcode = opcode;
//     for (uint8_t i = 0; i < PAYLOAD_LENGTH; i++)
//     {
//         data->Payload[i] = payload[i];
//     }
// }

// /**
//  * @brief 内部总线数据包解码为原始数据包
//  * @param  payload          原始数据包
//  * @param  opcode           数据类型
//  * @param  characode        舱位指示
//  * @param  data             内部总线数据包输入
//  */
// void FrameData_Decode(uint8_t* payload, uint8_t* opcode, Characode_t* characode, const RovData_t* data)
// {
//     *opcode = data->Opcode;
//     *characode = data->Characode;
//     for (uint8_t i = 0; i < 6; i++)
//     {
//         payload[i] = data->Payload[i];
//     }
// }

// /**
//  * @brief 内部总线数据包封装为标准数据包
//  * @param  package          标准数据包
//  * @param  data             内部总线数据包
//  */
// void FrameData_Package(RovData_Package_t* package, const RovData_t* data)
// {
//     package->FrameHead = 0xFD;
//     package->DataBody = *data;
//     package->FrameEnd = 0x00; //DEBUG: 验证位
// }

// /**
//  * @brief 标准数据包解包为内部总线数据包
//  * @param  data             内部总线数据包
//  * @param  package          标准数据包
//  * @return uint8_t 成功解包返回ROV_TRUE, 解包失败返回ROV_FALSE
//  */
// uint8_t FrameData_Depackage(RovData_t* data, const RovData_Package_t* package)
// {
//     if (package->FrameHead == 0xFD)
//     {
//         if (package->DataBody.Characode.Valid & FRAME_END_CHECK_ENABLE) //CRC有效
//         {
//             //DEBUG
//             // if (IdTest(&(package->DataBody), CRC8, 8, package->FrameEnd)) //校验
//             // {
//             *data = package->DataBody;
//             // }
//         }
//         else //CRC无效
//         {
//             *data = package->DataBody;
//         }
//         return ROV_TRUE;
//     }
//     return ROV_FALSE;
// }

// /**
//  * @brief 将标准数据包转换成可发送的总线数据帧
//  * @param  DataFrame        总线数据帧输出
//  * @param  package          标准数据包
//  */
// void FrameData_StdPackage2Frame(uint8_t* DataFrame, const RovData_Package_t* package)
// {
//     DataFrame[0] = package->FrameHead;
//     DataFrame[1] = package->DataBody.Opcode;
//     DataFrame[2] = (package->DataBody.Characode.Identify << 4) | (package->DataBody.Characode.DLC << 2)
//             | (package->DataBody.Characode.Valid << 1) | (package->DataBody.Characode.Sensor);
//     DataFrame[3] = package->DataBody.Payload[0];
//     DataFrame[4] = package->DataBody.Payload[1];
//     DataFrame[5] = package->DataBody.Payload[2];
//     DataFrame[6] = package->DataBody.Payload[3];
//     DataFrame[7] = package->DataBody.Payload[4];
//     DataFrame[8] = package->DataBody.Payload[5];
//     DataFrame[9] = package->FrameEnd;
// }

// /**
//  * @brief 将总线接收到的数据帧合并为标准数据包
//  * @param  package          标准数据包输出
//  * @param  DataFrame        总线数据帧输入
//  * @param  DataFrame_size   总线数据帧大小
//  * @return uint8_t 成功解包返回ROV_TRUE, 解包失败返回ROV_FALSE
//  */
// uint8_t FrameData_Frame2StdPackage(RovData_Package_t* package, const uint8_t* DataFrame, uint8_t DataFrame_size)
// {
//     if (DataFrame_size == STD_FRAME_LENGTH)
//     {
//         package->FrameHead = DataFrame[0];
//         package->DataBody.Opcode = DataFrame[1];
//         package->DataBody.Characode.Identify = (DataFrame[2] & 0xF0) >> 4;
//         package->DataBody.Characode.DLC = (DataFrame[2] & 0x0C) >> 2;
//         package->DataBody.Characode.Valid = (DataFrame[2] & 0x02) >> 1;
//         package->DataBody.Characode.Sensor = DataFrame[2] & 0x01;
//         package->DataBody.Payload[0] = DataFrame[3];
//         package->DataBody.Payload[1] = DataFrame[4];
//         package->DataBody.Payload[2] = DataFrame[5];
//         package->DataBody.Payload[3] = DataFrame[6];
//         package->DataBody.Payload[4] = DataFrame[7];
//         package->DataBody.Payload[5] = DataFrame[8];
//         package->FrameEnd = DataFrame[9];
//         return ROV_TRUE;
//     }
//     return ROV_FALSE;
// }

// /**
//  * @brief 将内部数据包转换成可发送的总线数据帧
//  * @param  DataFrame        总线数据帧输出
//  * @param  data             内部数据包
//  */
// void FrameData_InnPackage2Frame(uint8_t* DataFrame, const RovData_t* data)
// {
//     DataFrame[0] = data->Opcode;
//     DataFrame[1] = (data->Characode.Identify << 4) | (data->Characode.DLC << 2) | (data->Characode.Valid << 1)
//             | (data->Characode.Sensor);
//     DataFrame[2] = data->Payload[0];
//     DataFrame[3] = data->Payload[1];
//     DataFrame[4] = data->Payload[2];
//     DataFrame[5] = data->Payload[3];
//     DataFrame[6] = data->Payload[4];
//     DataFrame[7] = data->Payload[5];
// }

// /**
//  * @brief 将总线接收到的数据帧合并为内部数据包
//  * @param  data             内部数据包输出
//  * @param  DataFrame        总线数据帧输入
//  * @param  DataFrame_size   总线数据帧大小
//  * @return uint8_t 成功解包返回ROV_TRUE, 解包失败返回ROV_FALSE
//  */
// uint8_t FrameData_Frame2InnPackage(RovData_t* data, const uint8_t* DataFrame, uint8_t DataFrame_size)
// {
//     if (DataFrame_size == INN_FRAME_LENGTH)
//     {
//         data->Opcode = DataFrame[0];
//         data->Characode.Identify = (DataFrame[1] & 0xF0) >> 4;
//         data->Characode.DLC = (DataFrame[1] & 0x0C) >> 2;
//         data->Characode.Valid = (DataFrame[1] & 0x02) >> 1;
//         data->Characode.Sensor = DataFrame[1] & 0x01;
//         data->Payload[0] = DataFrame[2];
//         data->Payload[1] = DataFrame[3];
//         data->Payload[2] = DataFrame[4];
//         data->Payload[3] = DataFrame[5];
//         data->Payload[4] = DataFrame[6];
//         data->Payload[5] = DataFrame[7];
//         return ROV_TRUE;
//     }
//     return ROV_FALSE;
// }

// //! 通用解包程序
// /**
//  * @brief 通用解包程序
//  * @param  raw_data         可用数据
//  * @param  characode        舱位指示
//  * @param  payload          原始数据包
//  */
// void Payload_CommonDecode(const ROV_VOID_POINTER raw_data, const Characode_t* characode, const uint8_t* payload)
// {
//     switch (characode->DLC)
//     {
//     case MULTI_DATA:
//         Payload_MultipleDecode((GeneralData_multiple_t*) raw_data, payload);
//         break;
//     case SINGLE_DATA:
//         Payload_SingleDecode((GeneralData_single_t*) raw_data, payload);
//         break;
//     case DOUBLE_DATA:
//         Payload_DoubleDecode((GeneralData_double_t*) raw_data, payload);
//         break;
//     case TRIPLE_DATA:
//         Payload_TripleDecode((GeneralData_triple_t*) raw_data, payload);
//         break;
//     default:
//         break;
//     }
// }

// /**
//  * @brief 通用解包程序-用于多数据数据包
//  * @param  raw_data         可用数据
//  * @param  payload          原始数据包
//  */
// void Payload_MultipleDecode(GeneralData_multiple_t* raw_data, const uint8_t* payload)
// {
//     for (uint8_t i = 0; i < 6; i++)
//     {
//         raw_data->data_8bit[i] = payload[i];
//     }
// }

// /**
//  * @brief 通用解包程序-用于单数据数据包
//  * @param  raw_data         可用数据
//  * @param  payload          原始数据包
//  */
// void Payload_SingleDecode(GeneralData_single_t* raw_data, const uint8_t* payload)
// {
//     if (payload[5] != 0x00) //48bit data
//     {
//         raw_data->data_48bit = (uint64_t) (((uint64_t) (((uint64_t) (payload[0])) << (40U)))
//                 | ((uint64_t) (((uint64_t) (payload[1])) << (32U))) | ((uint64_t) (((uint64_t) (payload[2])) << (24U)))
//                 | ((uint64_t) (((uint64_t) (payload[3])) << (16U))) | ((uint64_t) (((uint64_t) (payload[4])) << (8U)))
//                 | (uint64_t) (payload[5]));
//     }
//     else //32bit data
//     {
//         raw_data->data_32bit = COMBINE_UINT32(payload[0]);
//     }
// }

// /**
//  * @brief 通用解包程序-用于双数据数据包
//  * @param  raw_data         可用数据
//  * @param  payload          原始数据包
//  */
// void Payload_DoubleDecode(GeneralData_double_t* raw_data, const uint8_t* payload)
// {
//     raw_data->data_32bit = COMBINE_UINT32(payload[0]);
//     raw_data->data_16bit = COMBINE_UINT16(payload[4]);
// }

// /**
//  * @brief 通用解包程序-用于三数据数据包
//  * @param  raw_data         可用数据
//  * @param  payload          原始数据包
//  */
// void Payload_TripleDecode(GeneralData_triple_t* raw_data, const uint8_t* payload)
// {
//     raw_data->data_16bit[0] = COMBINE_UINT16(payload[0]);
//     raw_data->data_16bit[1] = COMBINE_UINT16(payload[2]);
//     raw_data->data_16bit[2] = COMBINE_UINT16(payload[4]);
// }

// /**
//  * @brief 通用打包程序
//  * @param  payload          可用数据包
//  * @param  characode        舱位指示
//  * @param  raw_data         原始数据
//  */
// void Payload_CommonEncode(uint8_t* payload, const Characode_t* characode, const ROV_VOID_POINTER raw_data)
// {
//     switch (characode->DLC)
//     {
//     case MULTI_DATA:
//         Payload_MultipleEncode(payload, (GeneralData_multiple_t*) raw_data);
//         break;
//     case SINGLE_DATA:
//         Payload_SingleEncode(payload, (GeneralData_single_t*) raw_data);
//         break;
//     case DOUBLE_DATA:
//         Payload_DoubleEncode(payload, (GeneralData_double_t*) raw_data);
//         break;
//     case TRIPLE_DATA:
//         Payload_TripleEncode(payload, (GeneralData_triple_t*) raw_data);
//         break;
//     default:
//         break;
//     }
// }

// /**
//  * @brief 通用打包程序-用于多数据数据包
//  * @param  payload          可用数据包
//  * @param  raw_data         原始数据
//  */
// void Payload_MultipleEncode(uint8_t* payload, const GeneralData_multiple_t* raw_data)
// {
//     for (uint8_t i = 0; i < 6; i++)
//     {
//         payload[i] = raw_data->data_8bit[i];
//     }
// }

// /**
//  * @brief 通用打包程序-用于单数据数据包
//  * @param  payload          可用数据包
//  * @param  raw_data         原始数据
//  */
// void Payload_SingleEncode(uint8_t* payload, const GeneralData_single_t* raw_data)
// {
//     if ((payload[4] != 0x00) && (payload[5] != 0x00)) //48bit data
//     {
//         payload[0] = ((uint8_t) ((((uint64_t) (raw_data->data_48bit)) & (uint64_t) (0xFF0000000000)) >> (40U)));
//         payload[1] = ((uint8_t) ((((uint64_t) (raw_data->data_48bit)) & (uint64_t) (0x00FF00000000)) >> (32U)));
//         payload[2] = ((uint8_t) ((((uint64_t) (raw_data->data_48bit)) & (uint64_t) (0x0000FF000000)) >> (24U)));
//         payload[3] = ((uint8_t) ((((uint64_t) (raw_data->data_48bit)) & (uint64_t) (0x000000FF0000)) >> (16U)));
//         payload[4] = ((uint8_t) ((((uint64_t) (raw_data->data_48bit)) & (uint64_t) (0x00000000FF00)) >> (8U)));
//         payload[5] = ((uint8_t) ((((uint64_t) (raw_data->data_48bit)) & (uint64_t) (0x0000000000FF)) >> (0U)));
//     }
//     else //32bit data
//     {
//         payload[0] = SPLIT_UINT32_8HH(raw_data->data_32bit);
//         payload[1] = SPLIT_UINT32_8HL(raw_data->data_32bit);
//         payload[2] = SPLIT_UINT32_8LH(raw_data->data_32bit);
//         payload[3] = SPLIT_UINT32_8LL(raw_data->data_32bit);
//         payload[4] = 0x00;
//         payload[5] = 0x00;
//     }
// }

// /**
//  * @brief 通用打包程序-用于双数据数据包
//  * @param  payload          可用数据包
//  * @param  raw_data         原始数据
//  */
// void Payload_DoubleEncode(uint8_t* payload, const GeneralData_double_t* raw_data)
// {
//     payload[0] = SPLIT_UINT32_8HH(raw_data->data_32bit);
//     payload[1] = SPLIT_UINT32_8HL(raw_data->data_32bit);
//     payload[2] = SPLIT_UINT32_8LH(raw_data->data_32bit);
//     payload[3] = SPLIT_UINT32_8LL(raw_data->data_32bit);
//     payload[4] = SPLIT_UINT16_8H(raw_data->data_16bit);
//     payload[5] = SPLIT_UINT16_8L(raw_data->data_16bit);
// }

// /**
//  * @brief 通用打包程序-用于三数据数据包
//  * @param  payload          可用数据包
//  * @param  raw_data         原始数据
//  */
// void Payload_TripleEncode(uint8_t* payload, const GeneralData_triple_t* raw_data)
// {
//     payload[0] = SPLIT_UINT16_8H(raw_data->data_16bit[0]);
//     payload[1] = SPLIT_UINT16_8L(raw_data->data_16bit[0]);
//     payload[2] = SPLIT_UINT16_8H(raw_data->data_16bit[1]);
//     payload[3] = SPLIT_UINT16_8L(raw_data->data_16bit[1]);
//     payload[4] = SPLIT_UINT16_8H(raw_data->data_16bit[2]);
//     payload[5] = SPLIT_UINT16_8L(raw_data->data_16bit[2]);
// }

#endif /* LIBROV_USE_ROVLINK */
