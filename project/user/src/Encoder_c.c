/*
 * Encoder_c.c
 *
 *  Created on: 2024年4月7日
 *      Author: pp576
 */
#include "Encoder_c.h"
#include "main.h"


//编码器部分：
float Real_Distance=0;//真实的距离 ：毫米
unsigned char EncoderSum_flag=0;    //车辆跑动编码器累加标志


void EncoderSum(void)
{
    if(EncoderSum_flag==1)
    {
        Real_Distance += encoder_data_quaddec*0.0444;
    }
    }




