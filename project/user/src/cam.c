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
float campit_time=0;     //中断计时1ms
//定义变量
//像素和灰度
#define GrayScale 256 //灰度值
int pixelCount[GrayScale];
float pixelPro[GrayScale];
//画线：
#define BOUNDARY_NUM            (MT9V03X_H * 3 / 2)
//补线
unsigned char PaddingR = 0;
unsigned char PaddingL = 0;
unsigned char Paddingcurve = 0;            //补曲线标志，1：补曲线 ，0：补直线
uint8 Link_Right_One_Point[2];               //补线点
uint8 Link_Right_Two_Point[2];
uint8 Link_Left_One_Point[2];
uint8 Link_Left_Two_Point[2];

//拐点定义：
unsigned char Right_Up_Point_finish_flag = 0;       //拐点标志位
unsigned char Left_Up_Point_finish_flag = 0;
unsigned char Right_Down_Point_finish_flag = 0;
unsigned char Left_Down_Point_finish_flag = 0;
uint8 Last_Right_Point[2];                //上一次拐点，拐点有时候会突然转移 0 ：down 1：up
uint8 Last_Left_Point[2];
uint8 Right_Down_Point[2];                //拐点   0 : x  1 : y
uint8 Right_Up_Point[2];
uint8 Left_Down_Point[2];
uint8 Left_Up_Point[2];
int findrcount = 0;                     //记录拐点到边界距离，用于区分圆环和回转
int findlcount = 0;

//处理后的图像
uint8 Emo_imag[120][188];
vuint8 IPS_Flag = 0;                    //图像处理完毕标志


int EmoBlackcount = 0,EmoWhitecount = 0;            //截止行查找
uint8 OSTU=140;   //大津法阈值
uint8 OUST1 = 0;  //阈值替代，方便不同场地对大津法阈值处理
uint8 Endline = 0;

uint8 BoundaryLeft = 0;             //边界计数
uint8 BoundaryRight = 0;

uint8 Left_Black_Point[120];     //一维点（大小写）
uint8 Right_Black_Point[120];


//转弯,弯道：
//unsigned char Slalom_Padding = 0;  //Slalom补线标志、
unsigned char Corners_flag = 0;              //弯道矢量矩标志
unsigned char CornerRight_flag = 0;   //弯道标志
unsigned char CornerLeft_flag = 0;
unsigned char Near_CornerLeft_flag = 0;      //近端弯道标志
unsigned char Near_CornerRight_flag = 0;
unsigned char Near_Corners_flag = 0;         //近端弯道矢量矩标志
unsigned char CornerS_flag = 0;       //S弯标志


//slalom,p字变量:
unsigned char SlalomLeft_flag = 0;             //Slalom标志
int Slalomcount = 0;                 //Slalom内部步骤
unsigned char SlalomRight_flag = 0;
unsigned char Slalom_Padding = 0;  //Slalom补线标志
uint8 Slalom_Point[2];
static unsigned char ObservationS_finish = 0;//观察s弯道
static unsigned char CorneringS_finish = 0;//s弯道是否过完
unsigned char SlC = 0; //P字计数程序，帮助检测入库条件

//圆环：
uint8 CircleOut_Point[2];
float CircleLeft_flag = 0;         //圆环标志
float CircleRight_flag = 0;
unsigned char CircleBig = 0;           //大圆环标志
unsigned char CircleSwitch_flag = 1;       //圆环开关标志 ：0代表关闭，1代表开启，默认为开启
int Circlecount = 0;                //圆环内部步骤
unsigned char  Circle_RC = 0; //圆环计数程序，帮助完赛，以防万一
//三岔路口：
unsigned char Trifork_flag = 0;                        //三岔
unsigned char Trifork_PointLeft_Findfinish_flag = 0;
unsigned char Trifork_PointRight_Findfinish_flag = 0;
unsigned char Trifork_PointMiddle_Findfinish_flag = 0;
unsigned char Triforkpadding_flag = 0;       //三岔补线标志
int Triforkcount = 0;               //三岔内部步骤，根据TriforkTurn来决定三岔转动方向
int TriforkTurn = 0;                //三岔圈数，计一则代表三岔从进到出完全通过一次
uint8 TriforkLeft_Point[2];         //三岔左点
uint8 TriforkRight_Point[2];       //三岔右点
uint8 TriforkMiddle_Point[2];       //三岔顶点
static unsigned char ObservationT_finish = 0;
static unsigned char CorneringT_finish = 0;
unsigned char dieReady = 0; //0:刚出库 1:三叉 2:圆环 3:回环 4:入库



//车库：
float Garage_Findfinish_flag = 0;    //库寻找标志 0：没找到 1：找到了
unsigned char Garage_flag = 0;                //执行车库补线标志
float Garagecount = 0;

