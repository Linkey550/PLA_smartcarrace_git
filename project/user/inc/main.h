/*
 * main.h
 *
 *  Created on: 2024年3月23日
 *      Author: 北白川硝子
 */

#ifndef MAIN_H_
#define MAIN_H_
#include "zf_common_headfile.h"
#define ENCODER_QUADDEC                 (TIM10_ENCOEDER)                         // 正交编码器对应使用的编码器接口 这里使用QTIMER1的ENCOEDER1
#define ENCODER_QUADDEC_A               (TIM10_ENCOEDER_MAP3_CH2_D3)             // A 相对应的引脚
#define ENCODER_QUADDEC_B               (TIM10_ENCOEDER_MAP3_CH1_D1)             // B 相对应的引脚

extern int16 encoder_data_quaddec ;

#endif /* MAIN_H_ */

