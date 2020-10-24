#include "videoplayer.h" 
#include "string.h"  
#include "key.h" 
#include "usart.h"   
#include "delay.h"
#include "timer.h"
#include "ili93xx.h"
#include "led.h"
#include "key.h"
#include "malloc.h"
//#include "i2s.h" 
//#include "wm8978.h" 
#include "mjpeg.h" 
#include "avi.h"
#include "exfuns.h"
#include "text.h"
#include "exti.h"
#include "textfont.h"
   
extern u16 frame;
extern vu8 frameup;//��Ƶ����ʱ϶���Ʊ���,������1��ʱ��,���Ը�����һ֡��Ƶ
extern vu8 framecnt;		//ͳһ��֡������
extern vu8 framecntout;	//ͳһ��֡�������������

u8 videoruning=0;

volatile u8 i2splaybuf;	//�������ŵ���Ƶ֡������
u8* i2sbuf[4]; 			//��Ƶ����֡,��4֡,4*5K=20K
  

//��ʾ��ǰ����ʱ��
//favi:��ǰ���ŵ���Ƶ�ļ�
//aviinfo;avi���ƽṹ��
void video_time_show(FIL *favi,AVI_INFO *aviinfo)
{	 
	static u32 oldsec;	//��һ�εĲ���ʱ��
	u8* buf;
	u32 totsec=0;		//video�ļ���ʱ�� 
	u32 cursec; 		//��ǰ����ʱ�� 
	totsec=(aviinfo->SecPerFrame/1000)*aviinfo->TotalFrame;	//�ܳ���(��λ:ms) 
	totsec/=1000;		//������. 
  	cursec=((double)favi->fptr/favi->fsize)*totsec;//��ǰ���ŵ���������?  
	if(oldsec!=cursec)	//��Ҫ������ʾʱ��
	{
		buf=mymalloc(SRAMEX,100);//����100�ֽ��ڴ�
		oldsec=cursec; 
		sprintf((char*)buf,"%02d:%02d:%02d/%02d:%02d:%02d",cursec/3600,(cursec%3600)/60,cursec%60,totsec/3600,(totsec%3600)/60,totsec%60);
 		Show_Str(136,291,lcddev.width-5,12,buf,12,0,LGRAY);
		myfree(SRAMEX,buf);		
	}
    LCD_Fill(0, 320, lcddev.width*((float)cursec/totsec), 320, LGRAY);
}
//��ʾ��ǰ��Ƶ�ļ��������Ϣ 
//aviinfo;avi���ƽṹ��
//0:�ɹ� 1:ʧ��
u8 video_info_show(AVI_INFO *aviinfo)
{	  
	u8 *buf;
	buf=mymalloc(SRAMEX,100);//����100�ֽ��ڴ� 
    sprintf((char*)buf,"FPS:%02d",0); 
    Show_Str(79,291,lcddev.width-10,12,buf,12,0,LGRAY);
    sprintf((char*)buf,"%02d:%02d:%02d/%02d:%02d:%02d",0,0,0,0,0,0);
 	Show_Str(136,291,lcddev.width-5,12,buf,12,0,LGRAY);
	sprintf((char*)buf,"֡��:%02d֡",1000/(aviinfo->SecPerFrame/1000)); 
 	Show_Str(3,304,lcddev.width-10,12,buf,12,0,LGRAY);
    sprintf((char*)buf,"%d x %d",aviinfo->Width, aviinfo->Height); 
 	Show_Str(3,291,lcddev.width-10,12,buf,12,0,LGRAY);
    sprintf((char*)buf,"��Ƶͨ��:%d  ��Ƶ������:%d",aviinfo->Channels,aviinfo->SampleRate*10); 
 	Show_Str(64,304,lcddev.width-10,12,buf,12,0,LGRAY);
	myfree(SRAMEX,buf);
    return ((aviinfo->Width > lcddev.width) || (aviinfo->Height > lcddev.height));
}

void video_fps(void) {
    u8 *buf;
	buf=mymalloc(SRAMEX, 20);//����100�ֽ��ڴ�
    sprintf((char*)buf,"%02d",framecntout); 
    Show_Str(79+6*4,291,lcddev.width-10,12,buf,12,0,LGRAY);
    myfree(SRAMEX,buf);
}


