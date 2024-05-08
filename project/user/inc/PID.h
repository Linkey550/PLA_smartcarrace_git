#ifndef __PID_H
#define __PID_H




#include "zf_common_headfile.h"

//���ȶ���PID�ṹ�����ڴ��һ��PID������
typedef struct
{
    float kp,ki,kd;//����ϵ��
    float error,lastError;//���ϴ����
    float integral,maxIntegral;//���֡������޷�
    float output,maxOutput;//�������������޷�
}PID_struct;



extern float kp;//����ϵ��
extern float ki;
extern float kd;
extern float PID[3];
extern float error, lastError;//���ϴ����
extern float integral, maxIntegral;//���֡������޷�
extern float output;
extern float maxOutput;
extern float minOutput;//���������޷�����
extern int pwm ;

void PID_Realize(PID_struct *pid, float NowPlace, float Point);
void PID_drive(int32 NowPlace, int32 Point,pwm_channel_enum pin1,pwm_channel_enum pin2);
void PID_lgs(float NowPlace, float Point);
void PID_DirveUse(PID_struct *pid1,PID_struct *pid2);
void PID_Init(PID_struct *pid,float p,float i,float d,float maxI,float maxOut);
void PID_Calc(PID_struct *pid,float reference,float feedback);

#endif