unsigned char GarageL_In_flag = 0;
unsigned char GarageR_In_flag = 0;


unsigned char Garage_Out_flag = 1;          //出库标志 0：不进行出库 1：进行出库

//避障
float ObscountR=0;
float ObscountL=0;
float Obscount2=0;
float ObstacleR_flag = 0;//障碍右标志
float ObstacleL_flag = 0;//障碍左标志
//元素前摇：
unsigned char WindupL_flag = 0;                //元素前摇
unsigned char WindupR_flag = 0;                //元素前摇


//曲率
float CurvatureLeft=0;                  //曲率计算
float CurvatureRight=0;

//十字标志和计数
unsigned char Cross_flag = 0;
int Crosscount = 0;

//摄像头开始标志
unsigned char flag_start = 0;



extern float angv[3];//陀螺仪Z轴速度
float Emo_Angle=0;



//电机部分：
unsigned char need_cornerL = 0;              //小转弯辅助：用于元素出入的一些转弯辅助
unsigned char need_cornerR = 0;
//以下两个酌情需要
unsigned char Auxiliary_CorneringLeft_flag = 0;    //强制向左辅助打角
unsigned char Auxiliary_CorneringRight_flag = 0;    //强制向右辅助打角


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
                        94, 95, 95, 95, 96, 97, 98, 98, 99, 99};//   拐点Ss弯道


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
                                    93, 93, 93, 93, 93, 93, 93, 93, 93, 93};//中线黑点

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
                        81, 82, 82, 83, 84, 85, 85, 86, 86, 87};//直线阈值


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
                               74, 74, 74, 74, 74, 74, 74, 74, 74, 74};//三岔阈值







//********************************************************************************************************************/
//********************************************************************************************************************/
//********************************************************************************************************************/



