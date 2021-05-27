//
// Created by 或者 on 2020/10/3.
//

#include "Timer.h"

int32_t StepsTemp=0;//计算走过的步数要用到的中间变量
int32_t STEPS=0;    //走过的步数
int32_t SetSTEPS=0; //设定要走到的步数

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&htim6))
    {
        if(FlagStepperMotorDirection==1 && STEPS<SetSTEPS)
        {
            HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_15);
            StepsTemp++;
            STEPS = StepsTemp / 2;           //顺时针转动，记步加一
        }
        else if(FlagStepperMotorDirection==0 && STEPS>SetSTEPS)
        {
            HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_15);
            StepsTemp--;
            STEPS = StepsTemp / 2;           //逆时针转动，记步减一
        }
    }
}
