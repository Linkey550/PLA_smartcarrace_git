/*
 * Encoder_c.c
 *
 *  Created on: 2024��4��7��
 *      Author: pp576
 */
#include "Encoder_c.h"
#include "main.h"


//���������֣�
float Real_Distance=0;//��ʵ�ľ��� ������
unsigned char EncoderSum_flag=0;    //�����ܶ��������ۼӱ�־


void EncoderSum(void)
{
    if(EncoderSum_flag==1)
    {
        Real_Distance += encoder_data_quaddec*0.0444;
    }
    }




