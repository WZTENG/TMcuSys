#include <stdlib.h>  /* for rand */

//#include "GUIDEMO.h"
#include "GUI.h"
#include "DIALOG.h"
#include "ili93xx.h"
#include "malloc.h"

u8 ITERATION = 128; //��������
#define REAL_CONSTANT 0.285f //ʵ������
#define IMG_CONSTANT 0.01f //�鲿����

//���������б�
//const u16 zoom_ratio[26] =
//{
//    120, 110, 100, 150, 200, 275, 350, 450,
//    600, 800, 1000, 1200, 1500, 2000, 1500,
//    1200, 1000, 800, 600, 450, 350, 275, 200,
//    150, 100, 110,
//}; 

//��ʼ����ɫ��
//clut:��ɫ��ָ��
void InitCLUT(u16 *clut)
{
    u32 i=0x00;
    u16 red=0,green=0,blue=0;
    for(i=0;i<ITERATION;i++)//������ɫ��
    {
        //���� RGB ��ɫֵ
        red=(i*8*256/ITERATION)%256;
        green=(i*6*256/ITERATION)%256;
        blue=(i*4*256/ITERATION)%256;
        //�� RGB888,ת��Ϊ RGB565
        red=red>>3;
        red=red<<11;
        green=green>>2;
        green=green<<5;
        blue=blue>>3;
        clut[i]=red+green+blue;
    }
} 
    
    
//���� Julia ����ͼ��
//size_x,size_y:��Ļ x,y ����ĳߴ�
//offset_x,offset_y:��Ļ x,y �����ƫ��
//zoom:��������
void GenerateJulia_fpu(u16 size_x,u16 size_y,u16 offset_x,u16 offset_y,u16 zoom)
{
    u8 i; u16 x,y;
    float tmp1,tmp2;
    float num_real,num_img;
    float radius;
    u16 color_map[256];
    
    InitCLUT(color_map);
    for(y=0;y<size_y;y++)
    {
        for(x=0;x<size_x;x++)
        {
            num_real=y-offset_y;
            num_real=num_real/zoom;
            num_img=x-offset_x;
            num_img=num_img/zoom;
            i=0;
            radius=0;
            while((i<ITERATION-1)&&(radius<4))
            {
                tmp1=num_real*num_real;
                tmp2=num_img*num_img;
                num_img=2*num_real*num_img+IMG_CONSTANT;
                num_real=tmp1-tmp2+REAL_CONSTANT;
                radius=tmp1+tmp2;
                i++;
            }
            TFTLCD->LCD_RAM=color_map[i];//���Ƶ���Ļ
        }
    }
}


void CreateJulia(void) {
    int TimeStart, i;
    WM_HWIN videoWin;
    u16 r;

    videoWin = WM_CreateWindow(0,0,lcddev.width,lcddev.height,WM_CF_SHOW|WM_CF_STAYONTOP,NULL,0);
    WM_SelectWindow(videoWin);
    GUI_SetBkColor(GUI_BLACK);
    GUI_Clear();
    
    LCD_Set_Window(0,0,lcddev.width,lcddev.height);//���ô���
    LCD_WriteRAM_Prepare();
    do {
        ITERATION = rand()%256;
    } while (ITERATION<64);
//    r = zoom_ratio[rand()%26];
    do {
        r = rand();
    } while (r<100 || r>1500);
    GenerateJulia_fpu(lcddev.width,lcddev.height,lcddev.width/2,lcddev.height/2,r);

    GUI_SetColor(0xFFFFFF);
    GUI_SetBkColor(0x000000);
    TimeStart = 5000;
//    for (i=0;i<=lcddev.width;i++) {
//        GUI_FillRect(0, lcddev.height-1, i, lcddev.height-1);
//        GUI_Delay(TimeStart/lcddev.width);
//    }
    GUI_SetFont(&GUI_Font10_ASCII);
    GUI_SetTextMode(GUI_TM_NORMAL);
    for (i=0;i<=TimeStart/1000;i++) {
        GUI_DispDecAt(TimeStart/1000-i, lcddev.width-11, 5, 1);
        GUI_Delay(1000);
    }

    WM_DeleteWindow(videoWin);
}


