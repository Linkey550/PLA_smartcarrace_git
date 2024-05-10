#include "zf_common_headfile.h"

const uint8 yj901s_unluck[]={0xFF,0xAA,0x69,0x88,0xB5};
const uint8 yj901s_init[]={0xFF,0xAA,0x01,0x08,0x00};
const uint8 yj901s_save[]={0xFF,0xAA,0x00,0x00,0x00};
const uint8 yj901s_z_zero[]={0xFF,0xAA,0x01,0x01,0x00};
void YJ901S_init(void)
{
    Send_data(UART8,yj901s_unluck,sizeof(yj901s_unluck));
    system_delay_ms(200);
//    Send_data(UART8,yj901s_init,sizeof(yj901s_init));
//    system_delay_ms(3000);
    Send_data(UART8,yj901s_z_zero,sizeof(yj901s_init));
    system_delay_ms(5000);
    Send_data(UART8,yj901s_save,sizeof(yj901s_save));
}
