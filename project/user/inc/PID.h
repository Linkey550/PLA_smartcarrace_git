#ifndef __PID_H
#define __PID_H




#include "zf_common_headfile.h"

//首先定义PID结构体用于存放一个PID的数据
typedef struct
{
    float kp,ki,kd;//三个系数
    float error,lastError;//误差、上次误差
    float integral,maxIntegral;//积分、积分限幅
    float output,maxOutput;//输出、输出上下限幅
}PID_struct;



extern float kp;//三个系数
extern float ki;
extern float kd;
extern float PID[3];
extern float error, lastError;//误差、上次误差
extern float integral, maxIntegral;//积分、积分限幅
extern float output;
extern float maxOutput;
extern float minOutput;//输出、输出限幅上限
extern int pwm ;

void PID_Realize(PID_struct *pid, float NowPlace, float Point);
void PID_drive(int32 NowPlace, int32 Point,pwm_channel_enum pin1,pwm_channel_enum pin2);
void PID_lgs(float NowPlace, float Point);
void PID_DirveUse(PID_struct *pid1,PID_struct *pid2);
void PID_Init(PID_struct *pid,float p,float i,float d,float maxI,float maxOut);
void PID_Calc(PID_struct *pid,float reference,float feedback);

#endif
