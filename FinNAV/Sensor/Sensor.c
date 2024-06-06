#include "Sensor.h"
#include "Algorithm.h"


#ifdef SENSOR_CABIN_ENV
/**
 * @brief 舱内传感器数据封包
 * @param  carbin_data      舱内传感器数据
 * @param  payload          数据包输出数组
 * @param  payload_size     数据包数组大小
 */
void CarbinData2Payload(CarbinData_t* carbin_data, uint8_t* payload, uint8_t payload_size)
{
	if (payload_size == 6)
	{
		payload[0] = SPLIT_UINT16_8H(carbin_data->CarbinTemperature);
		payload[1] = SPLIT_UINT16_8L(carbin_data->CarbinTemperature);
		payload[2] = SPLIT_UINT16_8H(carbin_data->CarbinHumidity);
		payload[3] = SPLIT_UINT16_8L(carbin_data->CarbinHumidity);
		payload[4] = SPLIT_UINT16_8H(carbin_data->CarbinBarometric);
		payload[5] = SPLIT_UINT16_8L(carbin_data->CarbinBarometric);
	}
}
#endif

#ifdef SENSOR_DEPTH
/**
 * @brief 水深传感器数据封包
 * @param  depth_data      	水深传感器数据
 * @param  payload          数据包输出数组
 * @param  payload_size     数据包数组大小
 */
void DepthData2Payload(DepthData_t* depth_data, uint8_t* payload, uint8_t payload_size)
{
	if (payload_size == 6)
	{
		payload[0] = SPLIT_UINT16_8H(depth_data->WaterTemperature);
		payload[1] = SPLIT_UINT16_8L(depth_data->WaterTemperature);
		payload[2] = SPLIT_UINT16_8H(depth_data->WaterDepth);
		payload[3] = SPLIT_UINT16_8L(depth_data->WaterDepth);
		payload[4] = SPLIT_UINT16_8H(depth_data->WaterPressure);
		payload[5] = SPLIT_UINT16_8L(depth_data->WaterPressure);
	}
}
#endif

#ifdef SENSOR_AHRS
/**
 * @brief 加速度传感器数据封包
 * @param  acc_data      	加速度传感器数据
 * @param  payload          数据包输出数组
 * @param  payload_size     数据包数组大小
 */
void ImuAcc2Payload(AHRSData_t* acc_data, uint8_t* payload, uint8_t payload_size)
{
	if (payload_size == 6)
	{
		payload[0] = SPLIT_UINT16_8H(acc_data->Acceleration[0]);
		payload[1] = SPLIT_UINT16_8L(acc_data->Acceleration[0]);
		payload[2] = SPLIT_UINT16_8H(acc_data->Acceleration[1]);
		payload[3] = SPLIT_UINT16_8L(acc_data->Acceleration[1]);
		payload[4] = SPLIT_UINT16_8H(acc_data->Acceleration[2]);
		payload[5] = SPLIT_UINT16_8L(acc_data->Acceleration[2]);
	}
}

/**
 * @brief 角速度传感器数据封包
 * @param  gyr_data      	角速度传感器数据
 * @param  payload          数据包输出数组
 * @param  payload_size     数据包数组大小
 */
void ImuGyr2Payload(AHRSData_t* gyr_data, uint8_t* payload, uint8_t payload_size)
{
	if (payload_size == 6)
	{
		payload[0] = SPLIT_UINT16_8H(gyr_data->AngularSpeed[0]);
		payload[1] = SPLIT_UINT16_8L(gyr_data->AngularSpeed[0]);
		payload[2] = SPLIT_UINT16_8H(gyr_data->AngularSpeed[1]);
		payload[3] = SPLIT_UINT16_8L(gyr_data->AngularSpeed[1]);
		payload[4] = SPLIT_UINT16_8H(gyr_data->AngularSpeed[2]);
		payload[5] = SPLIT_UINT16_8L(gyr_data->AngularSpeed[2]);
	}
}

/**
 * @brief 欧拉角数据封包
 * @param  eul_data       	欧拉角数据
 * @param  payload          数据包输出数组
 * @param  payload_size     数据包数组大小
 */
void ImuEul2Payload(AHRSData_t* eul_data, uint8_t* payload, uint8_t payload_size)
{
	if (payload_size == 6)
	{
		payload[0] = SPLIT_UINT16_8H(eul_data->EulerAngle[0]);
		payload[1] = SPLIT_UINT16_8L(eul_data->EulerAngle[0]);
		payload[2] = SPLIT_UINT16_8H(eul_data->EulerAngle[1]);
		payload[3] = SPLIT_UINT16_8L(eul_data->EulerAngle[1]);
		payload[4] = SPLIT_UINT16_8H(eul_data->EulerAngle[2]);
		payload[5] = SPLIT_UINT16_8L(eul_data->EulerAngle[2]);
	}
}

/**
 * @brief 磁传感器数据封包
 * @param  mag_data       	磁传感器数据
 * @param  payload          数据包输出数组
 * @param  payload_size     数据包数组大小
 */
void ImuMag2Payload(AHRSData_t* mag_data, uint8_t* payload, uint8_t payload_size)
{
	if (payload_size == 6)
	{
		payload[0] = SPLIT_UINT16_8H(mag_data->MagneticValue[0]);
		payload[1] = SPLIT_UINT16_8L(mag_data->MagneticValue[0]);
		payload[2] = SPLIT_UINT16_8H(mag_data->MagneticValue[1]);
		payload[3] = SPLIT_UINT16_8L(mag_data->MagneticValue[1]);
		payload[4] = SPLIT_UINT16_8H(mag_data->MagneticValue[2]);
		payload[5] = SPLIT_UINT16_8L(mag_data->MagneticValue[2]);
	}
}
#endif

#ifdef SENSOR_SONAR
/**
 * @brief 下探声呐数据封包
 * @param  sonar_data       下探声呐数据
 * @param  payload          数据包输出数组
 * @param  payload_size     数据包数组大小
 */
void HeightSonar2Payload(SonarData_t* sonar_data, uint8_t* payload, uint8_t payload_size)
{
	if (payload_size == 6)
	{
		payload[0] = (uint8_t)(((sonar_data->SonarHeight) & (0xFF000000)) >> (24U));
		payload[1] = (uint8_t)(((sonar_data->SonarHeight) & (0x00FF0000)) >> (16U));
		payload[2] = (uint8_t)(((sonar_data->SonarHeight) & (0x0000FF00)) >> (8U));
		payload[3] = (uint8_t)((sonar_data->SonarHeight) & (0x000000FF));
		payload[4] = SPLIT_UINT16_8H(sonar_data->Confidence);
		payload[5] = SPLIT_UINT16_8L(sonar_data->Confidence);
	}
}
#endif



