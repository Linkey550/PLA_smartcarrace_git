#include "zf_common_headfile.h"
#include "cam.h"
#include "PID.h"
#include "main.h"
#include "Encoder_c.h"
#include "Gyroscope_c.h"

//wifi

#define WIFI_SSID_TEST          "ppFFS"
#define WIFI_PASSWORD_TEST      "lhr040210"                                    // 如果需要连接的WIFI 没有密码则需要将 这里 替换为 NULL

#define FLASH_SECTION_INDEX       (63)                                          // flash存储数据用的扇区 倒数第一个扇区
#define FLASH_PAGE_INDEX          (3)                                           // falsh存储数据用的页码 倒数第一个页码

#define CHANNEL_NUMBER          (4)

#define MOTOR_PWM_R                 (TIM2_PWM_MAP0_CH1_A0)
#define MOTOR_DIR_R                 (A1)
#define MOTOR_DIR_L                 (A2)
#define MOTOR_PWM_L                 (TIM2_PWM_MAP0_CH4_A3)                       //后轮电机的引脚定义

#define BLDC_PIN_R                (TIM1_PWM_MAP3_CH1_E9)                    
#define BLDC_PIN_L                (TIM1_PWM_MAP3_CH2_E11)                       //无刷电机的引脚定义
 
#define PIT_CH                  (TIM3_PIT )                                      // 使用的周期中断编号 如果修改 需要同步对应修改周期中断编号与 isr.c 中的调用
#define PIT_PRIORITY            (TIM3_IRQn)                                      // 对应周期中断的中断编号

#define KEY1                    (D8 )                                           // 按键 使用的外部中断输入引脚 如果修改 需要同步对应修改外部中断编号与 isr.c 中的调用
#define KEY2                    (B12)                                           // 按键 使用的外部中断输入引脚 如果修改 需要同步对应修改外部中断编号与 isr.c 中的调用
#define KEY1_EXTI               (EXTI9_5_IRQn)                                  // 对应外部中断的中断编号
#define KEY2_EXTI               (EXTI15_10_IRQn)                                // 对应外部中断的中断编号

int16 encoder_data_quaddec = 0;                                                 //编码器获取转速
float encoder_data_quaddec_v = 0;                                               //编码器获取转速
float encoder_point= 0;

uint16 pit_time=0;                                                              //中断计时1ms

uint8 get_date_uart8 = 0;                                                       //陀螺仪数据接收缓存
uint8 get_date_uart7 = 0;                                                       //调试接收缓存
uint8 uart8_buff[20]={0};                                                       //陀螺仪数据缓存
int uart8_buff_i=0;                                                             //陀螺仪数据游标
uint8 uart7_buff[50]={0};                                                       //调试数据缓存
int uart7_buff_i=0;                                                             //调试数据游标

float Point=0;                                                                  //pid目标
int pid_ang_switch=0;                                                           //pid开关
int pid_v_switch=0;                                                             //pid开关
int pid_switch=0;                                                               //pid开关
int pid_canmer=0;                                                               //pid开关

float PWM[4]={0,0,0,0};                                                         //四个电机的转速存储方便上位机显示
float angv[3]={0};                                                              //Roll_v,Pitch_v,Yaw_v
u8 tail[4]={0x00, 0x00, 0x80, 0x7f};                                            //包尾



PID_struct camera_pid;                                                          //摄像头pid结构体(外环pid)
PID_struct angv_pid;                                                            //陀螺仪角速度pid结构体(内环pid)
PID_struct speed_pid;                                                           //速度环pid结构体(速度环pid)

extern cam_parameter camera_p;                                                  //摄像头信息传递结构体
void falsh_ReadPid(void);
void falsh_SavePid(void);                                                       //声明flash存储
                  
