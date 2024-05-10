#include "zf_common_headfile.h"
#include "cam.h"
#include "PID.h"
#include "main.h"
#include "Encoder_c.h"
#include "Gyroscope_c.h"


//wifi

#define WIFI_SSID_TEST          "ppFFS"
#define WIFI_PASSWORD_TEST      "lhr040210" // �����Ҫ���ӵ�WIFI û����������Ҫ�� ���� �滻Ϊ NULL


//����һ������test

#define CHANNEL_NUMBER          (4)

#define MOTOR_PWM_R                 (TIM2_PWM_MAP0_CH1_A0)
#define MOTOR_DIR_R                 (A1)
#define MOTOR_DIR_L                 (A2)
#define MOTOR_PWM_L                 (TIM2_PWM_MAP0_CH4_A3)

#define BLDC_PIN_R                (TIM1_PWM_MAP3_CH1_E9)
#define BLDC_PIN_L                (TIM1_PWM_MAP3_CH2_E11)

#define PIT_CH                  (TIM3_PIT )                                      // ʹ�õ������жϱ�� ����޸� ��Ҫͬ����Ӧ�޸������жϱ���� isr.c �еĵ���
#define PIT_PRIORITY            (TIM3_IRQn)                                      // ��Ӧ�����жϵ��жϱ��

//#define ENCODER_QUADDEC                 (TIM10_ENCOEDER)                         // ������������Ӧʹ�õı������ӿ� ����ʹ��QTIMER1��ENCOEDER1
//#define ENCODER_QUADDEC_A               (TIM10_ENCOEDER_MAP3_CH2_D3)             // A ���Ӧ������
//#define ENCODER_QUADDEC_B               (TIM10_ENCOEDER_MAP3_CH1_D1)             // B ���Ӧ������

#define KEY1                    (D8 )                                           // ʹ�õ��ⲿ�ж��������� ����޸� ��Ҫͬ����Ӧ�޸��ⲿ�жϱ���� isr.c �еĵ���
#define KEY2                    (B12)                                           // ʹ�õ��ⲿ�ж��������� ����޸� ��Ҫͬ����Ӧ�޸��ⲿ�жϱ���� isr.c �еĵ���



#define KEY1_EXTI               (EXTI9_5_IRQn)                                  // ��Ӧ�ⲿ�жϵ��жϱ��
#define KEY2_EXTI               (EXTI15_10_IRQn)                                // ��Ӧ�ⲿ�жϵ��жϱ��

int16 encoder_data_quaddec = 0;
//float encoder_data_quaddec_float= 0; //����������
float encoder_data_quaddec_v = 0;                                                //ת��
float encoder_point= 0;

uint16 pit_time=0;     //�жϼ�ʱ1ms

//int16 duty = 0;
//uint8 channel_index = 0;
//pwm_channel_enum channel_list[CHANNEL_NUMBER] = {PWM_CH1, PWM_CH2};

uint8 get_date_uart8 = 0;//���������ݽ��ջ���
uint8 get_date_uart7 = 0;//���Խ��ջ���
uint8 uart8_buff[20]={0};//���������ݻ���
int uart8_buff_i=0;//�����������α�
uint8 uart7_buff[50]={0};//�������ݻ���
int uart7_buff_i=0;//���������α�

float Point=0;//pidĿ��
int pid_ang_switch=0;//pid����
int pid_v_switch=0;//pid����
int pid_switch=0;//pid����
int pid_canmer=0;//pid����

float PWM[4]={0,0,0,0};//�������
//float ang[5]={0};//Roll,Pitch,Yaw
float angv[3]={0};//Roll_v,Pitch_v,Yaw_v
u8 tail[4]={0x00, 0x00, 0x80, 0x7f};//��β



PID_struct camera_pid;            //����ͷpid�ṹ��(�⻷pid)
PID_struct angv_pid;            //�����ǽ��ٶ�pid�ṹ��(�ڻ�pid)
PID_struct speed_pid;            //�ٶȻ�pid�ṹ��(�ٶȻ�pid)

extern cam_parameter camera_p;

