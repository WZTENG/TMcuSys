#include "sys.h"
#include "ff.h"
#include "exfuns.h" 
#include "ili93xx.h"
//#include "audioplay.h"
//#include "spb.h"

#include "sms_vdp.h"
#include "sms_main.h"
#include "sms_sn76496.h"
#include "sms_z80a.h"

#include "nes_main.h" 
#include "malloc.h"	            //�ڴ���� 
//#include "usbh_hid_gamepad.h"
//#include "i2s.h" 
#include "timer.h"
#include "audiosel.h"
#include "nes_apu.h"
#include "vs10xx.h"
#include "string.h"
//////////////////////////////////////////////////////////////////////////////////	 
//��������ֲ������ye781205��SMSģ��������
//ALIENTEK STM32F407������
//SMS������ ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/10/12
//�汾��V1.0  			  
////////////////////////////////////////////////////////////////////////////////// 	 
extern u8 nesruning;
extern u8 *nesapusbuf[NES_APU_BUF_NUM];		//��Ƶ����֡

u16 *smsi2sbuf1; 			//��Ƶ����֡,ռ���ڴ��� 367*2 �ֽ�@22050Hz
u16 *smsi2sbuf2; 			//��Ƶ����֡,ռ���ڴ��� 367*2 �ֽ�@22050Hz

u8* sms_rom;				//SMS ROM�洢��ַָ��
u8* SMS_romfile;			//ROMָ��=sms_rom/sms_rom+512
u8* S_RAM;					//internal SMS RAM	16k  [0x4000] 	 
u8* E_RAM;					//external cartridge RAM (2 X 16K Bank Max) [0x8000] 


//�ͷ�SMS����������ڴ�
void sms_sram_free(void)
{
    u8 i;
	myfree(SRAMEX,sms_rom);
	myfree(SRAMEX,E_RAM);
	myfree(SRAMEX,cache);
	
	myfree(SRAMEX,S_RAM);
	myfree(SRAMEX,SMS_VDP);
	myfree(SRAMEX,psg_buffer);
	myfree(SRAMEX,SN76496);
	myfree(SRAMEX,Z80A);
	myfree(SRAMEX,VRam);
	
	myfree(SRAMEX,smsi2sbuf1);
	myfree(SRAMEX,smsi2sbuf2);
	myfree(SRAMEX,lut);
    for (i=0;i<NES_APU_BUF_NUM;i++) {
        myfree(SRAMEX,nesapusbuf[i]);//�ͷ�APU BUFs
        nesapusbuf[i] = 0;
    }
}

