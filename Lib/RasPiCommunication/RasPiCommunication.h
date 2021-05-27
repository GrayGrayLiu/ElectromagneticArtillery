//
// Created by 或者 on 2020/10/13.
//

#ifndef NCMEASUREMENT_RASPICOMMUNICATION_H
#define NCMEASUREMENT_RASPICOMMUNICATION_H

#include "main.h"

#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "Timer.h"

#define RASPI_UART UART5
#define Raspi_uart huart5

float SlidMeanFilter(float x);             //滑动均值滤波
#endif //NCMEASUREMENT_RASPICOMMUNICATION_H