int main (void)
{
    clock_init(SYSTEM_CLOCK_144M);      // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 144MHz
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    // �˴���д�û����� ���������ʼ�������


    pwm_init(MOTOR_PWM_R, 17000, 0);                                                  // ��ʼ�� �ҵ��pwm ͨ�� Ƶ�� 17KHz ��ʼռ�ձ� 0%
    pwm_init(MOTOR_PWM_L, 17000, 0);                                                  // ��ʼ������pwm ͨ�� Ƶ�� 17KHz ��ʼռ�ձ� 0%
    gpio_init(MOTOR_DIR_R, GPO, GPIO_LOW, GPO_PUSH_PULL);                              // ��ʼ�� �ҵ��ʹ�� ��� Ĭ�ϵ͵�ƽ �������ģʽ
    gpio_init(MOTOR_DIR_L, GPO, GPIO_LOW, GPO_PUSH_PULL);                              // ��ʼ�� ����ʹ�� ��� Ĭ�ϵ͵�ƽ �������ģʽ

 //   exti_init(KEY1, EXTI_TRIGGER_FALLING);                                       // ��ʼ�� KEY1 Ϊ�ⲿ�ж����� �����ش���
    exti_init(KEY1, EXTI_TRIGGER_FALLING);                                      // ��ʼ�� KEY2 Ϊ�ⲿ�ж����� �½��ش���
    exti_init(KEY2, EXTI_TRIGGER_FALLING);                                         // ��ʼ�� KEY3 Ϊ�ⲿ�ж����� ˫���ش���

    interrupt_set_priority(KEY1_EXTI, (0<<5) || 1);                             // ���� KEY1 ��Ӧ�ⲿ�жϵ��ж���ռ���ȼ�0�������ȼ�1
    interrupt_set_priority(KEY2_EXTI, (0<<5) || 1);                           // ���� KEY2 ��Ӧ�ⲿ��

    pwm_init(BLDC_PIN_R, 50, 0);                                                   // ��ʼ�� ����ˢ���pwm ͨ�� Ƶ�� 17KHz ��ʼռ�ձ� 0%
    pwm_init(BLDC_PIN_L, 50, 0);                                                   // ��ʼ�� ����ˢ���pwm ͨ�� Ƶ�� 17KHz ��ʼռ�ձ� 0%

    encoder_quad_init(ENCODER_QUADDEC, ENCODER_QUADDEC_A, ENCODER_QUADDEC_B);   // ��ʼ��������ģ�������� �������������ģʽ

    PID_Init(&camera_pid, 23, 0, 12, 300, 250);                                   //��ʼ���⻷pid
    PID_Init(&angv_pid,11, 0, 1, 50, 1200);                                     //��ʼ���ڻ�pid
    PID_Init(&speed_pid, 10000, 0, 2, 300, 4300);                                    //��ʼ���ٶȻ�pid

    pit_ms_init(PIT_CH, 100);                                                   // ��ʼ�� PIT_CH0 Ϊ�����ж� 100ms ����
    interrupt_set_priority(PIT_PRIORITY, 0);                                    // ���� PIT1 �������жϵ��ж����ȼ�Ϊ 0

    uart_init(UART_8, 115200, UART8_MAP3_TX_E14, UART8_MAP3_RX_E15);            //�����ǳ�ʼ��
    uart_init(UART_7, 115200, UART7_MAP3_TX_E12, UART7_MAP3_RX_E13);            //��λ�����Գ�ʼ��
    uart_rx_interrupt(UART_7, ZF_ENABLE);                                       //��λ������
    uart_rx_interrupt(UART_8, ZF_ENABLE);                                       //������

    YJ901S_init();                                                              //�����ǽ��ٶ�У׼

    mt9v03x_init();
   wifi_spi();
   seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIFI_SPI);

    while(1)
    {
        seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, Emo_imag[0], MT9V03X_W, MT9V03X_H);//�������ͨ������
        seekfree_assistant_camera_boundary_config(X_BOUNDARY, MT9V03X_H, Left_Black_Point, Middle_Black_Point, Right_Black_Point, NULL, NULL ,NULL);//�������ͨ��
        mt9v03x_finish_flag = 0;//����ͷ�ɼ����
        seekfree_assistant_camera_send();//��λ����ʾͼ��
    }

}
//�������
void pit_handler (void)
{
   //ת��,���ٶ�
    if(pid_switch==1)
    {
//        Camera_Head();
//     PID_Calc(&camera_pid, CentralValue, averageX.T_X);   //����ͷ��ȡ���ݲ����pid
      //�⻷pid 10msһ��
     // printf("%d",camera_p.T_X);
      PID_Realize(&camera_pid,camera_p.T_X ,camera_p.N_X);//�⻷pid
      PID_Realize(&angv_pid,angv[2],camera_pid.output);//�ڻ�pid 1msһ��

    }


    encoder_data_quaddec = encoder_get_count(ENCODER_QUADDEC);                  // ��ȡ����������
    encoder_clear_count(ENCODER_QUADDEC);                                       // ��ձ���������
    encoder_data_quaddec_v=(encoder_data_quaddec/4096.0)/0.1;                   //ת�ټ���
//    Real_Distance += encoder_data_quaddec*0.0444;
    //�ٶȻ�
    if(pid_switch==1)
    {
  //      encoder_point=1-(0.7*abs(angv[2]/250));                                    //Ŀ���ٶȼ���
      encoder_point=1;                                    //Ŀ���ٶȼ���
        PID_Realize(&speed_pid,encoder_data_quaddec_v,encoder_point);               //�ٶȻ�pid
        PID_DirveUse(&angv_pid,&speed_pid);//��ֵ�����
    }


//ͣ��
    if(camera_p.Garage_In_flag==1)
      {
          pit_time++;//��ʱ
          if(pit_time>= 30)
          {//��ʱ
          pid_switch=0;
          PWM[0]=0;
          PWM[1]=0;
          PWM[2]=0;
          PWM[3]=0;
          pwm_set_duty(BLDC_PIN_L,PWM[0]);
          pwm_set_duty(BLDC_PIN_R,PWM[1]);
          pwm_set_duty(MOTOR_PWM_L,PWM[2]);
          pwm_set_duty(MOTOR_PWM_R,PWM[3]);

          }
      }
  //  encoder_data_quaddec_float=(float)encoder_data_quaddec;

    //��λ������
    Send_data(UART7, PWM,sizeof(float)*4);//pwm
    Send_data(UART7, &angv[2],sizeof(float));//���ٶ�
    Send_data(UART7, &camera_p.T_X,sizeof(float));//Ŀ��ֵ
    Send_data(UART7, &camera_p.N_X,sizeof(float));//Ŀ��ֵ
//    Send_data(UART7, &camera_pid.output,sizeof(float));//Ŀ��ֵ
//    Send_data(UART7, &angv_pid.output,sizeof(float));//Ŀ��ֵ
//    Send_data(UART7, &speed_pid.output,sizeof(float));//Ŀ��ֵ
////    Send_data(UART7,&encoder_data_quaddec_float,sizeof(float));//����������ֵ
//    Send_data(UART7,&encoder_data_quaddec_v,sizeof(float));//�������ٶ�
//    Send_data(UART7,&encoder_point,sizeof(float));//�������ٶ�
//    Send_data(UART7,&(camera_pid.kp),sizeof(float));//P
//    Send_data(UART7,&(camera_pid.ki),sizeof(float));//I
//    Send_data(UART7,&(camera_pid.kd),sizeof(float));//D
//    Send_data(UART7,&(angv_pid.kp),sizeof(float));//P
//    Send_data(UART7,&(angv_pid.ki),sizeof(float));//I
//    Send_data(UART7,&(angv_pid.kd),sizeof(float));//D
//    Send_data(UART7,&(speed_pid.kp),sizeof(float));//P
//    Send_data(UART7,&(speed_pid.ki),sizeof(float));//I
//    Send_data(UART7,&(speed_pid.kd),sizeof(float));//D
    Send_data(UART7,&Garagecount,sizeof(float));//encoder_data_quaddec
    Send_data(UART7,&camera_p.Garage_In_flag,sizeof(float));
    Send_data(UART7,&camera_p.test1_flag,sizeof(float));
    Send_data(UART7,&camera_p.test2_flag,sizeof(float));
    Send_data(UART7,&CircleLeft_flag,sizeof(float));
    Send_data(UART7,&CircleRight_flag,sizeof(float));
//    Send_data(UART7,&Garage_flag,sizeof(float));
//
//
//    Send_data(UART7,&(Left_Down_Point[0]),sizeof(float));
//    Send_data(UART7,&(Right_Down_Point[1]),sizeof(float));
    Send_data(UART7, tail,4);//��β


}

