/*
 * main.h
 *
 *  Created on: 2024��3��23��
 *      Author: ���״�����
 */

#ifndef MAIN_H_
#define MAIN_H_
#include "zf_common_headfile.h"
#define ENCODER_QUADDEC                 (TIM10_ENCOEDER)                         // ������������Ӧʹ�õı������ӿ� ����ʹ��QTIMER1��ENCOEDER1
#define ENCODER_QUADDEC_A               (TIM10_ENCOEDER_MAP3_CH2_D3)             // A ���Ӧ������
#define ENCODER_QUADDEC_B               (TIM10_ENCOEDER_MAP3_CH1_D1)             // B ���Ӧ������

extern int16 encoder_data_quaddec ;

#endif /* MAIN_H_ */