//ΪSMS���������ڴ�
//����ֵ:0,����ɹ�
//      1,����ʧ��
u8 sms_sram_malloc(u32 romsize)
{
    u8 i;
	E_RAM=mymalloc(SRAMEX,0X8000);				//����2*16K�ֽ�
	cache=mymalloc(SRAMEX,0x20000);				//128K
	sms_rom=mymalloc(SRAMEX,romsize);			//����romsize�ֽڵ��ڴ�����	
	if (sms_rom==NULL) {
//		spb_delete();//�ͷ�SPBռ�õ��ڴ�
		sms_rom=mymalloc(SRAMEX,romsize);		//��������
	}	
	
	S_RAM=mymalloc(SRAMEX,0X4000);				//����16K�ֽ�
 	SMS_VDP=mymalloc(SRAMEX,sizeof(SVDP));		
	psg_buffer=mymalloc(SRAMEX,SNBUF_size*2);	//�����ڴ�SNBUF_size
	SN76496=mymalloc(SRAMEX,sizeof(t_SN76496));//�����ڴ�184
	Z80A=mymalloc(SRAMEX,sizeof(SMS_CPU80));		//�����ڴ� 
	VRam=mymalloc(SRAMEX,0x4000); 				//����16K�ֽ�
	
	smsi2sbuf1=mymalloc(SRAMEX,SNBUF_size*4+10);
	smsi2sbuf2=mymalloc(SRAMEX,SNBUF_size*4+10);  
	lut=mymalloc(SRAMEX,0x10000); 				//64K
    for (i=0;i<NES_APU_BUF_NUM;i++) {
		nesapusbuf[i]=mymalloc(SRAMEX,APU_PCMBUF_SIZE+10);//�����ڴ�
	}
	if(sms_rom&&cache&&VRam&&lut)
	{ 
		memset(E_RAM,0,0X8000);					//����
		memset(cache,0,0x20000);				//����
		memset(S_RAM,0,0X4000);					//����
		memset(SMS_VDP,0,sizeof(SVDP));			//����
		
		memset(psg_buffer,0,SNBUF_size*2);		//����
		memset(SN76496,0,sizeof(t_SN76496));	//����
		memset(Z80A,0,sizeof(SMS_CPU80));			//���� 
		memset(VRam,0,0X4000);					//����
		
		memset(smsi2sbuf1,0,SNBUF_size*4+10);	//����
		memset(smsi2sbuf2,0,SNBUF_size*4+10);	//����
		memset(lut,0,0x10000);					//����
        for (i=0;i<NES_APU_BUF_NUM;i++) {
            memset(nesapusbuf[i],0,APU_PCMBUF_SIZE+10);//����
        }
		return 0;
	} else {
		sms_sram_free();						//�ͷ������ڴ�.
		return 1;
	}
} 

u8 sms_xoff=0;	//��ʾ��x�᷽���ƫ����(ʵ����ʾ���=256-2*sms_xoff)
//������Ϸ��ʾ����
void sms_set_window(void)
{	
	u16 xoff=0,yoff=0; 
	u16 lcdwidth,lcdheight;
	if(lcddev.width==240)
	{
		lcdwidth=240;
		lcdheight=192;
		sms_xoff=(256-lcddev.width)/2;	//�õ�x�᷽���ƫ����
 		xoff=0; 
	}else if(lcddev.width==320) 
	{
		lcdwidth=256;
		lcdheight=192; 
		sms_xoff=0;
		xoff=(lcddev.width-256)/2;
	}else if(lcddev.width==480)
	{
		lcdwidth=480;
		lcdheight=192*2; 
		sms_xoff=(256-(lcddev.width/2))/2;//�õ�x�᷽���ƫ����
 		xoff=0;  
	}	
	yoff=(lcddev.height-lcdheight)/2;//��Ļ�߶� 
	LCD_Set_Window(xoff,yoff,lcdwidth,lcdheight);//��NESʼ������Ļ����������ʾ
	LCD_SetCursor(xoff,yoff);
	LCD_WriteRAM_Prepare();//д��LCD RAM��׼��  
}

extern u8 framecnt; 

//ģ�������������ֳ�ʼ��,Ȼ��ѭ������ģ����
void sms_start(u8 bank_mun)
{
	u8 zhen;
	u8 res=0;  
	res=VDP_init(); 	
    res+=SMS_CPU_Init(S_RAM, E_RAM,SMS_romfile,bank_mun);//0x8080000,0x0f,"Sonic the Hedgehog '91"
    res+=sms_audio_init(); 
	if (res==0) {
//		TIM3_Int_Init(10000-1,8400-1);//����TIM3 ,1s�ж�һ��
        TIM7_Int_Init(10000-1,7200-1);    
        EXTIX_Init();//tengʹ���ж����˳���Ϸ 
        JOYPAD_Init();
        Audiosel_Set(AUDIO_MP3);        
		sms_set_window();			//���ô���
        nesruning=1;
		while (nesruning) {				
			SMS_frame(zhen);		//+FB_OFS  (24+240*32)	
			nes_get_gamepadval();	//����NES���ֱ����ݻ�ȡ����
			sms_update_Sound();
			sms_update_pad();		//��ȡ�ֱ�ֵ
			zhen++;
			framecnt++; 
			if(zhen>2)zhen=0; 		//��2֡
		}
//		TIM3->CR1&=~(1<<0);//�رն�ʱ��3
        TIM_Cmd(TIM7,DISABLE); //�رն�ʱ��7
        EXTI->IMR &= ~(EXTI_Line2);// �ر��жϰ�
//        Audiosel_Set(AUDIO_NONE);
		LCD_Set_Window(0,0,lcddev.width,lcddev.height);//�ָ���Ļ����
	}
	sms_sound_close();//�ر���Ƶ���
} 

