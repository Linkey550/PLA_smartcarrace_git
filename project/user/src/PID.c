#include "zf_common_headfile.h"
#include "isr.h"
#include "PID.h"

float PID[3]= {10,0,0};//三个系数
float error = 0, lastError = 0;//当前误差、上次误差
//float integral, maxIntegral;//积分、积分限幅
float output;
//float maxOutput=300;
//float minOutput=0;//输出、输出限幅上限
int pwm = 0;
float iError = 0;

#define MOTOR_PWM_R                 (TIM2_PWM_MAP0_CH1_A0)
#define MOTOR_DIR_R                 (A1)
#define MOTOR_DIR_L                 (A2)
#define MOTOR_PWM_L                 (TIM2_PWM_MAP0_CH4_A3)



//用于初始化pid参数的函数
void PID_Init(PID_struct *pid,float p,float i,float d,float maxI,float maxOut)
{
    pid->kp=p;
    pid->ki=i;
    pid->kd=d;
    pid->maxIntegral=maxI;
    pid->maxOutput=maxOut;
}

//进行一次pid计算
//参数为(pid结构体,目标值,反馈值)，计算结果放在pid结构体的output成员中
void PID_Calc(PID_struct *pid,float reference,float feedback)
{
    //更新数据
    pid->lastError=pid->error;//将旧error存起来
    pid->error=reference-feedback;//计算新error
    //计算微分
    float dout=(pid->error-pid->lastError)*pid->kd;
    //计算比例
    float pout=pid->error*pid->kp;
    //计算积分
    pid->integral+=pid->error*pid->ki;
    //积分限幅
    if(pid->integral > pid->maxIntegral) pid->integral=pid->maxIntegral;
    else if(pid->integral < -pid->maxIntegral) pid->integral=-pid->maxIntegral;
    //计算输出
    pid->output=pout+dout+pid->integral;
    //输出限幅
    if(pid->output > pid->maxOutput) pid->output=pid->maxOutput;
    if(pid->output < -pid->maxOutput) pid->output=-pid->maxOutput;
}

/*!
 *  @brief      对输出参数限幅
 *  @since      v1.0
 *  min :       最小值
 *  max:       最大值
 */
//void xianfu(PID_struct *pid,int32 min,int32 max)
//{
//    if(pid->output > max )pid->output = max;
//    if(pid->output < max))pid->output = min;
//
//}



/*!
 *  @brief      位置式PID
 *  @since      v1.0
 *  *sptr ：误差参数
 *  *pid:  PID参数
 *  NowPlace：当前位置
 *  Point：   预期位置
 */

// 位置式PID控制
void PID_Realize(PID_struct *pid, float NowPlace, float Point)
{

    float iError,   // 当前误差
         Realize;   //实际输出

    iError = Point - NowPlace;  // 计算当前误差
    pid->integral += pid->ki * iError; // 误差积分
    pid->integral = pid->integral > pid->maxIntegral?pid->maxIntegral:pid->integral;//积分限幅
    pid->integral = pid->integral <-pid->maxIntegral?-pid->maxIntegral:pid->integral;
    Realize = pid->kp * iError       //比例P
            + pid->integral   //积分I
            + pid->kd * (iError - pid->lastError);  //微分D
    pid->lastError = iError;
    pid->output=Realize;// 更新上次误差
    if(pid->output > pid->maxOutput) pid->output=pid->maxOutput;
    if(pid->output < -pid->maxOutput) pid->output=-pid->maxOutput;
    //return Realize; // 返回实际值
}

/*!
 *  @brief      PID结果赋值到电机
 *  @since      v1.0
 *  *pid1 ：速度环结构体
 *  *pid2:  位置环结构体
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




