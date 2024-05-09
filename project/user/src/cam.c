#include "zf_common_debug.h"
#include "zf_common_interrupt.h"
#include "zf_driver_exti.h"
#include "zf_driver_timer.h"
#include "zf_device_type.h"
#include "zf_device_mt9v03x_dvp.h"
#include "zf_device_scc8660_dvp.h"
#include "cam.h"
#include "main.h"
#include "Gyroscope_c.h"
#include "Encoder_c.h"


cam_parameter camera_p;
float campit_time=0;     //�жϼ�ʱ1ms
//�������
//���غͻҶ�
#define GrayScale 256 //�Ҷ�ֵ
int pixelCount[GrayScale];
float pixelPro[GrayScale];
//���ߣ�
#define BOUNDARY_NUM            (MT9V03X_H * 3 / 2)
//����
unsigned char PaddingR = 0;
unsigned char PaddingL = 0;
unsigned char Paddingcurve = 0;            //�����߱�־��1�������� ��0����ֱ��
uint8 Link_Right_One_Point[2];               //���ߵ�
uint8 Link_Right_Two_Point[2];
uint8 Link_Left_One_Point[2];
uint8 Link_Left_Two_Point[2];

//�յ㶨�壺
unsigned char Right_Up_Point_finish_flag = 0;       //�յ��־λ
unsigned char Left_Up_Point_finish_flag = 0;
unsigned char Right_Down_Point_finish_flag = 0;
unsigned char Left_Down_Point_finish_flag = 0;
uint8 Last_Right_Point[2];                //��һ�ιյ㣬�յ���ʱ���ͻȻת�� 0 ��down 1��up
uint8 Last_Left_Point[2];
uint8 Right_Down_Point[2];                //�յ�   0 : x  1 : y
uint8 Right_Up_Point[2];
uint8 Left_Down_Point[2];
uint8 Left_Up_Point[2];
int findrcount = 0;                     //��¼�յ㵽�߽���룬��������Բ���ͻ�ת
int findlcount = 0;

//������ͼ��
uint8 Emo_imag[120][188];
vuint8 IPS_Flag = 0;                    //ͼ������ϱ�־


int EmoBlackcount = 0,EmoWhitecount = 0;            //��ֹ�в���
uint8 OSTU=140;   //�����ֵ
uint8 OUST1 = 0;  //��ֵ��������㲻ͬ���ضԴ����ֵ����
uint8 Endline = 0;

uint8 BoundaryLeft = 0;             //�߽����
uint8 BoundaryRight = 0;

uint8 Left_Black_Point[120];     //һά�㣨��Сд��
uint8 Right_Black_Point[120];


//ת��,�����
//unsigned char Slalom_Padding = 0;  //Slalom���߱�־��
unsigned char Corners_flag = 0;              //���ʸ���ر�־
unsigned char CornerRight_flag = 0;   //�����־
unsigned char CornerLeft_flag = 0;
unsigned char Near_CornerLeft_flag = 0;      //���������־
unsigned char Near_CornerRight_flag = 0;
unsigned char Near_Corners_flag = 0;         //�������ʸ���ر�־
unsigned char CornerS_flag = 0;       //S���־


//slalom,p�ֱ���:
unsigned char SlalomLeft_flag = 0;             //Slalom��־
int Slalomcount = 0;                 //Slalom�ڲ�����
unsigned char SlalomRight_flag = 0;
unsigned char Slalom_Padding = 0;  //Slalom���߱�־
uint8 Slalom_Point[2];
static unsigned char ObservationS_finish = 0;//�۲�s���
static unsigned char CorneringS_finish = 0;//s����Ƿ����
unsigned char SlC = 0; //P�ּ������򣬰�������������

//Բ����
uint8 CircleOut_Point[2];
float CircleLeft_flag = 0;         //Բ����־
float CircleRight_flag = 0;
unsigned char CircleBig = 0;           //��Բ����־
unsigned char CircleSwitch_flag = 1;       //Բ�����ر�־ ��0����رգ�1��������Ĭ��Ϊ����
int Circlecount = 0;                //Բ���ڲ�����
unsigned char  Circle_RC = 0; //Բ���������򣬰����������Է���һ
//����·�ڣ�
unsigned char Trifork_flag = 0;                        //����
unsigned char Trifork_PointLeft_Findfinish_flag = 0;
unsigned char Trifork_PointRight_Findfinish_flag = 0;
unsigned char Trifork_PointMiddle_Findfinish_flag = 0;
unsigned char Triforkpadding_flag = 0;       //�����߱�־
int Triforkcount = 0;               //�����ڲ����裬����TriforkTurn����������ת������
int TriforkTurn = 0;                //����Ȧ������һ���������ӽ�������ȫͨ��һ��
uint8 TriforkLeft_Point[2];         //�������
uint8 TriforkRight_Point[2];       //�����ҵ�
uint8 TriforkMiddle_Point[2];       //������
static unsigned char ObservationT_finish = 0;
static unsigned char CorneringT_finish = 0;
unsigned char dieReady = 0; //0:�ճ��� 1:���� 2:Բ�� 3:�ػ� 4:���



//���⣺
float Garage_Findfinish_flag = 0;    //��Ѱ�ұ�־ 0��û�ҵ� 1���ҵ���
unsigned char Garage_flag = 0;                //ִ�г��ⲹ�߱�־
float Garagecount = 0;

unsigned char GarageL_In_flag = 0;
unsigned char GarageR_In_flag = 0;


unsigned char Garage_Out_flag = 1;          //�����־ 0�������г��� 1�����г���

//����
float ObscountR=0;
float ObscountL=0;
float Obscount2=0;
float ObstacleR_flag = 0;//�ϰ��ұ�־
float ObstacleL_flag = 0;//�ϰ����־
//Ԫ��ǰҡ��
unsigned char WindupL_flag = 0;                //Ԫ��ǰҡ
unsigned char WindupR_flag = 0;                //Ԫ��ǰҡ


//����
float CurvatureLeft=0;                  //���ʼ���
float CurvatureRight=0;

//ʮ�ֱ�־�ͼ���
unsigned char Cross_flag = 0;
int Crosscount = 0;

//����ͷ��ʼ��־
unsigned char flag_start = 0;



extern float angv[3];//������Z���ٶ�
float Emo_Angle=0;



//������֣�
unsigned char need_cornerL = 0;              //Сת�丨��������Ԫ�س����һЩת�丨��
unsigned char need_cornerR = 0;
//��������������Ҫ
unsigned char Auxiliary_CorneringLeft_flag = 0;    //ǿ�����������
unsigned char Auxiliary_CorneringRight_flag = 0;    //ǿ�����Ҹ������


uint8 Corners[120] =  { 187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
                        187, 187, 187, 187, 187, 187, 187, 187, 187, 187,
                        187, 187, 187, 187, 187, 187, 187, 179, 157, 137,
                        120, 105, 95, 84, 77, 73, 73, 73, 72, 72,
                        70, 69, 68, 67, 66, 65, 64, 64, 64, 64,
                        65, 65, 65, 66, 66, 66, 67, 67, 68, 68,
                        68, 69, 69, 69, 69, 70, 70, 70, 71, 72,
                        73, 73, 73, 74, 74, 74, 75, 76, 76, 77,
                        77, 78, 78, 78, 79, 79, 80, 80, 81, 81,
                        82, 82, 83, 83, 84, 84, 85, 86, 87, 88,
                        88, 89, 90, 90, 91, 91, 92, 92, 93, 94,
                        94, 95, 95, 95, 96, 97, 98, 98, 99, 99};//   �յ�Ss���


uint8 Middle_Black_Point[120] = {   93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93,
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93};//���ߺڵ�

uint8 Straight[120] = { 15, 16, 16, 17, 18, 18, 19, 19, 20, 21,
                        21, 22, 22, 23, 24, 24, 25, 25, 26, 26,
                        27, 28, 29, 29, 30, 31, 32, 32, 33, 34,
                        34, 35, 35, 36, 36, 37, 38, 38, 39, 39,
                        40, 41, 41, 42, 42, 43, 44, 44, 45, 45,
                        46, 46, 47, 48, 48, 49, 49, 50, 51, 51,
                        52, 52, 53, 54, 54, 55, 55, 56, 56, 57,
                        58, 58, 59, 59, 60, 61, 61, 62, 62, 63,
                        64, 64, 65, 65, 66, 66, 67, 68, 68, 69,
                        69, 70, 71, 71, 72, 72, 73, 74, 74, 75,
                        75, 76, 76, 77, 78, 78, 79, 79, 80, 81,
                        81, 82, 82, 83, 84, 85, 85, 86, 86, 87};//ֱ����ֵ


uint8 Trifork_padding[120] = { 74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74,
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74};//������ֵ







//********************************************************************************************************************/
//********************************************************************************************************************/
//********************************************************************************************************************/



void Camera_Init(void)       //����ͷ��ʼ��
{
    camera_p.Garage_In_flag = 0;           //����־  0����������� 1���������
    Emo_Angle=angv[2];
    //�ṹ���ʼ��
    camera_p.T_X = 0;
    camera_p.CurvatureLeft = 0;
    camera_p.CurvatureRight = 0;
//    camera_p.test1_flag = 0;
//    camera_p.test2_flag = 0;


}

