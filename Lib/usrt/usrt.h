//
// Created by lenovo on 2020/8/28.
//

#ifndef INC_2333_USRT_H
#define INC_2333_USRT_H

#include "stdio.h"

#include "usart.h"
#include "SerialServo.h"
#include "UsartScreen.h"
#include "ReceiveADS1292R.h"
#include "RasPiCommunication.h"
#include "NCMeasurement.h"

extern uint8_t usart_empty[1];
extern uint8_t SerialServo_usart[8];
extern int8_t color,shape;
extern int16_t centre_x,centre_y,angle;
extern int16_t width,high;
extern int32_t area;
extern uint8_t RASPI_UART_EMPTY[18];

extern uint8_t flag_RasPi_Receive;

void UsartIRQHandler(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

#endif //INC_2333_USRT_H