void Camera_Init(void)       //摄像头初始化
{
    camera_p.Garage_In_flag = 0;           //入库标志  0：不进行入库 1：进行入库
    Emo_Angle=angv[2];
    //结构体初始化
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
//  @brief      无符号8位数据相减的绝对值
//  @param      a        数一
//  @param      b        数二
//  @param
//  @param
//  @return     int
//  @note
//-------------------------------------------------------------------------------------------------------------------
int Emo_u8Decabs(uint8 a,uint8 b)    //无符号8位的相减绝对值
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
//  @brief      无符号8位数据相减
//  @param      a        数一
//  @param      b        数二
//  @param
//  @param
//  @return     int
//  @note
//-------------------------------------------------------------------------------------------------------------------
int Emo_Uint8_dec(uint8 a,uint8 b)   //无符号8位数据相减
{
    int c = 0;
    int d = 0;
    c=(int)a;
    d=(int)b;
    return c-d;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      两数之间的三分之一
//  @param      a        数一
//  @param      b        数二
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
//  @brief      两数之间的四分之一
//  @param      a        数一
//  @param      b        数二
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
//  @brief      两数之间的八分之一
//  @param      a        数一
//  @param      b        数二
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
//  @brief      两数之间的三分之二
//  @param      a        数一
//  @param      b        数二
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
int Emo_abs(int x)                  //绝对值
{
    x = x < 0 ? (-x) : x;
    return x;
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      两数最大
//  @param      a        数一
//  @param      b        数二
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
//  @brief      二值化
//  @param      ROUST   按键阈值调节变量
//  @param
//  @param
//  @param
//  @return     void
//  @note       内部使用了大津法，并做了按键调节阈值的结合
//-------------------------------------------------------------------------------------------------------------------
void Thresholding(void)   //二值化
{
    OSTU=Ostu(mt9v03x_image[0], 188, 120);
    OUST1 = OSTU;
//    OUST1 = OUST1 > 118 ? 118 : OUST1;
//    OUST1 = OUST1 < 103 ? 103 : OUST1;

    Endline = 0;   //寻找到赛道封顶值，接下来的拐点寻找和元素判断不会再此值以后进行
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
//  @brief      大津法
//  @param      image  图像地址
//  @param      width  图像宽度
//  @param      height 图像高度
//  @param
//  @return     uint8
//  @note       二值化函数内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint8 Ostu(uint8 *image, uint16 width, uint16 height)
{
//    uint16 width = col;
//    uint16 height = row;
    uint8 threshold = 0 ;

    int i, j, pixelSum = width * height/4;

    uint8* data = image;  //指向像素数据的指针
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    uint32 gray_sum=0;
    //统计灰度级中每个像素在整幅图像中的个数
    for (i = 0; i < height; i+=2)
    {
        for (j = 0; j < width; j+=2)
        {
            pixelCount[(int)data[i * width + j]]++;  //将当前的点的像素值作为计数数组的下标
            gray_sum+=(int)data[i * width + j];       //灰度值总和
        }
    }

    //计算每个像素值的点在整幅图像中的比例

    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;

    }
    //遍历灰度级[0,255]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;

    w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
    for (j = 0; j < GrayScale; j++)
    {
            w0 += pixelPro[j];  //背景部分每个灰度值的像素点所占比例之和   即背景部分的比例
            u0tmp += j * pixelPro[j];  //背景部分       每个灰度值的点的比例 *灰度值

            w1=1-w0;
            u1tmp=gray_sum/pixelSum-u0tmp;

            u0 = u0tmp / w0;              //背景平均灰度
            u1 = u1tmp / w1;              //前景平均灰度
            u = u0tmp + u1tmp;            //全局平均灰度
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
            { //一个黑点的上下左右的白点大于等于三个，令这个点为白
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
//  @brief      左右巡边线
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       采用左右扫线的方法，从图像最低端开始，每行扫完会计算一次中线，下一行扫描从上一行中线开始
//-------------------------------------------------------------------------------------------------------------------
static uint8 star = 93;                             //寻线初始点
//需优化：有时其他赛道会干扰
//////如果当左边线寻到有边界则使以后边线都处于边界
void Find_Line(void)
{
    BoundaryRight = 0;
    BoundaryLeft = 0;
    if(Middle_Black_Point[119] == 0 || Middle_Black_Point[119] == 187)  //判断起始点是否在图像中间
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
            if(Emo_imag[y][x]==EmoBlack)  //黑黑黑即判断为边线
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
            if(x==186)                      //有点问题，返校复查
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
        if(Right_Black_Point[y]==187&&Left_Black_Point[y]==0)        //两边都没找到线
        {
            Middle_Black_Point[y]=Middle_Black_Point[y+1];
            //star=Middle_Black_Point[y];
            star = 93;
        }
        else if(Right_Black_Point[y]==187&&Left_Black_Point[y]!=0)    //左边找到线
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
        else if(Left_Black_Point[y]==0&&Right_Black_Point[y]!=187)    //右边找到线
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
        else             //两边都找到线
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




//补曲线，利用弯道进行补
//Cx曲线上点x，Cy曲线上点y
//-------------------------------------------------------------------------------------------------------------------
//  @brief      曲线补线函数
//  @param      Ux  上补线点x坐标
//  @param      Uy  上补线点y坐标
//  @param      Dx  下补线点x坐标
//  @param      Dx  下补线点y坐标
//  @return     void
//  @note       利用拉个朗日插值法，上下两个点由图像决定，中间点为固定点，如果补线效果不好，需要重新校准中间点
//  Left_Black_Point[y]为我的左边线数组 Right_Black_Point[y]为我的右边线数组
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





/*********判断赛道类型*************/
//寻到边界时，先判断赛道是否为弯道或S弯，再进行拐点寻找
//如果处在元素中时，不进行判断赛道类型，因为十字、和圆环过去就是弯道，则自动开启弯道,小S也在此处判断
//远端判断弯道，近端判断弯道
//使用曲率判断弯道和小S
void Judge(void)
{
    uint8 star;
    int LeftXSum = 0, LeftYSum = 0, LeftXYSum = 0, LeftXXSum = 0;
    int RightXSum = 0, RightYSum = 0, RightXYSum = 0, RightXXSum = 0;
    //unsigned char JudgeCorner = 0;    //如果出现边界但不是弯道就不执行判断S弯
    //unsigned char JudgeS = 0;         //表示执行了S弯却没判断成功

    Near_CornerLeft_flag = 0;
    Near_CornerRight_flag = 0;
    Near_Corners_flag = 0;
    //JudgeCorner = 0;
    Judge_CornerS();
    for(uint8 y=60;y>35;y--)
    {
        //右侧弯道判断
        if(Right_Black_Point[y-1] == 187 && Right_Black_Point[y-2] == 187 && Right_Black_Point[y-3] == 187
        && Right_Black_Point[y-4] == 187 && Right_Black_Point[y-5] == 187 && Right_Black_Point[y-6] == 187)
        {
            //JudgeCorner = 1;
            star=y;//弯道起始位置,y轴
            for (uint8 y = (star-16); y < star; y++)//对赛道边界进行累加计算
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
                // camera_p.CurvatureRight曲率传出去做转弯处理
                CornerRight_flag = 1;//弯道标志
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
        else//否定弯道
        {
            CornerRight_flag = 0;
            Corners_flag = 0;
        }
        //左弯道处理
        if(Left_Black_Point[y-1] == 0 && Left_Black_Point[y-2] == 0 && Left_Black_Point[y-3] == 0
        && Left_Black_Point[y-4] == 0 && Left_Black_Point[y-5] == 0 && Left_Black_Point[y-6] == 0)
        {
            star=y;//起始点
            for (uint8 y = (star-16); y < star; y++)//对赛道边界进行累加计算
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
                // camera_p.CurvatureRight曲率传出去做转弯处理
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
        else//否定弯道
        {
            CornerLeft_flag = 0;
            Corners_flag = 0;
        }
    }
}


//用于结束小S弯，弯道标志初始化
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
//  @brief      拐点寻找
//  @param      findlcount   拐点距离丢线的行数，用于判断大小圆环，和区分P字和圆环
//  @param
//  @param
//  @param
//  @return     void
//  @note       采用5邻域的原理寻找拐点，下拐点从图像低端往上扫，上拐点从图像上方向下扫，左右扫线会在斑马线出现问题，
//-------------------------------------------------------------------------------------------------------------------
void Identify(void)
{
    uint8 findr_x = 0;    //右点
    uint8 findr_y = 0;
    uint8 examr_x = 0;
    uint8 examr_y = 0;
    uint8 findl_x = 0;    //左点
    uint8 findl_y = 0;
    uint8 examl_x = 0;
    uint8 examl_y = 0;
    uint8 star = 0;
    uint8 end = 0;
    uint8 examcount = 0;
    //uint8 count;
    //uint8 examerror;
//    uint8 dircount;
    int directionrd[5][2] =  {{-1,1}, {-1,0}, {-1,-1}, {0,1}, {1,1}};  //顺时针下方向数组先x再y
    int directionld[5][2] =  {{1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};  //逆时针下方向数组
    int directionru[5][2] =  {{1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}};  //逆时针上方向数组
    int directionlu[5][2] =  {{-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}};  //逆时针上方向数组

    //每次采集后都对拐点标志位清零
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
               && Emo_imag[y-2][Right_Black_Point[y]] == EmoWhite && Emo_imag[y-5][Right_Black_Point[y]] == EmoWhite)    //右下拐点
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
               && Emo_imag[y-5][Left_Black_Point[y] + 1] == EmoWhite && Emo_imag[y-6][Left_Black_Point[y] + 1] == EmoWhite)     //左下拐点
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
            if(y > Endline && Right_Black_Point[y+1]==187 && Right_Black_Point[y+2]==187 && Right_Black_Point[y+3]==187)   //右上拐点
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
            if(y > Endline && Left_Black_Point[y+1]==0 && Left_Black_Point[y+2]==0 && Left_Black_Point[y+3]==0)     //左上拐点
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
//  @brief      车库寻找
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
            Garage_Findfinish_flag = 1;//找到车库标志
            Garagecount++;                 //遇见车库计数
        }
        else if(Garage_Findfinish_flag == 1)
        {
            break;
        }
    }
}


}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      根据拐点情况进行防误判
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       根据5邻域的拐点寻找会带来很多问题,所以进行非一般拐点的判断
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
//  @brief      车库函数
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       因为斑马线对左右扫线的影响，直接强行补线保证顺利通过斑马线
//-------------------------------------------------------------------------------------------------------------------

void Garage(void)
{
        Garage_Find();//找斑马线
        if(Garagecount >= GarageIn )   //满足入库条件&& dieReady == 4
        {
            camera_p.Garage_In_flag = 1;//停车标志
        }


}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      十字函数
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


//元素前摇
//-------------------------------------------------------------------------------------------------------------------
//  @brief      元素前摇
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       在扫描到两个符合的上下两个拐点后，针对先形拐点进行判断是什么元素，判断包括圆环、十字、P字
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

//清理一些拐点残余线
//-------------------------------------------------------------------------------------------------------------------
//  @brief      清理一些拐点残余线
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       因为车身不正，导致拐点上下的多余点会带偏中线的计算
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
//  @brief      P字出P的补线点搜寻
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       P字函数内部调用
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
//  @brief      P字函数
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
void Slalom(void)
{

    if(SlalomRight_flag == 1)  //右
   {
       if(Slalomcount == 1)
       {
           if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 0 && Right_Down_Point[1] > 80)     //上拐补线
           {
               Slalomcount=2;
           }
       }
       if(Slalomcount == 2)
       {
           if(Right_Up_Point_finish_flag == 0 && Right_Up_Point[1] > 70)    //弯道
           {
               Slalomcount=3;
           }
       }
       if(Slalomcount == 3)
       {
           Gyroscope_Star_flag = 1;
           EncoderSum_flag = 0;
           if(Emo_Angle >= 40)   //出现不该出现的情况，Slalom取消
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
           if(Left_Down_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1)   //出Slalom
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
           if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 0 && Left_Down_Point[1] > 80)     //上拐补线
           {
               Slalomcount=2;
           }
       }
       if(Slalomcount == 2)
       {
           if(Left_Up_Point_finish_flag == 0 && Left_Up_Point[1] > 70)    //弯道
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
           if(Right_Down_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1)   //出Slalomm
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
           if((Left_Down_Point[0]/2 + Right_Down_Point[0]/2) >= 60)  //进入待转位置
           {
               EncoderSum_flag = 1;
               Gyroscope_Star_flag = 1;
           }
           if(Right_Down_Point[1] > 73)
           {
               ObservationS_finish = 1;
           }
           if(Real_Distance >= 3100 && Emo_Angle <= -35)     //大概转向与距离
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
//  @brief      出圆环的补线点搜寻
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note       圆环函数内部调用
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
//  @brief      圆环的补充识别
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note
//-------------------------------------------------------------------------------------------------------------------
//static unsigned char circlrsu = 0;
void Circle_supplement(void)
{
    if(CornerLeft_flag == 0 && CornerRight_flag == 0 && Corners_flag == 0  && findrcount <= 4
    && Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1 && Right_Up_Point[1] >= 25 && Right_Up_Point[1] <= 50 && Right_Up_Point[0] < 145 && Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 0
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
    && Emo_imag[Right_Up_Point[1] - 1][Right_Up_Point[0] + 10] == EmoWhite
    && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 10] == EmoWhite
    )//&& Right_Black_Point[112] == 187 && Right_Black_Point[113] == 187 && Right_Black_Point[115] == 187
    {
        CircleRight_flag = 1;
    }
    if(CornerLeft_flag == 0 && CornerRight_flag == 0 && WindupL_flag == 0 && WindupR_flag == 0
       && SlalomLeft_flag == 0 && SlalomRight_flag == 0 && CircleLeft_flag == 0 && CircleRight_flag == 0 && camera_p.Garage_In_flag == 0
       && Emo_imag[Left_Up_Point[1] - 5][Left_Up_Point[0] + 20] == EmoWhite && Emo_imag[Left_Up_Point[1] + 15][Left_Up_Point[0] - 15] == EmoWhite
       && Left_Up_Point[1] >= 20 && Right_Up_Point[1] == 0 && Right_Down_Point[1] == 0
       && Emo_u8Decabs(Right_Black_Point[Left_Up_Point[1]],Right_Black_Point[Left_Up_Point[1]+30])<20 && Emo_u8Decabs(Right_Black_Point[Left_Up_Point[1]],Right_Black_Point[Left_Up_Point[1]+15])<10)
    {
        CircleLeft_flag = 1;
    }


}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      圆环函数
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
//圆环,环环相扣，走一步看一步
void Circle(void)
{
    uint8 ReplacePoint = 0;
    Circle_supplement();
    if(CircleLeft_flag == 1)
       {
           if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && Circlecount == 0)  //上下拐补线&& findlcount > 6
           {
               Circlecount = 1;
           }
           if(Circlecount == 1)
           {
               if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 0 && Left_Down_Point[1] > 70)    //下拐消失上拐补线
               {
                   Circlecount = 2;
               }
               else if(Left_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 1 && findlcount <= 3
                   && Emo_imag[Left_Up_Point[1] + 5][Left_Up_Point[0] - 5] == EmoWhite && Left_Up_Point[1] > 15)
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
               if(Left_Down_Point_finish_flag == 1 && Left_Up_Point_finish_flag == 0)    //下拐出现，等上拐
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
               && Emo_imag[Left_Up_Point[1] + 5][Left_Up_Point[0] - 5] == EmoWhite)        //上拐斜补线进环
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
               if(Left_Up_Point_finish_flag == 0 )        //下拐消失，上拐斜补线进环&& Real_Distance >= 4500
               {
                   if(Emo_Angle >= 30)                   //拐入成功
                   {
                       need_cornerL = 0;
                       Auxiliary_CorneringLeft_flag = 0;
                       Gyroscope_Star_flag = 0;
                       Circlecount = 5;
                       Paddingcurve = 0;
                       EncoderSum_flag = 0;
                       CC = 0;
                   }
                   else                                  //拐入失败
                   {
                       CircleLeft_flag = 0;
                       Circlecount = 0;
                       PaddingR = 0;
                       PaddingL = 0;
                       Paddingcurve = 0;
                       CC = 0;
                   }
               }
           }
           if(Circlecount == 5)
           {
               await++;
               if(await >= 3)
               {
                   if(Emo_Angle > 40)
                   {
                       Circlecount = 6;
                       await = 0;
                   }
               }
           }
           if(Circlecount == 6)
           {
               if(Right_Down_Point_finish_flag == 1 && Left_Up_Point_finish_flag == 0)       //右拐出现，进行右拐斜补线出环
               {
                   Circlecount = 7;
               }
           }
           if(Circlecount == 7)
           {
               Paddingcurve = 1;
               CircleOutPoint();
               if(Left_Down_Point_finish_flag == 1 && Left_Up_Point_finish_flag == 0 && Right_Down_Point_finish_flag == 0)//出口出而下拐出现上拐无    && Real_Distance >= 3800 && Emo_Angle > 38
               {

                   Paddingcurve = 0;
                   Gyroscope_Star_flag = 0;
                   EncoderSum_flag = 0;
                   Circlecount = 8;
               }
               else if(Left_Down_Point_finish_flag == 1 && Left_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 0)  //出口出上下拐都有 && Real_Distance >= 3800&& Emo_Angle > 38

               {
                   Paddingcurve = 0;
                   Gyroscope_Star_flag = 0;
                   EncoderSum_flag = 0;
                   Circlecount = 9;

               }
               else if(Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 0)  //下拐单补&& Real_Distance >= 3800&& Emo_Angle > 38

               {
                   Paddingcurve = 0;
                   Circlecount = 10;
               }
           }
           if(Circlecount == 8)
           {
               if(Left_Down_Point_finish_flag == 1 && Left_Up_Point_finish_flag == 1)       //上下拐不补线只记录
               {
                   Circlecount = 9;
               }
               else if(Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1)  //上拐单补
               {
                   Circlecount = 10;
               }
           }
           if(Circlecount == 9)
           {
               Circlecount = 10;
               if(Left_Down_Point_finish_flag == 0 && Left_Up_Point_finish_flag == 1)       //上拐单补
               {
                   Circlecount = 10;
               }
           }
           if(Circlecount == 10)                                                            //圆环结束
           {

               if(Left_Up_Point[1] >= 63)
               {
                   Circlecount = 11;
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
                //Near_Corners_flag = 0;
                Circlecount = 0;
                PaddingR = 0;
                PaddingL = 0;
                //Beepindex = 0;
                Circle_RC++;
                break;
        }

    }
    else if(CircleRight_flag == 1)
    {
        if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 1 && findrcount > 6 && Circlecount == 0)  //上下拐补线
        {
            Circlecount = 1;
        }
        if(Circlecount == 1)
        {
            if(Right_Up_Point_finish_flag == 1 && Right_Down_Point_finish_flag == 0 && Right_Down_Point[1] > 80)   //下拐消失上拐补线
            {
                Circlecount = 2;
            }
            else if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1
                && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] == EmoWhite && findrcount <= 3 && Right_Up_Point[1] > 15)
            {
                Circlecount = 4;

            }
            if(Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1
            && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] == EmoWhite && findrcount <= 3 && Right_Up_Point[1] > 15)        //上拐斜补线进环
            {
                Circlecount = 4;
            }
        }
        if(Circlecount == 2)
        {
            if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 0)    //下拐出现，等上拐
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
            && Emo_imag[Right_Up_Point[1]][Right_Up_Point[0] + 5] == EmoWhite)        //上拐斜补线进环
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
            if(Right_Up_Point_finish_flag == 0)        //下拐消失，上拐斜补线进环
            {
                if(Emo_Angle <= -40)        //拐入成功
                {
                    need_cornerR = 0;
                    Auxiliary_CorneringRight_flag = 0;
                    Gyroscope_Star_flag = 0;
                    Circlecount = 5;
                    EncoderSum_flag = 0;
                    Paddingcurve = 0;
                }
                else                                  //拐入失败
                {
                    CircleRight_flag = 0;
                    Circlecount = 0;
                    PaddingR = 0;
                    PaddingL = 0;
                    Paddingcurve = 0;
                    CC = 0;
                }
            }
        }
        if(Circlecount == 5)
        {
            await++;
            if(await >= 3)
            {
              if(Emo_Angle < -28)
                {
                    Circlecount = 6;
                    Gyroscope_Star_flag = 0;
                    EncoderSum_flag = 0;
                    await = 0;
                }
               }
            }
        if(Circlecount == 6)
        {
            if(Left_Down_Point_finish_flag == 1 || Right_Up_Point_finish_flag == 1)                  //左拐出现，进行左拐斜补线出环
            {
                Circlecount = 7;
            }
        }
        if(Circlecount == 7)
        {
            Paddingcurve = 1;
            CircleOutPoint();
            if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 0 && Left_Down_Point_finish_flag == 0
                 )   //出口出而下拐出现上拐无&& Real_Distance >= 3800  && Emo_Angle <-38
            {
                //Auxiliary_CorneringRight_flag = 0;
                //need_cornerR = 0;
                Paddingcurve = 0;
                Gyroscope_Star_flag = 0;
                EncoderSum_flag = 0;
                Circlecount = 8;
            }
            else if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 0
                   )  //出口出上下拐都有 && Real_Distance >= 3800 && Emo_Angle <-38
            {
                //Auxiliary_CorneringRight_flag = 0;
                //need_cornerR = 0;
                Paddingcurve = 0;
                Gyroscope_Star_flag = 0;
                EncoderSum_flag = 0;
                Circlecount = 9;
            }
            else if(Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1 && Left_Down_Point_finish_flag == 0
                   )  //下拐单补 && Real_Distance >= 3800 && Emo_Angle <-38
            {
                //Auxiliary_CorneringRight_flag = 0;
                //need_cornerR = 0;
                Paddingcurve = 0;
                Gyroscope_Star_flag = 0;
                EncoderSum_flag = 0;
                Circlecount = 10;
            }
        }
        if(Circlecount == 8)
        {

            if(Right_Down_Point_finish_flag == 1 && Right_Up_Point_finish_flag == 1)
            {
                Circlecount = 9;
            }
            else if(Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1)  //上拐单补
            {
                Circlecount = 10;
            }
        }
        if(Circlecount == 9)
        {
            Circlecount = 10;

            if(Right_Down_Point_finish_flag == 0 && Right_Up_Point_finish_flag == 1)  //上拐单补
            {
                Circlecount = 10;
            }
        }
        if(Circlecount == 10)
        {
            EncoderSum_flag = 1;
            if(Right_Up_Point[1] >= 60)     //圆环结束
            {
                Circlecount = 11;

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
                //Near_Corners_flag = 0;
                Circlecount = 0;
                PaddingR = 0;
                PaddingL = 0;
                //Beepindex = 0;
                Circle_RC++;
                break;
            case 12 :
                Link_Right_One_Point[0] = 187;
                Link_Right_One_Point[1] = 119;
                Link_Right_Two_Point[0] = Right_Up_Point[0];
                Link_Right_Two_Point[1] = Right_Up_Point[1];
                PaddingR = 1;
                PaddingL = 0;
                break;
        }

    }

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      避障函数
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
        //右边找障碍
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
            //左边找障碍
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

           //退出补线
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






