//
// Created by 或者 on 2020/10/4.
//

#ifndef USMART_RECEIVEADS1292R_H
#define USMART_RECEIVEADS1292R_H

#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stm32f4xx.h"

#include "usart.h"

#define ADS1292RUart huart4         //定义使用的串口句柄
#define ADS1292RTimer htim4         //定义使用的定时器句柄
#define ADS1292RUART UART4         //定义使用到的串口

#define ADS1292R_USART_REC_LEN 8    //定义最大接收字节数8
#define ADS1292R_RXBUFFERSIZE 1     //缓存大小

extern uint8_t ADS1292R_USART_RX_BUF[ADS1292R_USART_REC_LEN];
extern uint16_t ADS1292R_USART_RX_STA;
extern uint8_t ADS1292R_aRxBuffer[ADS1292R_RXBUFFERSIZE];

extern float DISTANCE;

void ADS1292R_DataProcessing(void);

void Judge_ADS1292R_Received(void);

void SerialWrite_U2(uint8_t *data, uint8_t len);

void send_to_pi(int distance);

#endif //USMART_RECEIVEADS1292R_H
