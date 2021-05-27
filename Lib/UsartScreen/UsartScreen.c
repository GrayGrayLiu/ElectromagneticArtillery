//
// Created by 或者 on 2020/10/2.
//

#include "UsartScreen.h"

uint8_t USART_RX_BUF[USART_REC_LEN];    //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
uint16_t USART_RX_STA=0;                //接收状态标记

uint8_t aRxBuffer[RXBUFFERSIZE];        //HAL库使用的串口接收缓冲

uint8_t CannonMode=0;                   //炮模式 0:键盘输入目标 1:自动搜寻目标
uint16_t InputDistance=0;               //键盘设定的距离
int32_t InputAngle=0;                   //键盘输入的夹角（顺时针为正，逆时针为负）
uint8_t CannonState=0;                  //炮状态 0:未充电 1:收到充电指令，调整仰角与夹角后开始充电 2:充电中 3:充电完成可发射

//处理命令函数
void ProcessingCommands(void)
{
    //指令格式:前三位为操作码，后面为操作数
    uint8_t order_buffer[3];
    int order;                               //三位操作码

    float number;                            //操作数

    char str[50];
    uint8_t len;

    //获取串口储存数组的前三位，前三位为操作码
    order_buffer[0]=USART_RX_BUF[0];
    order_buffer[1]=USART_RX_BUF[1];
    order_buffer[2]=USART_RX_BUF[2];

    len=USART_RX_STA&0x3fff;
    USART_RX_STA=0;
    memcpy(str,USART_RX_BUF,len);

    order=atoi(order_buffer); //C语言标准库函数atoi()，将字符串转换为整型数。获取操作数。
    number=atof(str+3); //C语言标准库函数atof()，将字符串转换为浮点数，精度（10 000以内小数点后三位）。获取操作数。

    if(order==900)           //树莓派设定电磁炮模式，0为键盘输入目标，1为自动搜寻目标
    {
        if(number==0)
        {
            CannonMode=0;
        }
        else if(number==1)
        {
//            CannonMode=1;
        }
    }
    else if(order==901)      //树莓派键盘设定距离
    {
        InputDistance=(uint16_t)number;
    }
    else if(order==902)     //树莓派键盘设定角度
    {
        InputAngle=(int32_t)number;
    }
    else if(order==903)     //树莓派键盘控制发射，0不发射，1发射
    {
        if(number==0)
        {
            CannonState=0;
        }
        else if(number==1)
        {
            CannonState=1;
        }
    }
}

//判断串口是否已接收函数
void JudgeUsartScreenReceived(void)
{
    if(USART_RX_STA&0x8000)
    {
        ProcessingCommands();
    }
}