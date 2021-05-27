//
// Created by Wirano on 2020/8/21.
//

#ifndef ROLLINGBALLCONTROLSYSTEM_SERIALSERVO_H
#define ROLLINGBALLCONTROLSYSTEM_SERIALSERVO_H

#include "stm32f4xx_hal.h"

#define    SERVO_MOVE_TIME_WRITE    1
#define    SERVO_MOVE_TIME_READ    2
#define    SERVO_MOVE_TIME_WAIT_WRITE    7
#define    SERVO_MOVE_TIME_WAIT_READ    8
#define    SERVO_MOVE_START    11
#define    SERVO_MOVE_STOP    12
#define    SERVO_ID_WRITE    13
#define    SERVO_ID_READ    14
#define    SERVO_ANGLE_OFFSET_ADJUST    17
#define    SERVO_ANGLE_OFFSET_WRITE    18
#define    SERVO_ANGLE_OFFSET_READ    19
#define    SERVO_ANGLE_LIMIT_WRITE    20
#define    SERVO_ANGLE_LIMIT_READ    21
#define    SERVO_VIN_LIMIT_WRITE    22
#define    SERVO_VIN_LIMIT_READ    21
#define    SERVO_TEMP_MAX_LIMIT_WRITE    24
#define    SERVO_TEMP_MAX_LIMIT_READ    25
#define    SERVO_TEMP_READ    26
#define    SERVO_VIN_READ    27
#define    SERVO_POS_READ    28
#define    SERVO_OR_MOTOR_MODE_WRITE    29
#define    SERVO_OR_MOTOR_MODE_READ    30
#define    SERVO_LOAD_OR_UNLOAD_WRITE    31
#define    SERVO_LOAD_OR_UNLOAD_READ    32
#define    SERVO_LED_CTRL_WRITE    33
#define    SERVO_LED_CTRL_READ    34
#define    SERVO_LED_ERROR_WRITE    35
#define    SERVO_LED_ERROR_READ    36

#define    SERVO_FRAME_HEADER   0x55

#define SERVO_USART USART3
#define SERVO_READUSART huart3

extern int16_t get_position[256];
extern uint8_t Servo_State[256];

void SerialRead(void) ;


void SerialServoMove(uint8_t id, int16_t position, uint16_t time); //舵机模式移动，(id,位置，移动时间 )

void SerialServoReadPosition(uint8_t id);//读取舵机当前角度 id

void SerialServoUnload(uint8_t id); //舵机下电

void SerialServoLoad(uint8_t id);//舵机上电

void Servo_State_Read(uint8_t id) ;//舵机状态阅读 非0为报错

void SerialServomode(uint8_t id ,uint8_t mode ,int16_t speed) ; //舵机模式设置 id，模式0为舵机模式，模式1为电机模式 当舵机模式是speed=0 电机speed为速度

void SerialServo_stop(uint8_t id);

#endif //ROLLINGBALLCONTROLSYSTEM_SERIALSERVO_H