//�����ֱ�����
//SMS��ֵ 1111 1111 ȫ1��ʾû����
//	     D7  D6  D5   D4   D3  D2  D1  D0
//SMS    B   A   ��   ��   ��  ��  
// FC    ��  ��  ��   ��   ST   S   B   A	
void sms_update_pad(void) 
{
	u8 key,key1;
//	key=255-fcpad.ctrlval;	//��FC�ֱ���ֵȡ��
    key=255-JOYPAD_Read();
	key1=(key>>4)|0xf0; 	//ת��ΪSMS�ֱ���ֵ
	key1&=((key<<4)|0xcf); 
    SetController(key1); 
}
//����SMS��Ϸ
//pname:sms��Ϸ·��
//����ֵ:
//0,�����˳�
//1,�ڴ����
//2,�ļ����� 
u8 sms_load(u8* pname)
{
	u8 bank_mun;//16K bank������
	u8 res=0;  
	FIL* f_sms; 
//	if(audiodev.status&(1<<7))		//��ǰ�ڷŸ�??
//	{
//		audio_stop_req(&audiodev);	//ֹͣ��Ƶ����
//		audio_task_delete();		//ɾ�����ֲ�������.
//	}  
 	f_sms=(FIL *)mymalloc(SRAMEX,sizeof(FIL));		//����FIL�ֽڵ��ڴ����� 
	if (f_sms==NULL) {
        return 1;//����ʧ��
    }
 	res=f_open(f_sms,(const TCHAR*)pname,FA_READ);	//���ļ�
   	if (res==0) {
        res=sms_sram_malloc(f_sms->fsize);	//�����ڴ�
        if (res==1) {
            myfree(SRAMEX,f_sms);
            return 1;
        }
    }
	if (res==0) {		 
		if((f_sms->fsize/512)&1) {					//�չ�ͼ�����,�������
			SMS_romfile=sms_rom+512;
			bank_mun=((f_sms->fsize-512)/0x4000)-1;	//16K bank������
		} else {
			SMS_romfile=sms_rom;
            bank_mun=(f_sms->fsize/0x4000)-1;		//16K bank������
		}		   
		res=f_read(f_sms,sms_rom,f_sms->fsize,&br);	//��ȡ����SMS��Ϸ�ļ� 
		if (res) {
            res=2;								//�ļ�����
        }
		f_close(f_sms);   							//�ر��ļ�
	}
	myfree(SRAMEX,f_sms);						 	//�ͷ��ڴ�	
 	if (res==0) {
        sms_start(bank_mun);						//��ʼ��Ϸ
	} 	
	sms_sram_free(); 
	return res;
} 
 

