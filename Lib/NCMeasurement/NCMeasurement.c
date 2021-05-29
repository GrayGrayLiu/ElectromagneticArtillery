//
// Created by 或者 on 2020/10/10.
//

#include "NCMeasurement.h"

uint8_t FlagStepperMotorDirection=0;                    //步进电机转向标志位，0为逆时针，1为顺时针

void NCMeasurement(uint8_t cannon_mode)
{
    static uint8_t  flag_key2=0;

    if(cannon_mode==0)
    {
        if(CannonState==0)           //未击发，未收到充电指令
        {
        }
        else if(CannonState==1)      //收到充电指令，调整仰角与夹角后开始充电
        {
            StepperMotorAngle_Position(InputAngle,999); //步进电机调整夹角
            //在任务调度器里调整舵机角度
            HAL_GPIO_WritePin(ControlRelay_GPIO_Port,ControlRelay_Pin,GPIO_PIN_RESET);     //继电器吸合，开始充电
//            CannonState=2;
        }
        else if(CannonState==2)      //充电中
        {
            if( HAL_GPIO_ReadPin(VoltageComparisonInput_GPIO_Port,VoltageComparisonInput_Pin)==0 ) //如果电容电压充到阈值电压
            {
                HAL_Delay(5);   //消抖
                if( HAL_GPIO_ReadPin(VoltageComparisonInput_GPIO_Port,VoltageComparisonInput_Pin)==0 )
                {
                    CannonState = 3;
                    HAL_GPIO_WritePin(ControlRelay_GPIO_Port, ControlRelay_Pin, GPIO_PIN_SET); //继电器释放
                }
            }
        }
        else if(CannonState==3)      //充电完成
        {
            //在任务调度器中将舵机归0后重新切换到0状态
        }
    }
    else if(cannon_mode==1)
    {
        StepperMotorMove(0,8999,0);
        while(flag_RasPi_Receive==0)
        {
            if(STEPS<=300 && flag_RasPi_Receive==0 && flag_key2==0)
            {
                StepperMotorSteps(5,0);
                if(STEPS<=-300) flag_key2=1;
            }
            else if(STEPS>=-300 && flag_RasPi_Receive==0 && flag_key2==1)
            {
                StepperMotorSteps(5,1);
                if(STEPS>=300) flag_key2=0;
            }
        }
        if(flag_RasPi_Receive==1)
        {
            TrackCentralPoint(PITCHER_CENTRAL_POINT, centre_x);
            HAL_Delay(1);
            flag_RasPi_Receive=0;
            HAL_Delay(300);
        }
    }
}

//设定角度移动_增量式
void StepperMotorAngle_Incremental(int32_t angle,uint16_t speed)
{
    if(angle>=0)
    {
        StepperMotorMove( (StepperMotorSubdivision*angle)/360 , speed , 1);
    }
    else
    {
        angle*=(-1);
        StepperMotorMove( (StepperMotorSubdivision*angle)/360 , speed , 0);
    }
}

//设定角度移动_位置式
void StepperMotorAngle_Position(int32_t angle,uint16_t speed)
{
    NCMTIM.Instance->ARR=speed;
    if(angle>=0)
    {
        StepperMotorTurnClockwise();
        SetSTEPS=(StepperMotorSubdivision*angle)/360;
    }
    else if(angle<0)
    {
        StepperMotorTurnAnticlockwise();
        SetSTEPS=(StepperMotorSubdivision*angle)/360;
    }
}

