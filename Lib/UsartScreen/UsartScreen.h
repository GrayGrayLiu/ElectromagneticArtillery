//
// Created by 或者 on 2020/10/2.
//

#ifndef USMART_USARTSCREEN_H
#define USMART_USARTSCREEN_H

#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stm32f4xx.h"

#include "usart.h"
#include "tim.h"
#include "usrt.h"

#define ScreenUart huart2         //定义使用的串口句柄
#define ScreenTimer htim2         //定义使用的定时器句柄
#define ScreenUART USART2         //定义使用到的串口

#define USART_REC_LEN 200  	//定义最大接收字节数 200
#define RXBUFFERSIZE 1      //缓存大小

void ProcessingCommands(void);
void JudgeUsartScreenReceived(void);

extern uint8_t aRxBuffer[RXBUFFERSIZE];
extern uint8_t USART_RX_BUF[USART_REC_LEN];    //接收缓冲,最大USART_REC_LEN个字节.
extern uint16_t USART_RX_STA;                  //接收状态标记

extern uint8_t CannonMode;                   //炮模式 0:键盘输入目标 1:自动搜寻目标
extern uint16_t InputDistance;               //键盘设定的距离
extern int32_t InputAngle;                   //键盘输入的夹角（顺时针为正，逆时针为负）
extern uint8_t CannonState;                  //炮状态 0:未充电 1:收到充电指令 2:充电中 3:发射

#endif //USMART_USARTSCREEN_H