void Pit_Init(void)
{
    if(campit_time != 0)
    {
        campit_time = 0;
    }

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �޷���8λ��������ľ���ֵ
//  @param      a        ��һ
//  @param      b        ����
//  @param
//  @param
//  @return     int
//  @note
//-------------------------------------------------------------------------------------------------------------------
int Emo_u8Decabs(uint8 a,uint8 b)    //�޷���8λ���������ֵ
{
    int c = (int)a;
    int d = (int)b;
    if(c>d)
    {
        return c-d;
    }
    else
    {
        return d-c;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �޷���8λ�������
//  @param      a        ��һ
//  @param      b        ����
//  @param
//  @param
//  @return     int
//  @note
//-------------------------------------------------------------------------------------------------------------------
int Emo_Uint8_dec(uint8 a,uint8 b)   //�޷���8λ�������
{
    int c = 0;
    int d = 0;
    c=(int)a;
    d=(int)b;
    return c-d;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����֮�������֮һ
//  @param      a        ��һ
//  @param      b        ����
//  @param
//  @param
//  @return     uint8
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8 Emo_one_third(uint8 a, uint8 b)
{
    int c = a;
    int d = b;
    if(c > d)
    {
        return (uint8)(d+((c-d)/3));
    }
    else
    {
        return (uint8)(c+((d-c)/3));
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����֮����ķ�֮һ
//  @param      a        ��һ
//  @param      b        ����
//  @param
//  @param
//  @return     uint8
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8 Emo_one_fourth(uint8 a, uint8 b)
{
    int c = a;
    int d = b;
    if(c > d)
    {
        return (uint8)(d+((c-d)/4));
    }
    else
    {
        return (uint8)(c+((d-c)/4));
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����֮��İ˷�֮һ
//  @param      a        ��һ
//  @param      b        ����
//  @param
//  @param
//  @return     uint8
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8 Emo_one_eighth(uint8 a, uint8 b)
{
    int c = a;
    int d = b;
    if(c > d)
    {
        return (uint8)(d+((c-d)/8));
    }
    else
    {
        return (uint8)(c+((d-c)/8));
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����֮�������֮��
//  @param      a        ��һ
//  @param      b        ����
//  @param
//  @param
//  @return     uint8
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8 Emo_two_third(uint8 a, uint8 b)
{
    int c = a;
    int d = b;
    if(c > d)
    {
        return (uint8)(d+((c-d)*2/3));
    }
    else
    {
        return (uint8)(c+((d-c)*2/3));
    }
}
int Emo_abs(int x)                  //����ֵ
{
    x = x < 0 ? (-x) : x;
    return x;
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������
//  @param      a        ��һ
//  @param      b        ����
//  @param
//  @param
//  @return     uint8
//  @note
//-------------------------------------------------------------------------------------------------------------------
uint8 Emo_max(uint8 x , uint8 y)
{
    if(x >= y)
        return x;
    else
        return y;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ֵ��
//  @param      ROUST   ������ֵ���ڱ���
//  @param
//  @param
//  @param
//  @return     void
//  @note       �ڲ�ʹ���˴�򷨣������˰���������ֵ�Ľ��
//-------------------------------------------------------------------------------------------------------------------
void Thresholding(void)   //��ֵ��
{
    OSTU=Ostu(mt9v03x_image[0], 188, 120);
    OUST1 = OSTU;
//    OUST1 = OUST1 > 118 ? 118 : OUST1;
//    OUST1 = OUST1 < 103 ? 103 : OUST1;

    Endline = 0;   //Ѱ�ҵ������ⶥֵ���������Ĺյ�Ѱ�Һ�Ԫ���жϲ����ٴ�ֵ�Ժ����
    for(uint8 y=0;y<120;y++)
    {
        EmoWhitecount = 0;
        for(uint8 x=0;x<188;x++)
        {
//            Emo_imag[y][x] = mt9v03x_image[y][x] < (OUST1 + ROUST) ? EmoBlack : EmoWhite;
            Emo_imag[y][x] = mt9v03x_image[y][x] < OUST1  ? EmoBlack : EmoWhite;

            if(Emo_imag[y][x] == EmoWhite)
                EmoWhitecount++;
        }
        if(EmoWhitecount < 40 )
        {
            Endline = y;
        }
    }
    Pixle_Filter();
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���
//  @param      image  ͼ���ַ
//  @param      width  ͼ����
//  @param      height ͼ��߶�
//  @param
//  @return     uint8
//  @note       ��ֵ�������ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8 Ostu(uint8 *image, uint16 width, uint16 height)
{
//    uint16 width = col;
//    uint16 height = row;
    uint8 threshold = 0 ;

    int i, j, pixelSum = width * height/4;

    uint8* data = image;  //ָ���������ݵ�ָ��
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    uint32 gray_sum=0;
    //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
    for (i = 0; i < height; i+=2)
    {
        for (j = 0; j < width; j+=2)
        {
            pixelCount[(int)data[i * width + j]]++;  //����ǰ�ĵ������ֵ��Ϊ����������±�
            gray_sum+=(int)data[i * width + j];       //�Ҷ�ֵ�ܺ�
        }
    }

    //����ÿ������ֵ�ĵ�������ͼ���еı���

    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;

    }
    //�����Ҷȼ�[0,255]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;

    w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
    for (j = 0; j < GrayScale; j++)
    {
            w0 += pixelPro[j];  //��������ÿ���Ҷ�ֵ�����ص���ռ����֮��   ���������ֵı���
            u0tmp += j * pixelPro[j];  //��������       ÿ���Ҷ�ֵ�ĵ�ı��� *�Ҷ�ֵ

            w1=1-w0;
            u1tmp=gray_sum/pixelSum-u0tmp;

            u0 = u0tmp / w0;              //����ƽ���Ҷ�
            u1 = u1tmp / w1;              //ǰ��ƽ���Ҷ�
            u = u0tmp + u1tmp;            //ȫ��ƽ���Ҷ�
            deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
            if (deltaTmp > deltaMax)
            {
                deltaMax = deltaTmp;
                threshold = (uint8)j;
            }
            if (deltaTmp < deltaMax)
            {
                break;
            }
     }
    return threshold;
}


void Pixle_Filter(void)
{
    for (uint8 height = 10; height < MT9V03X_H-10; height++)
    {
        for (uint8 width = 10; width < MT9V03X_W -10; width++)
        {
            if ((Emo_imag[height][width] == 0) && (Emo_imag[height - 1][width] + Emo_imag[height + 1][width] + Emo_imag[height][width + 1] + Emo_imag[height][width - 1] >=3*255))
            { //һ���ڵ���������ҵİ׵���ڵ����������������Ϊ��
                Emo_imag[height][width] = EmoWhite;
            }
            else if((Emo_imag[height][width] !=0)&&(Emo_imag[height-1][width]+Emo_imag[height+1][width]+Emo_imag[height][width+1]+Emo_imag[height][width-1]<2*255))
            {
                Emo_imag[height][width] = EmoBlack;
            }
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����Ѳ����
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��������ɨ�ߵķ�������ͼ����Ͷ˿�ʼ��ÿ��ɨ������һ�����ߣ���һ��ɨ�����һ�����߿�ʼ
//-------------------------------------------------------------------------------------------------------------------
static uint8 star = 93;                             //Ѱ�߳�ʼ��
//���Ż�����ʱ�������������
//////����������Ѱ���б߽���ʹ�Ժ���߶����ڱ߽�
void Find_Line(void)
{
    BoundaryRight = 0;
    BoundaryLeft = 0;
    if(Middle_Black_Point[119] == 0 || Middle_Black_Point[119] == 187)  //�ж���ʼ���Ƿ���ͼ���м�
    {
        star = 93;
    }
    else
    {
        star = Middle_Black_Point[119];
    }
    for(uint8 y=119;y>=0;y--)
    {
        for(uint8 x=star;x<188;x++)
        {
            if(Emo_imag[y][x]==EmoBlack)  //�ںںڼ��ж�Ϊ����
            {
                if(Emo_imag[y][x+2]==EmoBlack && Emo_imag[y][x+3]==EmoBlack && Emo_imag[y][x+6]==EmoBlack)
                {
                    if(y < Endline )
                        Right_Black_Point[y] = 187;
                    else
                        Right_Black_Point[y]=x;
                    //left=star;
                    break;
                }
            }
            if(x==186)                      //�е����⣬��У����
            {
                Right_Black_Point[y]=187;
                //left=star;
                if(y > Endline && y < 108)
                    BoundaryRight++;
                break;
            }
        }
        for(uint8 x=star;x>=0;x--)
        {
            if(Emo_imag[y][x]==EmoBlack)
            {
                if(Emo_imag[y][x-2]==EmoBlack && Emo_imag[y][x-3]==EmoBlack && Emo_imag[y][x-6]==EmoBlack)
                {
                    if(y < Endline)
                        Left_Black_Point[y] = 0;
                    else
                        Left_Black_Point[y]=x;
                    break;
                }
            }
            if(x==0)
            {
                Left_Black_Point[y]=0;
                if(y > Endline && y < 108)
                    BoundaryLeft++;
                break;
            }
        }
        if(Right_Black_Point[y]==187&&Left_Black_Point[y]==0)        //���߶�û�ҵ���
        {
            Middle_Black_Point[y]=Middle_Black_Point[y+1];
            //star=Middle_Black_Point[y];
            star = 93;
        }
        else if(Right_Black_Point[y]==187&&Left_Black_Point[y]!=0)    //����ҵ���
        {
            Middle_Black_Point[y]=Left_Black_Point[y]+Straight[y];
            star=Middle_Black_Point[y];
            if( camera_p.CurvatureRight < -0.0045)
            {
//                kuan = ((y-120)*(y-120)/(20)+93);
//                kuan = kuan > (187-Right_Black_Point[y]) ? (187-Right_Black_Point[y]) : kuan;
//                Middle_Black_Point[y]=Left_Black_Point[y]+kuan;
            }
        }
        else if(Left_Black_Point[y]==0&&Right_Black_Point[y]!=187)    //�ұ��ҵ���
        {
            Middle_Black_Point[y]=Right_Black_Point[y]-Straight[y];
            star=Middle_Black_Point[y];
            if( camera_p.CurvatureRight < -0.0045)
            {
//                kuan = ((y-120)*(y-120)/(20)+93);
//                kuan = kuan > Right_Black_Point[y] ? Right_Black_Point[y] : kuan;
//                Middle_Black_Point[y]=Right_Black_Point[y]-kuan;
            }
        }
        else             //���߶��ҵ���
        {
            Middle_Black_Point[y]=(uint8)(((int)Right_Black_Point[y]+(int)Left_Black_Point[y])/2);
            star=Middle_Black_Point[y];
        }
        Middle_Black_Point[y] = Middle_Black_Point[y] < 1 ? 1 : Middle_Black_Point[y];
        Middle_Black_Point[y] = Middle_Black_Point[y] > 186 ? 186 : Middle_Black_Point[y];
        Middle_Black_Point[y] = Middle_Black_Point[y] < 1 ? 0 : Middle_Black_Point[y];
        Middle_Black_Point[y] = Middle_Black_Point[y] >186 ? 187 :Middle_Black_Point[y];
        if(y==0)
            break;
    }
    //star = Middle_Black_Point[119];
}




//�����ߣ�����������в�
//Cx�����ϵ�x��Cy�����ϵ�y
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���߲��ߺ���
//  @param      Ux  �ϲ��ߵ�x����
//  @param      Uy  �ϲ��ߵ�y����
//  @param      Dx  �²��ߵ�x����
//  @param      Dx  �²��ߵ�y����
//  @return     void
//  @note       �����������ղ�ֵ����������������ͼ��������м��Ϊ�̶��㣬�������Ч�����ã���Ҫ����У׼�м��
//  Left_Black_Point[y]Ϊ�ҵ���������� Right_Black_Point[y]Ϊ�ҵ��ұ�������
//-------------------------------------------------------------------------------------------------------------------
void Padding_CurveL(uint8 Ux,uint8 Uy,uint8 Dx,uint8 Dy)
{
    int x0 = 0,x1 = 0,x2 = 0;
    int y0 = 0,y1 = 0,y2 = 0;


    //0.0096   -2.1047  138.5182
    //0.0103   -2.2049  141.8985
    //x=x0(y-y1)(y-y2)/(y0-y1)(y0-y2)+x1(y-y0)(y-y2)/(y1-y0)(y1-y2)+x2(y-y0)(y-y1)/(y2-y0)(y2-y1)
    x0 = (int)Dx;
    x1 = (int)(Dx + (float)3*(Ux-Dx)/5);
    x2 = (int)Ux;
    y0 = (int)Dy;
    y1 = (int)(Dy - (float)2*(Dy-Uy)/3);
    y2 = (int)Uy;
    if(Ux == 0 && Ux == 0 && Dx == 0 && Dy == 0)
    {

    }
    else
    {
        if(Dy > 110)
        {
            Dy = 110;
        }
        //Re = Left_Black_Point[Dy];
//        Left_Black_Point[Dy] = (uint8)(a*(float)(Dy*Dy)+b*(float)Dy+c);
        //error = (int)Re - (int)Left_Black_Point[Dy];
        for(uint8 y = Uy ;y <= Dy;y++)
        {
//            Re = y - Uy + 25;
//            Left_Black_Point[y]=(uint8)(a*(float)(Re*Re)+b*(float)Re+c);
            Left_Black_Point[y]=(uint8)((x0*(y-y1)*(y-y2))/((y0-y1)*(y0-y2)))+((x1*(y-y0)*(y-y2))/((y1-y0)*(y1-y2)))+((x2*(y-y0)*(y-y1))/((y2-y0)*(y2-y1)));
        }
    }

}

void Padding_CurveR(uint8 Ux,uint8 Uy,uint8 Dx,uint8 Dy)
{
    int x0 = 0,x1 = 0,x2 = 0;
    int y0 = 0,y1 = 0,y2 = 0;
    //0.0096   -2.1047  138.5182
    //0.0103   -2.2049  141.8985
    //x=x0(y-y1)(y-y2)/(y0-y1)(y0-y2)+x1(y-y0)(y-y2)/(y1-y0)(y1-y2)+x2(y-y0)(y-y1)/(y2-y0)(y2-y1)
    x0 = (int)Dx;
    x1 = (int)(Dx - (float)3*(Dx-Ux)/5);
    x2 = (int)Ux;
    y0 = (int)Dy;
    y1 = (int)(Dy - (float)2*(Dy-Uy)/3);
    y2 = (int)Uy;
    if(Ux == 0 && Ux == 0 && Dx == 0 && Dy == 0)
    {

    }
    else
    {
        if(Dy > 110)
        {
            Dy = 110;
        }
        for(uint8 y = Uy ;y <= Dy;y++)
        {
            Right_Black_Point[y]=(uint8)((x0*(y-y1)*(y-y2))/((y0-y1)*(y0-y2)))+((x1*(y-y0)*(y-y2))/((y1-y0)*(y1-y2)))+((x2*(y-y0)*(y-y1))/((y2-y0)*(y2-y1)));
        }
    }

}





/*********�ж���������*************/
//Ѱ���߽�ʱ�����ж������Ƿ�Ϊ�����S�䣬�ٽ��йյ�Ѱ��
//�������Ԫ����ʱ���������ж��������ͣ���Ϊʮ�֡���Բ����ȥ������������Զ��������,СSҲ�ڴ˴��ж�
//Զ���ж�����������ж����
//ʹ�������ж������СS
void Judge(void)
{
    uint8 star;
    int LeftXSum = 0, LeftYSum = 0, LeftXYSum = 0, LeftXXSum = 0;
    int RightXSum = 0, RightYSum = 0, RightXYSum = 0, RightXXSum = 0;
    //unsigned char JudgeCorner = 0;    //������ֱ߽絫��������Ͳ�ִ���ж�S��
    //unsigned char JudgeS = 0;         //��ʾִ����S��ȴû�жϳɹ�

    Near_CornerLeft_flag = 0;
    Near_CornerRight_flag = 0;
    Near_Corners_flag = 0;
    //JudgeCorner = 0;
    Judge_CornerS();
    for(uint8 y=60;y>35;y--)
    {
        //�Ҳ�����ж�
        if(Right_Black_Point[y-1] == 187 && Right_Black_Point[y-2] == 187 && Right_Black_Point[y-3] == 187
        && Right_Black_Point[y-4] == 187 && Right_Black_Point[y-5] == 187 && Right_Black_Point[y-6] == 187)
        {
            //JudgeCorner = 1;
            star=y;//�����ʼλ��,y��
            for (uint8 y = (star-16); y < star; y++)//�������߽�����ۼӼ���
            {
                if (y % 2 == 0)
                {
                    LeftXSum += Left_Black_Point[y];
                    LeftYSum += y;
                    LeftXXSum += Left_Black_Point[y] * Left_Black_Point[y];
                    LeftXYSum += y * Left_Black_Point[y];
                }
             }

            if(8 * LeftXXSum - LeftXSum * LeftXSum !=0)
            {
                camera_p.CurvatureLeft = (float)(8 * LeftXYSum - LeftXSum * LeftYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);
            }
            else
            {
                camera_p.CurvatureLeft = 0;
            }
            if(camera_p.CurvatureLeft > (-0.95) && camera_p.CurvatureLeft < -0.17)
            {
                // camera_p.CurvatureRight���ʴ���ȥ��ת�䴦��
                CornerRight_flag = 1;//�����־
                Corners_flag = 1;
                break;
            }
            else
            {
                CornerRight_flag = 0;
                Corners_flag = 0;
                break;
            }
        }
        else//�����
        {
            CornerRight_flag = 0;
            Corners_flag = 0;
        }
        //���������
        if(Left_Black_Point[y-1] == 0 && Left_Black_Point[y-2] == 0 && Left_Black_Point[y-3] == 0
        && Left_Black_Point[y-4] == 0 && Left_Black_Point[y-5] == 0 && Left_Black_Point[y-6] == 0)
        {
            star=y;//��ʼ��
            for (uint8 y = (star-16); y < star; y++)//�������߽�����ۼӼ���
            {
                if (y % 2 == 0)
                {
                    RightXSum += Right_Black_Point[y];
                    RightYSum += y;
                    RightXXSum += Right_Black_Point[y] * Right_Black_Point[y];
                    RightXYSum += y * Right_Black_Point[y];
                }
             }
            if(8 * RightXXSum - RightXSum * RightXSum != 0)
            {
                 camera_p.CurvatureRight = (float)(8 * RightXYSum - RightXSum * RightYSum) / (8 * RightXXSum - RightXSum * RightXSum);
            }
            else
            {
                 camera_p.CurvatureRight = 0;
            }
            if( camera_p.CurvatureRight < 0.95 &&  camera_p.CurvatureRight > 0.17)
            {
                // camera_p.CurvatureRight���ʴ���ȥ��ת�䴦��
                CornerLeft_flag = 1;
                Corners_flag = 1;
                break;
            }
            else
            {
                CornerLeft_flag = 0;
                Corners_flag = 0;
                break;
            }
        }
        else//�����
        {
            CornerLeft_flag = 0;
            Corners_flag = 0;
        }
    }
}


//���ڽ���СS�䣬�����־��ʼ��
void Judge_CornerS(void)
{
    if(CornerS_flag == 1)
    {
        for(uint8 y=35;y>20;y--)
        {
            if((Right_Black_Point[y-1] == 187 && Right_Black_Point[y-2] == 187 && Right_Black_Point[y-3] == 187) || (Left_Black_Point[y-1] == 0 && Left_Black_Point[y-2] == 0 && Left_Black_Point[y-3] == 0))
            {
                PaddingR = 0;
                PaddingL = 0;
                CornerS_flag = 0;
                break;
            }
        }
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      �յ�Ѱ��
//  @param      findlcount   �յ���붪�ߵ������������жϴ�СԲ����������P�ֺ�Բ��
//  @param
//  @param
//  @param
//  @return     void
//  @note       ����5�����ԭ��Ѱ�ҹյ㣬�¹յ��ͼ��Ͷ�����ɨ���Ϲյ��ͼ���Ϸ�����ɨ������ɨ�߻��ڰ����߳������⣬
//-------------------------------------------------------------------------------------------------------------------
void Identify(void)
{
    uint8 findr_x = 0;    //�ҵ�
    uint8 findr_y = 0;
    uint8 examr_x = 0;
    uint8 examr_y = 0;
    uint8 findl_x = 0;    //���
    uint8 findl_y = 0;
    uint8 examl_x = 0;
    uint8 examl_y = 0;
    uint8 star = 0;
    uint8 end = 0;
    uint8 examcount = 0;
    //uint8 count;
    //uint8 examerror;
//    uint8 dircount;
    int directionrd[5][2] =  {{-1,1}, {-1,0}, {-1,-1}, {0,1}, {1,1}};  //˳ʱ���·���������x��y
    int directionld[5][2] =  {{1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};  //��ʱ���·�������
    int directionru[5][2] =  {{1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}};  //��ʱ���Ϸ�������
    int directionlu[5][2] =  {{-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}};  //��ʱ���Ϸ�������

    //ÿ�βɼ��󶼶Թյ��־λ����
    if(Right_Up_Point_finish_flag == 1)
        Right_Up_Point_finish_flag = 0;
    if(Left_Up_Point_finish_flag == 1)
        Left_Up_Point_finish_flag = 0;
    if(Right_Down_Point_finish_flag == 1)
        Right_Down_Point_finish_flag = 0;
    if(Left_Down_Point_finish_flag == 1)
        Left_Down_Point_finish_flag = 0;
    for(uint8 y = 105 ; y >= 30 ; y--)
    {
        if(Right_Down_Point_finish_flag == 0)
        {
            if(y > Endline && Right_Black_Point[y-1]==187 && Right_Black_Point[y-2]==187 && Emo_imag[y][Right_Black_Point[y]-6] == EmoWhite
               && Emo_imag[y-2][Right_Black_Point[y]] == EmoWhite && Emo_imag[y-5][Right_Black_Point[y]] == EmoWhite)    //���¹յ�
            {
                star=y;
                for(uint8 y=star;y<=(star+18);y++)
                {
                    if(Right_Black_Point[y]<184 && Emo_abs(Right_Black_Point[y+1]-Right_Black_Point[y])<8
                    && Emo_abs(Right_Black_Point[y+2]-Right_Black_Point[y])<8)
                    {
                        findr_x=Right_Black_Point[y];
                        findr_y=y;
                        for(uint8 dircount = 0;dircount<5;dircount++)
                        {
                            examr_x=findr_x+directionrd[dircount][0];
                            examr_y=findr_y+directionrd[dircount][1];
                            if(Emo_imag[examr_y][examr_x]==255)
                            {
                                examcount++;
                            }
                        }
                        if(examcount >= 4)
                        {
                            examcount=0;
                            Right_Down_Point[0]=findr_x;
                            Right_Down_Point[1]=findr_y;
                            Right_Down_Point_finish_flag = 1;
                            break;
                        }
                        else
                        {
                            Right_Down_Point_finish_flag = 0;
                            examcount=0;
                        }
                    }
                    if(y==100)
                    {
                        Right_Down_Point_finish_flag=0;
                    }
                }
            }
        }
        if(Left_Down_Point_finish_flag == 0)
        {
            if(y > Endline && Left_Black_Point[y-1]==0 && Left_Black_Point[y-2]==0 && Emo_imag[y][Left_Black_Point[y]+6] == EmoWhite
               && Emo_imag[y-5][Left_Black_Point[y] + 1] == EmoWhite && Emo_imag[y-6][Left_Black_Point[y] + 1] == EmoWhite)     //���¹յ�
            {
                star=y;
                for(uint8 y=star;y<=(star+18);y++)
                {
                    if(Left_Black_Point[y]>4 && Emo_abs(Left_Black_Point[y+1]-Left_Black_Point[y])<8
                       && Emo_abs(Left_Black_Point[y+2]-Left_Black_Point[y])<8)
                    {
                        findl_x=Left_Black_Point[y];
                        findl_y=y;
                        for(uint8 dircount = 0;dircount<5;dircount++)
                        {
                            examl_x=findl_x+directionld[dircount][0];
                            examl_y=findl_y+directionld[dircount][1];
                            if(Emo_imag[examl_y][examl_x]==255)
                            {
                                examcount++;
                            }
                        }
                        if(examcount>=4 )
                        {
                            examcount=0;
                            Left_Down_Point[0]=findl_x;
                            Left_Down_Point[1]=findl_y;
                            Left_Down_Point_finish_flag = 1;
                            break;
                        }
                        else
                        {
                            Left_Down_Point_finish_flag = 0;
                            examcount=0;
                        }
                    }
                    if(y==100)
                    {
                        Left_Down_Point_finish_flag=0;
                    }
                }
            }
        }
    }
    if(Left_Down_Point_finish_flag==1 && Right_Down_Point_finish_flag==1)
        end=Right_Down_Point[1];
    else if(Left_Down_Point_finish_flag==1)
        end=Left_Down_Point[1];
    else if(Right_Down_Point_finish_flag==1)
        end=Right_Down_Point[1];
    else
        end=94;
    for(uint8 y=20;y<=end;y++)
    {
        if(Right_Up_Point_finish_flag == 0)
        {
            if(y > Endline && Right_Black_Point[y+1]==187 && Right_Black_Point[y+2]==187 && Right_Black_Point[y+3]==187)   //���Ϲյ�
            {
               star=y;
               for(uint8 y=star;y>=(star-22);y--)
               {
                   if(Right_Black_Point[y]<180 && Emo_abs(Right_Black_Point[y-1]-Right_Black_Point[y])<4
                   && Emo_abs(Right_Black_Point[y-2]-Right_Black_Point[y])<4 && Emo_imag[y][Right_Black_Point[y]-6] == EmoWhite
                   && Emo_imag[y-1][Right_Black_Point[y-1]-5] == EmoWhite && Emo_imag[y-2][Right_Black_Point[y]-5] == EmoWhite
                   && Emo_imag[y-3][Right_Black_Point[y]-5] == EmoWhite && Right_Black_Point[y] > Middle_Black_Point[y] && Emo_imag[y+3][Right_Black_Point[y]] == EmoWhite
                   && Emo_imag[y+5][Right_Black_Point[y]] == EmoWhite && Emo_imag[y+7][Right_Black_Point[y]] == EmoWhite)
                   {
                       findr_x=Right_Black_Point[y];
                       findr_y=y;
                       for(uint8 dircount = 0;dircount<5;dircount++)
                       {
                           examr_x=findr_x+directionru[dircount][0];
                           examr_y=findr_y+directionru[dircount][1];
                           if(Emo_imag[examr_y][examr_x]==255)
                           {
                               examcount++;
                           }
                       }
                       if(examcount>=4 && findr_y >Endline)
                       {
                           examcount=0;
                           Right_Up_Point[0]=findr_x;
                           Right_Up_Point[1]=findr_y;
                           if(Last_Right_Point[1] == 0)
                           {
                               Last_Right_Point[1] = Right_Up_Point[1];
                           }
                           if(Right_Up_Point[1] < 16)
                           {
                               Right_Up_Point[1] = Last_Right_Point[1];
                               Right_Up_Point_finish_flag = 0;
                           }
                           else
                           {
                               Right_Up_Point_finish_flag = 1;
                               Last_Right_Point[1] = Right_Up_Point[1];
                           }
                           findrcount=(int)star-(int)findr_y;
                           break;
                       }
                       else
                       {
                           Right_Up_Point_finish_flag = 0;
                           examcount=0;
                       }
                   }
                   if(y==16)
                   {
                       Right_Up_Point_finish_flag=0;
                       break;
                   }
                   if(y == 1)
                   {
                       break;
                   }
               }
            }
        }
        if(Left_Up_Point_finish_flag == 0)
        {
            if(y > Endline && Left_Black_Point[y+1]==0 && Left_Black_Point[y+2]==0 && Left_Black_Point[y+3]==0)     //���Ϲյ�
            {
                star=y;
                for(uint8 y=star;y>=(star-22);y--)
                {
                    if(Left_Black_Point[y]>8 && Emo_abs(Left_Black_Point[y-1]-Left_Black_Point[y])<4
                   && Emo_abs(Left_Black_Point[y-2]-Left_Black_Point[y])<4 && Emo_imag[y][Left_Black_Point[y]+6] == EmoWhite
                   && Emo_imag[y-1][Left_Black_Point[y-1]+5] == EmoWhite && Emo_imag[y-2][Left_Black_Point[y]+5] == EmoWhite
                   && Emo_imag[y-3][Left_Black_Point[y]+5] == EmoWhite && Left_Black_Point[y] < Middle_Black_Point[y] && Emo_imag[y+3][Left_Black_Point[y]] == EmoWhite
                   && Emo_imag[y+5][Left_Black_Point[y]] == EmoWhite && Emo_imag[y+7][Left_Black_Point[y]] == EmoWhite)
                    {
                        findl_x=Left_Black_Point[y];
                        findl_y=y;
                        for(uint8 dircount = 0;dircount<5;dircount++)
                        {
                            examl_x=findl_x+directionlu[dircount][0];
                            examl_y=findl_y+directionlu[dircount][1];
                            if(Emo_imag[examl_y][examl_x]==255)
                            {
                                examcount++;
                            }
                        }
                        if(examcount>=4 && findl_y > Endline)
                        {
                            examcount=0;
                            Left_Up_Point[0]=findl_x;
                            Left_Up_Point[1]=findl_y;
                            if(Last_Left_Point[1] == 0)
                            {
                                Last_Left_Point[1] = Left_Up_Point[1];
                            }
                            if(Left_Up_Point[1] < 16)
                            {
                                Left_Up_Point[1] = Last_Left_Point[1];
                                Left_Up_Point_finish_flag = 0;
                            }
                            else
                            {
                                Left_Up_Point_finish_flag = 1;
                                Last_Left_Point[1] = Left_Up_Point[1];
                            }
                            findlcount=(int)star-(int)y;
                            break;
                        }
                        else
                        {
                            Left_Up_Point_finish_flag = 0;
                            examcount=0;
                        }
                    }
                    if(y==16)
                    {
                        Left_Up_Point_finish_flag=0;
                        break;
                    }
                    if(y == 1)
                    {
                        break;
                    }
                }
            }
        }
    }

}




//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����Ѱ��
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Garage_Find(void)
{
    uint8 BlackonefindR = 0,BlackoneR = 0;
    uint8 WhiteonefindR = 0,WhiteoneR = 0;
    uint8 BlacktwofindR = 0,BlacktwoR = 0;
    uint8 WhitetwofindR = 0;

    uint8 BlackonefindL = 0,BlackoneL = 0;
    uint8 WhiteonefindL = 0,WhiteoneL = 0;
    uint8 BlacktwofindL = 0,BlacktwoL = 0;
    uint8 WhitetwofindL = 0;
if(Garage_Findfinish_flag == 0)
{
//    for(uint8 y=Emo_one_eighth(Right_Down_Point[1],Right_Up_Point[1]);y<=Emo_two_third(Right_Down_Point[1],Right_Up_Point[1]);y++)
      for(uint8 y=75;y<=95;y++)
    {
        if(Emo_imag[y][91] == EmoWhite)
        {
//            for(uint8 x=Right_Down_Point[0];x>(Left_Black_Point[Right_Up_Point[1]]+10);x--)
            for(uint8 x=140;x>40;x-- )
            {
                if(Emo_imag[y][x] == EmoBlack && Emo_imag[y][x-1] == EmoBlack)
                {
                    BlackonefindR = 1;
                    BlackoneR = x;

                    break;
                }
                if(x == (Left_Black_Point[Right_Up_Point[1]]+10))
                {
                    break;
                }
            }

            for(uint8 x=40;x<140;x++)
            {
                if(Emo_imag[y][x] == EmoBlack && Emo_imag[y][x+1] == EmoBlack)
                {
                    BlackonefindL = 1;
                    BlackoneL = x;
                    break;
                }
                if(x == (Right_Black_Point[Left_Up_Point[1]]-10))
                {
                    BlackonefindL = 0;
                    break;
                }
            }

        }
        if(BlackonefindR == 1 && BlackonefindL == 1)
        {
            for(uint8 x=BlackoneR;x>50;x-- )
            {
                if(Emo_imag[y][x] == EmoWhite && Emo_imag[y][x-1] == EmoWhite && x > BlackoneR - 8)
                {
                    WhiteonefindR = 1;
                    WhiteoneR = x;
                    break;
                }
                if(x == (Left_Black_Point[Right_Up_Point[1]]+10))
                {
                    BlackonefindR = 0;
                    break;
                }
            }

            for(uint8 x = BlackoneL;x<135;x++)
            {
                if(Emo_imag[y][x] == EmoWhite && Emo_imag[y][x+1] == EmoWhite && x <= BlackoneL + 8)
                {
                    WhiteonefindL = 1;
                    WhiteoneL = x;
//                    camera_p.test1_flag=x;
//                    camera_p.test2_flag=y;
                    break;
                }
                if(x == (Right_Black_Point[Left_Up_Point[1]]-10))
                {
                    BlackonefindL = 0;
                    break;
                }
            }
        }


        if(WhiteonefindR == 1 && WhiteonefindL==1)
        {
//            for(uint8 x = Whiteone;x>(Left_Black_Point[Right_Up_Point[1]]+10);x--)
            for(uint8 x=WhiteoneR;x>60;x-- )
            {
                if(Emo_imag[y][x] == EmoBlack && Emo_imag[y][x-1] == EmoBlack && x > WhiteoneR - 8)
                {
                    BlacktwofindR = 1;
                    BlacktwoR = x;
                    break;
                }
                if(x == (Left_Black_Point[Right_Up_Point[1]]+10))
                {
                    BlackonefindR = 0;
                    WhiteonefindR = 0;
                    break;
                }
            }

            for(uint8 x = WhiteoneL;x<125;x++)
            {
                if(Emo_imag[y][x] == EmoBlack && Emo_imag[y][x+1] == EmoBlack && x < WhiteoneL + 8)
                {
                    BlacktwofindL = 1;
                    break;
                }
                if(x == (Right_Black_Point[Left_Up_Point[1]]-10))
                {
                    BlackonefindL = 0;
                    WhiteonefindL = 0;
                    break;
                }
            }

        }

        if(BlacktwofindR == 1 && BlacktwofindL == 1)
        {
//            for(uint8 x = Blackone;x>(Left_Black_Point[Right_Up_Point[1]]+10);x--)
            for(uint8 x=BlacktwoR;x>70;x-- )
            {
                if(Emo_imag[y][x] == EmoWhite && Emo_imag[y][x-1] == EmoWhite && x > BlacktwoR - 8)
                {
                    WhitetwofindR = 1;
                    break;
                }
                if(x == (Left_Black_Point[Right_Up_Point[1]]+10))
                {
                    BlackonefindR = 0;
                    WhiteonefindR = 0;
                    BlacktwofindR = 0;
                    break;
                }
            }

            for(uint8 x=BlacktwoL;x<115;x++ )
            {
                if(Emo_imag[y][x] == EmoWhite && Emo_imag[y][x-1] == EmoWhite && x > BlacktwoL + 8)
                {
                    WhitetwofindL = 1;
                    break;
                }

                if(x == (Left_Black_Point[Right_Up_Point[1]]+10))
                {
                    BlackonefindL = 0;
                    WhiteonefindL = 0;
                    BlacktwofindL = 0;
                    break;
                }
            }


        }
        if((BlackonefindR == 1 && WhiteonefindR == 1 && BlacktwofindR == 1 && WhitetwofindR == 1) || (BlackonefindL == 1&& WhiteonefindL == 1 && BlacktwofindL == 1 && WhitetwofindL == 1) && Emo_u8Decabs(Emo_Angle,0)<=3)
        {
            Garage_Findfinish_flag = 1;//�ҵ������־
            Garagecount++;                 //�����������
        }
        else if(Garage_Findfinish_flag == 1)
        {
            break;
        }
    }
}


}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ݹյ�������з�����
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ����5����Ĺյ�Ѱ�һ�����ܶ�����,���Խ��з�һ��յ���ж�
//-------------------------------------------------------------------------------------------------------------------
void Element_dispose(void)
{
    if(SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0 && Garage_flag == 0 && Garage_flag == 0 && WindupR_flag == 0 && WindupL_flag == 0 && Cross_flag == 0)
    {
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1)
        {
            if(Left_Up_Point[0] - Left_Down_Point[0] > 48)
            {
                Left_Up_Point_finish_flag = 0;
                Left_Down_Point_finish_flag = 0;
            }
        }
        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1)
        {
            if(Right_Down_Point[0] - Right_Up_Point[0] > 48)
            {
                Right_Up_Point_finish_flag = 0;
                Right_Down_Point_finish_flag = 0;
            }
        }
    }
    if(SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0 && Trifork_flag == 0 && Garage_flag == 0 && Garage_flag == 0 && WindupR_flag == 0 && WindupL_flag == 0 && Cross_flag == 0)
    {
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1)
        {
            if(Left_Up_Point[0] < Left_Down_Point[0])
            {
                Left_Up_Point_finish_flag = 0;
                Left_Down_Point_finish_flag = 0;
            }
        }
        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1)
        {
            if(Right_Up_Point[0] > Right_Down_Point[0])
            {
                Right_Up_Point_finish_flag = 0;
                Right_Down_Point_finish_flag = 0;
            }
        }
        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1)
        {
            if(Right_Down_Point[1] - Right_Up_Point[1] < 15)
            {
                Right_Up_Point_finish_flag = 0;
                Right_Down_Point_finish_flag = 0;
            }
        }
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1)
        {
            if(Left_Down_Point[1] - Left_Up_Point[1] < 15)
            {
                Left_Up_Point_finish_flag = 0;
                Left_Down_Point_finish_flag = 0;
            }
        }
        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1)
        {
            if(Right_Down_Point[0] > 170 && Right_Up_Point[0] > 170)
            {
                Right_Up_Point_finish_flag = 0;
                Right_Down_Point_finish_flag = 0;
            }
        }
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1)
        {
            if(Left_Down_Point[0] > 170 && Left_Up_Point[0] > 170)
            {
                Left_Up_Point_finish_flag = 0;
                Left_Down_Point_finish_flag = 0;
            }
        }
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1  && (Right_Black_Point[Left_Up_Point[1]] - Right_Black_Point[Left_Down_Point[1]] < 0) && Garage_Findfinish_flag == 0)
        {
            if( Right_Up_Point_finish_flag == 0 && Right_Down_Point_finish_flag == 0)
            {
                Garage_Find();
            }
            if(Garage_Findfinish_flag == 1)
            {
                Garage_flag = 1;
            }
            else
            {
                if((Left_Down_Point[1] - Left_Up_Point[1] > 32))
                {
                    WindupL_flag = 1;
                }
            }
        }
        else if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 &&  (Left_Black_Point[Right_Up_Point[1]] - Left_Black_Point[Right_Down_Point[1]] > 0) && Garage_Findfinish_flag == 0)
        {
            if((Right_Down_Point[1] - Right_Up_Point[1] <= 32) && Left_Up_Point_finish_flag == 0 && Left_Down_Point_finish_flag == 0)
            {
                Garage_Find();
            }
            if(Garage_Findfinish_flag == 1)
            {
                Garage_flag = 1;
            }
            else
            {
                if((Right_Down_Point[1] - Right_Up_Point[1] > 32))
                {
                    WindupR_flag = 1;
                }
            }
        }

    }

}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���⺯��
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��Ϊ�����߶�����ɨ�ߵ�Ӱ�죬ֱ��ǿ�в��߱�֤˳��ͨ��������
//-------------------------------------------------------------------------------------------------------------------

void Garage(void)
{
        Garage_Find();//�Ұ�����
        if(Garagecount >= GarageIn )   //�����������&& dieReady == 4
        {
            camera_p.Garage_In_flag = 1;//ͣ����־
        }


}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ʮ�ֺ���
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Cross(void)
{
    if(Cross_flag == 1)//
        {
            if(Crosscount == 0)
            {
                Crosscount = 1;
            }
            if(Crosscount == 1)
            {
                if(Left_Up_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1
                && Left_Down_Point[1] >= 74 && Right_Down_Point[1] >= 74)
                {
                    Crosscount = 2;
                }
            }
            if(Crosscount == 2)
            {
                if((Left_Up_Point[1] >= 78 || Right_Up_Point[1] >= 78))
                {
                    Crosscount = 3;
                }
            }
            else {
                Crosscount = 3;
            }
            switch(Crosscount)
            {
                case 1 :
                    Link_Left_One_Point[0] = Left_Down_Point[0];
                    Link_Left_One_Point[1] = Left_Down_Point[1];
                    Link_Left_Two_Point[0] = Left_Up_Point[0];
                    Link_Left_Two_Point[1] = Left_Up_Point[1];
                    Link_Right_One_Point[0] = Right_Down_Point[0];
                    Link_Right_One_Point[1] = Right_Down_Point[1];
                    Link_Right_Two_Point[0] = Right_Up_Point[0];
                    Link_Right_Two_Point[1] = Right_Up_Point[1];
                    PaddingR = 1;
                    PaddingL = 1;
                    break;
                case 2 :
                    Link_Left_One_Point[0] = 40;
                    Link_Left_One_Point[1] = 119;
                    Link_Left_Two_Point[0] = Left_Up_Point[0];
                    Link_Left_Two_Point[1] = Left_Up_Point[1];
                    Link_Right_One_Point[0] = 140;
                    Link_Right_One_Point[1] = 119;
                    Link_Right_Two_Point[0] = Right_Up_Point[0];
                    Link_Right_Two_Point[1] = Right_Up_Point[1];
                    PaddingR = 1;
                    PaddingL = 1;
                    break;
                case 3 :
                    Cross_flag = 0;
                    Crosscount = 0;
                    PaddingR = 0;
                    PaddingL = 0;
                    //Beepindex = 0;
                    break;
            }
        }
}


//Ԫ��ǰҡ
//-------------------------------------------------------------------------------------------------------------------
//  @brief      Ԫ��ǰҡ
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��ɨ�赽�������ϵ����������յ��������ιյ�����ж���ʲôԪ�أ��жϰ���Բ����ʮ�֡�P��
//-------------------------------------------------------------------------------------------------------------------
void Windup(void)
{
    if(WindupL_flag == 1)
    {
        Link_Left_One_Point[0] = Left_Down_Point[0];
        Link_Left_One_Point[1] = Left_Down_Point[1];
        Link_Left_Two_Point[0] = Left_Up_Point[0];
        Link_Left_Two_Point[1] = Left_Up_Point[1];
        PaddingR = 0;
        PaddingL = 1;
        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 && Left_Down_Point[1] > 42 && findlcount < 6 && Left_Up_Point[0] > 30)
        {
            Cross_flag = 1;
            WindupL_flag = 0;
        }
        else if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 &&
                Right_Up_Point_finish_flag == 0 && Right_Down_Point_finish_flag == 0
                && Left_Down_Point[1] >= 75 && Left_Down_Point[1] <= 105 && findlcount < 4 && Left_Up_Point[0] > 30
                && (Left_Up_Point[0] - Left_Down_Point[0]) <= 42 && (Left_Down_Point[1] - Left_Up_Point[1]) >= 45
                && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[(Left_Up_Point[1]+Left_Down_Point[1])/2]
                && Right_Black_Point[(Left_Up_Point[1]+Left_Down_Point[1])/2] <  Right_Black_Point[Left_Down_Point[1]]
                && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Emo_one_third(Left_Down_Point[1],Left_Up_Point[1])]
                && Right_Black_Point[Emo_one_third(Left_Down_Point[1],Left_Up_Point[1])] <  Right_Black_Point[Left_Down_Point[1]]
                && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Emo_two_third(Left_Down_Point[1],Left_Up_Point[1])]
                && Right_Black_Point[Emo_two_third(Left_Down_Point[1],Left_Up_Point[1])] <  Right_Black_Point[Left_Down_Point[1]]
                && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Left_Down_Point[1]])
        {
            SlalomLeft_flag = 1;
            Slalomcount = 1;
            WindupL_flag = 0;
        }
        else if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 &&
                Right_Up_Point_finish_flag == 0 && Right_Down_Point_finish_flag == 0
                && Left_Down_Point[1] >= 75 && findlcount >= 8 && Left_Up_Point[0] > 30 && (Left_Down_Point[1] - Left_Up_Point[1]) >= 45
                && (Left_Down_Point[1] - Left_Up_Point[1]) <= 78 && Emo_imag[Left_Up_Point[1]][Left_Up_Point[0] - 5] != EmoWhite
                && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[(Left_Up_Point[1]+Left_Down_Point[1])/2]
                && Right_Black_Point[(Left_Up_Point[1]+Left_Down_Point[1])/2] <  Right_Black_Point[Left_Down_Point[1]]
                && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Emo_one_third(Left_Down_Point[1],Left_Up_Point[1])]
                && Right_Black_Point[Emo_one_third(Left_Down_Point[1],Left_Up_Point[1])] <  Right_Black_Point[Left_Down_Point[1]]
                && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Emo_two_third(Left_Down_Point[1],Left_Up_Point[1])]
                && Right_Black_Point[Emo_two_third(Left_Down_Point[1],Left_Up_Point[1])] <  Right_Black_Point[Left_Down_Point[1]]
                && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Left_Down_Point[1]])
        {
            if(findlcount >= 16)
            {
                CircleBig = 1;
            }
            CircleLeft_flag = 1;
            Circlecount = 1;
            WindupL_flag = 0;
        }
        else if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 0 && Right_Down_Point_finish_flag == 0 && findlcount <= 17)//&& Left_Down_Point[1] <= 110
        {
            Garage_Find();
            if(Garage_Findfinish_flag == 1)
            {
                Garage_flag = 1;
                WindupL_flag = 0;
            }
        }
        else if(Left_Down_Point_finish_flag == 0)
        {
            WindupL_flag = 0;
            PaddingR = 0;
            PaddingL = 0;
//            //Beepindex = 0;
        }
    }


    else if(WindupR_flag == 1)
    {
        Link_Right_One_Point[0] = Right_Down_Point[0];
        Link_Right_One_Point[1] = Right_Down_Point[1];
        Link_Right_Two_Point[0] = Right_Up_Point[0];
        Link_Right_Two_Point[1] = Right_Up_Point[1];
        PaddingR = 1;
        PaddingL = 0;
        if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && Right_Down_Point[1] > 42 && findrcount < 6 && Right_Up_Point[0] < 158)
        {
            Cross_flag = 1;
            WindupR_flag = 0;
        }
        else if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 &&
                Left_Up_Point_finish_flag == 0 && Left_Down_Point_finish_flag == 0
            && Right_Down_Point[1] >= 75 && Right_Down_Point[1] <= 105 && findrcount < 4 && Right_Up_Point[0] < 158
            && (Right_Down_Point[0] - Right_Up_Point[0]) <= 42 && Right_Down_Point[1] - Right_Up_Point[1] >= 45
            && Right_Down_Point[1] - Right_Up_Point[1] <= 78 && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] != EmoWhite
            && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[(Right_Up_Point[1]+Right_Down_Point[1])/2]
            && Left_Black_Point[(Right_Up_Point[1]+Right_Down_Point[1])/2] >  Left_Black_Point[Right_Down_Point[1]]
            && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Emo_one_third(Right_Down_Point[1],Right_Up_Point[1])]
            && Left_Black_Point[Emo_one_third(Right_Down_Point[1],Right_Up_Point[1])] >  Left_Black_Point[Right_Down_Point[1]]
            && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Emo_two_third(Right_Down_Point[1],Right_Up_Point[1])]
            && Left_Black_Point[Emo_two_third(Right_Down_Point[1],Right_Up_Point[1])] >  Left_Black_Point[Right_Down_Point[1]]
            && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Right_Down_Point[1]])
        {
            SlalomRight_flag = 1;
            Slalomcount = 1;
            WindupR_flag = 0;
        }
        else if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 &&
                Left_Up_Point_finish_flag == 0 && Left_Down_Point_finish_flag == 0
            && Right_Down_Point[1] >= 75 && findrcount >= 9 && Right_Up_Point[0] < 158 && Right_Down_Point[1] - Right_Up_Point[1] >= 45
            && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[(Right_Up_Point[1]+Right_Down_Point[1])/2]
            && Left_Black_Point[(Right_Up_Point[1]+Right_Down_Point[1])/2] >  Left_Black_Point[Right_Down_Point[1]]
            && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Emo_one_third(Right_Down_Point[1],Right_Up_Point[1])]
            && Left_Black_Point[Emo_one_third(Right_Down_Point[1],Right_Up_Point[1])] >  Left_Black_Point[Right_Down_Point[1]]
            && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Emo_two_third(Right_Down_Point[1],Right_Up_Point[1])]
            && Left_Black_Point[Emo_two_third(Right_Down_Point[1],Right_Up_Point[1])] >  Left_Black_Point[Right_Down_Point[1]]
            && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Right_Down_Point[1]])
        {
            CircleRight_flag = 1;
            Circlecount = 1;
            WindupR_flag = 0;
        }
        else if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 &&
                Left_Up_Point_finish_flag == 0 && Left_Down_Point_finish_flag == 0  && findrcount <= 17)//&& Right_Down_Point[1] <= 110
        {
            Garage_Find();
            if(Garage_Findfinish_flag == 1)
            {
                Garage_flag = 1;
                WindupR_flag = 0;
            }
        }
        else if(Right_Down_Point_finish_flag == 0)
        {
            WindupR_flag = 0;
            PaddingR = 0;
            PaddingL = 0;
        }
    }
}