int main (void)
{
    clock_init(SYSTEM_CLOCK_144M);                                              // 初始化芯片时钟 工作频率为 144MHz
    debug_init();                                                               // 务必保留，本函数用于初始化MPU 时钟 调试串口
    // 此处编写用户代码 例如外设初始化代码等


    pwm_init(MOTOR_PWM_R, 17000, 0);                                                  // 初始化 右电机pwm 通道 频率 17KHz 初始占空比 0%
    pwm_init(MOTOR_PWM_L, 17000, 0);                                                  // 初始化左电机pwm 通道 频率 17KHz 初始占空比 0%
    gpio_init(MOTOR_DIR_R, GPO, GPIO_LOW, GPO_PUSH_PULL);                              // 初始化 右电机使能 输出 默认低电平 推挽输出模式
    gpio_init(MOTOR_DIR_L, GPO, GPIO_LOW, GPO_PUSH_PULL);                              // 初始化 左电机使能 输出 默认低电平 推挽输出模式

    exti_init(KEY1, EXTI_TRIGGER_FALLING);                                         // 初始化 KEY2 为外部中断输入 下降沿触发
    exti_init(KEY2, EXTI_TRIGGER_FALLING);                                         // 初始化 KEY3 为外部中断输入 下降沿触发

    interrupt_set_priority(KEY1_EXTI, (0<<5) || 1);                             // 设置 KEY1 对应外部中断的中断抢占优先级0，子优先级1
    interrupt_set_priority(KEY2_EXTI, (0<<5) || 1);                             // 设置 KEY2 对应外部中断的中断抢占优先级0，子优先级1

    pwm_init(BLDC_PIN_R, 50, 0);                                                   // 初始化 右无刷电机pwm 通道 频率 50Hz 初始占空比 0%
    pwm_init(BLDC_PIN_L, 50, 0);                                                   // 初始化 右无刷电机pwm 通道 频率 50Hz 初始占空比 0%

    encoder_quad_init(ENCODER_QUADDEC, ENCODER_QUADDEC_A, ENCODER_QUADDEC_B);   // 初始化编码器模块与引脚 正交解码编码器模式

    falsh_ReadPid();                                                            //从flash读取并初始化pid

    pit_ms_init(PIT_CH, 100);                                                   // 初始化 PIT_CH0 为周期中断 100ms 周期
    interrupt_set_priority(PIT_PRIORITY, 0);                                    // 设置 PIT1 对周期中断的中断优先级为 0

    uart_init(UART_8, 115200, UART8_MAP3_TX_E14, UART8_MAP3_RX_E15);            //陀螺仪初始化
    uart_init(UART_7, 115200, UART7_MAP3_TX_E12, UART7_MAP3_RX_E13);            //上位机调试初始化
    uart_rx_interrupt(UART_7, ZF_ENABLE);                                       //上位机调试
    uart_rx_interrupt(UART_8, ZF_ENABLE);                                       //陀螺仪

    YJ901S_init();                                                              //陀螺仪角速度校准

    mt9v03x_init();                                                             //摄像头初始化
    wifi_spi();                                                                 //wifi图传初始化
    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIFI_SPI);             //逐飞图传程序

    while(1)
    {
        seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, Emo_imag[0], MT9V03X_W, MT9V03X_H);                                //逐飞助手通信设置
        seekfree_assistant_camera_boundary_config(X_BOUNDARY, MT9V03X_H, Left_Black_Point, Middle_Black_Point, Right_Black_Point, NULL, NULL ,NULL);//逐飞助手通信
        mt9v03x_finish_flag = 0;                                                                                                                    //摄像头采集完成
        seekfree_assistant_camera_send();                                                                                                           //上位机显示图像
    }

}
//周期输出
void pit_handler (void)
{
   //转向环,角速度
    if(pid_switch==1)
    {
      PID_Realize(&camera_pid,camera_p.T_X ,camera_p.N_X);//外环pid
      PID_Realize(&angv_pid,angv[2],camera_pid.output);//内环pid 
    }

    encoder_data_quaddec = encoder_get_count(ENCODER_QUADDEC);                  // 获取编码器计数
    encoder_clear_count(ENCODER_QUADDEC);                                       // 清空编码器计数
    encoder_data_quaddec_v=(encoder_data_quaddec/4096.0)/0.1;                   //转速计算
    //速度环
    if(pid_switch==1)
    {
        encoder_point=1-(0.6*abs(angv[2]/250));                                    //目标速度计算
        PID_Realize(&speed_pid,encoder_data_quaddec_v,encoder_point);              //速度环pid
        PID_DirveUse(&angv_pid,&speed_pid);                                        //赋值到电机
    }


//停车
    if(camera_p.Garage_In_flag==1)
      {
          pit_time++;//计时
          if(pit_time>= 30)
          {//计时
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


    //上位机调试，内容都可以自定义，只要是float类型就行，包尾不能删除
    Send_data(UART7, PWM,sizeof(float)*4);//4个pwm输出
    Send_data(UART7, &angv[2],sizeof(float));//角速度
    Send_data(UART7, &camera_p.T_X,sizeof(float));//实际值
    Send_data(UART7, &camera_p.N_X,sizeof(float));//目标值
    Send_data(UART7, &camera_pid.output,sizeof(float));//摄像头pid输出
    Send_data(UART7, &angv_pid.output,sizeof(float));//角度环输出
    Send_data(UART7, &speed_pid.output,sizeof(float));//速度环输出
//    Send_data(UART7,&encoder_data_quaddec_float,sizeof(float));//编码器计数值
    Send_data(UART7,&encoder_data_quaddec_v,sizeof(float));//编码器速度
//   Send_data(UART7,&encoder_point,sizeof(float));
    Send_data(UART7,&(camera_pid.kp),sizeof(float));//摄像头P
    Send_data(UART7,&(camera_pid.ki),sizeof(float));//摄像头I
    Send_data(UART7,&(camera_pid.kd),sizeof(float));//摄像头D
    Send_data(UART7,&(angv_pid.kp),sizeof(float));//角度环P
    Send_data(UART7,&(angv_pid.ki),sizeof(float));//角度环I
    Send_data(UART7,&(angv_pid.kd),sizeof(float));//角度环D
    Send_data(UART7,&(speed_pid.kp),sizeof(float));//速度环P
    Send_data(UART7,&(speed_pid.ki),sizeof(float));//速度环I
    Send_data(UART7,&(speed_pid.kd),sizeof(float));//速度环D
    Send_data(UART7,&Garagecount,sizeof(float));//encoder_data_quaddec
    Send_data(UART7,&camera_p.Garage_In_flag,sizeof(float));
    Send_data(UART7,&camera_p.test1_flag,sizeof(float));
    Send_data(UART7,&camera_p.test2_flag,sizeof(float));
    Send_data(UART7,&CircleLeft_flag,sizeof(float));
    Send_data(UART7,&CircleRight_flag,sizeof(float));
//    Send_data(UART7,&Garage_flag,sizeof(float));
//    Send_data(UART7,&(Left_Down_Point[0]),sizeof(float));
//    Send_data(UART7,&(Right_Down_Point[1]),sizeof(float));
    Send_data(UART7, tail,4);//包尾
}

//uart7-调试串口
void uart7_rx_interrupt_handler (void)//配合vofa使用
{
    uart_query_byte(UART_7, &get_date_uart7);// 接收数据 查询式 有数据会返回 TRUE 没有数据会返回 FALSE
    if(get_date_uart7 == 0x0A ) //配合vofa使用详情请查看vofa的发送格式
    {
        char directives[20]={0};
        int  target_value=0;
        sscanf(uart7_buff, "%[^:]:%d ", directives, &target_value);//获取指令和值
        if(!strcmp(directives,"chaR"))//右底盘控制
                {
                    PWM[0]=target_value;
                    pwm_set_duty(BLDC_PIN_R,PWM[0]);
                }
        else if(!strcmp(directives,"chaL"))//左底盘控制
                {
                    PWM[1]=target_value;
                    pwm_set_duty(BLDC_PIN_L,PWM[1]);
                }
        else if(!strcmp(directives,"gasR"))//左电机控制
                {
                    PWM[2]=target_value;
                    pwm_set_duty(MOTOR_PWM_R,PWM[2]);
                }
        else if(!strcmp(directives,"gasL"))//右电机控制
                {
                    PWM[2]=target_value;
                    pwm_set_duty(MOTOR_PWM_L,PWM[3]);
                }
        else if(!strcmp(directives,"stop"))//急停
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
        else if(!strcmp(directives,"start"))//启动
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
        else if(!strcmp(directives,"c_p"))//摄像头P
                {
                    camera_pid.kp=target_value;
                }
        else if(!strcmp(directives,"c_i"))//摄像头I
                {
                    camera_pid.ki=target_value;
                }
        else if(!strcmp(directives,"c_d"))//摄像头D
                {
                    camera_pid.kd=target_value;
                }
        else if(!strcmp(directives,"a_p"))//角度环P
                {
                    angv_pid.kp=target_value;
                }
        else if(!strcmp(directives,"a_i"))//角度环I
                {
                    angv_pid.ki=target_value;
                }
        else if(!strcmp(directives,"a_d"))//角度环D
                {
                    angv_pid.kd=target_value;
                }
        else if(!strcmp(directives,"s_p"))//速度环P
                {
                    speed_pid.kp=target_value;
                }
        else if(!strcmp(directives,"s_i"))//速度环I
                {
                    speed_pid.ki=target_value;
                }
        else if(!strcmp(directives,"s_d"))//速度环D
                {
                    speed_pid.kd=target_value;
                }
        else if(!strcmp(directives,"save"))//存储pid
                  {
                      falsh_SavePid();
                  }

       //清空缓存区
       uart7_buff_i=0;
       memset(uart7_buff, 0x00, sizeof( uart7_buff ));
    }
    else {
        //意外处理
        uart7_buff[uart7_buff_i]=get_date_uart7;
        uart7_buff_i++;
    }

}
//uart8-陀螺仪处理中断，配合yj901使用，具体请看yj901的通信协议
void uart_rx_interrupt_handler()
{
         uart_query_byte(UART_8, &get_date_uart8);// 接收数据 查询式 有数据会返回 TRUE 没有数据会返回 FALSE
         if(uart8_buff_i>=0&&uart8_buff_i<11)
         {
             uart8_buff[uart8_buff_i]=get_date_uart8;
             uart8_buff_i++;
             if(uart8_buff[0]!=0x55){
                 uart8_buff_i=0;
                 memset(uart8_buff, 0x00, sizeof( uart8_buff ));
             }
             else//数据处理
              {
//               if(uart8_buff[10]==((uart8_buff[0]+uart8_buff[1]+uart8_buff[2]+uart8_buff[3]+uart8_buff[4]+uart8_buff[5]+uart8_buff[6]+uart8_buff[7]+uart8_buff[8]+uart8_buff[9])&0xff)){
//                    ang[0]=(((int16)(uart8_buff[3]<<8)|uart8_buff[2])/32768.0)*180.0;
//                    ang[1]=(((int16)(uart8_buff[5]<<8)|uart8_buff[4])/32768.0)*180.0;
//                    ang[2]=(((int16)(uart8_buff[7]<<8)|uart8_buff[6])/32768.0)*180.0;
//                    uart8_buff_i=0;
//                    memset(uart8_buff, 0x00, sizeof( uart8_buff ));
//               }
                if(uart8_buff[10]==((uart8_buff[0]+uart8_buff[1]+uart8_buff[2]+uart8_buff[3]+uart8_buff[4]+uart8_buff[5]+uart8_buff[6]+uart8_buff[7]+uart8_buff[8]+uart8_buff[9])&0xff))
                {
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
// 函数简介     KEY1 的按键外部中断处理函数 这个函数将在 KEY1 引脚对应的外部中断调用 详见 isr.c
// 参数说明     void
// 返回参数     void
// 使用示例     key1_exti_handler();
//-------------------------------------------------------------------------------------------------------------------
void key1_exti_handler (void)
{
    // 上升沿触发，进入中断的时候GPIO状态是高电平。
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
// 函数简介     KEY2 的按键外部中断处理函数 这个函数将在 KEY2 引脚对应的外部中断调用 详见 isr.c
// 参数说明     void
// 返回参数     void
// 使用示例     key2_exti_handler();
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



//wifi初始化
void wifi_spi(void)
{    //wifi初始化
    while(wifi_spi_init(WIFI_SSID_TEST, WIFI_PASSWORD_TEST))
               {
                   printf("\r\n connect wifi failed. \r\n");
                   system_delay_ms(100);                                                   // 初始化失败 等待 100ms
               }
    // zf_device_wifi_spi.h 文件内的宏定义可以更改模块连接(建立) WIFI 之后，是否自动连接 TCP 服务器、创建 UDP 连接、创建 TCP 服务器等操作
    if(1 != WIFI_SPI_AUTO_CONNECT)                                              // 如果没有开启自动连接 就需要手动连接目标 IP
    {
        while(wifi_spi_socket_connect(                                          // 向指定目标 IP 的端口建立 TCP 连接
                                    "TCP",                                                              // 指定使用TCP方式通讯
                                    WIFI_SPI_TARGET_IP,                                                 // 指定远端的IP地址，填写上位机的IP地址
                                    WIFI_SPI_TARGET_PORT,                                               // 指定远端的端口号，填写上位机的端口号，通常上位机默认是8080
                                    WIFI_SPI_LOCAL_PORT))                                               // 指定本机的端口号
                   {
                       // 如果一直建立失败 考虑一下是不是没有接硬件复位
                       printf("\r\n Connect TCP Servers error, try again.");
                       system_delay_ms(100);                                               // 建立连接失败 等待 100ms
                   }
               }
}

//falsh读
void falsh_ReadPid(void)
{
    if(flash_check(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX))                      // 判断是否有数据
    {
        flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
        camera_pid.kp= flash_union_buffer[0].float_type ;                              // 向缓冲区第 0 个位置写入 float  数据
        camera_pid.ki=flash_union_buffer[1].float_type ;                             // 向缓冲区第 1 个位置写入 uint32 数据
        camera_pid.kd=flash_union_buffer[2].float_type ;                            // 向缓冲区第 2 个位置写入 int32  数据
        camera_pid.maxIntegral=flash_union_buffer[3].float_type ;                            // 向缓冲区第 2 个位置写入 int32  数据
        camera_pid.maxOutput=flash_union_buffer[4].float_type ;                            // 向缓冲区第 2 个位置写入 int32  数据
        angv_pid.kp=flash_union_buffer[5].float_type ;                                  // 向缓冲区第 3 个位置写入 uint16 数据
        angv_pid.ki=flash_union_buffer[6].float_type ;                                 // 向缓冲区第 4 个位置写入 int16  数据
        angv_pid.kd=flash_union_buffer[7].float_type ;                                    // 向缓冲区第 5 个位置写入 uint8  数据
        angv_pid.maxIntegral=flash_union_buffer[8].float_type ;                            // 向缓冲区第 2 个位置写入 int32  数据
        angv_pid.maxOutput=flash_union_buffer[9].float_type ;                            // 向缓冲区第 2 个位置写入 int32  数据
        speed_pid.kp=flash_union_buffer[10].float_type;                                   // 向缓冲区第 6 个位置写入 int8   数据
        speed_pid.ki=flash_union_buffer[11].float_type;                                   // 向缓冲区第 6 个位置写入 int8   数据
        speed_pid.kd=flash_union_buffer[12].float_type;                                   // 向缓冲区第 6 个位置写入 int8   数据
        speed_pid.maxIntegral=flash_union_buffer[13].float_type;                            // 向缓冲区第 2 个位置写入 int32  数据
        speed_pid.maxOutput=flash_union_buffer[14].float_type;                            // 向缓冲区第 2 个位置写入 int32  数据
    }
    else {
        PID_Init(&camera_pid, 20, 0, 0, 50, 250);                                   //初始化外环pid
        PID_Init(&angv_pid,11, 0, 0, 50, 1200);                                     //初始化内环pid
        PID_Init(&speed_pid, 10000, 0, 0, 50, 4300);                                    //初始化速度环pid
    }

}

//falsh写
void falsh_SavePid(void)
{
    flash_buffer_clear();                                                       // 清空缓冲区
    flash_union_buffer[0].float_type  = camera_pid.kp;                              // 向缓冲区第 0 个位置写入 float  数据
    flash_union_buffer[1].float_type = camera_pid.ki;                             // 向缓冲区第 1 个位置写入 uint32 数据
    flash_union_buffer[2].float_type  = camera_pid.kd;                            // 向缓冲区第 2 个位置写入 int32  数据
    flash_union_buffer[3].float_type  = camera_pid.maxIntegral;                            // 向缓冲区第 2 个位置写入 int32  数据
    flash_union_buffer[4].float_type  = camera_pid.maxOutput;                            // 向缓冲区第 2 个位置写入 int32  数据
    flash_union_buffer[5].float_type = angv_pid.kp;                                  // 向缓冲区第 3 个位置写入 uint16 数据
    flash_union_buffer[6].float_type  = angv_pid.ki;                                 // 向缓冲区第 4 个位置写入 int16  数据
    flash_union_buffer[7].float_type  = angv_pid.kd;                                    // 向缓冲区第 5 个位置写入 uint8  数据
    flash_union_buffer[8].float_type  = angv_pid.maxIntegral;                            // 向缓冲区第 2 个位置写入 int32  数据
    flash_union_buffer[9].float_type  = angv_pid.maxOutput;                            // 向缓冲区第 2 个位置写入 int32  数据
    flash_union_buffer[10].float_type   = speed_pid.kp;                                   // 向缓冲区第 6 个位置写入 int8   数据
    flash_union_buffer[11].float_type   = speed_pid.ki;                                   // 向缓冲区第 6 个位置写入 int8   数据
    flash_union_buffer[12].float_type   = speed_pid.kd;                                   // 向缓冲区第 6 个位置写入 int8   数据
    flash_union_buffer[13].float_type  = speed_pid.maxIntegral;                            // 向缓冲区第 2 个位置写入 int32  数据
    flash_union_buffer[14].float_type  = speed_pid.maxOutput;                            // 向缓冲区第 2 个位置写入 int32  数据
    flash_erase_sector(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);              // 擦除这一页
    flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据
}

