/*
 * Gyroscope_c.c
 *�����ǵ���ؼ���
 * *  Created on: 2024��4��7��
 *      Author: pp576
 */

#include "Gyroscope_c.h"

int16 Emo_gyro_z = 0,Normal_gyro_z = 0,Emo_gyro_y = 0;
float Emo_LastAngleSpeed = 0,Emo_AngleSpeed = 0;
float Emo_Pitch = 0,Emo_PitchSpeed = 0,Emo_LastPitchSpeed = 0;
float dt=0.008;
float Emo_Angle_Max =  360;
float Emo_Angle_Min = -360;
float Emo_AngleSpeed_Max = 500;
float Emo_AngleSpeed_Min = -500;
float AngleSpeed = 0;
int GyroscopeTime = 0;
int test = 0;
int test_sum = 0;
volatile unsigned char Gyroscope_Star_flag = 0;  //�������������ǵĽǶ������ж�Ԫ�ؽ������
volatile unsigned char GyroscopePitch_Star_flag = 0;  //�������������ǵĽǶ������ж�Ԫ�ؽ������

//extern float angv[3];//������Z���ٶ�

//float Emo_Angle;


////�����ǳ�ʼ��
//void Gyroscope_Time_Star(void)
//{
//    GyroscopeTime++;
//}
//
//void Gyroscope_Time_Clear(void)
//{
//    GyroscopeTime = 0;
//}
//void Gyroscope_GetData(void)
//{
//
//    AngleSpeed = angv[2];
//}
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      �����Ǽ��㺽ƫ�ǽǶ�
////  @param
////  @param
////  @param
////  @param
////  @return     void
////  @note   һ�������˲����ٶȻ��ֵõ�ƫ����
////-------------------------------------------------------------------------------------------------------------------
//void Get_Gyroscope_Angle(void)
//{
//    float K=0.7;
//    Emo_gyro_z = angv[2];
//    Emo_LastAngleSpeed=Emo_AngleSpeed;
//    Emo_AngleSpeed += ((Emo_gyro_z-ZeroDrift_gyro_z) * GYRO_SENS)*dt;
//    Emo_Angle = Emo_AngleSpeed*K+Emo_LastAngleSpeed*(1-K);                //����Ϊ��
//    Emo_Angle = Emo_Angle > Emo_Angle_Max ? Emo_Angle_Max : Emo_Angle;
//    Emo_Angle = Emo_Angle < Emo_Angle_Min ? Emo_Angle_Min : Emo_Angle;
//    Emo_Angle = -Emo_Angle;
//}
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      �����ǽǶ�����
////  @param
////  @param
////  @param
////  @param
////  @return     void
////  @note
////-------------------------------------------------------------------------------------------------------------------
//void Clear_Gyroscope_Pitch(void)
//{
//    Emo_PitchSpeed = 0;
//    Emo_Pitch = 0;
//    Emo_LastPitchSpeed = 0;
//    Emo_gyro_y = 0;
//}
////-------------------------------------------------------------------------------------------------------------------
////  @brief      ƫ���ǽǶ�����
////  @param
////  @param
////  @param
////  @param
////  @return     void
////  @note
////-------------------------------------------------------------------------------------------------------------------
void Clear_Gyroscope_Angle(void)
{
//    Emo_LastAngleSpeed = 0;
//    Emo_AngleSpeed = 0;
//    Emo_gyro_z = 0;
//    Emo_Angle = 0;
//    Gyroscope_Time_Clear();
}
