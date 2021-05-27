//
// Created by 或者 on 2020/10/4.
//

#include "ReceiveADS1292R.h"

uint8_t ADS1292R_USART_RX_BUF[ADS1292R_USART_REC_LEN];    //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
uint16_t ADS1292R_USART_RX_STA=0;                         //接收状态标记

uint8_t ADS1292R_aRxBuffer[ADS1292R_RXBUFFERSIZE];        //HAL库使用的串口接收缓冲

float DISTANCE;

//处理数据函数
void ADS1292R_DataProcessing(void)
{
    char str[30];
    int len;
    float distance;

    len=ADS1292R_USART_RX_STA&0x3fff;//寰楀埌姝ゆ鎺ユ敹鍒扮殑鏁版嵁闀垮害
    ADS1292R_USART_RX_STA=0;
    memcpy(str,ADS1292R_USART_RX_BUF,len);

    DISTANCE=atof(str);                 //C语言标准库函数atof()，将字符串转换为浮点数，精度（10 000以内小数点后三位）。获取操作数。

//    printf("distance:%.2f\r\n",DISTANCE);
}

//判断串口是否已接收函数
void Judge_ADS1292R_Received(void)
{
    if(ADS1292R_USART_RX_STA&0x8000)
    {
        ADS1292R_DataProcessing();
    }
}

void SerialWrite_U2(uint8_t *data, uint8_t len) {
    while (len--) {
        while ((USART2->SR & 0X40U) == 0);
        USART2->DR = *data++;
    }
}

void send_to_pi(int distance)
{
    uint8_t pi[6];
    pi[0]=0XAA;
    pi[1]=(uint8_t)distance;
    pi[2]=(uint8_t)((distance) >> 8);
    pi[3]=(uint8_t)((distance) >> 16);
    pi[4]=(uint8_t)((distance) >> 24);
    pi[5]=0X55;
    SerialWrite_U2(pi,6);
}