/*******************补线**********************/
//先找到要补充的两条线，通过两点计算斜率得到两点组成的一次方程，得到剩余x的位置，将线换做左右边线
//-------------------------------------------------------------------------------------------------------------------
//  @brief      直线补线函数
//  @param      xone  第一个补线点x坐标
//  @param      yone  第一个补线点y坐标
//  @param      xtwo  第二个补线点x坐标
//  @param      ytwo  第二个补线点y坐标
//  @return     void
//  @note  Left_Black_Point[y]为我的左边线数组 Right_Black_Point[y]为我的右边线数组
//-------------------------------------------------------------------------------------------------------------------
void Padding_LineR(uint8 xone,uint8 yone,uint8 xtwo,uint8 ytwo)
{
    float k=0;  //斜率
    float b=0;  //截距
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
        Right_Black_Point[y]=(uint8)(((float)y-b)/k);  //两点之间补线
    }
}

void Padding_LineL(uint8 xone,uint8 yone,uint8 xtwo,uint8 ytwo)
{
    float k=0;  //斜率
    float b=0;  //截距
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
//  @brief      曲线函数
//  @param      PaddingR  右补线标志  0：不补线 1：要补线
//  @param      PaddingL  左补线标志
//  @param      Padding_CurveR  右曲线补线标志 0：补直线 1：补曲线
//  @param      Padding_CurveL  左曲线补线标志
//  @return     void
//  @note       补线的方式都通过此函数进行，外部只需要做到决定补线点的位置，和是否左右补线
//  Left_Black_Point[y]为我的左边线数组 Right_Black_Point[y]为我的右边线数组
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
//  @brief      最小二乘法计算曲率
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note  Left_Black_Point[y]为我的左边线数组 Right_Black_Point[y]为我的右边线数组
//-------------------------------------------------------------------------------------------------------------------
void curvature_computeL(void)
{
    int LeftXSum = 0, LeftYSum = 0, LeftXYSum = 0, LeftXXSum = 0;
    //float LeftK = 0, LeftB = 0;

    //int RightXSum = 0, RightYSum = 0, RightXYSum = 0, RightXXSum = 0;
    //float RightK = 0, RightB = 0;

    //int temp;
    //int LeftBlackError = 0, RightBlackError = 0;

    for (uint8 y = 53; y < 61; y++)//对赛道边界进行累加计算
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

    for (uint8 y = 53; y < 61; y++)//对赛道边界进行累加计算
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

    for (uint8 y = 53; y < 61; y++)//对赛道边界进行累加计算
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
//  @brief      平滑滤波
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
//  @brief      再次确定中线
//  @param
//  @param
//  @param
//  @param      因为补线后边线发生变化，需要再次计算中线，这里可以对丢线做处理
//  @return     void
//  @note  Left_Black_Point[y]为我的左边线数组 Right_Black_Point[y]为我的右边线数组
//-------------------------------------------------------------------------------------------------------------------
static uint8 Last_Middle_Point = 93;   //有时候中线会因为补线而跃迁，此处用于搬回曲线

//再次确定中线
void Get_Middle_Line(void)
{
    for(uint8 y=119 ; y >= 0 ; y--)
      {
          if(Right_Black_Point[y]==187 && Left_Black_Point[y]==0 && Corners_flag == 0 && Triforkpadding_flag == 0 && Near_Corners_flag == 0)        //两边都没找到线
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
          else if(Right_Black_Point[y]==187 && Left_Black_Point[y]!=0 && Corners_flag == 0 && Triforkpadding_flag == 0 && Near_Corners_flag == 0)    //直道左边找到线
          {
              Middle_Black_Point[y]=Left_Black_Point[y]+Straight[y];

          }
          else if(Left_Black_Point[y]==0 && Right_Black_Point[y]!=187 && Corners_flag == 0 && Triforkpadding_flag == 0 && Near_Corners_flag == 0)    //直道右边找到线
          {
              Middle_Black_Point[y]=Right_Black_Point[y]-Straight[y];

          }
          else if(Left_Black_Point[y]==0 && Right_Black_Point[y]!=187 && Corners_flag == 1 && Triforkpadding_flag == 0 && Near_Corners_flag == 0)    //弯道右边找到线
          {
              if(Right_Black_Point[y] < Corners[y])
                  Middle_Black_Point[y]=0;
              else
                  Middle_Black_Point[y]=Right_Black_Point[y]-(Corners[y] - 6);
          }
          else if(Right_Black_Point[y]==187 && Left_Black_Point[y]!=0 && Corners_flag == 1 && Triforkpadding_flag == 0 && Near_Corners_flag == 0)    //左边弯道找到线
          {
              if(Left_Black_Point[y] + Corners[y] > 187)
                  Middle_Black_Point[y]=187;
              else
                  Middle_Black_Point[y]=Left_Black_Point[y]+(Corners[y] - 6);
          }
  //        else if(Right_Black_Point[y]==187 && Left_Black_Point[y]!=0 && Triforkpadding_flag == 0 && Corners_flag == 1 && Near_Corners_flag == 1)    //右近端弯道找到线
  //        {
  //            if(Left_Black_Point[y] + Corners[y] > 187)
  //                Middle_Black_Point[y]=187;
  //            else
  //                Middle_Black_Point[y]=Left_Black_Point[y]+(Corners[y]-6);
  //        }
  //        else if(Left_Black_Point[y]==0 && Right_Black_Point[y]!=187 && Triforkpadding_flag == 0 && Corners_flag == 1 && Near_Corners_flag == 1)    //左近端弯道找到线
  //        {
  //            if(Right_Black_Point[y] < Corners[y])
  //                Middle_Black_Point[y]=0;
  //            else
  //                Middle_Black_Point[y]=Right_Black_Point[y]-(Corners[y]-6);
  //        }
          else if(Right_Black_Point[y]==187 && Left_Black_Point[y]!=0 && Slalom_Padding == 1 && Corners_flag == 0 && Near_Corners_flag == 0)    //向右Slalom找到线
          {
              if(Left_Black_Point[y] > 113)
                  Middle_Black_Point[y]=187;
              else
                  Middle_Black_Point[y]=Left_Black_Point[y]+(Corners[y]);
          }
          else if(Left_Black_Point[y]==0 && Right_Black_Point[y]!=187 && Slalom_Padding == 1 && Corners_flag == 0 && Near_Corners_flag == 0)    //向左Slalom找到线
          {
              if(Right_Black_Point[y] < 75)
                  Middle_Black_Point[y]=0;
              else
                  Middle_Black_Point[y]=Right_Black_Point[y]-(Corners[y]);
          }
          else             //两边都找到线
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
              // 累加每一行中线 X 轴位置
              totalX += All_x[y];
            }
        }
        //X轴的位置
        camera_p.T_X=totalX/59;


}





//元素识别的集合
//-------------------------------------------------------------------------------------------------------------------
//  @brief      元素识别的集合
//  @param
//  @param
//  @param
//  @param
//  @return     void
//  @note  元素识别的总处理
//  @note  Left_Black_Point[y]为我的左边线数组 Right_Black_Point[y]为我的右边线数组
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
        Identify();//拐点寻找
        Element_dispose();//拐点情况进行防误判
        Cross();//十字
        Windup();//前瞻
        Garage();//斑马线
        Slalom();//p字
        Circle();//圆环
//        Obstacle_avoidance();//避障
    }
}

void Camera_Head(void)        //摄像头处理总函数
{
        Camera_Init();
        Thresholding();//二值化
        Find_Line();//获取边缘和中心线
        Think();
        camera_p.test1_flag=Circlecount;
        Padding_Line();//对十字等岔路口补线
        Get_Middle_Line();//确认中心线
        if(flag_start == 0)
                {
                 if((camera_p.T_X>80&&camera_p.T_X<98)&&camera_p.T_X!=93)
                {
                    camera_p.N_X = 93;
                    flag_start = 1;
                }
                }
        IPS_Flag = 1;//标志一个循环结束
}