//����һЩ�յ������
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����һЩ�յ������
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       ��Ϊ�����������¹յ����µĶ������ƫ���ߵļ���
//-------------------------------------------------------------------------------------------------------------------
void Point_ClearDL(uint8 y)
{
    for(uint8 i=y;i>=y-10;i--)
    {
        if(Left_Black_Point[i] == 0)
        {
            break;
        }
        else
        {
            Left_Black_Point[i] = 0;
        }
    }
}

void Point_ClearDR(uint8 y)
{
    for(uint8 i=y;i>=y-10;i--)
    {
        if(Right_Black_Point[i] == 187)
        {
            break;
        }
        else
        {
            Right_Black_Point[i] = 187;
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      P�ֳ�P�Ĳ��ߵ���Ѱ
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       P�ֺ����ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void SlalomPoint(void)
{
    if(SlalomLeft_flag == 1)
    {
        for(uint8 y = Right_Down_Point[1];y>10;y--)
        {
            if(Emo_imag[y+1][Right_Down_Point[0]-(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5)] == EmoWhite
            && Emo_imag[y][Right_Down_Point[0]-(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5)] == EmoBlack
            && Emo_imag[y-1][Right_Down_Point[0]-(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5)] == EmoBlack
            && Emo_imag[y-2][Right_Down_Point[0]-(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5)] == EmoBlack)
            {
                Slalom_Point[0]=Right_Down_Point[0]-(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5);
                Slalom_Point[1]=y;
                break;
            }
            if(y==10)
            {
                Slalom_Point[0]=Right_Down_Point[0]-(((Right_Down_Point[0]-Left_Down_Point[0]))/2);
                Slalom_Point[1]=Right_Down_Point[1]/2;
                break;
            }
        }
    }
    else
    {
        for(uint8 y = Left_Down_Point[1];y>10;y--)
        {
            if(Emo_imag[y+1][Left_Down_Point[0]+(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5)] == EmoWhite
            && Emo_imag[y][Left_Down_Point[0]+(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5)] == EmoBlack
            && Emo_imag[y-1][Left_Down_Point[0]+(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5)] == EmoBlack
            && Emo_imag[y-2][Left_Down_Point[0]+(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5)] == EmoBlack)
            {
                Slalom_Point[0]=Left_Down_Point[0]+(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5);
                Slalom_Point[1]=y;
                break;
            }
            if(y==10)
            {
                Slalom_Point[0]=Left_Down_Point[0]+(((Right_Down_Point[0]-Left_Down_Point[0])*2)/5);
                Slalom_Point[1]=Left_Down_Point[1]/2;
                break;
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      P�ֺ���
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Slalom(void)
{

    if(SlalomRight_flag == 1)  //��
   {
       if(Slalomcount == 1)
       {
           if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 0 && Right_Down_Point[1] > 80)     //�Ϲղ���
           {
               Slalomcount=2;
           }
       }
       if(Slalomcount == 2)
       {
           if(Right_Up_Point_finish_flag == 0 && Right_Up_Point[1] > 70)    //���
           {
               Slalomcount=3;
           }
       }
       if(Slalomcount == 3)
       {
           Gyroscope_Star_flag = 1;
           EncoderSum_flag = 0;
           if(Emo_Angle >= 40)   //���ֲ��ó��ֵ������Slalomȡ��
           {

               Gyroscope_Star_flag = 0;
               need_cornerL = 0;
               PaddingR = 0;
               PaddingL = 0;
               SlalomRight_flag = 0;
               Slalom_Padding = 0;
               Slalomcount = 0;
               Paddingcurve = 0;
               //Beepindex = 0;
           }
           if(Left_Down_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1)   //��Slalom
           {
               SlalomPoint();
               Slalomcount = 4;

           }
       }
       if(Slalomcount == 4)
       {
           Paddingcurve = 1;
           SlalomPoint();
           if((Left_Down_Point[0]/2 + Right_Down_Point[0]/2) <= 128)
           {

           }
           if(Left_Down_Point[1] > 73)
           {
               ObservationS_finish = 1;
           }
           if(Real_Distance >= 3100 && Emo_Angle >= 35)
           {
               CorneringS_finish = 1;
               Auxiliary_CorneringLeft_flag = 0;
           }
           if(ObservationS_finish == 1 && CorneringS_finish == 1)
           {
               Auxiliary_CorneringLeft_flag = 0;
               Gyroscope_Star_flag = 0;
               EncoderSum_flag = 0;
               Slalomcount = 5;
               CorneringS_finish = 0;
               ObservationS_finish = 0;
           }
       }
       switch(Slalomcount)
       {
           case 1 :
               Link_Right_One_Point[0] = Right_Down_Point[0];
               Link_Right_One_Point[1] = Right_Down_Point[1];
               Link_Right_Two_Point[0] = Right_Up_Point[0];
               Link_Right_Two_Point[1] = Right_Up_Point[1];
               PaddingR = 1;
               PaddingL = 0;
               break;
           case 2 :
               Link_Right_One_Point[0] = Right_Down_Point[0];
               Link_Right_One_Point[1] = Right_Down_Point[1];
               Link_Right_Two_Point[0] = Right_Up_Point[0];
               Link_Right_Two_Point[1] = Right_Up_Point[1];
               PaddingR = 1;
               PaddingL = 0;
               break;
           case 3 :
               Corners_flag = 1;
               PaddingR = 0;
               PaddingL = 0;
               break;
           case 4 :
               Link_Right_One_Point[0] = Slalom_Point[0];
               Link_Right_One_Point[1] = Slalom_Point[1];
               Link_Right_Two_Point[0] = Right_Down_Point[0];
               Link_Right_Two_Point[1] = Right_Down_Point[1];
               Point_ClearDL(Left_Down_Point[1]);
               Corners_flag = 0;
               Slalom_Padding = 1;

               if(Slalom_Point[1] >= 42)
               {
                   need_cornerL = 1;
               }
               PaddingR = 1;
               PaddingL = 0;
               break;
           case 5 :

               SlC++;
               need_cornerL = 0;
               PaddingR = 0;
               PaddingL = 0;
               SlalomRight_flag = 0;
               Slalom_Padding = 0;
               Slalomcount = 0;
               Paddingcurve = 0;
               //Beepindex = 0;
               break;
       }
   }
   else if(SlalomLeft_flag == 1)
   {
       if(Slalomcount == 1)
       {
           if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 0 && Left_Down_Point[1] > 80)     //�Ϲղ���
           {
               Slalomcount=2;
           }
       }
       if(Slalomcount == 2)
       {
           if(Left_Up_Point_finish_flag == 0 && Left_Up_Point[1] > 70)    //���
           {
               Slalomcount=3;
           }
       }
       if(Slalomcount == 3)
       {
           if(Emo_Angle <= -40)
           {

               Gyroscope_Star_flag = 0;
               need_cornerR = 0;
               PaddingR = 0;
               PaddingL = 0;
               SlalomLeft_flag = 0;
               Near_Corners_flag = 0;
               Slalom_Padding = 0;
               Slalomcount = 0;
               Paddingcurve = 0;
           }
           if(Right_Down_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1)   //��Slalomm
           {
               SlalomPoint();
               Slalomcount = 4;
               Gyroscope_Star_flag = 0;
               Clear_Gyroscope_Angle();
           }
       }
       if(Slalomcount == 4)
       {
           Paddingcurve = 1;
           SlalomPoint();
           if((Left_Down_Point[0]/2 + Right_Down_Point[0]/2) >= 60)  //�����תλ��
           {
               EncoderSum_flag = 1;
               Gyroscope_Star_flag = 1;
           }
           if(Right_Down_Point[1] > 73)
           {
               ObservationS_finish = 1;
           }
           if(Real_Distance >= 3100 && Emo_Angle <= -35)     //���ת�������
           {
               CorneringS_finish = 1;
               Auxiliary_CorneringRight_flag = 0;
           }
           if(ObservationS_finish == 1 && CorneringS_finish == 1)
           {
               Auxiliary_CorneringRight_flag = 0;
               Gyroscope_Star_flag = 0;
               EncoderSum_flag = 0;
               Slalomcount = 5;
               CorneringS_finish = 0;
               ObservationS_finish = 0;
           }
       }
       switch(Slalomcount)
       {
           case 1 :
               Link_Left_One_Point[0] = Left_Down_Point[0];
               Link_Left_One_Point[1] = Left_Down_Point[1];
               Link_Left_Two_Point[0] = Left_Up_Point[0];
               Link_Left_Two_Point[1] = Left_Up_Point[1];
               PaddingR = 0;
               PaddingL = 1;
               break;
           case 2 :
               Link_Left_One_Point[0] = Left_Down_Point[0];
               Link_Left_One_Point[1] = Left_Down_Point[1];
               Link_Left_Two_Point[0] = Left_Up_Point[0];
               Link_Left_Two_Point[1] = Left_Up_Point[1];
               PaddingR = 0;
               PaddingL = 1;
               break;
           case 3 :
               Corners_flag = 1;
               PaddingR = 0;
               PaddingL = 0;
               break;
           case 4 :
               Link_Left_One_Point[0] = Slalom_Point[0];
               Link_Left_One_Point[1] = Slalom_Point[1];
               Link_Left_Two_Point[0] = Left_Down_Point[0];
               Link_Left_Two_Point[1] = Left_Down_Point[1];
               Point_ClearDR(Right_Down_Point[1]);
               Corners_flag = 0;
               Slalom_Padding = 1;
               PaddingR = 0;
               PaddingL = 1;
               break;
           case 5 :

               SlC++;
               need_cornerR = 0;
               PaddingR = 0;
               PaddingL = 0;
               SlalomLeft_flag = 0;
               Near_Corners_flag = 0;
               Slalom_Padding = 0;
               Slalomcount = 0;
               //Beepindex = 0;
               Paddingcurve = 0;
               break;
       }
   }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��Բ���Ĳ��ߵ���Ѱ
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       Բ�������ڲ�����
//-------------------------------------------------------------------------------------------------------------------
void CircleOutPoint(void)
{
    if(CircleLeft_flag == 1)
    {
        for(int y = Right_Down_Point[1];y>=20;y--)
        {
            if(Emo_imag[y+1][Right_Down_Point[0] - 78] == EmoWhite && Emo_imag[y][Right_Down_Point[0] - 78] == EmoBlack && Emo_imag[y-1][Right_Down_Point[0] - 78] == EmoBlack && Emo_imag[y-2][Right_Down_Point[0] - 78] == EmoBlack)
            {
                CircleOut_Point[0] = Right_Down_Point[0] - 78;
                CircleOut_Point[1] = (uint8)y;
                break;
            }
            if(y==20)
            {
                CircleOut_Point[0] = Right_Down_Point[0] - 78;
                CircleOut_Point[1] = 20;
                break;
            }
        }
    }
    else if(CircleRight_flag == 1)
    {
        for(int y = Left_Down_Point[1];y>=20;y--)
        {
            if(Emo_imag[y+1][Left_Down_Point[0] + 85] == EmoWhite && Emo_imag[y][Left_Down_Point[0] + 85] == EmoBlack && Emo_imag[y-1][Left_Down_Point[0] + 85] == EmoBlack && Emo_imag[y-2][Left_Down_Point[0] + 85] == EmoBlack)
            {
                CircleOut_Point[0] = Left_Down_Point[0] + 85;
                CircleOut_Point[1] = (uint8)y;
                break;
            }
            if(y==20)
            {
                CircleOut_Point[0] = Left_Down_Point[0] + 85;
                CircleOut_Point[1] = 20;
                break;
            }
        }
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      Բ���Ĳ���ʶ��
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
static unsigned char circlrsu = 0;
void Circle_supplement(void)
{
    if(CornerLeft_flag == 0 && CornerRight_flag == 0 && Corners_flag == 0
    && Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1 && Right_Up_Point[1] >= 25
    && Right_Up_Point[1] <= 50 && Right_Up_Point[0] < 145 && Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 0
    && WindupL_flag == 0 && WindupR_flag == 0
    && SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0
    && camera_p.Garage_In_flag == 0 && Cross_flag == 0 && CornerS_flag == 0
    && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[(Right_Up_Point[1]+105)/2]
    && Left_Black_Point[(Right_Up_Point[1]+105)/2] >  Left_Black_Point[105]
    && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Emo_one_third(105,Right_Up_Point[1])]
    && Left_Black_Point[Emo_one_third(105,Right_Up_Point[1])] >  Left_Black_Point[105]
    && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Emo_two_third(105,Right_Up_Point[1])]
    && Left_Black_Point[Emo_two_third(105,Right_Up_Point[1])] >  Left_Black_Point[105]
    && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[105]
    && Emo_imag[Right_Up_Point[1] + 5][Right_Up_Point[0] + 10] == EmoWhite
    && Emo_imag[Right_Up_Point[1] - 5][Right_Up_Point[0] - 10] == EmoWhite
    &&  Left_Black_Point[Right_Up_Point[1]] == EmoBlack && Left_Black_Point[Right_Up_Point[1] - 10] == EmoBlack
    )//&& Right_Black_Point[112] == 187 && Right_Black_Point[113] == 187 && Right_Black_Point[115] == 187  && findrcount <= 4
    {
        CircleRight_flag = 1;
    }
//    if(CornerLeft_flag == 0 && CornerRight_flag == 0 && WindupL_flag == 0 && WindupR_flag == 0
//       && SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0 && camera_p.Garage_In_flag == 0
//       && Emo_imag[Left_Up_Point[1] - 5][Left_Up_Point[0] + 20] == EmoWhite && Emo_imag[Left_Up_Point[1] + 15][Left_Up_Point[0] - 15] == EmoWhite
//       && Left_Up_Point[1] >= 20 && Right_Up_Point[1] == 0 && Right_Down_Point[1] == 0
//       && Emo_u8Decabs(Right_Black_Point[Left_Up_Point[1]],Right_Black_Point[Left_Up_Point[1]+30])<20 && Emo_u8Decabs(Right_Black_Point[Left_Up_Point[1]],Right_Black_Point[Left_Up_Point[1]+15])<10)
   if(CornerLeft_flag == 0 && CornerRight_flag == 0 && Corners_flag == 0&& Right_Down_Point_finish_flag == 0
    && Right_Up_Point_finish_flag == 0 && Left_Up_Point[1] >= 25 && Left_Up_Point[1] <= 50 && Left_Up_Point[0] > 45
    && Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1
    && camera_p.Garage_In_flag == 0 && WindupL_flag == 0 && WindupR_flag == 0
    && SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0
    && Cross_flag == 0 && CornerS_flag == 0
    && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[(Left_Up_Point[1]+105)/2]
    && Right_Black_Point[(Left_Up_Point[1]+105)/2] <  Right_Black_Point[105]
    && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Emo_one_third(105,Left_Up_Point[1])]
    && Right_Black_Point[Emo_one_third(105,Left_Up_Point[1])] <  Right_Black_Point[105]
    && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Emo_two_third(105,Left_Up_Point[1])]
    && Right_Black_Point[Emo_two_third(105,Left_Up_Point[1])] <  Right_Black_Point[105]
    && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[105]
    && Emo_imag[Left_Up_Point[1]][Left_Up_Point[0] - 10] == EmoWhite
    && Emo_imag[Left_Up_Point[1] - 1][Left_Up_Point[0] - 10] == EmoWhite
    && Right_Black_Point[Left_Up_Point[1]] == EmoBlack && Right_Black_Point[Left_Up_Point[1] - 10] == EmoBlack)//&& findrcount <= 4 && Left_Black_Point[112] == 0 && Left_Black_Point[113] == 0 && Left_Black_Point[115] == 0
    {
        CircleLeft_flag = 1;
    }

  else if(dieReady == 2 && CornerLeft_flag == 0 && CornerRight_flag == 0 && Corners_flag == 0  
  && Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1 && Right_Up_Point[1] >= 25 && Right_Up_Point[1] <= 66 && Right_Up_Point[0] < 165 && Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 0
  && WindupL_flag == 0 && WindupR_flag == 0
  && SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0
  && camera_p.Garage_In_flag == 0 && Cross_flag == 0 && Trifork_flag == 0
  && CornerS_flag == 0
  && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[(Right_Up_Point[1]+105)/2]
  && Left_Black_Point[(Right_Up_Point[1]+105)/2] >  Left_Black_Point[105]
  && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Emo_one_third(105,Right_Up_Point[1])]
  && Left_Black_Point[Emo_one_third(105,Right_Up_Point[1])] >  Left_Black_Point[105]
  && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[Emo_two_third(105,Right_Up_Point[1])]
  && Left_Black_Point[Emo_two_third(105,Right_Up_Point[1])] >  Left_Black_Point[105]
  && Left_Black_Point[Right_Up_Point[1]] > Left_Black_Point[105]
  && Left_Black_Point[10] > Left_Black_Point[Right_Up_Point[1]] && Left_Black_Point[10] > Left_Black_Point[(Right_Up_Point[1]+10)/2]
  && Right_Black_Point[Right_Up_Point[1]] <= Right_Black_Point[Right_Up_Point[1]+1] && Right_Black_Point[Right_Up_Point[1]+1] <= Right_Black_Point[Right_Up_Point[1]+2]
  && Right_Black_Point[Right_Up_Point[1]+2] <= Right_Black_Point[Right_Up_Point[1]+3] && Right_Black_Point[Right_Up_Point[1]+3] <= Right_Black_Point[Right_Up_Point[1]+4]
  && Right_Black_Point[Right_Up_Point[1]+4] <= Right_Black_Point[Right_Up_Point[1]+5] && Right_Black_Point[Right_Up_Point[1]+5] <= Right_Black_Point[Right_Up_Point[1]+6]
  && Right_Black_Point[Right_Up_Point[1]] < Right_Black_Point[Right_Up_Point[1]+5] && Right_Black_Point[Right_Up_Point[1]+1] < Right_Black_Point[Right_Up_Point[1]+6]
  && Right_Black_Point[Right_Up_Point[1]] < Right_Black_Point[Right_Up_Point[1]+8] && Right_Black_Point[Right_Up_Point[1]+1] < Right_Black_Point[Right_Up_Point[1]+9]
  && Right_Black_Point[Right_Up_Point[1]] < Right_Black_Point[Right_Up_Point[1]+11] && Right_Black_Point[Right_Up_Point[1]+1] < Right_Black_Point[Right_Up_Point[1]+12])
  {
      for(uint8 y=Right_Up_Point[1] - 3;y>=5;y--)
      {
          if(circlrsu == 0 && Right_Black_Point[y] <= Right_Black_Point[y-1] && Right_Black_Point[y-1] <= Right_Black_Point[y-2] && Right_Black_Point[y] < Right_Black_Point[y-2] )
          {
              circlrsu = 1;
          }
          if(circlrsu == 1)
          {
              if(Right_Black_Point[y] <= 187 && Right_Black_Point[y-1] >= 177 && Right_Black_Point[y-2] >= 177)
              {
                  CircleRight_flag = 1;
     
                  circlrsu = 0;
                  break;
              }
          }
          if(y == 5)
          {
              circlrsu = 0;
              break;
          }

      }
  }
  else if(CornerLeft_flag == 0 && CornerRight_flag == 0 && Corners_flag == 0  
  && Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 0 && Left_Up_Point[1] >= 25 && Left_Up_Point[1] <= 66 && Left_Up_Point[0] > 25 && Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1
  && WindupL_flag == 0 && WindupR_flag == 0
  && SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0
  && camera_p.Garage_In_flag == 0 && Cross_flag == 0 && Trifork_flag == 0
  && CornerS_flag == 0 && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[(Left_Up_Point[1]+105)/2]
  && Right_Black_Point[(Left_Up_Point[1]+105)/2] <  Right_Black_Point[105]
  && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Emo_one_third(105,Left_Up_Point[1])]
  && Right_Black_Point[Emo_one_third(105,Left_Up_Point[1])] <  Right_Black_Point[105]
  && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[Emo_two_third(105,Left_Up_Point[1])]
  && Right_Black_Point[Emo_two_third(105,Left_Up_Point[1])] <  Right_Black_Point[105]
  && Right_Black_Point[Left_Up_Point[1]] < Right_Black_Point[105]
  && Right_Black_Point[10] < Right_Black_Point[Left_Up_Point[1]] && Right_Black_Point[10] < Right_Black_Point[(Left_Up_Point[1]+10)/2]
  && Left_Black_Point[Left_Up_Point[1]] >= Left_Black_Point[Left_Up_Point[1]+1] && Left_Black_Point[Left_Up_Point[1]+1] >= Left_Black_Point[Left_Up_Point[1]+2]
  && Left_Black_Point[Left_Up_Point[1]+2] >= Left_Black_Point[Left_Up_Point[1]+3] && Left_Black_Point[Left_Up_Point[1]+3] >= Left_Black_Point[Left_Up_Point[1]+4]
  && Left_Black_Point[Left_Up_Point[1]+4] >= Left_Black_Point[Left_Up_Point[1]+5] && Left_Black_Point[Left_Up_Point[1]+5] >= Left_Black_Point[Left_Up_Point[1]+6]
  && Left_Black_Point[Left_Up_Point[1]] > Left_Black_Point[Left_Up_Point[1]+5] && Left_Black_Point[Left_Up_Point[1]+1] > Left_Black_Point[Left_Up_Point[1]+6]
  && Left_Black_Point[Left_Up_Point[1]] > Left_Black_Point[Left_Up_Point[1]+8] && Left_Black_Point[Left_Up_Point[1]+1] > Left_Black_Point[Left_Up_Point[1]+9]
  && Left_Black_Point[Left_Up_Point[1]] > Left_Black_Point[Left_Up_Point[1]+11] && Left_Black_Point[Left_Up_Point[1]+1] > Left_Black_Point[Left_Up_Point[1]+12])
  {
      for(uint8 y=Left_Up_Point[1] - 3;y>=5;y--)
      {
          if(circlrsu == 0 && Left_Black_Point[y] >= Left_Black_Point[y-1] && Left_Black_Point[y-1] >= Left_Black_Point[y-2] && Left_Black_Point[y] > Left_Black_Point[y-2] )
          {
              circlrsu = 1;
          }
          if(circlrsu == 1)
          {
              if(Left_Black_Point[y] >= 0 && Left_Black_Point[y-1] <= 10 && Left_Black_Point[y-2] <= 10)
              {
                  CircleLeft_flag = 1;
                  Circlecount = 12;
                  //CircleBig = 1;
                  circlrsu = 0;
                  break;
              }
          }
          if(y == 5)
          {
              circlrsu = 0;
              break;
          }
      }
  }


}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      Բ������
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
static uint8 RX = 0;
static uint8 RY = 0;
static int await = 0;
static unsigned char CC = 0;
//Բ��,������ۣ���һ����һ��
void Circle(void)
{
    uint8 ReplacePoint = 0;
    Circle_supplement();
    if(CircleLeft_flag == 1)
       {
           if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && Circlecount == 0)  //���¹ղ���&& findlcount > 6
           {
               Circlecount = 1;
           }
           if(Circlecount == 1)
           {
               if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 0 && Left_Down_Point[1] > 70)    //�¹���ʧ�Ϲղ���
               {
                   Circlecount = 2;
               }
               else if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1
                   && Emo_imag[Left_Up_Point[1] + 5][Left_Up_Point[0] - 5] == EmoWhite && Left_Up_Point[1] > 15)//&& findlcount <= 3
               {
                   Circlecount = 4;
               }
               else if(Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1
                    && Emo_imag[Left_Up_Point[1] + 5][Left_Up_Point[0] - 5] == EmoWhite && Left_Up_Point[1] > 15)
               {
                   Circlecount = 4;
               }
           }
           if(Circlecount == 2)
           {
               if(Left_Down_Point_finish_flag == 1 || Left_Up_Point_finish_flag == 0)    //�¹ճ��֣����Ϲ�
               {
                   Circlecount = 3;
               }
               else if(Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1
                    && Emo_imag[Left_Up_Point[1] + 5][Left_Up_Point[0] - 5] == EmoWhite && Left_Up_Point[1] > 15)
               {
                   Circlecount = 4;
               }
               else if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && findlcount <= 3
                    && Emo_imag[Left_Up_Point[1] + 5][Left_Up_Point[0] - 5] == EmoWhite && Left_Up_Point[1] > 15)
               {
                   Circlecount = 4;
               }
           }
           if(Circlecount == 3)
           {
               if(Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1
               && Emo_imag[Left_Up_Point[1] + 5][Left_Up_Point[0] - 5] == EmoWhite)        //�Ϲ�б���߽���
               {
                   Circlecount = 4;
               }
               else if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && findlcount <= 3
                    && Emo_imag[Left_Up_Point[1] + 5][Left_Up_Point[0] - 5] == EmoWhite && Left_Up_Point[1] > 15)
               {
                   Circlecount = 4;
               }
               else if(Left_Up_Point_finish_flag == 1 && Left_Up_Point[1] <= 40 && findlcount <= 4 && Left_Up_Point[1] > 15)
               {
                   Circlecount = 4;
               }
           }
           if(Circlecount == 4)
           {
               if(Left_Up_Point[1] < (RY - 10) && Emo_imag[Left_Up_Point[1]][Left_Up_Point[0] - 10] != EmoWhite)
               {
                   Left_Up_Point[0] = RX;
                   Left_Up_Point[1] = RY;
               }
               RX = Left_Up_Point[0];
               RY = Left_Up_Point[1];
               if(Left_Up_Point[1] >= 17)
               {
                   CC = 1;
               }
               if(Left_Up_Point_finish_flag == 0 )        //�¹���ʧ���Ϲ�б���߽���&& Real_Distance >= 4500
               {
                   if(Emo_Angle >= 30)                   //����ɹ�
                   {
                       need_cornerL = 0;
                       Auxiliary_CorneringLeft_flag = 0;
                       Gyroscope_Star_flag = 0;
                       Circlecount = 5;
                       Paddingcurve = 0;
                       EncoderSum_flag = 0;
                       CC = 0;
                   }
//                   else                                  //����ʧ��
//                   {
//                       CircleLeft_flag = 0;
//                       Circlecount = 0;
//                       PaddingR = 0;
//                       PaddingL = 0;
//                       Paddingcurve = 0;
//                       CC = 0;
//                   }
               }
           }
           if(Circlecount == 5)
           {
               await++;
               if(await >= 3)
               {
                   if(Emo_Angle > 30)
                   {
                       Circlecount = 6;
                       await = 0;
                   }
               }
           }
           if(Circlecount == 6)
           {
               if(Right_Down_Point_finish_flag == 1 || Left_Up_Point_finish_flag == 0)       //�ҹճ��֣������ҹ�б���߳���
               {
                   Circlecount = 7;
               }
           }
           if(Circlecount == 7)
           {
               Paddingcurve = 1;
               CircleOutPoint();
               if(Left_Down_Point_finish_flag == 1 && Left_Up_Point_finish_flag == 0 && Right_Down_Point_finish_flag == 0)//���ڳ����¹ճ����Ϲ���    && Real_Distance >= 3800 && Emo_Angle > 38
               {

                   Paddingcurve = 0;
                   Gyroscope_Star_flag = 0;
                   EncoderSum_flag = 0;
                   Circlecount = 8;
               }
               else if(Left_Down_Point_finish_flag == 1 && Left_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 0)  //���ڳ����¹ն��� && Real_Distance >= 3800&& Emo_Angle > 38

               {
                   Paddingcurve = 0;
                   Circlecount = 9;

               }
               else if(Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 0)  //�¹յ���&& Real_Distance >= 3800&& Emo_Angle > 38

               {
                   Paddingcurve = 0;
                   Circlecount = 10;
               }
           }
           if(Circlecount == 8)
           {
               if(Left_Down_Point_finish_flag == 1 && Left_Up_Point_finish_flag == 1)       //���¹ղ�����ֻ��¼
               {
                   Circlecount = 9;
               }
               else if(Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1)  //�Ϲյ���
               {
                   Circlecount = 10;
               }
           }
           if(Circlecount == 9)
           {
               Circlecount = 10;
               if(Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1)       //�Ϲյ���
               {
                   Circlecount = 10;
               }
           }
           if(Circlecount == 10)                                                            //Բ������
           {
               await++;
               if(await == 3)
               {
                   Circlecount = 11; //Բ������
                   await = 0;
               }
           }
        switch(Circlecount)
        {
            case 1 :
                Link_Left_One_Point[0] = Left_Down_Point[0];
                Link_Left_One_Point[1] = Left_Down_Point[1];
                Link_Left_Two_Point[0] = Left_Up_Point[0];
                Link_Left_Two_Point[1] = Left_Up_Point[1];
                PaddingR = 0;
                PaddingL = 1;
                break;
            case 2 :

                Link_Left_One_Point[0] = 5;
                Link_Left_One_Point[1] = 119;
                Link_Left_Two_Point[0] = Left_Up_Point[0];
                Link_Left_Two_Point[1] = Left_Up_Point[1];
                PaddingR = 0;
                PaddingL = 1;
                break;
            case 3 :

                PaddingR = 0;
                PaddingL = 0;
                break;
            case 4 :
                Link_Right_One_Point[0] = Left_Up_Point[0];
                Link_Right_One_Point[1] = Left_Up_Point[1];
                if(Left_Up_Point[1]*2 + 40 > 112)
                {
                    ReplacePoint = 112;
                }
                else
                {
                    ReplacePoint = Left_Up_Point[1]*2 + 40;
                }
                Link_Right_Two_Point[0] = Right_Black_Point[ReplacePoint];
                Link_Right_Two_Point[1] = ReplacePoint;
                Corners_flag = 1;
                if(Right_Black_Point[Left_Up_Point[1]] < Left_Up_Point[0] && Right_Black_Point[63] != 187 && Left_Up_Point[1] >= 30)
                {
                    Paddingcurve = 0;
                    PaddingR = 0;
                    PaddingL = 0;
                }
                else
                {
                    Paddingcurve = 1;
                    PaddingR = 1;
                    PaddingL = 0;
                }
                break;
            case 5 :
                PaddingR = 0;
                PaddingL = 0;
                break;
            case 6 :
                PaddingR = 0;
                PaddingL = 0;
                break;
            case 7 :
                Link_Right_One_Point[0] = CircleOut_Point[0];
                Link_Right_One_Point[1] = CircleOut_Point[1];
                Link_Right_Two_Point[0] = Right_Down_Point[0];
                Link_Right_Two_Point[1] = Right_Down_Point[1];
                PaddingR = 1;
                PaddingL = 0;
                break;
            case 8 :
                Link_Left_One_Point[0] = 0;
                Link_Left_One_Point[1] = 0;
                Link_Left_Two_Point[0] = Left_Down_Point[0];
                Link_Left_Two_Point[1] = Left_Down_Point[1];
                PaddingR = 0;
                PaddingL = 1;
                break;
            case 9 :
                Link_Left_One_Point[0] = Left_Down_Point[0];
                Link_Left_One_Point[1] = Left_Down_Point[1];
                Link_Left_Two_Point[0] = Left_Up_Point[0];
                Link_Left_Two_Point[1] = Left_Up_Point[1];
                PaddingR = 0;
                PaddingL = 1;
                break;
            case 10 :
                Link_Left_One_Point[0] = 0;
                Link_Left_One_Point[1] = 119;
                Link_Left_Two_Point[0] = Left_Up_Point[0];
                Link_Left_Two_Point[1] = Left_Up_Point[1];
                PaddingR = 0;
                PaddingL = 1;
                break;
            case 11 :
                CircleLeft_flag = 0;
                CircleBig = 0;
                Corners_flag = 0;
                Circlecount = 0;
                PaddingR = 0;
                PaddingL = 0;
                Circle_RC++;
                break;
        }

    }
   else if(CircleRight_flag == 1)
    {
        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 && Circlecount == 0)  //���¹ղ���&& findrcount > 6
        {
            Circlecount = 1;
        }
        if(Circlecount == 1)
        {
            if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 0 && Right_Down_Point[1] > 60)   //�¹���ʧ�Ϲղ���
            {
                Circlecount = 2;
            }
            else if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1
                && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] == EmoWhite  && Right_Up_Point[1] > 15)//&& findrcount <= 3
            {
                Circlecount = 4;

            }
            if(Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1
            && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] == EmoWhite && findrcount <= 3 && Right_Up_Point[1] > 15)        //�Ϲ�б���߽���
            {
                Circlecount = 4;
            }
        }
        if(Circlecount == 2)
        {
            if(Right_Down_Point_finish_flag == 1 || Right_Up_Point_finish_flag == 0)    //�¹ճ��֣����Ϲ�
            {
                Circlecount = 3;
            }
            else if(Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1
                && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] == EmoWhite && Right_Up_Point[1] > 15)
            {
                Circlecount = 4;

            }
            else if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1
                && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] == EmoWhite && findrcount <= 3 && Right_Up_Point[1] > 15)
            {
                Circlecount = 4;


            }
        }
        if(Circlecount == 3)
        {
            if(Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1
            && Emo_imag[Right_Up_Point[1] + 5][Right_Up_Point[0] + 10] == EmoWhite)        //�Ϲ�б���߽���
            {
                Circlecount = 4;

            }
            else if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1
                && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] == EmoWhite && findrcount <= 3 && Right_Up_Point[1] > 15)
            {
                Circlecount = 4;

            }
            else if(Right_Up_Point_finish_flag == 1 && Right_Up_Point[1] < 40 && findrcount <= 4 && Right_Up_Point[1] > 15)
           {
               Circlecount = 4;
           }
        }
        if(Circlecount == 4)
        {
            if(Right_Up_Point[1] < (RY - 10) && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 10] == EmoWhite)
            {
                Right_Up_Point[0] = RX;
                Right_Up_Point[1] = RY;
            }
            RX = Right_Up_Point[0];
            RY = Right_Up_Point[1];
            if(Right_Up_Point_finish_flag == 0)        //�¹���ʧ���Ϲ�б���߽���
            {
                if(Emo_Angle <= -45)        //����ɹ�
                {
                    Circlecount = 5;
                    Paddingcurve = 0;
                    await=0;
                }
//                else                                  //����ʧ��
//                {
//                    CircleRight_flag = 0;
//                    Circlecount = 0;
//                    PaddingR = 0;
//                    PaddingL = 0;
//                    Paddingcurve = 0;
//                    CC = 0;
//                    await=0;
//                }
            }
        }
        if(Circlecount == 5)
        {
            await++;
            if(await >= 3)
            {
              if(Emo_Angle < -45)
                {
                    Circlecount = 6;
                    await = 0;
                }
               }
            }
        if(Circlecount == 6)
        {
            if(Left_Down_Point_finish_flag == 1 || Right_Up_Point_finish_flag == 1)                  //��ճ��֣��������б���߳���
            {
                Circlecount = 7;
            }
        }
        if(Circlecount == 7)
        {
            Paddingcurve = 1;
            CircleOutPoint();
            if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 0 && Left_Down_Point_finish_flag == 0)   //���ڳ����¹ճ����Ϲ���&& Real_Distance >= 3800  && Emo_Angle <-38
            {
                Paddingcurve = 0;
                Circlecount = 8;
            }
            else if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 0)  //���ڳ����¹ն��� && Real_Distance >= 3800 && Emo_Angle <-38
            {
                Paddingcurve = 0;
                Circlecount = 9;
            }
            else if(Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 0)  //�¹յ��� && Real_Distance >= 3800 && Emo_Angle <-38
            {
                Paddingcurve = 0;
                Circlecount = 10;
            }
        }
        if(Circlecount == 8)
        {

            if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1)
            {
                Circlecount = 9;
            }
            else if(Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1)  //�Ϲյ���
            {
                Circlecount = 10;
            }
        }
        if(Circlecount == 9)
        {
            Circlecount = 10;

            if(Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1)  //�Ϲյ���
            {
                Circlecount = 10;
            }
        }
        if(Circlecount == 10)
        {
            await++;
            if(await == 3)
            {
                Circlecount = 11; //Բ������
                await = 0;

            }
        }
        switch(Circlecount)
        {
            case 1 :
                Link_Right_One_Point[0] = Right_Down_Point[0];
                Link_Right_One_Point[1] = Right_Down_Point[1];
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                PaddingR = 1;
                PaddingL = 0;
                break;
            case 2 :
                Link_Right_One_Point[0] = Right_Down_Point[0];
                Link_Right_One_Point[1] = Right_Down_Point[1];
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                PaddingR = 1;
                PaddingL = 0;
                break;
            case 3 :
                Link_Right_One_Point[0] = 0;
                Link_Right_One_Point[1] = 0;
                Link_Right_Two_Point[0] = 0;
                Link_Right_Two_Point[1] = 0;
                PaddingR = 1;
                PaddingL = 0;
                break;
            case 4 :
                Link_Left_One_Point[0] = Right_Up_Point[0];
                Link_Left_One_Point[1] = Right_Up_Point[1];
                if(Right_Up_Point[1]*2 + 40 > 112)
                {
                    ReplacePoint = 112;
                }
                else
                {
                    ReplacePoint = Right_Up_Point[1]*2 + 40;
                }
                Link_Left_Two_Point[0] = Left_Black_Point[ReplacePoint];
                Link_Left_Two_Point[1] = ReplacePoint;
                Corners_flag = 1;
                if(Left_Black_Point[Right_Up_Point[1]] > Right_Up_Point[0] && Left_Black_Point[62] != 0 && Right_Up_Point[1] >= 30)
                {
                    Paddingcurve = 0;
                    PaddingR = 0;
                    PaddingL = 0;
                }
                else
                {
                    Paddingcurve = 1;
                    PaddingR = 0;
                    PaddingL = 1;
                }
                break;
            case 5 :
                PaddingR = 0;
                PaddingL = 0;
                break;
            case 6 :
                PaddingR = 0;
                PaddingL = 0;
                break;
            case 7 :
                Link_Left_One_Point[0] = CircleOut_Point[0];
                Link_Left_One_Point[1] = CircleOut_Point[1];
                Link_Left_Two_Point[0] = Left_Down_Point[0];
                Link_Left_Two_Point[1] = Left_Down_Point[1];
                PaddingR = 0;
                PaddingL = 1;
                break;
            case 8 :
                Link_Right_One_Point[0] = 187;
                Link_Right_One_Point[1] = 0;
                Link_Right_Two_Point[0] = Right_Down_Point[0];
                Link_Right_Two_Point[1] = Right_Down_Point[1];
                PaddingR = 1;
                PaddingL = 0;
                break;
            case 9 :
                Link_Right_One_Point[0] = Right_Down_Point[0];
                Link_Right_One_Point[1] = Right_Down_Point[1];
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                PaddingR = 1;
                PaddingL = 0;
                break;
            case 10 :
                Link_Right_One_Point[0] = 187;
                Link_Right_One_Point[1] = 119;
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                PaddingR = 1;
                PaddingL = 0;
                break;
            case 11 :
                CircleRight_flag = 0;
                Corners_flag = 0;
                CircleBig = 0;
                Circlecount = 0;
                PaddingR = 0;
                PaddingL = 0;
                Circle_RC++;
                break;
//            case 12 :
//                Link_Right_One_Point[0] = 187;
//                Link_Right_One_Point[1] = 119;
//                Link_Right_Two_Point[0] = Right_Up_Point[0];
//                Link_Right_Two_Point[1] = Right_Up_Point[1];
//                PaddingR = 1;
//                PaddingL = 0;
//                break;
        }

    }

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���Ϻ���
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Obstacle_avoidance(void)
{
    if( camera_p.Garage_In_flag==0 && Emo_u8Decabs(camera_p.T_X,camera_p.N_X) <=8 ) //camera_p.ObstacleR_flag == 0 && camera_p.ObstacleL_flag == 0 &&
    {
//            camera_p.test_flag =Emo_u8Decabs(Right_Down_Point[1],Right_Up_Point[1]) ;//Emo_u8Decabs(Right_Black_Point[y-1],Right_Black_Point[y])
        //�ұ����ϰ�
            if(Emo_u8Decabs(Right_Black_Point[60],Right_Black_Point[95])>=25 && Emo_u8Decabs(Right_Black_Point[50],Right_Black_Point[60])<8 && Emo_Angle < 15)//&& (Emo_u8Decabs(Left_Down_Point[1],Left_Up_Point[1])>30|| Emo_u8Decabs(Right_Down_Point[1],Right_Up_Point[1])>30)
            {
                ObstacleR_flag = 1;
                ObstacleL_flag = 0;
                ObscountR++;
                Link_Right_One_Point[0] =187;
                Link_Right_One_Point[1] = 119;
                Link_Right_Two_Point[0] = 40;
                Link_Right_Two_Point[1] = 20;
                PaddingR = 1;
                PaddingL = 0;


             }
            //������ϰ�
           if(Emo_u8Decabs(Left_Black_Point[60],Left_Black_Point[90])>=25 && Emo_u8Decabs(Left_Black_Point[60],Left_Black_Point[50])<8 && Emo_Angle < 15)//&& ((Right_Down_Point[1]-Right_Up_Point[1]>30) || (Left_Down_Point[1]-Left_Up_Point[1]>30))
            {
                ObstacleL_flag = 1;
                ObstacleR_flag = 0;
                ObscountL++;
                Link_Left_One_Point[0] = 1;
                Link_Left_One_Point[1] = 119;
                Link_Left_Two_Point[0] =130;
                Link_Left_Two_Point[1] = 60;
                PaddingR = 0;
                PaddingL = 1;
            }

           if (ObstacleL_flag == 1 || ObstacleR_flag == 1)
           {
               campit_time++;
           }

           //�˳�����
    }
    if(  ObstacleL_flag>0 && campit_time>10)//Emo_u8Decabs(Right_Black_Point[60],Right_Black_Point[90])<=15&&
    {
        Pit_Init();
        ObstacleL_flag = 0;
        ObscountR=0;
        Obscount2=0;
        PaddingR = 0;
        PaddingL = 0;
    }
    if( ObstacleR_flag>0 && campit_time>10)//Emo_u8Decabs(Left_Black_Point[60],Left_Black_Point[90])<=15 && ObscountL>0
    {
        Pit_Init();
        ObstacleR_flag = 0;
        ObscountL=0;
        Obscount2=0;
        PaddingR = 0;
        PaddingL = 0;
    }

}






