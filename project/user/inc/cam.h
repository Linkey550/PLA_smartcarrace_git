/*
 * cam.h
 *
 *  Created on: 2024��3��27��
 *      Author: pp
 */
#include "zf_common_headfile.h"
#include "zf_common_fifo.h"

#define CAMERA_RECEIVER_BUFFER_SIZE         (8)
#define EmoWhite 255 //������ֵ
#define EmoBlack 0 //����
#define GarageIn 2



/****************��������*******************/
extern uint8 Emo_imag[120][188],
             OSTU,
             Left_Black_Point[120],
             Middle_Black_Point[120],
             Right_Black_Point[120],
             Link_Right_One_Point[2],
             Link_Right_Two_Point[2],
             Link_Left_One_Point[2],
             Link_Left_Two_Point[2],
             Right_Up_Point[2],
             Right_Down_Point[2],
             Left_Up_Point[2],
             Left_Down_Point[2],
             Endline,OUST1,
             Corners[120],
             Straight[120],
             Trifork_padding[120],
             BoundaryLeft,
             BoundaryRight,
             TriforkLeft_Point[2],
             TriforkMiddle_Point[2],
             TriforkRight_Point[2],
             Slalom_Point[2],
             Left_Point[120][188],
             Right_Point[120][188],
             CircleOut_Point[2];

             //Garage_Point[2];
extern int Triforkcount,
           findrcount,
           findlcount,
           Slalomcount,
           Circlecount,
           Triforkcount,
           TriforkTurn,
           starcount,
           Crosscount;

//           Garage_Count,
//           Garage_Out_Count,
//           Garage_In_Count;
extern unsigned char Corners_flag,
                     CornerRight_flag,
                     CornerLeft_flag,
                     CornerS_flag,
                     Element_Corners_flag,
                     SlalomLeft_flag,
                     SlalomRight_flag,
//                     CircleLeft_flag,
//                     CircleRight_flag,
                     Trifork_flag,
                     Trifork_PointLeft_Findfinish_flag,
                     Trifork_PointRight_Findfinish_flag,
                     Trifork_PointMiddle_Findfinish_flag,
                     Triforkpadding_flag,
                     Near_CornerLeft_flag,
                     Near_CornerRight_flag,
                     Near_Corners_flag,
                     Right_Up_Point_finish_flag,
                     Right_Down_Point_finish_flag,
                     Left_Up_Point_finish_flag,
                     Left_Down_Point_finish_flag,
                     CircleSwitch_flag,
                     Garage_flag,
//                     Garage_In_flag,
                     WindupL_flag,
                     WindupR_flag,
                     Cross_flag,
                     Ramp_flag,
                     CircleBig,
                     finish,
                     SlC,
                     RampReady_flag,
                     dieReady;
//                     Garage_Out_flag,
//                     Garage_In_flag,
//                     Garage_Out_Finsh_flag;
extern vuint8 IPS_Flag;
extern  float   Garagecount,
                ObscountR,
                ObscountL,
                Obscount2,
                CircleLeft_flag,
                CircleRight_flag,
                campit_time,
                ObstacleL_flag,//�ϰ���߱�־
                ObstacleR_flag,//�ϰ��ұ߱�־
                Garage_Findfinish_flag;
extern volatile float Differential_Error;

typedef struct Contours
{
    int height;
    int width;
    int stateFlag;
} contour;

typedef struct  {
    float T_X; //x��λ��
    float N_X; //x��λ��
    float CurvatureLeft ;//������ʼ���
    float CurvatureRight ;//�Ҳ����ʼ���
    float Garage_In_flag;//ͣ����־
    float test1_flag;//����ֵ
    float test2_flag;
    float test3_flag;

}cam_parameter;





void Camera_Init(void);
int Emo_abs(int x);
uint8 Emo_max(uint8 x , uint8 y);
static uint8 Ostu(uint8 *image, uint16 width, uint16 height);
void Thresholding(void);
void Get_Middle_Line(void);
void Judge_Ramp(void);
void Windup(void);
void Identify(void);
void Padding_LineR(uint8 xone,uint8 yone,uint8 xtwo,uint8 ytwo);
void Padding_LineL(uint8 xone,uint8 yone,uint8 xtwo,uint8 ytwo);\
void edgeTracing( const unsigned char* _Binary, contour** _TracingPtr, const int _Width, const int _Height );
//float radius_3pts(float pt0[2], float pt1[2], float pt2[2]);
float process_curvity(uint8 x1, uint8 y1, uint8 x2, uint8 y2, uint8 x3, uint8 y3);
void curvature_computeL(void);
void curvature_computeR(void);
void curvature_compute(void);
void Judge(void);
void Judge_CornerS(void);
void Think(void);
void CircleOutPoint(void);
void leastSquares(uint8 n);
//void Camera_Pro(void);
//void exhibition_match1(void);
//void exhibition_match2(void);
//void Judge_exhibition_match(void);
//void exhibition_match(void);
void Camera_Head(void);
//static void Garage_Findpoint(void);
//void Garage_Out(void);
//void Garage_In(void);
void Garage(void);
void Garage_Find(void);
void Clear_flag(void);
void Obstacle_avoidance(void);//���Ϻ���
void Trifork_Shuttle(void);
void Differential_Calculate(void);
uint8 HDPJ_lvbo(uint8 data[], uint8 N, uint8 size);

