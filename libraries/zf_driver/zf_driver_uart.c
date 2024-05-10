/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library ����CH32V307VCT6 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ���CH32V307VCT6 ��Դ���һ����
*
* CH32V307VCT6 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          zf_driver_uart
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MounRiver Studio V1.8.1
* ����ƽ̨          CH32V307VCT6
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����                                      ����                             ��ע
* 2022-09-15        ��W            first version
********************************************************************************************************************/
#include "zf_driver_gpio.h"
#include "zf_driver_uart.h"


// �������ֹ�޸ģ��ڲ�ʹ���û��������
const uint8 uart_irq[] = {USART1_IRQn, USART2_IRQn, USART3_IRQn, UART4_IRQn, UART5_IRQn, UART6_IRQn, UART7_IRQn, UART8_IRQn};
const uint32 uart_index[] = {USART1_BASE, USART2_BASE, USART3_BASE, UART4_BASE, UART5_BASE, UART6_BASE, UART7_BASE, UART8_BASE};

// ���建������С
#define USART1_BUFLEN_RX 11

// ������
uint8_t RxBuffer1[USART1_BUFLEN_RX] = {0};



//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڷ���һ���ֽ�
// ����˵��     uartn       ����ͨ��
// ����˵��     dat         ��������
// ���ز���     void
// ʹ��ʾ��     uart_write_byte(UART_1, 0x43);        //����1����0x43��
//-------------------------------------------------------------------------------------------------------------------
void uart_write_byte(uart_index_enum uartn, const uint8 dat)
{
    while((((USART_TypeDef*)uart_index[uartn])->STATR & USART_FLAG_TXE)==0);
    ((USART_TypeDef*)uart_index[uartn])->DATAR = dat;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڷ�������
// ����˵��     uartn       ����ͨ��
// ����˵��     buff        Ҫ���͵������ַ
// ����˵��     len         ���ݳ���
// ���ز���     void
// ʹ��ʾ��     uart_write_buffer(UART_1, buff, 10);     //����1����10��buff���顣
//-------------------------------------------------------------------------------------------------------------------
void uart_write_buffer(uart_index_enum uartn, const uint8 *buff, uint32 len)
{
    zf_assert(buff != NULL);
    while(len--)
        uart_write_byte(uartn, *buff++);
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڷ����ַ���
// ����˵��     uartn       ����ͨ��
// ����˵��     str         �ַ����׵�ַ
// ���ز���     void
// ʹ��ʾ��     uart_putstr(UART_1, (uint8 *)"12345")   //����1����12345����ַ���
//-------------------------------------------------------------------------------------------------------------------
void uart_write_string(uart_index_enum uartn, const char *str)
{
    zf_assert(str != NULL);
    while(*str)                                                                 // һֱѭ������β
    {
        uart_write_byte(uartn, *str++);
    }
}



//-------------------------------------------------------------------------------------------------------------------
// �������     �򿪴��ڽ����ж�
// ����˵��     uartn       ����ͨ��
// ����˵��     status      ʹ�ܻ���ʧ��
// ���ز���     void
// ʹ��ʾ��     uart_rx_irq(UART_1, ENABLE);        //�򿪴���1�����ж�
//-------------------------------------------------------------------------------------------------------------------
void uart_rx_interrupt(uart_index_enum uartn, uint8 status)
{
    USART_ITConfig(((USART_TypeDef*)uart_index[uartn]), USART_IT_RXNE, status);

    // �����ж����ȼ�
    interrupt_set_priority((uint32)((IRQn_Type)uart_irq[uartn]), 0);

    if(status)  interrupt_enable((IRQn_Type)uart_irq[uartn]);
    else        interrupt_disable((IRQn_Type)uart_irq[uartn]);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �򿪴��ڷ����ж�
// ����˵��     uartn       ����ͨ��
// ����˵��     status      ʹ�ܻ���ʧ��
// ���ز���     void
// ʹ��ʾ��     uart_tx_irq(UART_1, DISABLE);       //�رմ���1���� �ж�
//-------------------------------------------------------------------------------------------------------------------
void uart_tx_interrupt(uart_index_enum uartn, uint8 status)
{
    USART_ITConfig(((USART_TypeDef*)uart_index[uartn]), USART_IT_TXE, status);

    // �����ж����ȼ�
    interrupt_set_priority((uint32)((IRQn_Type)uart_irq[uartn]), 0);

    if(status)  interrupt_enable((IRQn_Type)uart_irq[uartn]);
    else        interrupt_disable((IRQn_Type)uart_irq[uartn]);
}

/////
uint32_t Uart_pow(uint32_t x,uint32_t y)
{
    uint32_t result =1;
    while(y--)
    {
        result *=x;
    }
    return result;
}

void Uart_sendnum(uart_index_enum uartn , uint32_t number)
{
    uint8_t i,count_Uart =0;
    uint32_t Temp_Uart = 0;
    Temp_Uart = number;
    while(Temp_Uart !=0 )
    {
        Temp_Uart/= 10;
        count_Uart++;
    }
    for (i=0;i<count_Uart;i++)
    {
        uart_write_byte( uartn , number/Uart_pow(10,count_Uart - i-1)%10 + '0');
    }
}
////

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ���ڽ��յ����ݣ�whlie�ȴ���
// ����˵��     uartn           ����ģ���(UART_1 - UART_8)
// ����˵��     *dat            �������ݵĵ�ַ
// ���ز���     void
// ʹ��ʾ��     uint8 dat; uart_read_byte(USART_1,&dat);       // ���մ���1����  ������dat������
//-------------------------------------------------------------------------------------------------------------------
uint8 uart_read_byte(uart_index_enum uartn)
{
    while((((USART_TypeDef*)uart_index[uartn])->STATR & USART_FLAG_RXNE) == 0);
    return (((USART_TypeDef*)uart_index[uartn])->DATAR & (uint16)0xFF);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ���ڽ��յ����ݣ���ѯ���գ�
// ����˵��     uartn           ����ģ���(UART_1 - UART_8)
// ����˵��     *dat            �������ݵĵ�ַ
// ���ز���     uint8           1�����ճɹ�   0��δ���յ�����
// ʹ��ʾ��     uint8 dat; uart_query_byte(USART_1,&dat);       // ���մ���1����  ������dat������
//-------------------------------------------------------------------------------------------------------------------
uint8 uart_query_byte(uart_index_enum uartn, uint8 *dat)
{
    if((((USART_TypeDef*)uart_index[uartn])->STATR & USART_FLAG_RXNE) != 0)
    {
        *dat = (((USART_TypeDef*)uart_index[uartn])->DATAR & 0xFF);
        return 1;
    }
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڳ�ʼ��
// ����˵��     uartn       ����ͨ��
// ����˵��     baud        ������
// ����˵��     tx_pin      ���ڷ������ź�
// ����˵��     rx_pin      ���ڽ������ź�
// ���ز���     void
// ʹ��ʾ��     uart_init(UART_1, 115200, UART1_TX_A9, UART1_RX_A10); //����1��ʼ�����ź�,TXΪA9,RXΪA10
//-------------------------------------------------------------------------------------------------------------------
void uart_init(uart_index_enum uart_n, uint32 baud, uart_pin_enum tx_pin, uart_pin_enum rx_pin)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ȥ�鿴����ʲô�ط������������ �����Ĵ������
    // RX��TX������Ҫ����ͬһ��ӳ�����ţ������ͬ�ͻ������
    zf_assert((tx_pin & (uart_n << 12)) == (rx_pin & (uart_n << 12)));      // tx_pin �� rx_pin ������ uart_n ƥ��
    zf_assert((tx_pin >> 8) == (rx_pin >> 8));                              // tx_pin �� rx_pin ������鴫��

    gpio_init(tx_pin & 0xFF, GPO, 0, GPO_AF_PUSH_PULL);
    gpio_init(rx_pin & 0xFF, GPI, 0, GPI_PULL_UP);

    // AFIO���߿���
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);



    switch(tx_pin & 0xFFFF)
    {
        case UART1_MAP1_TX_B6:
           AFIO->PCFR2 &= ~(0x01<<26);
           AFIO->PCFR1 &= ~(0x01<<2);
           AFIO->PCFR1 |=  (0x01<<2);
           break;
        case UART1_MAP2_TX_B15:
            AFIO->PCFR2 &= ~(0x01<<26);
            AFIO->PCFR2 |=  (0x01<<26);
            AFIO->PCFR1 &= ~(0x01<<2);
           break;
        case UART1_MAP3_TX_A6:
            AFIO->PCFR2 &= ~(0x01<<26);
            AFIO->PCFR2 |=  (0x01<<26);
            AFIO->PCFR1 &= ~(0x01<<2);
            AFIO->PCFR1 |=  (0x01<<2);
           break;

        case UART2_MAP1_TX_D5:
            AFIO->PCFR1 &= ~(0x01<<3);
            AFIO->PCFR1 |=  (0x01<<3);
           break;

        case UART3_MAP1_TX_C10:
            AFIO->PCFR1 &= ~(0x03<<4);
            AFIO->PCFR1 |=  (0x01<<4);
           break;

        case UART3_MAP2_TX_D8:
            AFIO->PCFR1 &= ~(0x03<<4);
            AFIO->PCFR1 |=  (0x03<<4);
           break;

        case UART4_MAP1_TX_B0:
            AFIO->PCFR2 &= ~(0x03<<16);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 16);
           break;

        case UART4_MAP3_TX_E0:
            AFIO->PCFR2 &= ~(0x03<<16);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 16);
           break;

        case UART5_MAP1_TX_B4:
            AFIO->PCFR2 &= ~(0x03<<18);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 18);
           break;

        case UART5_MAP3_TX_E8:
            AFIO->PCFR2 &= ~(0x03<<18);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 18);
           break;

        case UART6_MAP1_TX_B8:
            AFIO->PCFR2 &= ~(0x03<<20);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 20);
           break;

        case UART6_MAP3_TX_E10:
            AFIO->PCFR2 &= ~(0x03<<20);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 20);
           break;

        case UART7_MAP1_TX_A6:
            AFIO->PCFR2 &= ~(0x03<<22);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 22);
           break;

        case UART7_MAP3_TX_E12:
            AFIO->PCFR2 &= ~(0x03<<22);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 22);
           break;

        case UART8_MAP1_TX_A14:
            AFIO->PCFR2 &= ~(0x03<<24);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 24);
           break;

        case UART8_MAP3_TX_E14:
            AFIO->PCFR2 &= ~(0x03<<24);
            AFIO->PCFR2 |=  (((tx_pin >> 8) & 0x03 ) << 24);
           break;
    }


    // ��������ʹ��
    if(UART_1 == uart_n)        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    else if(UART_2 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    else if(UART_3 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    else if(UART_4 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,  ENABLE);
    else if(UART_5 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,  ENABLE);
    else if(UART_6 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART6,  ENABLE);
    else if(UART_7 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7,  ENABLE);
    else if(UART_8 == uart_n)   RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8,  ENABLE);

    // ���ڲ�������
    USART_InitTypeDef USART_InitStructure = {0};
    USART_InitStructure.USART_BaudRate = baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;



    // ʹ�ܴ���
    USART_Init((USART_TypeDef*)uart_index[uart_n], &USART_InitStructure);
    USART_Cmd((USART_TypeDef*)uart_index[uart_n], ENABLE);

}