//步进电机微调
void StepperMotorFineTune(void)
{
    static uint8_t Key1Continue=0;
    static uint8_t Key2Continue=0;
    static uint8_t Key3Continue=0;
    static uint8_t Key4Continue=0;
    static uint8_t Key5Continue=0;

    if( HAL_GPIO_ReadPin(Key1_GPIO_Port,Key1_Pin)==0 && Key1Continue==0 )  //如果Key1按下，归零步进电机角度
    {
        HAL_Delay(5);   //消抖
        if( HAL_GPIO_ReadPin(Key1_GPIO_Port,Key1_Pin)==0 )  //如果Key1按下，归零步进电机角度
        {
            STEPS=0;
            SetSTEPS=0;
            Key1Continue=1;
        }
    }
    else if( HAL_GPIO_ReadPin(Key1_GPIO_Port,Key1_Pin)==1 )       //松手检测
    {
        Key1Continue=0;
    }

    if( HAL_GPIO_ReadPin(Key2_GPIO_Port,Key2_Pin)==0 && Key2Continue==0)  //如果Key2按下，逆时针转1步
    {
        HAL_Delay(5);   //消抖
        if( HAL_GPIO_ReadPin(Key2_GPIO_Port,Key2_Pin)==0 )  //如果Key2按下，逆时针转1步
        {
            StepperMotorMove(1,8999,0);
            Key2Continue=1;
        }
    }
    else if( HAL_GPIO_ReadPin(Key2_GPIO_Port,Key2_Pin)==1 )
    {
        Key2Continue=0;
    }

    if( HAL_GPIO_ReadPin(Key3_GPIO_Port,Key3_Pin)==0 && Key3Continue==0)  //如果Key3按下，顺时针转1步
    {
        HAL_Delay(5);   //消抖
        if( HAL_GPIO_ReadPin(Key3_GPIO_Port,Key3_Pin)==0 )  //如果Key3按下，顺时针转1步
        {
            StepperMotorMove(1,8999,1);
            Key3Continue=1;
        }
    }
    else if( HAL_GPIO_ReadPin(Key3_GPIO_Port,Key3_Pin)==1 )
    {
        Key3Continue=0;
    }

    if( HAL_GPIO_ReadPin(Key4_GPIO_Port,Key4_Pin)==0 && Key4Continue==0)  //如果Key4按下，逆时针转10步
    {
        HAL_Delay(5);   //消抖
        if( HAL_GPIO_ReadPin(Key4_GPIO_Port,Key4_Pin)==0 )  //如果Key4按下，逆时针转10步
        {
            StepperMotorMove(10,8999,0);
            Key4Continue=1;
        }
    }
    else if( HAL_GPIO_ReadPin(Key4_GPIO_Port,Key4_Pin)==1 )
    {
        Key4Continue=0;
    }

    if( HAL_GPIO_ReadPin(Key5_GPIO_Port,Key5_Pin)==0 && Key5Continue==0)  //如果Key4按下，顺时针转10步
    {
        HAL_Delay(5);   //消抖
        if( HAL_GPIO_ReadPin(Key5_GPIO_Port,Key5_Pin)==0 )  //如果Key4按下，顺时针转10步
        {
            StepperMotorMove(10,8999,1);
            Key5Continue=1;
        }
    }
    else if( HAL_GPIO_ReadPin(Key5_GPIO_Port,Key5_Pin)==1 )
    {
        Key5Continue=0;
    }
}

//步进电机移动函数（步数，速度【重装载值】，方向）
void StepperMotorMove(int32_t steps,uint16_t speed,uint8_t direction)
{
    NCMTIM.Instance->ARR=speed;
    if(direction==1)
    {
        StepperMotorTurnClockwise();
        SetSTEPS=STEPS+steps;
    }
    else if(direction==0)
    {
        StepperMotorTurnAnticlockwise();
        SetSTEPS=STEPS-steps;
    }
}

void StepperMotorSpeed(uint16_t speed,uint8_t direction)
{
    NCMTIM.Instance->ARR=speed;
    if(direction==0)
    {
        StepperMotorTurnClockwise();
    }
    else if(direction==1)
    {
        StepperMotorTurnAnticlockwise();
    }
}

void StepperMotorSteps(int16_t steps,uint8_t direction)
{
    if(direction==1)
    {
        StepperMotorTurnClockwise();
        SetSTEPS=STEPS+steps;
    }
    else if(direction==0)
    {
        StepperMotorTurnAnticlockwise();
        SetSTEPS=STEPS-steps;
    }
}

//步进电机顺时针转动函数
void StepperMotorTurnClockwise(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);
    FlagStepperMotorDirection=1;
}

//步进电机逆时针转动函数
void StepperMotorTurnAnticlockwise(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);
    FlagStepperMotorDirection=0;
}

//停转
void StepperMotorStop(void)
{
    FlagStepperMotorDirection=2;
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);
}

//启动
void StepperMotorStart(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);
}

//根据距离设定舵机仰角
uint8_t SetServoElevation(uint16_t distance)
{
    static int16_t Angle=0;
    static int16_t AngleValue=0;
    static uint8_t State=0;   //设定舵机角度标志位 0:未开始设置  1:开始设置 2:设置中 3:可能到达设定位置(一次确认) 4:可能到达设定位置(二次确认) 5:完成
    static uint8_t SwitchReadWrite=0;  //切换舵机的读写 舵机的读和写需要间隔一定的时间

    printf("St=%d\r\n",State);
    if(State==0)
    {
        Angle=CalculateServoAngle(distance);
        AngleValue=Angle;
        State=1;
        return 0;
    }
    else if(State==1)
    {
        SerialServoMove(0,Angle,0);
        State=2;
        return 0;
    }
    else if(State==2)
    {
        if(SwitchReadWrite==0)
        {
            SerialServoReadPosition(0);
        }
        else if(SwitchReadWrite!=0)
        {
            printf("An=%d\r\n",Angle);

            if(  abs( get_position[0] - Angle )>1  )
            {
                if ((get_position[0] - Angle) > 0)
                {
                    SerialServoMove(0,(--AngleValue),0);
                }
                else if ((get_position[0] - Angle) < 0)
                {
                    SerialServoMove(0,(++AngleValue),0);
                }
            }
            else
            {
                State=3;
            }
            State=3;
        }
        SwitchReadWrite=!SwitchReadWrite;
        return 0;
    }
    else if(State==3)
    {
        if(SwitchReadWrite==0)
        {
            SerialServoReadPosition(0);
        }
        else
        {
            if(  abs( get_position[0] - Angle )<=1  )
            {
                State=4;
            }
            else
            {
                State=2;
            }
        }
        SwitchReadWrite=!SwitchReadWrite;
        return 0;
    }
    else if(State==4)
    {
        if(SwitchReadWrite==0)
        {
            SerialServoReadPosition(0);
        }
        else
        {
            if(  abs( get_position[0] - Angle )<=1  )
            {
                State=5;
            }
            else
            {
                State=2;
            }
        }
        SwitchReadWrite=!SwitchReadWrite;
        return 0;
    }
    else if(State==5)
    {
        State=0;
        return 1;
    }
}

