#include "zf_common_headfile.h"
#include "isr.h"
#include "PID.h"

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
       if(pid2->output>1100)//��������
    {
       if(pid1->output>0)
       {
       PWM[2]=pid2->output;
       PWM[3]=pid2->output+(pid1->output);
       pwm_set_duty(MOTOR_PWM_L,PWM[2]);
       pwm_set_duty(MOTOR_PWM_R,PWM[3]);
       }
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
       else if(pid2->output<1100)//��������
          {
             if(pid1->output>0)
             {
             PWM[2]=1;
             PWM[3]=1200+(pid1->output);
             pwm_set_duty(MOTOR_PWM_L,PWM[2]);
             pwm_set_duty(MOTOR_PWM_R,PWM[3]);
             }
             else if(pid1->output<=0)
             {
             PWM[2]=1200-(pid1->output);
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
   else if(pid1->output<0)//���پ��ߣ����ｫpid2д����pid1����֪��ΪʲôЧ������һ��
     {
         if(pid1->output>=0)
         {
         PWM[2]=0;
         PWM[3]=950+(pid1->output);
         pwm_set_duty(MOTOR_PWM_L,PWM[2]);
         pwm_set_duty(MOTOR_PWM_R,PWM[3]);
         }
         else if(pid1->output<0)
         {
         PWM[2]=950-(pid1->output);
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