//void USART1_DMAConfig(uint32_t baudrate) {
//    // ��ʼ�� DMA �ṹ��
//    DMA_InitTypeDef DMA_InitStructure_USART1_RX;//DMA
//    NVIC_InitTypeDef  NVIC_InitStructure;
//    // ʹ�� DMA1 ʱ��
//    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//    // ʹ�� USART1 ʱ��
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
//
//    // ���� DMA ����ͨ��
//    DMA_DeInit(DMA1_Channel5);
//    DMA_InitStructure_USART1_RX.DMA_PeripheralBaseAddr = (u32)(&USART1->DATAR);
//    DMA_InitStructure_USART1_RX.DMA_MemoryBaseAddr = (u32)RxBuffer1;
//    DMA_InitStructure_USART1_RX.DMA_DIR = DMA_DIR_PeripheralSRC;
//    DMA_InitStructure_USART1_RX.DMA_BufferSize = USART1_BUFLEN_RX;
//    DMA_InitStructure_USART1_RX.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//    DMA_InitStructure_USART1_RX.DMA_MemoryInc = DMA_MemoryInc_Enable;
//    DMA_InitStructure_USART1_RX.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//    DMA_InitStructure_USART1_RX.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//    DMA_InitStructure_USART1_RX.DMA_Mode = DMA_Mode_Normal;
//    DMA_InitStructure_USART1_RX.DMA_Priority = DMA_Priority_VeryHigh;
//    DMA_InitStructure_USART1_RX.DMA_M2M = DMA_M2M_Disable;
//    DMA_Init(DMA1_Channel5, &DMA_InitStructure_USART1_RX);
//
//    // ���� USART1
//    uart_init(UART_1, baudrate, UART1_MAP0_TX_A9, UART1_MAP0_RX_A10);
//    // ... ���� USART1 ���� ...
//
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//
//    DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);  //ʹ��DMA��������ж�
//    // ʹ�� DMA ����ͨ��
//    DMA_Cmd(DMA1_Channel5, ENABLE);
//
//
//}

//��ָ��Ϊ�������ݰ��ֽڷ��͵Ĵ��ڷ��ͺ���
void Send_data(USART_TypeDef * USARTx,u8 *s,int bit)
{
   int bit_buff=0;
 while(bit_buff<bit)
 {
  while(USART_GetFlagStatus(USARTx,USART_FLAG_TC )==RESET);
  USART_SendData(USARTx,*s);
  s++;
  bit_buff++;
 }
}

//void DMA1_Channel2_IRQHandler(void)
//{
//    if(DMA_GetITStatus(DMA1_IT_TC2))
//    {
//        //printf("USART DMA complete\r\n");
//        uart_write_string(UART_1, "PWM2:");
//        DMA_ClearITPendingBit(DMA1_IT_TC2); //���ȫ���жϱ�־
//    }
//}