//uart7-���Դ���
void uart7_rx_interrupt_handler (void)
{
    uart_query_byte(UART_7, &get_date_uart7);// �������� ��ѯʽ �����ݻ᷵�� TRUE û�����ݻ᷵�� FALSE
    switch(get_date_uart7)
    {
        case 0xc0:
            camera_pid.kp +=1;
        break;
        case 0xc1:
            camera_pid.kp -=1;
        break;
        case 0xc2:
            camera_pid.ki +=0.1;
        break;
        case 0xc3:
            camera_pid.ki -=0.1;
        break;
        case 0xc4:
            camera_pid.kd +=0.1;
        break;
        case 0xc5:
            camera_pid.kd -=0.1;
        break;
    }
    if(get_date_uart7 == 0x0A )
    {
        char directives[20]={0};
        int  target_value=0;
        sscanf(uart7_buff, "%[^:]:%d ", directives, &target_value);//��ȡָ���ֵ
        if(!strcmp(directives,"chaR"))//�ҵ��̿���
        {
            PWM[0]=target_value;
            pwm_set_duty(BLDC_PIN_R,PWM[0]);
        }
        else if(!strcmp(directives,"chaL"))//����̿���
              {
                  PWM[1]=target_value;
                  pwm_set_duty(BLDC_PIN_L,PWM[1]);
              }
        else if(!strcmp(directives,"gasR"))//����̿���
              {
                  PWM[2]=target_value;
                  pwm_set_duty(MOTOR_PWM_L,PWM[2]);
              }
        else if(!strcmp(directives,"stop"))//��ͣ
        {
            PWM[0]=0;
            PWM[1]=0;
            PWM[2]=0;
            PWM[3]=0;
            pwm_set_duty(BLDC_PIN_L,PWM[0]);
            pwm_set_duty(BLDC_PIN_R,PWM[1]);
            pwm_set_duty(MOTOR_PWM_L,PWM[2]);
            pwm_set_duty(MOTOR_PWM_R,PWM[3]);
            pid_switch=0;
        }
        else if(!strcmp(directives,"start"))//����
                {
                    PWM[0]=600;
                    PWM[1]=600;
                    pwm_set_duty(BLDC_PIN_L,PWM[0]);
                    pwm_set_duty(BLDC_PIN_R,PWM[1]);
                    system_delay_ms(10);
                    PWM[0]=800;
                    PWM[1]=803;
                    pwm_set_duty(BLDC_PIN_L,PWM[0]);
                    pwm_set_duty(BLDC_PIN_R,PWM[1]);


                        pid_switch=1;
                }
        else if(!strcmp(directives,"c_p"))//P
                {
                    camera_pid.kp=target_value;
                }
        else if(!strcmp(directives,"c_i"))//I
                {
                    camera_pid.ki=target_value;
                }
        else if(!strcmp(directives,"c_d"))//D
                {
                    camera_pid.kd=target_value;
                }
        else if(!strcmp(directives,"a_p"))//P
                {
                    angv_pid.kp=target_value;
                }
        else if(!strcmp(directives,"a_i"))//I
                {
                    angv_pid.ki=target_value;
                }
        else if(!strcmp(directives,"a_d"))//D
                {
                    angv_pid.kd=target_value;
                }
        else if(!strcmp(directives,"s_p"))//P
                {
                    speed_pid.kp=target_value;
                }
        else if(!strcmp(directives,"s_i"))//I
                {
                    speed_pid.ki=target_value;
                }
        else if(!strcmp(directives,"s_d"))//D
                {
                    speed_pid.kd=target_value;
                }

       //��ջ�����
       uart7_buff_i=0;
       memset(uart7_buff, 0x00, sizeof( uart7_buff ));
    }
    else {
        uart7_buff[uart7_buff_i]=get_date_uart7;
        uart7_buff_i++;
    }

}
//uart8-�����Ǵ����ж�
void uart_rx_interrupt_handler()
{
         uart_query_byte(UART_8, &get_date_uart8);// �������� ��ѯʽ �����ݻ᷵�� TRUE û�����ݻ᷵�� FALSE
         if(uart8_buff_i>=0&&uart8_buff_i<11)
         {
             uart8_buff[uart8_buff_i]=get_date_uart8;
             uart8_buff_i++;
             if(uart8_buff[0]!=0x55){
                 uart8_buff_i=0;
                 memset(uart8_buff, 0x00, sizeof( uart8_buff ));
             }
             else {
//               if(uart8_buff[10]==((uart8_buff[0]+uart8_buff[1]+uart8_buff[2]+uart8_buff[3]+uart8_buff[4]+uart8_buff[5]+uart8_buff[6]+uart8_buff[7]+uart8_buff[8]+uart8_buff[9])&0xff)){
//                    ang[0]=(((int16)(uart8_buff[3]<<8)|uart8_buff[2])/32768.0)*180.0;
//                    ang[1]=(((int16)(uart8_buff[5]<<8)|uart8_buff[4])/32768.0)*180.0;
//                    ang[2]=(((int16)(uart8_buff[7]<<8)|uart8_buff[6])/32768.0)*180.0;
//                    uart8_buff_i=0;
//                    memset(uart8_buff, 0x00, sizeof( uart8_buff ));
//               }
                if(uart8_buff[10]==((uart8_buff[0]+uart8_buff[1]+uart8_buff[2]+uart8_buff[3]+uart8_buff[4]+uart8_buff[5]+uart8_buff[6]+uart8_buff[7]+uart8_buff[8]+uart8_buff[9])&0xff)){
//                     angv[0]=(((int16)(uart8_buff[3]<<8)|uart8_buff[2])/32768.0)*2000.0; //xv
//                     angv[1]=(((int16)(uart8_buff[5]<<8)|uart8_buff[4])/32768.0)*2000.0;//yv
                     angv[2]=(((int16)(uart8_buff[7]<<8)|uart8_buff[6])/32768.0)*2000.0;//zv
                     uart8_buff_i=0;
                     memset(uart8_buff, 0x00, sizeof( uart8_buff ));
                }

            }
         }
         else {
             uart8_buff_i=0;
             memset(uart8_buff, 0x00, sizeof( uart8_buff ));
        }
}



