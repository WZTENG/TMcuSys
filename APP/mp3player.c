#include "mp3player.h"
#include "vs10xx.h"	 
#include "delay.h"
#include "led.h"
#include "key.h"
#include "malloc.h"
#include "text.h"
#include "string.h"
#include "exfuns.h"
#include "fattester.h"	 
#include "ff.h"   
#include "flac.h"	
#include "includes.h"


u16 f_kbps=0;//�����ļ�λ��	
u16 time=0;// ��ǰʱ�����
u16 totalTime=0;//�ܳ�
//��ʾ����ʱ��,������ ��Ϣ 
//lenth:�����ܳ���
void mp3_msg_show(u32 lenth)
{	
	static u16 playtime=0;//����ʱ����	     
 	
	u16 temp=0;	  
	if(f_kbps==0xffff)//δ���¹�
	{
		playtime=0;
		f_kbps=VS_Get_HeadInfo();	   //��ñ�����
	}	 	 
	time=VS_Get_DecodeTime(); //�õ�����ʱ��
	if (playtime==0) {
        playtime=time;
    } else if ((time!=playtime)&&(time!=0)) {//1sʱ�䵽,������ʾ����
		playtime=time;//����ʱ�� 	 				    
		temp=VS_Get_HeadInfo(); //��ñ�����	   				 
		if(temp!=f_kbps) {
			f_kbps=temp;//����KBPS	  				     
		}			 
		if (f_kbps) {
            totalTime=(lenth/f_kbps)/125;//�õ�������   (�ļ�����(�ֽ�)/(1000/8)/������=����������
        } else {
            totalTime=0;//�Ƿ�λ��
        }            
	}   		 
}			  		 


//����һ��ָ���ĸ���				     	   									    	 
//����ֵ:0,�����������
//		 1,��һ��
//       2,��һ��
//       0XFF,���ִ�����
extern char musicPlaying;
extern char musicChange;
u8 mp3_play_song(u8 *pname)
{	 
 	FIL* fmp3;
    u16 br;
	u8 res,rval;	  
	u8 *databuf;	   		   
	u16 i=0; 
	u8 key; 
    OS_ERR err;
    CPU_SR_ALLOC();
			   
	rval=0;	    
	fmp3 = (FIL*)mymalloc(SRAMIN,sizeof(FIL));//�����ڴ�
	databuf = (u8*)mymalloc(SRAMIN,4096);		//����4096�ֽڵ��ڴ�����
	if (databuf==NULL||fmp3==NULL) {
        rval=0XFF ;//�ڴ�����ʧ��
    }
	if (rval==0) {	  
	  	VS_Restart_Play();  					//�������� 
		VS_Set_All();        					//������������Ϣ 			 
		VS_Reset_DecodeTime();					//��λ����ʱ�� 	  
		res=f_typetell(pname);	 	 			//�õ��ļ���׺	 			  	 						 
		if (res==0x4c) {//�����flac,����patch	
			VS_Load_Patch((u16*)vs1053b_patch,VS1053B_PATCHLEN);
		}  				 		   		 						  
		res=f_open(fmp3,(const TCHAR*)pname,FA_READ);//���ļ�	 
 		if (res==0) {//�򿪳ɹ�
			VS_SPI_SpeedHigh();	//����
			while (rval==0 && musicPlaying && (musicChange==0)) {
                OS_CRITICAL_ENTER();
				res=f_read(fmp3,databuf,4096,(UINT*)&br);//����4096���ֽ�
                OS_CRITICAL_EXIT();
				i=0;
				do {//������ѭ��
					if (VS_Send_MusicData(databuf+i)==0) {//��VS10XX������Ƶ����
						i+=32;
					} else {
                        OSTimeDlyHMSM(0, 0, 0, 20, OS_OPT_TIME_PERIODIC, &err);
						mp3_msg_show(fmp3->fsize);//��ʾ��Ϣ	    
					}	    	    
				} while (i<4096 && musicPlaying && (musicChange==0));//ѭ������4096���ֽ� 
				if (br!=4096||res!=0) {
					rval=0;
					break;//������.		  
				} 							 
			}
			f_close(fmp3);
		} else {
            rval=0XFF;//���ִ���
        }            
	}					
    if (musicPlaying==0 || musicChange==1) {
        rval = 3;
    }
    
	myfree(SRAMIN,databuf);	  	 		  	    
	myfree(SRAMIN,fmp3);
	return rval;	  	 		  	    
}




