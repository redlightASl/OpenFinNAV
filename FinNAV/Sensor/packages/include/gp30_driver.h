#ifndef __GP30_DRIVER_H_
#define __GP30_DRIVER_H_
#include "Driver.h"

#define SONAR_UART huart2

struct p30_sonar {
	uint16_t Confidence;
    uint32_t SonarHeight;
};	
typedef struct p30_sonar p30_sonar_t;


void P30_Init(void);
void P30_Process(void);
void P30_get_height(uint32_t* height);
void P30_get_confidence(uint16_t* confidence);
void P30_read_data(uint8_t* recv);


#endif