//����һ��mjpeg�ļ�
//pname:�ļ���
//����ֵ:
//KEY0_PRES:��һ��
//KEY1_PRES:��һ��
//����:����
u8 video_play_mjpeg(u8 *pname)
{
    OS_ERR err;
	u8* framebuf;	//��Ƶ����buf	 
	u8* pbuf;		//bufָ��  
	FIL *favi;
	u8  res=0;
	u16 offset=0; 
	u32	nr; 
	u8 key;   
    u8 i2ssavebuf;
    
    videoruning = 1;
    
	i2sbuf[0]=mymalloc(SRAMEX,AVI_AUDIO_BUF_SIZE);	//������Ƶ�ڴ�
//	i2sbuf[1]=mymalloc(SRAMEX,AVI_AUDIO_BUF_SIZE);	//������Ƶ�ڴ�
//	i2sbuf[2]=mymalloc(SRAMEX,AVI_AUDIO_BUF_SIZE);	//������Ƶ�ڴ�
//	i2sbuf[3]=mymalloc(SRAMEX,AVI_AUDIO_BUF_SIZE);	//������Ƶ�ڴ� 
	framebuf=mymalloc(SRAMEX,AVI_VIDEO_BUF_SIZE);	//������Ƶbuf
	favi=(FIL*)mymalloc(SRAMEX,sizeof(FIL));		//����favi�ڴ� 
	memset(i2sbuf[0],0,AVI_AUDIO_BUF_SIZE);
//	memset(i2sbuf[1],0,AVI_AUDIO_BUF_SIZE); 
//	memset(i2sbuf[2],0,AVI_AUDIO_BUF_SIZE);
//	memset(i2sbuf[3],0,AVI_AUDIO_BUF_SIZE); 
	if(i2sbuf[0]==NULL||framebuf==NULL||favi==NULL) {
//		printf("memory error!\r\n");
		res=0XFF;
	}   
	while (res==0 && videoruning) { 
		res=f_open(favi,(char *)pname,FA_READ);
		if (res==0) {
			pbuf=framebuf;			
			res=f_read(favi,pbuf,AVI_VIDEO_BUF_SIZE,&nr);//��ʼ��ȡ	
			if (res) {
//				printf("fread error:%d\r\n",res);
                f_close(favi);
				break;
			} 	 
			//��ʼavi����
			res=avi_init(pbuf,AVI_VIDEO_BUF_SIZE);	//avi����
			if (res) {
//				printf("avi err:%d\r\n",res);
                f_close(favi);
				break;
			}
            framecnt = 0;
			res=video_info_show(&avix);
            if (res==1) {
                videoruning = 0;
                res=0x03;
                f_close(favi);
                break;
            }
			TIM6_Int_Init(avix.SecPerFrame/100-1,7200-1);//10Khz����Ƶ��,��1��100us 
            TIM7_Int_Init(10000-1,7200-1);//teng
            EXTIX_Init();//tengʹ���ж����˳�
			offset=avi_srarch_id(pbuf,AVI_VIDEO_BUF_SIZE,"movi");//Ѱ��movi ID	 
			avi_get_streaminfo(pbuf+offset+4);			//��ȡ����Ϣ 
			f_lseek(favi,offset+12);					//������־ID,����ַƫ�Ƶ������ݿ�ʼ��	 
			res=mjpegdec_init((lcddev.width-avix.Width)/2, (lcddev.height-avix.Height)/2);//JPG�����ʼ�� 
//			if(avix.SampleRate)							//����Ƶ��Ϣ,�ų�ʼ��
//			{
//				WM8978_I2S_Cfg(2,0);	//�����ֱ�׼,16λ���ݳ���
//				I2S2_Init(I2S_Standard_Phillips,I2S_Mode_MasterTx,I2S_CPOL_Low,I2S_DataFormat_16bextended);		//�����ֱ�׼,��������,ʱ�ӵ͵�ƽ��Ч,16λ֡����
//				I2S2_SampleRate_Set(avix.SampleRate);	//���ò�����
//				I2S2_TX_DMA_Init(i2sbuf[1],i2sbuf[2],avix.AudioBufSize/2); //����DMA
//				i2s_tx_callback=audio_i2s_dma_callback;	//�ص�����ָ��I2S_DMA_Callback
//				i2splaybuf=0;
//				i2ssavebuf=0; 
//				I2S_Play_Start(); //����I2S���� 
//			}
 			while (videoruning) {//����ѭ��
				if(avix.StreamID==AVI_VIDS_FLAG) {	//��Ƶ��
					pbuf=framebuf;
					f_read(favi,pbuf,avix.StreamSize+8,&nr);		//������֡+��һ������ID��Ϣ  
					res=mjpegdec_decode(pbuf,avix.StreamSize);
					if (res) {
//						printf("decode error!\r\n");
					} 
					while(frameup==0);	//�ȴ�ʱ�䵽��(��TIM6���ж���������Ϊ1)
					frameup=0;			//��־����
					frame++;
                    framecnt++;
				} else {	//��Ƶ��
//                    video_info_show(&avix); 
                    video_fps();
					video_time_show(favi,&avix); 	//��ʾ��ǰ����ʱ��
//					i2ssavebuf++;
//					if(i2ssavebuf>3)i2ssavebuf=0;
//					do
//					{
//						nr=i2splaybuf;
//						if(nr)nr--;
//						else nr=3; 
//					}while(i2ssavebuf==nr);//��ײ�ȴ�. 
                    i2ssavebuf=0;
					f_read(favi,i2sbuf[i2ssavebuf],avix.StreamSize+8,&nr);//���i2sbuf	 
					pbuf=i2sbuf[i2ssavebuf];  
				} 
//				key=KEY_Scan(0);
//				if(key==KEY0_PRES||key==KEY2_PRES)//KEY0/KEY2����,������һ��/��һ����Ƶ
//				{
//					res=key;
//					break; 
//				}else if(key==KEY1_PRES||key==WKUP_PRES)
//				{
//					I2S_Play_Stop();//�ر���Ƶ
//					video_seek(favi,&avix,framebuf);
//					pbuf=framebuf;
//					I2S_Play_Start();//����DMA���� 
//				}
				if(avi_get_streaminfo(pbuf+avix.StreamSize))//��ȡ��һ֡ ����־
				{
//					printf("frame error \r\n"); 
					res=KEY0_PRES;
					break; 
				}
                OSTimeDlyHMSM(0, 0, 0, 2, OS_OPT_TIME_PERIODIC, &err);                
			}
//			I2S_Play_Stop();	//�ر���Ƶ
			TIM6->CR1&=~(1<<0); //�رն�ʱ��6
            TIM_Cmd(TIM7,DISABLE); //�رն�ʱ��7 teng
            EXTI->IMR &= ~(EXTI_Line2);// �ر��жϰ�
			LCD_Set_Window(0,0,lcddev.width,lcddev.height);//�ָ�����
			mjpegdec_free();	//�ͷ��ڴ�
			f_close(favi); 
		}
	}
	myfree(SRAMEX,i2sbuf[0]);
//	myfree(SRAMEX,i2sbuf[1]);
//	myfree(SRAMEX,i2sbuf[2]);
//	myfree(SRAMEX,i2sbuf[3]);
	myfree(SRAMEX,framebuf);
	myfree(SRAMEX,favi);
    videoruning = 0;
	return res;
}
//avi�ļ�����
u8 video_seek(FIL *favi,AVI_INFO *aviinfo,u8 *mbuf)
{
	u32 fpos=favi->fptr;
	u8 *pbuf;
	u16 offset;
	u32 br;
	u32 delta;
	u32 totsec;
	u8 key; 
	totsec=(aviinfo->SecPerFrame/1000)*aviinfo->TotalFrame;	
	totsec/=1000;//������.
	delta=(favi->fsize/totsec)*5;		//ÿ��ǰ��5���ӵ������� 
	while(1) {
		key=KEY_Scan(1); 
		if(key==WKUP_PRES)//���
		{
			if(fpos<favi->fsize)fpos+=delta; 
			if(fpos>(favi->fsize-AVI_VIDEO_BUF_SIZE))
			{
				fpos=favi->fsize-AVI_VIDEO_BUF_SIZE;
			}
		} else if(key==KEY1_PRES)//����
		{
			if(fpos>delta)fpos-=delta;
			else fpos=0; 
		}else break;
		f_lseek(favi,fpos);
		f_read(favi,mbuf,AVI_VIDEO_BUF_SIZE,&br);	//������֡+��һ������ID��Ϣ 
		pbuf=mbuf; 
		if(fpos==0) //��0��ʼ,����Ѱ��movi ID
		{
			offset=avi_srarch_id(pbuf,AVI_VIDEO_BUF_SIZE,"movi"); 
		} else offset=0;
		offset+=avi_srarch_id(pbuf+offset,AVI_VIDEO_BUF_SIZE,avix.VideoFLAG);	//Ѱ����Ƶ֡	
		avi_get_streaminfo(pbuf+offset);			//��ȡ����Ϣ 
		f_lseek(favi,fpos+offset+8);				//������־ID,����ַƫ�Ƶ������ݿ�ʼ��	 
		if(avix.StreamID==AVI_VIDS_FLAG) {
			f_read(favi,mbuf,avix.StreamSize+8,&br);	//������֡ 
			mjpegdec_decode(mbuf,avix.StreamSize); 		//��ʾ��Ƶ֡
		} else {
			printf("error flag");
		}
		video_time_show(favi,&avix);  
	}
	return 0;
}