/*******************����**********************/
//���ҵ�Ҫ����������ߣ�ͨ���������б�ʵõ�������ɵ�һ�η��̣��õ�ʣ��x��λ�ã����߻������ұ���
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ֱ�߲��ߺ���
//  @param      xone  ��һ�����ߵ�x����
//  @param      yone  ��һ�����ߵ�y����
//  @param      xtwo  �ڶ������ߵ�x����
//  @param      ytwo  �ڶ������ߵ�y����
//  @return     void
//  @note  Left_Black_Point[y]Ϊ�ҵ���������� Right_Black_Point[y]Ϊ�ҵ��ұ�������
//-------------------------------------------------------------------------------------------------------------------
void Padding_LineR(uint8 xone,uint8 yone,uint8 xtwo,uint8 ytwo)
{
    float k=0;  //б��
    float b=0;  //�ؾ�
    //uint8 xstar=0;
    //uint8 xend=0;
    uint8 ystar=0;
    uint8 yend=0;

    k=((float)ytwo - (float)yone)/((float)xtwo - (float)xone);
    //k=((float)xtwo - (float)xone)/((float)ytwo - (float)yone);
    b=(float)yone - ((float)xone*k);

    if(yone>ytwo)
    {
        ystar=ytwo;
        yend=yone;
    }
    else
    {
        ystar=yone;
        yend=ytwo;
    }
    for(uint8 y=ystar;y<=yend;y++)
    {
        Right_Black_Point[y]=(uint8)(((float)y-b)/k);  //����֮�䲹��
    }
}