//-------------------------------------------------------------------------------------------------------------------
// �������     KEY1 �İ����ⲿ�жϴ����� ����������� KEY1 ���Ŷ�Ӧ���ⲿ�жϵ��� ��� isr.c
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     key1_exti_handler();
//-------------------------------------------------------------------------------------------------------------------
void key1_exti_handler (void)
{
    // �����ش����������жϵ�ʱ��GPIO״̬�Ǹߵ�ƽ��
    if(gpio_get_level(KEY1) == 0)
    {
        PWM[0]=600;
        PWM[1]=600;
        pwm_set_duty(BLDC_PIN_L,PWM[0]);
        pwm_set_duty(BLDC_PIN_R,PWM[1]);
        system_delay_ms(10);
        PWM[0]=800;
        PWM[1]=803;
        pwm_set_duty(BLDC_PIN_L,PWM[0]);
        pwm_set_duty(BLDC_PIN_R,PWM[1]);
        pid_switch=1;
    }

}

//-------------------------------------------------------------------------------------------------------------------
// �������     KEY2 �İ����ⲿ�жϴ����� ����������� KEY2 ���Ŷ�Ӧ���ⲿ�жϵ��� ��� isr.c
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     key2_exti_handler();
//-------------------------------------------------------------------------------------------------------------------
void key2_exti_handler (void)
{
    if(gpio_get_level(KEY2) == 0)
    {
        PWM[0]=0;
        PWM[1]=0;
        PWM[2]=0;
        PWM[3]=0;
        pwm_set_duty(BLDC_PIN_L,PWM[0]);
        pwm_set_duty(BLDC_PIN_R,PWM[1]);
        pwm_set_duty(MOTOR_PWM_L,PWM[2]);
        pwm_set_duty(MOTOR_PWM_R,PWM[3]);
        pid_switch=0;
    }
}




