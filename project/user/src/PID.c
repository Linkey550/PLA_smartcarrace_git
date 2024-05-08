#include "zf_common_headfile.h"
#include "isr.h"
#include "PID.h"

float PID[3]= {10,0,0};//����ϵ��
float error = 0, lastError = 0;//��ǰ���ϴ����
//float integral, maxIntegral;//���֡������޷�
float output;
//float maxOutput=300;
//float minOutput=0;//���������޷�����
int pwm = 0;
float iError = 0;

#define MOTOR_PWM_R                 (TIM2_PWM_MAP0_CH1_A0)
#define MOTOR_DIR_R                 (A1)
#define MOTOR_DIR_L                 (A2)
#define MOTOR_PWM_L                 (TIM2_PWM_MAP0_CH4_A3)



//���ڳ�ʼ��pid�����ĺ���
void PID_Init(PID_struct *pid,float p,float i,float d,float maxI,float maxOut)
{
    pid->kp=p;
    pid->ki=i;
    pid->kd=d;
    pid->maxIntegral=maxI;
    pid->maxOutput=maxOut;
}

//����һ��pid����
//����Ϊ(pid�ṹ��,Ŀ��ֵ,����ֵ)������������pid�ṹ���output��Ա��
void PID_Calc(PID_struct *pid,float reference,float feedback)
{
    //��������
    pid->lastError=pid->error;//����error������
    pid->error=reference-feedback;//������error
    //����΢��
    float dout=(pid->error-pid->lastError)*pid->kd;
    //�������
    float pout=pid->error*pid->kp;
    //�������
    pid->integral+=pid->error*pid->ki;
    //�����޷�
    if(pid->integral > pid->maxIntegral) pid->integral=pid->maxIntegral;
    else if(pid->integral < -pid->maxIntegral) pid->integral=-pid->maxIntegral;
    //�������
    pid->output=pout+dout+pid->integral;
    //����޷�
    if(pid->output > pid->maxOutput) pid->output=pid->maxOutput;
    if(pid->output < -pid->maxOutput) pid->output=-pid->maxOutput;
}

/*!
 *  @brief      ����������޷�
 *  @since      v1.0
 *  min :       ��Сֵ
 *  max:       ���ֵ
 */
//void xianfu(PID_struct *pid,int32 min,int32 max)
//{
//    if(pid->output > max )pid->output = max;
//    if(pid->output < max))pid->output = min;
//
//}



/*!
 *  @brief      λ��ʽPID
 *  @since      v1.0
 *  *sptr ��������
 *  *pid:  PID����
 *  NowPlace����ǰλ��
 *  Point��   Ԥ��λ��
 */

// λ��ʽPID����
void PID_Realize(PID_struct *pid, float NowPlace, float Point)
{

    float iError,   // ��ǰ���
         Realize;   //ʵ�����

    iError = Point - NowPlace;  // ���㵱ǰ���
    pid->integral += pid->ki * iError; // ������
    pid->integral = pid->integral > pid->maxIntegral?pid->maxIntegral:pid->integral;//�����޷�
    pid->integral = pid->integral <-pid->maxIntegral?-pid->maxIntegral:pid->integral;
    Realize = pid->kp * iError       //����P
            + pid->integral   //����I
            + pid->kd * (iError - pid->lastError);  //΢��D
    pid->lastError = iError;
    pid->output=Realize;// �����ϴ����
    if(pid->output > pid->maxOutput) pid->output=pid->maxOutput;
    if(pid->output < -pid->maxOutput) pid->output=-pid->maxOutput;
    //return Realize; // ����ʵ��ֵ
}

/*!
 *  @brief      PID�����ֵ�����
 *  @since      v1.0
 *  *pid1 ���ٶȻ��ṹ��
 *  *pid2:  λ�û��ṹ��
 */


