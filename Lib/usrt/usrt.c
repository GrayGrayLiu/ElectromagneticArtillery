//
// Created by lenovo on 2020/8/28.
//

#include "usrt.h"

#define BYTE_TO_HW(A, B) ((((uint16_t)(A)) << 8) | (uint8_t)(B))
#define BYTE_TO_W(A, B ,C,D) ((((uint32_t)(A)) << 24)|((uint32_t)(B) << 16)|((uint16_t)(C) << 8) | (uint8_t)(D))


uint8_t usart_empty[1]={'a'};
uint8_t SerialServo_usart[8]={'a'};
uint8_t RASPI_UART_EMPTY[18];
int8_t color,shape;
int16_t centre_x,centre_y,angle;
int16_t width,high;
int32_t area;
uint8_t ReceiveNumbers=0;

uint8_t flag_RasPi_Receive=0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == huart3.Instance) SerialRead();
    else if(huart->Instance==ScreenUART)//如果是串口2
    {
        if((USART_RX_STA&0x8000)==0)//接收未完成
        {
            if(USART_RX_STA&0x4000)//接收到了0x0d
            {
                if(aRxBuffer[0]!=0x0a)USART_RX_STA=0;//接收错误,重新开始
                else
                {
                    USART_RX_STA|=0x8000;	//接收完成了
                    ProcessingCommands();
                }
            }
            else //还没收到0X0D
            {
                if(aRxBuffer[0]==0x0d)USART_RX_STA|=0x4000;
                else
                {
                    USART_RX_BUF[USART_RX_STA&0X3FFF]=aRxBuffer[0] ;
                    USART_RX_STA++;
                    if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收
                }
            }
        }
    }
    else if(huart->Instance==ADS1292RUART)
    {
        if((ADS1292R_USART_RX_STA&0x8000)==0)//接收未完成
        {
            if(ADS1292R_USART_RX_STA&0x4000)//接收到了0x0d
            {
                if(ADS1292R_aRxBuffer[0]!=0x0a)ADS1292R_USART_RX_STA=0;//接收错误,重新开始
                else ADS1292R_USART_RX_STA|=0x8000;	//接收完成了
            }
            else //还没收到0X0D
            {
                if(ADS1292R_aRxBuffer[0]==0x0d)ADS1292R_USART_RX_STA|=0x4000;
                else
                {
                    ADS1292R_USART_RX_BUF[ADS1292R_USART_RX_STA&0X3FFF]=ADS1292R_aRxBuffer[0] ;
                    ADS1292R_USART_RX_STA++;
                    if(ADS1292R_USART_RX_STA>(ADS1292R_USART_REC_LEN-1))ADS1292R_USART_RX_STA=0;//接收数据错误,重新开始接收
                }
            }
        }
        Judge_ADS1292R_Received();
    }
    else if((huart->Instance)==huart5.Instance)
    {
//        printf("1234\r\n");
        color=RASPI_UART_EMPTY[1];
        shape=RASPI_UART_EMPTY[2];
        area=BYTE_TO_W(RASPI_UART_EMPTY[3], RASPI_UART_EMPTY[4] ,RASPI_UART_EMPTY[5],RASPI_UART_EMPTY[6]);
        centre_x=BYTE_TO_HW(RASPI_UART_EMPTY[7],RASPI_UART_EMPTY[8]);
        centre_y=BYTE_TO_HW(RASPI_UART_EMPTY[9],RASPI_UART_EMPTY[10]);
        width=BYTE_TO_HW(RASPI_UART_EMPTY[11],RASPI_UART_EMPTY[12]);
        high=BYTE_TO_HW(RASPI_UART_EMPTY[13],RASPI_UART_EMPTY[14]);
        angle=BYTE_TO_HW(RASPI_UART_EMPTY[15],RASPI_UART_EMPTY[16]);
        flag_RasPi_Receive=1;
        ReceiveNumbers++;
//        if(ReceiveNumbers>=20) HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);                 //控制蜂鸣器响的时间
//        if(ReceiveNumbers>=40) HAL_TIM_PWM_Stop(&htim4,TIM_CHANNEL_1),ReceiveNumbers=0;
//        printf("%ld,%d,%d,%d,%d\r\n",area,centre_x,centre_y,width,color);
        HAL_UART_Receive_IT(&huart5,RASPI_UART_EMPTY,18);
    }
}

//串口用户中断处理函数（避免各个串口中断间相互干扰），将此函数添加到相应的串口中断处理函数中
void UsartIRQHandler(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    uint32_t timeout=0;

    timeout=0;
    while (HAL_UART_GetState(huart) != HAL_UART_STATE_READY)//等待就绪
    {
        timeout++;////超时处理
        if(timeout>HAL_MAX_DELAY) break;
    }

    timeout=0;
    while(HAL_UART_Receive_IT(huart, (uint8_t *)pData, Size) != HAL_OK)//一次处理完成之后，重新开启中断并设置RxXferCount为1
    {
        timeout++; //超时处理
        if(timeout>HAL_MAX_DELAY) break;
    }
}