void SamplingTest(void)
{
    static uint8_t KeyContinue=0;

    if( HAL_GPIO_ReadPin(Key0_GPIO_Port,Key0_Pin)==0 && KeyContinue==0 )  //如果Key0按下，继电器吸合
    {
        HAL_Delay(5);   //消抖

        if( HAL_GPIO_ReadPin(Key0_GPIO_Port,Key0_Pin)==0 )  //如果Key0按下，继电器吸合
        {
            KeyContinue=1;
            HAL_GPIO_WritePin(ControlRelay_GPIO_Port,ControlRelay_Pin,GPIO_PIN_RESET);
        }
    }
    else if( HAL_GPIO_ReadPin(Key0_GPIO_Port,Key0_Pin)==1 )
    {
        KeyContinue=0;
    }

    if( HAL_GPIO_ReadPin(VoltageComparisonInput_GPIO_Port,VoltageComparisonInput_Pin)==0 ) //如果电容电压充到阈值电压，继电器释放
    {
        HAL_Delay(5);   //消抖
        if( HAL_GPIO_ReadPin(VoltageComparisonInput_GPIO_Port,VoltageComparisonInput_Pin)==0 )
        {
            HAL_GPIO_WritePin(ControlRelay_GPIO_Port,ControlRelay_Pin,GPIO_PIN_SET);
        }
    }
    StepperMotorFineTune();
}

//根据标靶距离计算舵机仰角
int16_t CalculateServoAngle(float distance)
{
    int16_t Angle=0;
    double p1,p2,p3,p4;

    p1 =   -3.38e-05 ;
    p2 =     0.02907 ;
    p3 =      -9.165 ;
    p4 =        1296 ;

    Angle = (int16_t)(p1*distance*distance*distance + p2*distance*distance + p3*distance + p4);

    return Angle;
}

//在任务调度器中用来计时
void Wait(uint16_t Hz,uint16_t time_s,uint16_t *actions_number)
{
    static uint16_t TimeCount=0;

    if( TimeCount<(Hz*time_s) )
    {
        TimeCount++;
    }
    else
    {
        (*actions_number)++;
        TimeCount=0;
    }
}

double CalculateSideLength(uint8_t shape,double distance,double pixels)
{
    double p1,p2,p3,p4,p5;
    double x;
    double y;
    double area;         //面积
    double length;

    x=distance;

    p1 =       514.2  ;
    p2 =       -6103  ;
    p3 =       27760  ;
    p4 =      -58720  ;
    p5 =       51460 ;

    y = p1*x*x*x*x + p2*x*x*x + p3*x*x + p4*x + p5;

    area=pixels/y;                     //面积单位：平方分米

    if(shape==2)                       //正方形
    {
        length=sqrt(area);
    }
    else if(shape==3)                  //三角形
    {
        length=sqrt(area*4/sqrt(3));
    }
    else if(shape==1)                  //圆形
    {
        length=2*sqrt(area/3.1415926);
    }

    return length;
}

void TrackCentralPoint( int PitcherCentralPoint,float point_x)
{
    PitcherCentralPoint=PITCHER_CENTRAL_POINT;
    static float Kp=3;
    float Ek;
    float Out;
    uint8_t direction;
    static uint flag=0;

    if(flag==0) flag++;

    Ek=PitcherCentralPoint-point_x;
    printf("Ek:%f\r\n",Ek);
    Out=Kp*Ek;

    if(Out>0) direction=0;
    else direction=1;

    if(flag==1) StepperMotorSpeed(40000,1);

    printf("Out:%f",Out);
//    if(fabs(Out)<4*Kp) StepperMotorStop();
//    else if(fabs(Out)>20*Kp) StepperMotorStart();
    if(fabs(Out)<5*Kp) StepperMotorSteps(0,0);
    else StepperMotorSteps(fabs(Out),direction);
}