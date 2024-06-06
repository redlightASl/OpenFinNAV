#include "gp30_driver.h"
#include "usart.h"


#define P30_STATE_IDLE 1
#define P30_STATE_START 2
#define P30_STATE_RECV 3
#define P30_STATE_SUMCHECK 4


p30_sonar_t P30_DATA;

static uint8_t P30_InitBuffer[12] = { 0x42, 0x52, 0x02, 0x00, 0x78, 0x05, 0x00, 0x00, 0x14, 0x05, 0x2C, 0x01 };
static uint8_t P30_RequestBuffer[10] = { 0x42, 0x52, 0x00, 0x00, 0xBB, 0x04, 0x00, 0x00, 0x53, 0x01 };

void P30_Init(void)
{
    //consequence: 42 52 02 00 78 05 00 00 14 05 2C 01
    //stop consequence: 42 52 02 00 79 05 00 00 14 05 2D 01
    //set voice speed=1400: 42 52 04 00 EA 03 00 00 C0 5C 15 00 B6 02

    HAL_UART_Transmit_DMA(&SONAR_UART, P30_InitBuffer, sizeof(P30_InitBuffer));
}

void P30_Process(void)
{
    //request: 42 52 00 00 BB 04 00 00 53 01
    HAL_UART_Transmit_DMA(&SONAR_UART, P30_RequestBuffer, sizeof(P30_RequestBuffer));
}

void P30_get_height(uint32_t* height)
{
    *height = P30_DATA.SonarHeight;
}

void P30_get_confidence(uint16_t* confidence)
{
    *confidence = P30_DATA.Confidence;
}

void P30_read_data(uint8_t* recv)
{
    static uint8_t P30_STATE = P30_STATE_IDLE;
    static uint8_t Bytenum = 0;
    // static uint8_t CheckSum = 0;
    static uint8_t datahex[13] = {0};

    for (uint8_t i = 0; i < 33; i++)
    {
        switch (P30_STATE)
        {
        case P30_STATE_IDLE:
            if (recv[i] == 0x42)
            {
                // CheckSum = recv[i];
                P30_STATE = P30_STATE_START;
            }
            else
            {
                P30_STATE = P30_STATE_IDLE;
            }
            break;
        case P30_STATE_START:
            if (recv[i] == 0x52)
            {
                // CheckSum += recv[i];
                Bytenum = 0;
                P30_STATE = P30_STATE_RECV;
            }
            else
            {
                P30_STATE = P30_STATE_IDLE;
            }
            break;
        case P30_STATE_RECV:
            if (Bytenum < 13)
            {
                // CheckSum += recv[i];
                datahex[Bytenum++] = recv[i];
                P30_STATE = P30_STATE_RECV;
            }
            else
            {
                P30_DATA.Confidence = ((uint16_t) datahex[11] << 8) | 
                    ((uint16_t) datahex[10]);
                P30_DATA.SonarHeight = ((uint32_t)datahex[9] << 24) |
                    ((uint32_t)datahex[8] << 16) |
                    ((uint32_t)datahex[7] << 8) |
                    ((uint32_t)datahex[6]);
                P30_STATE = P30_STATE_IDLE;
            }
            break;
        default:
            P30_STATE = P30_STATE_IDLE;
            break;
        }
    }
    // if ((recv[0] == 0x42) && (recv[1] == 0x52))
    // {
    //     P30_DATA.Confidence = (uint8_t)recv[10];
    //     P30_DATA.SonarHeight = ((uint32_t)recv[6] << 24) |
    //         ((uint32_t)recv[7] << 16) |
    //         ((uint32_t)recv[8] << 8) |
    //         ((uint32_t)recv[9]);
    // }
}