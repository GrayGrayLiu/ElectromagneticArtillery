//
// Created by 或者 on 2020/10/13.
//

#include "RasPiCommunication.h"

float SlidMeanFilter(float x)
{
    uint8_t i;
    uint8_t BlockSize=100;
    static float Block[100];
    float sum=0;

    for(i=1;i<BlockSize;i++)
    {
        Block[i]=Block[i-1];
    }
    Block[BlockSize-1]=x;

    for(i=0;i<BlockSize;i++)
    {
        sum+=Block[i];
    }
    sum/=BlockSize;

    return sum;
}