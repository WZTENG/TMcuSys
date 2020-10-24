#include "nesplay.h"
#include "nes_main.h"	 
#include "ff.h"//teng
#include "malloc.h"//teng
#include "ili93xx.h"//teng
#include "tpad.h"//teng
//#include "spb.h"	  
//#include "audioplay.h"	
//#include "usart3.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//APP-NESģ���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/7/20
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//*******************************************************************************
//�޸���Ϣ
//��
////////////////////////////////////////////////////////////////////////////////// 	   
  
u8 *rom_file;
extern u8 nesruning;

//������Ϸ����
void nes_load_ui(void)
{	
//	app_filebrower((u8*)nes_caption_tbl[gui_phy.language],0X05);//��ʾ���� 
//  	gui_fill_rectangle(0,20,lcddev.width,lcddev.height-20,BLACK);//����ɫ 		    	  
} 
//NES��Ϸ
u8 nes_play(u8 *path)
{
  	DIR nesdir;		//nesdirר��	  
	FILINFO nesinfo;	 	   
	u8 res;
	u8 rval=0;			//����ֵ	  
	u8 *pname=0;
	u8 *fn;	
  
	//Ϊ���ļ������뻺����
 	nesinfo.lfsize=_MAX_LFN*2+1;
	nesinfo.lfname=mymalloc(SRAMEX, nesinfo.lfsize);
	if(nesinfo.lfname==NULL) {
        rval=1;//�����ڴ�ʧ�� 
    } else {
        memset((u8*)nesinfo.lfname,0,nesinfo.lfsize); 
    }
    fn=(u8*)(*nesinfo.lfname?nesinfo.lfname:nesinfo.fname);
    pname=mymalloc(SRAMEX, strlen((const char*)fn)+strlen((const char*)path)+2);//�����ڴ�
    if(pname==NULL) {
        rval=1;//����ʧ��
    } else {
        pname=path;//�ļ�������·��  
//				if(audiodev.status&(1<<7))		//��ǰ�ڷŸ�??
//				{
//					audio_stop_req(&audiodev);	//ֹͣ��Ƶ����
//					audio_task_delete();		//ɾ�����ֲ�������.
//					delay_ms(1010);
//				}  				
        //��1963/9341/5510/5310����LCD��LCD,����
        if(lcddev.id!=0X1963&&lcddev.id!=0X9341&&lcddev.id!=0X5510&&lcddev.id!=0X5310) {
            FSMC_Bank1E->BWTR[6]&=0XFFFFFFF0;//���֮ǰ������
            FSMC_Bank1E->BWTR[6]|=3<<0;	//��ַ����ʱ�䣨ADDSET��Ϊ4��HCLK  	 	 
        }
        //SRAM����
        FSMC_Bank1->BTCR[5]&=0XFFFF00FF;//���֮ǰ������
        FSMC_Bank1->BTCR[5]|=4<<8;		//���ݱ���ʱ�䣨DATAST��Ϊ8��HCLK 8/128M=62.5ns	 	 
//        USART3->CR1&=~(1<<5);			//��ֹ����3���գ���ʱ���ٴ���SIM900A�����Ϣ��
        //��ʼnes��Ϸ
        nesruning = 1;
        rval = nes_load(pname);			//��ʼnes��Ϸ
        nesruning = 0;
        //��1963/9341/5510/5310����LCD��LCD,�ָ�
        if(lcddev.id!=0X1963&&lcddev.id!=0X9341&&lcddev.id!=0X5510&&lcddev.id!=0X5310) {
            FSMC_Bank1E->BWTR[6]&=0XFFFFFFF0;//���֮ǰ������
            FSMC_Bank1E->BWTR[6]|=0<<0;	//��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK  	 	 
        }
        //SRAM����
        FSMC_Bank1->BTCR[5]&=0XFFFF00FF;//���֮ǰ������
        FSMC_Bank1->BTCR[5]|=3<<8;		//���ݱ���ʱ�䣨DATAST��Ϊ7��HCLK 7/128M=55ns	 	 
//				usart3_init(36,115200);			//�ָ�����3����
    }	       
    myfree(SRAMEX, pname);				//�ͷ��ڴ�		  
    pname=NULL;
//    TPAD_Init(6);			//��������TPADֵ
	myfree(SRAMEX, pname);			//�ͷ��ڴ�		  
 	myfree(SRAMEX, nesinfo.lfname);		 
	return rval;  								  
}