void PID_DirveUse(PID_struct *pid1,PID_struct *pid2)
{
   if(pid2->output>=0)
   {
       if(pid2->output>1100)
    {
       if(pid1->output>0)
       {
       PWM[2]=pid2->output;
       PWM[3]=pid2->output+(pid1->output);
       pwm_set_duty(MOTOR_PWM_L,PWM[2]);
       pwm_set_duty(MOTOR_PWM_R,PWM[3]);
       }
//       else if(pid1->output<1500&&pid1->output>0)
//              {
//              PWM[2]=pid2->output;
//              PWM[3]=pid2->output+(pid1->output);
//              pwm_set_duty(MOTOR_PWM_L,PWM[2]);
//              pwm_set_duty(MOTOR_PWM_R,PWM[3]);
//              }
       else if(pid1->output<=0)
       {
       PWM[2]=pid2->output-(pid1->output);
       PWM[3]=pid2->output;
       pwm_set_duty(MOTOR_PWM_L,PWM[2]);
       pwm_set_duty(MOTOR_PWM_R,PWM[3]);
       }
       else{
        PWM[2]=pid2->output;
        PWM[3]=pid2->output;
        pwm_set_duty(MOTOR_PWM_L,PWM[2]);
        pwm_set_duty(MOTOR_PWM_R,PWM[3]);
        }
     }
       else if(pid2->output<1100)
          {
             if(pid1->output>0)
             {
             PWM[2]=1;
             PWM[3]=1000+(pid1->output);
             pwm_set_duty(MOTOR_PWM_L,PWM[2]);
             pwm_set_duty(MOTOR_PWM_R,PWM[3]);
             }
      //       else if(pid1->output<1500&&pid1->output>0)
      //              {
      //              PWM[2]=pid2->output;
      //              PWM[3]=pid2->output+(pid1->output);
      //              pwm_set_duty(MOTOR_PWM_L,PWM[2]);
      //              pwm_set_duty(MOTOR_PWM_R,PWM[3]);
      //              }
             else if(pid1->output<=0)
             {
             PWM[2]=1000-(pid1->output);
             PWM[3]=1;
             pwm_set_duty(MOTOR_PWM_L,PWM[2]);
             pwm_set_duty(MOTOR_PWM_R,PWM[3]);
             }
             else{
              PWM[2]=pid2->output;
              PWM[3]=pid2->output;
              pwm_set_duty(MOTOR_PWM_L,PWM[2]);
              pwm_set_duty(MOTOR_PWM_R,PWM[3]);
              }
           }
    }
   else if(pid1->output<0)
     {
         if(pid1->output>=0)
         {
         PWM[2]=0;
         PWM[3]=1200+(pid1->output);
         pwm_set_duty(MOTOR_PWM_L,PWM[2]);
         pwm_set_duty(MOTOR_PWM_R,PWM[3]);
         }
         else if(pid1->output<0)
         {
         PWM[2]=1200-(pid1->output);
         PWM[3]=0;
         pwm_set_duty(MOTOR_PWM_L,PWM[2]);
         pwm_set_duty(MOTOR_PWM_R,PWM[3]);
         }
         else{
          PWM[2]=0;
          PWM[3]=0;
          pwm_set_duty(MOTOR_PWM_L,PWM[2]);
          pwm_set_duty(MOTOR_PWM_R,PWM[3]);
         }
     }
}





//void PID_lgs(float NowPlace, float Point)
//{
//
//    error = NowPlace - Point ;
//    if(error<5 && error>-5) iError += PID[1] * error;  if(iError >=200) iError =200;    else if(iError <=-200) iError =-200;
//
//    pwm = PID[0]  * error + PID[1] * iError;
//
////    if(erro >0 && erro_last < 0)        pwm += Kd * (erro_last - erro);
////    else if (erro <0 && erro_last > 0)     pwm += Kd * (erro_last - erro);
//
//    if(error >0 && lastError < 0)        pwm +=0;
//    else if (error <0 && lastError > 0)     pwm += 0;
//    else pwm += PID[2] * (error-lastError);
//
//    if(error >0 &&pwm <0) pwm = 0;
//    else if(error <0 && pwm >0) pwm = 0;
//
//    if(pwm >280) pwm = 280; else if(pwm<-280)pwm = -280;
//
//    if(pwm > 0)
//    {
//       pwm_set_duty(PWM_CH2,720 );
//       pwm_set_duty(PWM_CH1,720 + pwm );
//
//    }
//    else if (pwm < 0)
//    {
//        pwm_set_duty(PWM_CH2,720 - pwm );
//        pwm_set_duty(PWM_CH1,720  );
//    }
//    lastError = error;
//
//
//}




