//
// Created by 或者 on 2020/10/10.
//

#ifndef NCMEASUREMENT_NCMEASUREMENT_H
#define NCMEASUREMENT_NCMEASUREMENT_H

#include "main.h"

#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "Timer.h"
#include "usrt.h"

#define NCMTIM htim6

#define PULSE_REV 8000                      //步进电机转一圈所需脉冲数
#define STEP_ANGLE 360/PULSE_REV            //步距角

#define PITCHER_CENTRAL_POINT 300           //图像中心点横坐标
#define StepperMotorSubdivision 8000        //步进电机细分数

void NCMeasurement(uint8_t cannon_mode);

void StepperMotorAngle_Incremental(int32_t angle,uint16_t speed);         //设定角度移动_增量式
void StepperMotorAngle_Position(int32_t angle,uint16_t speed);            //设定角度移动_位置式
void StepperMotorFineTune(void);                                          //步进电机微调
void StepperMotorMove(int32_t steps,uint16_t speed,uint8_t direction);    //设定步数，转速，方向。direction为0为逆时针，1为顺时针
void StepperMotorSpeed(uint16_t speed,uint8_t direction);                 //修改转速和方向
void StepperMotorSteps(int16_t steps,uint8_t direction);                  //修改步数和方向
void StepperMotorTurnClockwise(void);           //顺时针转动
void StepperMotorTurnAnticlockwise(void);       //逆时针转动
void StepperMotorStop(void);                    //停转
void StepperMotorStart(void);                   //启动

uint8_t SetServoElevation(uint16_t distance);      //根据距离设定舵机仰角

void SamplingTest(void);                        //采样测试程序
int16_t CalculateServoAngle(float distance);   //根据标靶距离计算舵机仰角

double CalculateSideLength(uint8_t shape,double distance,double pixels); //计算一维图形边长，入口参数（形状标号，与镜头距离，像素点数量）
void TrackCentralPoint( int PitcherCentralPoint,float point_x);       //跟踪图形中心点

extern uint8_t FlagStepperMotorDirection;
#endif //NCMEASUREMENT_NCMEASUREMENT_H
