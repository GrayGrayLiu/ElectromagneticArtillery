//
// Created by Wirano on 2020/8/21.
//

#include "SerialServo.h"
#include "usrt.h"
#include "usart.h"

#define GET_LOW_BYTE(A) ((uint8_t)(A))
#define GET_HIGH_BYTE(A) ((uint8_t)((A) >> 8))
#define BYTE_TO_HW(A, B) ((((uint16_t)(A)) << 8) | (uint8_t)(B))

uint8_t write_pin=0,Servo_State[256];
int16_t get_position[256];
uint16_t set_id;

uint8_t CheckSum(uint8_t *data, uint8_t len) {
    uint8_t temp = 0;

    data += 2;
    for (int i = 2; i < len - 1; ++i) {
        temp += *data++;
    }

    return ~temp;
}

void SerialWrite(uint8_t *data, uint8_t len) {
    while (len--) {
        while ((SERVO_USART->SR & 0X40U) == 0);
        SERVO_USART->DR = *data++;
    }
}

void SerialRead(void) {
    if(write_pin==SERVO_POS_READ)
    {
        get_position[set_id]=SerialServo_usart[6];
        get_position[set_id]<<=8;
        get_position[set_id]|=SerialServo_usart[5];
    }
    if(write_pin==SERVO_OR_MOTOR_MODE_READ)
        Servo_State[set_id]=SerialServo_usart[5];
}



void SerialServoMove(uint8_t id, int16_t position, uint16_t time) {
    uint8_t temp[10];

    if (position < 0) position = 0;
    if (position > 1000) position = 1000;

    temp[0] = temp[1] = SERVO_FRAME_HEADER;
    temp[2] = id;
    temp[3] = 7;
    temp[4] = SERVO_MOVE_TIME_WRITE;
    temp[5] = GET_LOW_BYTE(position);
    temp[6] = GET_HIGH_BYTE(position);
    temp[7] = GET_LOW_BYTE(time);
    temp[8] = GET_HIGH_BYTE(time);
    temp[9] = CheckSum(temp, 10);

    SerialWrite(temp,10);
}
//舵机移动

void SerialServomode(uint8_t id ,uint8_t mode , int16_t speed) {
    uint8_t temp[10];

    temp[0] = temp[1] = SERVO_FRAME_HEADER;
    temp[2] = id;
    temp[3] = 7;
    temp[4] = SERVO_OR_MOTOR_MODE_WRITE;
    temp[5]=mode;
    temp[6]=0;
    temp[7] = GET_LOW_BYTE(speed);
    temp[8] = GET_HIGH_BYTE(speed);
    temp[9] = CheckSum(temp, 10);

    SerialWrite(temp,10);
}
//舵机0or电机1


void SerialServoReadPosition(uint8_t id) {
    uint8_t temp[6];
    write_pin=SERVO_POS_READ;
    set_id=id;
    temp[0] = temp[1] = SERVO_FRAME_HEADER;
    temp[2] = id;
    temp[3] = 3;
    temp[4] = SERVO_POS_READ;
    temp[5] = CheckSum(temp, 6);

    SerialWrite(temp,6);
    HAL_UART_Receive_IT(&SERVO_READUSART, SerialServo_usart, 8);

}
//舵机位置读取

void SerialServoUnload(uint8_t id) {
    uint8_t temp[7];

    temp[0] = temp[1] = SERVO_FRAME_HEADER;
    temp[2] = id;
    temp[3] = 4;
    temp[4] = SERVO_LOAD_OR_UNLOAD_WRITE;
    temp[5] = 0;
    temp[6] = CheckSum(temp, 7);

    SerialWrite(temp,10);
}
//舵机下电

void SerialServoLoad(uint8_t id) {
    uint8_t temp[7];

    temp[0] = temp[1] = SERVO_FRAME_HEADER;
    temp[2] = id;
    temp[3] = 4;
    temp[4] = SERVO_LOAD_OR_UNLOAD_WRITE;
    temp[5] = 1;
    temp[6] = CheckSum(temp, 7);

    SerialWrite(temp,10);
}
//舵机上电

void Servo_State_Read(uint8_t id) {
    uint8_t temp[6];
    write_pin=SERVO_OR_MOTOR_MODE_READ;
    set_id=id;

    temp[0] = temp[1] = SERVO_OR_MOTOR_MODE_READ;
    temp[2] = id;
    temp[3] = 3;
    temp[4] = SERVO_POS_READ;
    temp[5] = CheckSum(temp, 6);

    SerialWrite(temp,6);
    HAL_UART_Receive_IT(&SERVO_READUSART, SerialServo_usart, 7);
}
//舵机状态检测

void SerialServo_stop(uint8_t id){
    uint8_t temp[6];

    temp[0] = temp[1] = SERVO_FRAME_HEADER;
    temp[2] = id;
    temp[3] = 3;
    temp[4] = SERVO_MOVE_STOP;
    temp[5] = CheckSum(temp, 6);

    SerialWrite(temp,6);

}