void Padding_LineL(uint8 xone,uint8 yone,uint8 xtwo,uint8 ytwo)
{
    float k=0;  //б��
    float b=0;  //�ؾ�
    //uint8 xstar=0;
    //uint8 xend=0;
    uint8 ystar=0;
    uint8 yend=0;

    k=((float)ytwo - (float)yone)/((float)xtwo - (float)xone);
    //k=((float)xtwo - (float)xone)/((float)ytwo - (float)yone);
    b=(float)yone - ((float)xone*k);

    if(yone>ytwo)
    {
        ystar=ytwo;
        yend=yone;
    }
    else
    {
        ystar=yone;
        yend=ytwo;
    }
    for(uint8 y=ystar;y<=yend;y++)
    {
        Left_Black_Point[y]=(uint8)(((float)y-b)/k);
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ߺ���
//  @param      PaddingR  �Ҳ��߱�־  0�������� 1��Ҫ����
//  @param      PaddingL  ���߱�־
//  @param      Padding_CurveR  �����߲��߱�־ 0����ֱ�� 1��������
//  @param      Padding_CurveL  �����߲��߱�־
//  @return     void
//  @note       ���ߵķ�ʽ��ͨ���˺������У��ⲿֻ��Ҫ�����������ߵ��λ�ã����Ƿ����Ҳ���
//  Left_Black_Point[y]Ϊ�ҵ���������� Right_Black_Point[y]Ϊ�ҵ��ұ�������
//-------------------------------------------------------------------------------------------------------------------
void Padding_Line(void)
{
    if(PaddingL == 1 && PaddingR == 1 && Paddingcurve == 0)
    {
        Padding_LineR(Link_Right_One_Point[0],Link_Right_One_Point[1],Link_Right_Two_Point[0],Link_Right_Two_Point[1]);
        Padding_LineL(Link_Left_One_Point[0],Link_Left_One_Point[1],Link_Left_Two_Point[0],Link_Left_Two_Point[1]);
    }
    else if(PaddingL == 1 && PaddingR == 0 && Paddingcurve == 0)
    {
        Padding_LineL(Link_Left_One_Point[0],Link_Left_One_Point[1],Link_Left_Two_Point[0],Link_Left_Two_Point[1]);
        Padding_LineR(0,0,0,0);
    }
    else if(PaddingL == 0 && PaddingR == 1 && Paddingcurve == 0)
    {
        Padding_LineR(Link_Right_One_Point[0],Link_Right_One_Point[1],Link_Right_Two_Point[0],Link_Right_Two_Point[1]);
        Padding_LineL(0,0,0,0);
    }
    else if(PaddingL == 0 && PaddingR == 1 && Paddingcurve == 1)
    {
        Padding_CurveR(Link_Right_One_Point[0],Link_Right_One_Point[1],Link_Right_Two_Point[0],Link_Right_Two_Point[1]);
        Padding_CurveL(0,0,0,0);
    }
    else if(PaddingL == 1 && PaddingR == 0 && Paddingcurve == 1)
    {
        Padding_CurveL(Link_Left_One_Point[0],Link_Left_One_Point[1],Link_Left_Two_Point[0],Link_Left_Two_Point[1]);
        Padding_CurveR(0,0,0,0);
    }
    else
    {
        Padding_LineL(0,0,0,0);
        Padding_LineR(0,0,0,0);
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��С���˷���������
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note  Left_Black_Point[y]Ϊ�ҵ���������� Right_Black_Point[y]Ϊ�ҵ��ұ�������
//-------------------------------------------------------------------------------------------------------------------
void curvature_computeL(void)
{
    int LeftXSum = 0, LeftYSum = 0, LeftXYSum = 0, LeftXXSum = 0;
    //float LeftK = 0, LeftB = 0;

    //int RightXSum = 0, RightYSum = 0, RightXYSum = 0, RightXXSum = 0;
    //float RightK = 0, RightB = 0;

    //int temp;
    //int LeftBlackError = 0, RightBlackError = 0;

    for (uint8 y = 53; y < 61; y++)//�������߽�����ۼӼ���
    {
        if (y % 2 == 0)
        {
            LeftXSum += Left_Black_Point[y];
            LeftYSum += y;
            LeftXXSum += Left_Black_Point[y] * Left_Black_Point[y];
            LeftXYSum += y * Left_Black_Point[y];

//            RightXSum += Right_Black_Point[y];
//            RightYSum += y;
//            RightXXSum += Right_Black_Point[y] * Right_Black_Point[y];
//            RightXYSum += y * Right_Black_Point[y];
        }
     }

    if(8 * LeftXXSum - LeftXSum * LeftXSum !=0)
    {
        CurvatureLeft = (float)(8 * LeftXYSum - LeftXSum * LeftYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);
    }

                 //Lintercede = (float)(LeftXXSum * LeftYSum - LeftXSum * LeftXYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);

    //CurvatureRight = (float)(8 * RightXYSum - RightXSum * RightYSum) / (8 * RightXXSum - RightXSum * RightXSum);
                 //Rintercede = (float)(
}

void curvature_computeR(void)
{
    //int LeftXSum = 0, LeftYSum = 0, LeftXYSum = 0, LeftXXSum = 0;
    //float LeftK = 0, LeftB = 0;

    int RightXSum = 0, RightYSum = 0, RightXYSum = 0, RightXXSum = 0;
    //float RightK = 0, RightB = 0;

    //int temp;
    //int LeftBlackError = 0, RightBlackError = 0;

    for (uint8 y = 53; y < 61; y++)//�������߽�����ۼӼ���
    {

        if (y % 2 == 0)
        {
//            LeftXSum += Left_Black_Point[y];
//            LeftYSum += y;
//            LeftXXSum += Left_Black_Point[y] * Left_Black_Point[y];
//            LeftXYSum += y * Left_Black_Point[y];

            RightXSum += Right_Black_Point[y];
            RightYSum += y;
            RightXXSum += Right_Black_Point[y] * Right_Black_Point[y];
            RightXYSum += y * Right_Black_Point[y];
        }
     }

//    if(8 * LeftXXSum - LeftXSum * LeftXSum !=0)
//    {
//        CurvatureLeft = (float)(8 * LeftXYSum - LeftXSum * LeftYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);
//    }

                 //Lintercede = (float)(LeftXXSum * LeftYSum - LeftXSum * LeftXYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);

    if(8 * RightXXSum - RightXSum * RightXSum != 0)
    {
        CurvatureRight = (float)(8 * RightXYSum - RightXSum * RightYSum) / (8 * RightXXSum - RightXSum * RightXSum);
    }
                 //Rintercede = (float)(
}

void curvature_compute(void)
{
    int LeftXSum = 0, LeftYSum = 0, LeftXYSum = 0, LeftXXSum = 0;
    //float LeftK = 0, LeftB = 0;

    int RightXSum = 0, RightYSum = 0, RightXYSum = 0, RightXXSum = 0;
    //float RightK = 0, RightB = 0;

    //int temp;
    //int LeftBlackError = 0, RightBlackError = 0;

    for (uint8 y = 53; y < 61; y++)//�������߽�����ۼӼ���
    {

        if (y % 2 == 0)
        {
            LeftXSum += Left_Black_Point[y];
            LeftYSum += y;
            LeftXXSum += Left_Black_Point[y] * Left_Black_Point[y];
            LeftXYSum += y * Left_Black_Point[y];

            RightXSum += Right_Black_Point[y];
            RightYSum += y;
            RightXXSum += Right_Black_Point[y] * Right_Black_Point[y];
            RightXYSum += y * Right_Black_Point[y];
        }
     }

    if(8 * LeftXXSum - LeftXSum * LeftXSum !=0)
    {
        CurvatureLeft = (float)(8 * LeftXYSum - LeftXSum * LeftYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);
    }

                 //Lintercede = (float)(LeftXXSum * LeftYSum - LeftXSum * LeftXYSum) / (8 * LeftXXSum - LeftXSum * LeftXSum);

    if(8 * RightXXSum - RightXSum * RightXSum != 0)
    {
        CurvatureRight = (float)(8 * RightXYSum - RightXSum * RightYSum) / (8 * RightXXSum - RightXSum * RightXSum);
    }
                 //Rintercede = (float)(
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ƽ���˲�
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
int16 Sum1;
uint8 HDPJ_lvbo(uint8 data[], uint8 N, uint8 size)
{
    Sum1 = 0;
    for(uint8 j =0; j <size; j++)
    {
        if(j <N /2)
        {
            for(uint8 k =0; k <N; k++)
            {
                Sum1 +=data[j +k];
            }
            data[j] =Sum1 /N;
        }
        else
            if(j <size -N /2)
            {
                for(uint8 k =0; k <N /2; k++)
                {
                    Sum1 +=(data[j +k] +data[j -k]);
                }
                data[j] = Sum1 /N;
            }
            else
            {
                for(uint8 k =0; k <size -j; k++)
                {
                    Sum1 +=data[j +k];
                }
                for(uint8 k =0; k <(N -size +j); k++)
                {
                    Sum1 +=data[j -k];
                }
                data[j] = Sum1 /N;
            }
        Sum1 = 0;
    }
    return  data;
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ٴ�ȷ������
//  @param
//  @param
//  @param
//  @param      ��Ϊ���ߺ���߷����仯����Ҫ�ٴμ������ߣ�������ԶԶ���������
//  @return     void
//  @note  Left_Black_Point[y]Ϊ�ҵ���������� Right_Black_Point[y]Ϊ�ҵ��ұ�������
//-------------------------------------------------------------------------------------------------------------------
static uint8 Last_Middle_Point = 93;   //��ʱ�����߻���Ϊ���߶�ԾǨ���˴����ڰ������

//�ٴ�ȷ������
void Get_Middle_Line(void)
{
    for(uint8 y=119 ; y >= 0 ; y--)
      {
          if(Right_Black_Point[y]==187 && Left_Black_Point[y]==0 && Corners_flag == 0 && Triforkpadding_flag == 0 && Near_Corners_flag == 0)        //���߶�û�ҵ���
          {
              if(y == 119 )
              {
                  Middle_Black_Point[y] = 93;
              }
              else
              {
                  Middle_Black_Point[y]=Middle_Black_Point[y+1];
              }
              if(Emo_imag[y][Middle_Black_Point[y]] == EmoBlack && y < 114)
              {
                  Middle_Black_Point[y] = Middle_Black_Point[y+5];
              }
              if(Emo_imag[y][Middle_Black_Point[y]] == EmoBlack && y > 114)
              {
                  Middle_Black_Point[y] = 93;
              }
          }
          else if(Right_Black_Point[y]==187 && Left_Black_Point[y]!=0 && Corners_flag == 0 && Triforkpadding_flag == 0 && Near_Corners_flag == 0)    //ֱ������ҵ���
          {
              Middle_Black_Point[y]=Left_Black_Point[y]+Straight[y];

          }
          else if(Left_Black_Point[y]==0 && Right_Black_Point[y]!=187 && Corners_flag == 0 && Triforkpadding_flag == 0 && Near_Corners_flag == 0)    //ֱ���ұ��ҵ���
          {
              Middle_Black_Point[y]=Right_Black_Point[y]-Straight[y];

          }
          else if(Left_Black_Point[y]==0 && Right_Black_Point[y]!=187 && Corners_flag == 1 && Triforkpadding_flag == 0 && Near_Corners_flag == 0)    //����ұ��ҵ���
          {
              if(Right_Black_Point[y] < Corners[y])
                  Middle_Black_Point[y]=0;
              else
                  Middle_Black_Point[y]=Right_Black_Point[y]-(Corners[y] - 6);
          }
          else if(Right_Black_Point[y]==187 && Left_Black_Point[y]!=0 && Corners_flag == 1 && Triforkpadding_flag == 0 && Near_Corners_flag == 0)    //�������ҵ���
          {
              if(Left_Black_Point[y] + Corners[y] > 187)
                  Middle_Black_Point[y]=187;
              else
                  Middle_Black_Point[y]=Left_Black_Point[y]+(Corners[y] - 6);
          }
  //        else if(Right_Black_Point[y]==187 && Left_Black_Point[y]!=0 && Triforkpadding_flag == 0 && Corners_flag == 1 && Near_Corners_flag == 1)    //�ҽ�������ҵ���
  //        {
  //            if(Left_Black_Point[y] + Corners[y] > 187)
  //                Middle_Black_Point[y]=187;
  //            else
  //                Middle_Black_Point[y]=Left_Black_Point[y]+(Corners[y]-6);
  //        }
  //        else if(Left_Black_Point[y]==0 && Right_Black_Point[y]!=187 && Triforkpadding_flag == 0 && Corners_flag == 1 && Near_Corners_flag == 1)    //���������ҵ���
  //        {
  //            if(Right_Black_Point[y] < Corners[y])
  //                Middle_Black_Point[y]=0;
  //            else
  //                Middle_Black_Point[y]=Right_Black_Point[y]-(Corners[y]-6);
  //        }
          else if(Right_Black_Point[y]==187 && Left_Black_Point[y]!=0 && Slalom_Padding == 1 && Corners_flag == 0 && Near_Corners_flag == 0)    //����Slalom�ҵ���
          {
              if(Left_Black_Point[y] > 113)
                  Middle_Black_Point[y]=187;
              else
                  Middle_Black_Point[y]=Left_Black_Point[y]+(Corners[y]);
          }
          else if(Left_Black_Point[y]==0 && Right_Black_Point[y]!=187 && Slalom_Padding == 1 && Corners_flag == 0 && Near_Corners_flag == 0)    //����Slalom�ҵ���
          {
              if(Right_Black_Point[y] < 75)
                  Middle_Black_Point[y]=0;
              else
                  Middle_Black_Point[y]=Right_Black_Point[y]-(Corners[y]);
          }
          else             //���߶��ҵ���
          {
              Middle_Black_Point[y]=(uint8)(((int)Right_Black_Point[y]+(int)Left_Black_Point[y])/2);
              if(Emo_imag[y][Middle_Black_Point[y]] == EmoBlack)
              {
                  if(y<=114)
                  {
                      Middle_Black_Point[y] = Middle_Black_Point[y+5];
                  }
                  else
                  {
                      Middle_Black_Point[y] = 93;
                  }

              }

          }
          if(y < 118 && Right_Black_Point[y] == 187 && Left_Black_Point[y] == 0 && (Emo_Uint8_dec(Middle_Black_Point[y],Last_Middle_Point) >= 18 || Emo_Uint8_dec(Middle_Black_Point[y],Last_Middle_Point) <= -18)
          && Corners_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0 && SlalomLeft_flag == 0 && SlalomRight_flag == 0 && Trifork_flag == 0)
          {
              Middle_Black_Point[y] = Last_Middle_Point;
          }
          else
          {
              Last_Middle_Point = Middle_Black_Point[y];
          }
  //        Middle_Black_Point[y] = Middle_Black_Point[y] < 1 ? 1 : Middle_Black_Point[y];
  //        Middle_Black_Point[y] = Middle_Black_Point[y] > 186 ? 186 : Middle_Black_Point[y];
          Middle_Black_Point[y] = Middle_Black_Point[y] < 1 ? 0 : Middle_Black_Point[y];
          Middle_Black_Point[y] = Middle_Black_Point[y] >186 ? 187 :Middle_Black_Point[y];
          if(y==0)
              break;
      }

        float totalX=0;
        uint8 All_x[120];
        HDPJ_lvbo(Middle_Black_Point,20,MT9V03X_H -1);
        memset(All_x, 0, sizeof(All_x));
        memcpy(All_x, Middle_Black_Point, sizeof(Middle_Black_Point));
        for (uint8_t y = 60 ;y < 119; y++) {
            if(Emo_u8Decabs(All_x[y+1],All_x[y])>5)
            {
                All_x[y+1]=All_x[y];

            }
            if(Emo_u8Decabs(All_x[y+1],All_x[y])<=5)
            {
              // �ۼ�ÿһ������ X ��λ��
              totalX += All_x[y];
            }
        }
        //X���λ��
        camera_p.T_X=totalX/59;


}





//Ԫ��ʶ��ļ���
//-------------------------------------------------------------------------------------------------------------------
//  @brief      Ԫ��ʶ��ļ���
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note  Ԫ��ʶ����ܴ���
//  @note  Left_Black_Point[y]Ϊ�ҵ���������� Right_Black_Point[y]Ϊ�ҵ��ұ�������
//-------------------------------------------------------------------------------------------------------------------
void Think(void)
{
    Judge_CornerS();
    if(SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0  && CornerS_flag == 0 && Cross_flag == 0 && WindupR_flag == 0 && WindupL_flag == 0  )//&& Trifork_flag == 0
    {
        Judge();
    }
    if(CornerS_flag == 0 && CornerLeft_flag == 0 && CornerRight_flag == 0)
    {
        Identify();//�յ�Ѱ��
        Element_dispose();//�յ�������з�����
        Cross();//ʮ��
        Windup();//ǰհ
        Garage();//������
        Slalom();//p��
        Circle();//Բ��
//        Obstacle_avoidance();//����
    }
}

void Camera_Head(void)        //����ͷ�����ܺ���
{
        Camera_Init();
        Thresholding();//��ֵ��
        Find_Line();//��ȡ��Ե��������
        Think();
        camera_p.test1_flag=Circlecount;
        Padding_Line();//��ʮ�ֵȲ�·�ڲ���
        Get_Middle_Line();//ȷ��������
        if(flag_start == 0)
                {
                 if((camera_p.T_X>80&&camera_p.T_X<98)&&camera_p.T_X!=93)
                {
                    camera_p.N_X = 90;
                    flag_start = 1;
                }
                }
        IPS_Flag = 1;//��־һ��ѭ������
}