//vu8 smstransferend=0;	//i2s������ɱ�־
//vu8 smswitchbuf=0;		//i2sbufxָʾ��־
//nes,��Ƶ���֧�ֲ���
extern vu16 nesbufpos;
extern vu8 nesplaybuf;		//�������ŵ���Ƶ֡������
extern vu8 nessavebuf;		//��ǰ���浽����Ƶ������
//I2S��Ƶ���Żص�����
void sms_i2s_dma_tx_callback(void)
{ 
    u8 n;
	u8 nbytes;
	u8 *p; 
	if(nesplaybuf==nessavebuf)return;//��û���յ��µ���Ƶ����
	if(VS_DQ!=0)//���Է������ݸ�VS10XX
	{		 
		p=nesapusbuf[nesplaybuf]+nesbufpos; 
		nesbufpos+=32; 
		if(nesbufpos>APU_PCMBUF_SIZE)
		{
			nesplaybuf++;
			if(nesplaybuf>(NES_APU_BUF_NUM-1))nesplaybuf=0; 	
			nbytes=APU_PCMBUF_SIZE+32-nesbufpos;
			nesbufpos=0; 
		}else nbytes=32;
		for(n=0;n<nbytes;n++)
		{
			if(p[n]!=0)break;	//�ж��ǲ���ʣ�����е����ݶ�Ϊ0? 
		}
		if(n==nbytes)return;	//����0,��ֱ�Ӳ�д��VS1053��,��������������. 
		VS_XDCS=0;  
		for(n=0;n<nbytes;n++)
		{
			SPI1_ReadWriteByte(p[n]);	 			
		}
		VS_XDCS=1;     				   
	} 
}
const u8 sms_wav_head[]=
{
    0X52,0X49,0X46,0X46,0XFF,0XFF,0XFF,0XFF,0X57,0X41,0X56,0X45,0X66,0X6D,0X74,0X20,
    0X10,0X00,0X00,0X00,0X01,0X00,0X01,0X00,0X11,0X2B,0X00,0X00,0X11,0X2B,0X00,0X00,
    0X01,0X00,0X08,0X00,0X64,0X61,0X74,0X61,0XFF,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X00,
    0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};
//SMS����Ƶ���
int sms_sound_open(int sample_rate) 
{
	u8 *p;
	u8 i; 
	p=mymalloc(SRAMIN,100);	//����100�ֽ��ڴ�
	if(p==NULL)return 1;	//�ڴ�����ʧ��,ֱ���˳�
	printf("sound open:%d\r\n",sample_rate);
	for(i=0;i<sizeof(sms_wav_head);i++)//����nes_wav_head����
	{
		p[i]=sms_wav_head[i];
	}
	if(lcddev.width==480)	//��480*480��Ļ
	{
		sample_rate=8000;	//����8Khz,Լԭ���ٶȵ�0.75��
	}
	p[24]=sample_rate&0XFF;			//���ò�����
	p[25]=(sample_rate>>8)&0XFF;
	p[28]=sample_rate&0XFF;			//�����ֽ�����(8λģʽ,���ڲ�����)
	p[29]=(sample_rate>>8)&0XFF; 
	nesplaybuf=0;
	nessavebuf=0;	
	VS_HD_Reset();		   			//Ӳ��λ
	VS_Soft_Reset();  				//��λ 
	VS_Set_All();					//���������Ȳ��� 			 
	VS_Reset_DecodeTime();			//��λ����ʱ�� 	  	 
	while(VS_Send_MusicData(p));	//����wav head
	while(VS_Send_MusicData(p+32));	//����wav head
	TIM6_Int_Init(100-1,720-1);	//1ms�ж�һ��
	myfree(SRAMIN,p);				//�ͷ��ڴ�
	return 1;    
}
//SMS�ر���Ƶ���
void sms_sound_close(void) 
{ 
    TIM6->CR1&=~(1<<0);				//�رն�ʱ��6
	VS_SPK_Set(0);					//�ر�������� 
	VS_Set_Vol(0);					//��������Ϊ0 
} 
//SMS��Ƶ�����I2S����
void sms_apu_fill_buffer(int samples,u16* wavebuf)
{	
 	u16	i;	
	u8 tbuf;
	for(i=0;i<APU_PCMBUF_SIZE;i++)
	{
		nesapusbuf[nessavebuf][i]=wavebuf[i]; 
	}
	tbuf=nessavebuf;
	tbuf++;
	if(tbuf>(NES_APU_BUF_NUM-1))tbuf=0;
	while(tbuf==nesplaybuf)//������ݸ�����Ƶ���ŵ�λ����,�ȴ�.
	{ 
		delay_ms(5);
	}
	nessavebuf=tbuf; 
} 