void wifi_spi(void)
{    //wifi��ʼ��
    while(wifi_spi_init(WIFI_SSID_TEST, WIFI_PASSWORD_TEST))
               {
                   printf("\r\n connect wifi failed. \r\n");
                   system_delay_ms(100);                                                   // ��ʼ��ʧ�� �ȴ� 100ms
               }
    // zf_device_wifi_spi.h �ļ��ڵĺ궨����Ը���ģ������(����) WIFI ֮���Ƿ��Զ����� TCP ������������ UDP ���ӡ����� TCP �������Ȳ���
    if(1 != WIFI_SPI_AUTO_CONNECT)                                              // ���û�п����Զ����� ����Ҫ�ֶ�����Ŀ�� IP
    {
        while(wifi_spi_socket_connect(                                          // ��ָ��Ŀ�� IP �Ķ˿ڽ��� TCP ����
                                    "TCP",                                                              // ָ��ʹ��TCP��ʽͨѶ
                                    WIFI_SPI_TARGET_IP,                                                 // ָ��Զ�˵�IP��ַ����д��λ����IP��ַ
                                    WIFI_SPI_TARGET_PORT,                                               // ָ��Զ�˵Ķ˿ںţ���д��λ���Ķ˿ںţ�ͨ����λ��Ĭ����8080
                                    WIFI_SPI_LOCAL_PORT))                                               // ָ�������Ķ˿ں�
                   {
                       // ���һֱ����ʧ�� ����һ���ǲ���û�н�Ӳ����λ
                       printf("\r\n Connect TCP Servers error, try again.");
                       system_delay_ms(100);                                               // ��������ʧ�� �ȴ� 100ms
                   }
               }
}




