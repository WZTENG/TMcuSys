#include "led.h"
#include "beep.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "ILI93xx.h"
#include "usart.h"	 
#include "24cxx.h"
#include "touch.h"
#include "sram.h"
#include "timer.h"
#include "rtc.h"//teng
#include "sdio_sdcard.h"
#include "mmc_sd.h"//teng
#include "spi.h"
#include "malloc.h"
#include "GUI.h"
#include "ff.h"
#include "exfuns.h"
#include "w25qxx.h"
#include "fontupd.h"
#include "textfont.h"//teng
#include "EmWinHZFont.h"
#include "pngdisplay.h"
#include "gifdisplay.h"
#include "bmpdisplay.h"
#include "jpegdisplay.h"
#include "includes.h"
#include "WM.h"
#include "DIALOG.h"
#include "GUIDemo.h"//teng
#include "app.h"//teng
#include "ExAppRun.h"
#include "common.h"
#include "tpad.h"
#include "adxl345.h"
#include "rda5820.h"
#include "vs10xx.h"
#include "audiosel.h"
#include "dht11.h"
#include "remote.h"
#include "24l01.h"
#include "MusicDLG.h"
#include "mp3player.h"
/************************************************

************************************************/

//START����
//������������ȼ�
#define START_TASK_PRIO				03
//�����ջ��С 
#define START_STK_SIZE			    128
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ	
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void StartTask(void *p_arg);


//�����������ȼ�
#define GUI_TASK_PRIO			15
//�����ջ��С
#define GUI_STK_SIZE			1280
//������ƿ�
OS_TCB GUITaskTCB;
//�����ջ
CPU_STK GUI_TASK_STK[GUI_STK_SIZE];
//task����
void GUITask(void *p_arg);


//LED����
//�����������ȼ�
#define LED_TASK_PRIO 				25
//�����ջ��С
#define LED_STK_SIZE				64
//������ƿ�
OS_TCB LedTaskTCB;
//�����ջ
CPU_STK LED_TASK_STK[LED_STK_SIZE];
//led����
void LedTask(void *p_arg);


//�����������ȼ�
#define GUIKEYPAD_TASK_PRIO			26
//�����ջ��С
#define GUIKEYPAD_STK_SIZE			256
//������ƿ�
OS_TCB GUIKEYPADTaskTCB;
//�����ջ
CPU_STK GUIKEYPAD_TASK_STK[GUIKEYPAD_STK_SIZE];
//task����
void GUIKEYPADTask(void *p_arg);


//�����������ȼ�
#define PRTSC_TASK_PRIO			27
//�����ջ��С
#define PRTSC_STK_SIZE			192
//������ƿ�
OS_TCB PRTSCTaskTCB;
//�����ջ
CPU_STK PRTSC_TASK_STK[PRTSC_STK_SIZE];
//task����
void PRTSCTask(void *p_arg);


//�����������ȼ�
#define MUSIC_TASK_PRIO			13
//�����ջ��С
#define MUSIC_STK_SIZE			128
//������ƿ�
OS_TCB MUSICTaskTCB;
//�����ջ
CPU_STK MUSIC_TASK_STK[MUSIC_STK_SIZE];
//task����
void MUSICTask(void *p_arg);



//�ⲿ�ڴ����(���֧��1M�ֽ��ڴ����)
//����ֵ:0,�ɹ�;1,ʧ��.
u8 system_exsram_test(u16 x,u16 y)
{  
	u32 i=0;  	  
	u16 temp=0;	   
	u16 sval=0;	//�ڵ�ַ0����������	  				   
  	LCD_ShowString(x,y,239,y+12,12,(void *)"Ex Memory:   0KB", 1, POINT_COLOR); 
	//ÿ��1K�ֽ�,д��һ������,�ܹ�д��1024������,�պ���1M�ֽ�
	for(i=0;i<1024*128;i+=8192)
	{
		FSMC_SRAM_WriteBuffer((u8*)&temp,i,2);
		temp++;
	}
	//���ζ���֮ǰд�������,����У��
 	for(i=0;i<1024*128;i+=8192) 
	{
  		FSMC_SRAM_ReadBuffer((u8*)&temp,i,2);
		if(i==0)sval=temp;
 		else if(temp<=sval)break;//�������������һ��Ҫ�ȵ�һ�ζ��������ݴ�.        
		LCD_ShowxNum(x+10*6,y,(u16)(temp-sval+1),4,12,0, GBLUE);//��ʾ�ڴ�����  
 	}
	if(i>=1024*128)
	{
		LCD_ShowxNum(x+10*6,y,i/128,4,12, 0, GBLUE);//��ʾ�ڴ�ֵ  		
		return 0;//�ڴ�����,�ɹ�
	}
	return 1;//ʧ��
}

//��ʾ������Ϣ
//x,y:����.err:������Ϣ
void system_error_show(u16 x,u16 y,u8*err)
{
 	while(1) {
		LCD_ShowString(x,y,240,320,12,err, 0, RED);
		delay_ms(400);
		LCD_Fill(x,y,240,y+18,BACK_COLOR);
		delay_ms(100);
		LED0=!LED0;
	} 
}	

u8 DHT11_CHECK_OK = 0;
int main(void)
{	
	OS_ERR err;
	CPU_SR_ALLOC();
    
    u16 ypos=0;
	u8 *version=0; 
	u8 verbuf[12];
    u8 j=0;
    const u8 okoffset=216-12+3;//186
    u16 temp=0;
    u32 dtsize=0,dfsize=0;
    u8 res=0;
    u8 *stastr=0;
    
    Stm32_Clock_Init(9);		//����ʱ��,72Mhz 
	delay_init(72);	    	//��ʱ������ʼ��
    
    exeplay_app_check();	//==========����Ƿ���Ҫ����APP����

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			    //LED�˿ڳ�ʼ��
	TFTLCD_Init();			//LCD��ʼ��
    LCD_PWM_Init(15);
	TP_Init();				//��������ʼ��
	KEY_Init();	 			//������ʼ��
	BEEP_Init();			//��ʼ��������
    DHT11_CHECK_OK = !DHT11_Init();
    Remote_Init();          //��ʹ����TIM4
    Audiosel_Init();        //��Ƶ���ѡ��
    Audiosel_Set(AUDIO_NONE);
	TIM3_Int_Init(999, 71);	//1KHZ ��ʱ��1ms      teng
	FSMC_SRAM_Init();		//��ʼ��SRAM
	my_mem_init(SRAMIN); 	//��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);  	//��ʼ���ⲿ�ڴ��
    
    // ��ʾ������Ϣ
//    LCD_Clear(BLUE);
    ypos=2;
	app_show_mono_icos(11,ypos,56,24,(u8*)APP_WZTENG_ICO,YELLOW,BLACK);
    POINT_COLOR=WHITE;
	BACK_COLOR=BLACK;
    LCD_ShowString(72,ypos+12*j++,240,320,12, (void *)">> WZTENG << STM32F103ZET6", 1, YELLOW);
	LCD_ShowString(72,ypos+12*j++,240,320,12, (void *)"TMcuSystem welcome for you", 1, YELLOW);
    app_get_version(verbuf,HARDWARE_VERSION,2);
    version=mymalloc(SRAMIN,31);//����31���ֽ��ڴ�
	strcpy((char*)version,"HARDWARE:");
	strcat((char*)version,(const char*)verbuf);
	strcat((char*)version,"  SOFTWARE:");
	app_get_version(verbuf,SOFTWARE_VERSION,3);
	strcat((char*)version,(const char*)verbuf);
	LCD_ShowString(5,ypos+12*j++,240,320,12,version, 1, POINT_COLOR);
    myfree(SRAMIN, version);
    LCD_ShowString(5,ypos+12*j++,240,320,12, (void *)"MCU:STM32F103ZET6 72MHz", 1, POINT_COLOR);
	LCD_ShowString(5,ypos+12*j++,240,320,12, (void *)"FLASH:512KB  SRAM:64KB", 1, POINT_COLOR);
    sprintf((char*)verbuf,"uCOS %d.%02d.%02d",OS_VERSION/10000, (OS_VERSION/100)%100, OS_VERSION%100);
    LCD_ShowString(5+6*24+15,ypos+12*(j-2),240,320,12, verbuf, 1, POINT_COLOR);
    sprintf((char*)verbuf,"emWin %d.%02d.%02d",GUI_VERSION/10000, (GUI_VERSION/100)%100, GUI_VERSION%100);
    LCD_ShowString(5+6*24+9,ypos+12*(j-1),240,320,12, verbuf, 1, POINT_COLOR);
    if (lcddev.id==0x9341) {   //9341    37697
		sprintf((char*)verbuf,"LCD ID:ILI%04X",lcddev.id);
	} else {
		sprintf((char*)verbuf,"LCD ID:%04X",lcddev.id);		//LCD ID��ӡ��verbuf����
	}
	LCD_ShowString(5,ypos+12*j,240,320,12, verbuf, 1, POINT_COLOR);	//��ʾLCD ID
    // ������ʽ
    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET) {//�����ϵ縴λ
        LCD_ShowString(200,ypos+12*j++,240,320,12, (u8 *)"PORRST", 1, POINT_COLOR);
    } else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET) {//�����ⲿRST�ܽŸ�λ
        LCD_ShowString(200,ypos+12*j++,240,320,12, (u8 *)"PINRST", 1, POINT_COLOR);
    } else if (RCC_GetFlagStatus(RCC_FLAG_SFTRST)!= RESET) {//���������λ
        LCD_ShowString(200,ypos+12*j++,240,320,12, (u8 *)"SFTRST", 1, RED);
    } else if (RCC_GetFlagStatus(RCC_FLAG_LPWRRST)!= RESET) {//���ǵ͵�����λ
        LCD_ShowString(194,ypos+12*j++,240,320,12, (u8 *)"LPWRRST", 1, YELLOW);
    }        
    RCC_ClearFlag();//���RCC�и�λ��־
    
    // ��һ��
    j++;
    if(system_exsram_test(5,ypos+12*j)) {
        system_error_show(5,ypos+12*j++,(void *)"EX Memory Error!");
    }
	LCD_ShowString(5+okoffset,ypos+12*j++,240,320,12,(void *)"PASS", 1, POINT_COLOR);			   
	my_mem_init(SRAMEX);	//�ⲿ�ڴ�صĳ�ʼ������ŵ��ڴ���֮�󣡣�
    
    W25QXX_Init();	//W25Qxx��ʼ��
    res = W25QXX_ReadID();
	switch(res) {	
		case 0x13: temp=1*1024; break;
		case 0x14: temp=2*1024; break;
		case 0x15: temp=4*1024; break;
		case 0x16: temp=8*1024; break;
		default: system_error_show(5,ypos+12*j++,(void *)"Ex Flash Error!");
			break;
	}
	LCD_ShowString(5,ypos+12*j,240,320,12, (void *)"Ex Flash:    KB", 1, POINT_COLOR);			   
	LCD_ShowxNum(5+9*6,ypos+12*j,temp,4,12,0, GBLUE);//��ʾflash��С  
	LCD_ShowString(5+okoffset,ypos+12*j++,240,320,12, (void *)"PASS", 1, POINT_COLOR);
    //SD Card
    LCD_ShowString(5,ypos+12*j,240,320,12, (void *)"SD Card Check...", 1, POINT_COLOR);
#if SD_MODE == 0
    res = SD_Init();	//��ʼ��SD��SDIO
#else
    res = SD_Initialize();  //��ʼ��SD��SPI
#endif
    if (res == 0) {
        LCD_ShowString(5+okoffset,ypos+12*j++,240,320,12, (void *)"PASS", 1, POINT_COLOR);
    } else {
        system_error_show(5,ypos+12*(j+1),(void *)"SD Card Init Error!");
    }
    
    // FATFS
    LCD_ShowString(5,ypos+12*j,240,320,12, (void *)"FATFS Check...", 1, POINT_COLOR);//FATFS���			   
	if(exfuns_init()) {
        system_error_show(5,ypos+12*(j+1),(void *)"FATFS Memory Error!");//�ڴ����
    }
	f_mount(fs[0],"0:",1);	//����SD��
	f_mount(fs[1],"1:",1);	//����FLASH
	LCD_ShowString(5+okoffset,ypos+12*j++,240,320,12, (void *)"PASS", 1, POINT_COLOR);
    //SD����С���
    LCD_ShowString(5,ypos+12*j,240,320,12, (void *)"SD Card:     MB", 1, POINT_COLOR);
    if (res == 0) {
        temp=0;	
        do {
            temp++;
            res=exf_getfree((void *)"0:",&dtsize,&dfsize);//�õ�SD��ʣ��������������
            delay_ms(200);		   
        } while (res&&temp<2);//�������2��
        if (res==0) { //�õ���������
            temp=dtsize>>10;//��λת��ΪMB
            stastr=(void *)"PASS";
        } else {
            temp=0;//������,��λΪ0
            stastr=(void *)"ERROR";
            system_error_show(5,ypos+12*(j+1),(void *)"SD Card Status Error!");
        }
        LCD_ShowxNum(5+8*6,ypos+12*j,temp,5,12,0, GBLUE);				//��ʾSD��������С
        LCD_ShowString(5+okoffset,ypos+12*j++,240,320,12,stastr, 1, POINT_COLOR);	//SD��״̬
    } else {
        temp = 0;
        stastr=(void *)"ERROR";
        system_error_show(5,ypos+12*(j+1),(void *)"SD Card Init Error!");
//        LCD_ShowxNum(5+8*6,ypos+12*j,temp,5,12,0, POINT_COLOR);				//��ʾSD��������С
//        LCD_ShowString(5+okoffset,ypos+12*j++,240,320,12,stastr, 1, POINT_COLOR);	//SD��״̬
    }
    //W25Q64���,����������ļ�ϵͳ,���ȴ���.
	temp=0;	
 	do {
		temp++;
 		res=exf_getfree((void *)"1:",&dtsize,&dfsize);//�õ�FLASHʣ��������������
		delay_ms(200);		   
	} while (res&&temp<2);//��Ϊ2��,�������20��		  
	if (res==0X0D) { //�ļ�ϵͳ������
		LCD_ShowString(5,ypos+12*j,240,320,12, (void *)"Flash Disk Formatting...", 1, POINT_COLOR);	//��ʽ��FLASH
		res=f_mkfs((void *)"1:",1,4096);//��ʽ��FLASH,1,�̷�;1,����Ҫ������,8������Ϊ1����
		if(res==0) {
			LCD_ShowString(5+okoffset,ypos+12*j++,240,320,12, (void *)"PASS", 1, POINT_COLOR);//��־��ʽ���ɹ�
 			res=exf_getfree((void *)"1:",&dtsize,&dfsize);//���»�ȡ����
		}
	}   
	if (res==0) { //�õ�FLASH��ʣ��������������
		LCD_ShowString(5,ypos+12*j,240,320,12, (void *)"Flash Disk:    KB", 1, POINT_COLOR);//FATFS���			   
		temp=dtsize; 	   
 	} else {
        system_error_show(5,ypos+12*(j+1),(void *)"Flash Fat Error!");	//flash �ļ�ϵͳ����
    }        
 	LCD_ShowxNum(5+11*6,ypos+12*j,temp,4,12, 0, GBLUE);						//��ʾ������С
	LCD_ShowString(5+okoffset,ypos+12*j++,240,320,12,(void *)"PASS", 1, POINT_COLOR);			//״̬
    //TPAD���		 
 	LCD_ShowString(5,ypos+12*j,240,320,12, (void *)"TPAD Check...", 1, POINT_COLOR);			   
 	if (TPAD_Init(36)) {
        system_error_show(5,ypos+12*(j+1),(void *)"TPAD Error!");//�����������
    } else {
        LCD_ShowString(5+okoffset,ypos+12*j++,240,320,12, (void *)"PASS", 1, POINT_COLOR);
    }
    //RTC���
  	LCD_ShowString(5,ypos+12*j,240,320,12, (void *)"RTC Check...", 1, POINT_COLOR);			   
 	if (RTC_Init()) {
        system_error_show(5,ypos+12*(j+1),(void *)"RTC Error!");//RTC���
    } else {
        LCD_ShowString(5+okoffset,ypos+12*j++,240,320,12, (void *)"PASS", 1, POINT_COLOR);
    }
    //ADXL345���
	LCD_ShowString(5,ypos+12*j,240,320,12, (void *)"ADXL345 Check...", 1, POINT_COLOR);			   
 	if (ADXL345_Init()) {
        system_error_show(5,ypos+12*(j+1),(void *)"ADXL345 Error!");//ADXL345���
    } else {
        LCD_ShowString(5+okoffset,ypos+12*j++,240,320,12, (void *)"PASS", 1, POINT_COLOR);
    }
    //AT24C02���
   	LCD_ShowString(5,ypos+12*j,240,320,12, (void *)"AT24C02 Check...", 1, POINT_COLOR);			   
 	if (AT24CXX_Check()) {
        system_error_show(5,ypos+12*(j+1),(void *)"AT24C02 Error!");//AT24C02���
    } else {
        LCD_ShowString(5+okoffset,ypos+12*j++,240,320,12, (void *)"PASS", 1, POINT_COLOR);
    }
    //RDA5820���			   
 	LCD_ShowString(5,ypos+12*j,240,320,12, (void *)"RDA5820 Check...", 1, POINT_COLOR);			   
 	if (RDA5820_Init()) {
        system_error_show(5,ypos+12*(j+1), (void *)"RDA5820 Error!");//RDA5820���
    } else {
        LCD_ShowString(5+okoffset,ypos+12*j++,240,320,12, (void *)"PASS", 1, POINT_COLOR);
    }
    //VS1053���
 	LCD_ShowString(5,ypos+12*j,240,320,12, (void *)"VS1053 Check...", 1, POINT_COLOR);			   
	VS_Init();		//��ʼ��VS1053�ӿ�
	VS_Sine_Test();	//���Ҳ���
	BEEP=0;		   
	if (VS_Ram_Test()!=0X83FF) {
        system_error_show(5,ypos+12*(j+1),(void *)"VS1053 Error!");//RAM����
    } else {
        LCD_ShowString(5+okoffset,ypos+12*j++,240,320,12, (void *)"PASS", 1, POINT_COLOR);
    }
    //�ֿ���									    
   	LCD_ShowString(5,ypos+12*j,240,320,12, (void *)"Font Check...", 1, POINT_COLOR);
	res=KEY_Scan(1);//��ⰴ��			   
  	while(font_init()||res==KEY_DOWN) {	//�������,������岻����/����KEY1,������ֿ�
		res=0;//������Ч
 		if(update_font(5,ypos+12*j,12,0)!=0) { //��SD������
 			if(update_font(5,ypos+12*j,12,1)!=0) {//��FLASH����
                system_error_show(5,ypos+12*(j+1), (void *)"Font Error!");	//�������
            }
		}	 
		LCD_Fill(5,ypos+12*j,240,ypos+12*(j+1),BLACK);//����ɫ
    	LCD_ShowString(5,ypos+12*j,240,320,12, (void *)"Font Check...", 1, POINT_COLOR);			   
 	} 
	LCD_ShowString(5+okoffset,ypos+12*j++,240,320,12, (void *)"PASS", 1, POINT_COLOR);//�ֿ���OK
    //��������� 
	LCD_ShowString(5,ypos+12*j,240,320,12, (void *)"Touch Check...", 1, POINT_COLOR);			   
	res=KEY_Scan(1);//��ⰴ��			   
	if(TP_Init()||res==KEY_RIGHT) { //�и���/������KEY0,ִ��У׼	 	
		if(res==1) {
            TP_Adjust();
        }
		res=0;//������Ч
//		goto REINIT;				//���¿�ʼ��ʼ��
	}
	LCD_ShowString(5+okoffset,ypos+12*j++,240,320,12, (void *)"PASS", 1, POINT_COLOR);//���������OK
//    //Ĭ�Ͽ�����ϵͳ�ļ����
//    LCD_ShowString(5,ypos+12*j,240,320,12, "SYSTEM Files Check...", 1, POINT_COLOR);			   
//    while(app_system_file_check()) { //ϵͳ�ļ����
//        LCD_Fill(5,ypos+12*j,240,ypos+12*(j+1),BLACK);		//����ɫ
//        LCD_ShowString(5,ypos+12*j,6*8,12,12, "Updating", 1, POINT_COLOR); 	//��ʾupdating	
//        app_boot_cpdmsg_set(5,ypos+12*j);//���õ�����
//        if(app_system_update(app_boot_cpdmsg)) { //���³���
//            system_error_show(5,ypos+12*(j+1), "SYSTEM File Error!");
//        }
//        LCD_Fill(5,ypos+12*j,240,ypos+12*(j+1),BLACK);//����ɫ
//        LCD_ShowString(5,ypos+12*j,240,320,12, "SYSTEM Files Check...", 1, POINT_COLOR); 
//        if(app_system_file_check()) { //������һ�Σ��ټ�⣬������в�ȫ��˵��SD���ļ��Ͳ�ȫ��
//            system_error_show(5,ypos+12*(j+1),"SYSTEM File Lost!");
//        } else {
//            break;
//        }            
//    }
//    LCD_ShowString(5+okoffset,ypos+12*j++,240,320,12, "OK", 1, POINT_COLOR);
    // ��������
    dtsize = AT24CXX_ReadLenByte(0, 2);
    AT24CXX_WriteLenByte(0, ++dtsize, 2);
    LCD_ShowxNum(206, 308, dtsize, 5, 12, 0x00, LBBLUE);
    
    LCD_ShowString(5,308,240,320,12, (void *)">> Starting", 1, LBBLUE);
    for (j=0;j<22;j++) {
        LCD_ShowString(5+6*11+j*6,308,240-12*11,320,12, (void *)".", 1, LBBLUE);
        delay_ms(50);
    }
    
	OSInit(&err);		//��ʼ��UCOSIII
	OS_CRITICAL_ENTER();//�����ٽ���
	//������ʼ����
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//������ƿ�
				 (CPU_CHAR	* )"StartTask", 		//��������
                 (OS_TASK_PTR )StartTask, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();	//�˳��ٽ���	 
	OSStart(&err);  //����UCOSIII
	while(1);
}


//��ʼ������
void StartTask(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
	OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//����CRCʱ��
	WM_SetCreateFlags(WM_CF_MEMDEV);
    WM_MOTION_Enable(1);
    WM_MULTIBUF_Enable(1);
	GUI_Init();  			//STemWin��ʼ��

	OS_CRITICAL_ENTER();	//�����ٽ���
	//UI����	
	OSTaskCreate((OS_TCB*     )&GUITaskTCB,		
				 (CPU_CHAR*   )"GUITask", 		
                 (OS_TASK_PTR )GUITask, 			
                 (void*       )0,					
                 (OS_PRIO	  )GUI_TASK_PRIO,     
                 (CPU_STK*    )&GUI_TASK_STK[0],	
                 (CPU_STK_SIZE)GUI_STK_SIZE/10,	
                 (CPU_STK_SIZE)GUI_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
		 
	//LED����
	OSTaskCreate((OS_TCB*     )&LedTaskTCB,		
				 (CPU_CHAR*   )"LedTask", 		
                 (OS_TASK_PTR )LedTask, 			
                 (void*       )0,					
                 (OS_PRIO	  )LED_TASK_PRIO,     
                 (CPU_STK*    )&LED_TASK_STK[0],	
                 (CPU_STK_SIZE)LED_STK_SIZE/10,	
                 (CPU_STK_SIZE)LED_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
                 
	//keypad����
	OSTaskCreate((OS_TCB*     )&GUIKEYPADTaskTCB,		
				 (CPU_CHAR*   )"GUIKEYPADTask", 		
                 (OS_TASK_PTR )GUIKEYPADTask, 			
                 (void*       )0,					
                 (OS_PRIO	  )GUIKEYPAD_TASK_PRIO,     
                 (CPU_STK*    )&GUIKEYPAD_TASK_STK[0],	
                 (CPU_STK_SIZE)GUIKEYPAD_STK_SIZE/10,	
                 (CPU_STK_SIZE)GUIKEYPAD_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
				 
	//PRTSC����
	OSTaskCreate((OS_TCB*     )&PRTSCTaskTCB,		
				 (CPU_CHAR*   )"PRTSCTask", 		
                 (OS_TASK_PTR )PRTSCTask, 			
                 (void*       )0,					
                 (OS_PRIO	  )PRTSC_TASK_PRIO,     
                 (CPU_STK*    )&PRTSC_TASK_STK[0],	
                 (CPU_STK_SIZE)PRTSC_STK_SIZE/10,	
                 (CPU_STK_SIZE)PRTSC_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);

    //MUSIC����
	OSTaskCreate((OS_TCB*     )&MUSICTaskTCB,		
				 (CPU_CHAR*   )"MUSICTask", 		
                 (OS_TASK_PTR )MUSICTask, 			
                 (void*       )0,					
                 (OS_PRIO	  )MUSIC_TASK_PRIO,     
                 (CPU_STK*    )&MUSIC_TASK_STK[0],	
                 (CPU_STK_SIZE)MUSIC_STK_SIZE/10,	
                 (CPU_STK_SIZE)MUSIC_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);                 
				 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//����ʼ����			 
	OS_CRITICAL_EXIT();	//�˳��ٽ���
}

//GUI����
void GUITask(void *p_arg)
{
//	GUI_CURSOR_Show();
//	while(1) {
//		GUIDEMO_Main();   //emWin����
//	}

	while (1) {
		MainAPP();
	}
}

// ���ȼ���ͳ�Ʋ�̫׼ȷ
///////////////////////CPUʹ���ʼ���/////////////////
#define MON_DATA_SIZE 226 // Ҫ�� PerfMonDLG ����һ����������ⶨ��һ����
volatile I16 cpuusage[MON_DATA_SIZE];//CPUʹ����
/////////////////////�ڲ��ڴ�ʹ�ü���///////////
volatile I16 inmemusage[MON_DATA_SIZE];//�ڲ��ڴ�
volatile I16 exmemusage[MON_DATA_SIZE];//��չ�ڴ�
volatile U8 runhour=0,runmin=0,runsec=0;         //����ʱ��

//LED����
void LedTask(void *p_arg)
{
	OS_ERR err;
    int i = 0;
    int count = 0;
    runhour=0;
    runmin=0;
    runsec=0;
    
	while(1) {        
        count++;
//        if ((count%29==0) || (count%30==0)) {
//            LED_RED = !LED_RED;
//        }
        if ((count % 2) == 0) {
            cpuusage[MON_DATA_SIZE-1] = (I16)OSStatTaskCPUUsage/100;//CPU
            for(i=1;i<MON_DATA_SIZE;i++) {
                cpuusage[i-1] = cpuusage[i];
            }
            inmemusage[MON_DATA_SIZE-1] = my_mem_perused(0);//�ڲ��ڴ�
            for(i=1;i<MON_DATA_SIZE;i++) {
                inmemusage[i-1] = inmemusage[i];
            }
            exmemusage[MON_DATA_SIZE-1] = my_mem_perused(1);//��չ�ڴ�
            for(i=1;i<MON_DATA_SIZE;i++) {
                exmemusage[i-1] = exmemusage[i];
            }
            // ����ʱ��
            runsec++;
            if(runsec==60) {
                runsec = 0;
                runmin++;
                if(runmin==60) {
                    runmin = 0;
                    runhour++;
                }
            }
        }
        OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_PERIODIC, &err);//��ʱ500ms
	}
}

extern keyflag;  //teng
static void GUIKEYPADTask(void *p_arg)
{
	OS_ERR   err;
	uint16_t *msg;
	OS_MSG_SIZE	msg_size;
	CPU_TS			ts;
	(void)p_arg;		/* ����������澯 */	
	while (1) {
		msg = OSTaskQPend(0,
						OS_OPT_PEND_BLOCKING,
						&msg_size,
						&ts,
						&err);
		if(err == OS_ERR_NONE) {
			OSSchedLock(&err);    //teng
			//printf("pend size=%d,hedit[0]=%d,hedit[1]=%d\n",msg_size,msg[0],msg[1]);
			keypad(msg);
			keyflag = 1;          //teng
			OSSchedUnlock(&err);  //teng
		}
        OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_PERIODIC, &err);//��ʱ500ms
    }	
}

/*
*********************************************************************************************************
*	�� �� ��: _WriteByte2File()
*	����˵��: 
*	��    �Σ�  	
*	�� �� ֵ: 
*********************************************************************************************************
*/
FIL Prtscfile;
void _WriteByte2File(uint8_t Data, void * p) 
{
	FRESULT result;
	result = f_write(p, &Data, 1, &bw);
}

/*
*********************************************************************************************************
*	�� �� ��: PRTSCTask
*	����˵��: 
*	��    �Σ�p_arg ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
	�� �� ����3
*********************************************************************************************************
*/
static void PRTSCTask(void *p_arg)
{
	OS_ERR err;
	CPU_TS Ts;
	char buf[35];
	FRESULT result;
	(void)p_arg;
//	f_mkdir("0:/PRTSC");
	while(1) {	
		if(KEY_Scan(0) == KEY1_PRES) {
            LED_GREEN = 0;
			sprintf(buf,"0:/PRTSC/PRTSC%02d%02d%02d%02d%02d%02d.bmp",
						calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
			OSSchedLock(&err);
			/* ������ͼ */
			result = f_open(&Prtscfile, buf, FA_WRITE|FA_CREATE_ALWAYS);
			/* ��SD������BMPͼƬ */
			GUI_BMP_Serialize(_WriteByte2File, &Prtscfile);
			
			/* ������ɺ�ر�file */
			result = f_close(&Prtscfile);
			OSSchedUnlock(&err);
            LED_GREEN = 1;
			BEEP=1;
			OSTimeDlyHMSM(0, 0, 0, 120, OS_OPT_TIME_HMSM_STRICT, &err);
			BEEP=0;
		}
		OSTimeDlyHMSM(0, 0, 0, 30, OS_OPT_TIME_HMSM_STRICT, &err);
	}   
}

//����
extern MUSIC_LIST *music;
extern char musicPlaying;
extern char musicChange;
extern int musicIndex;
void MUSICTask(void *p_arg)
{
	OS_ERR err;
    u8 res=0;
    uint16_t *msg;
    OS_MSG_SIZE	msg_size;
	CPU_TS ts;

//    OS_TaskSuspend((OS_TCB*)&MUSICTaskTCB,&err);
    VS_HD_Reset();
    VS_Soft_Reset();
    vsset.mvol=190;	
    VS_Set_Vol(vsset.mvol);
    Audiosel_Set(AUDIO_MP3);
//    mp3_play_song((u8 *)"0:/MUSIC/ǧ���һ��.mp3");
	while(1) {
        if (musicPlaying && music && music->music_path) {
            res = mp3_play_song((u8 *)music->music_path);
            if (musicChange) {
                musicChange = 0;
                musicPlaying = 1;
            }
            if (res == 0 && music && music->nextMusic) {
                music = music->nextMusic;
                musicIndex++;
            } else if (res == 0 && music && (music->nextMusic == 0)) {
                musicPlaying = 0;
            }
        } else {
//            msg = OSTaskQPend(0,
//						OS_OPT_PEND_BLOCKING,
//						&msg_size,
//						&ts,
//						&err);
//            if (err == OS_ERR_NONE) {
//                OSSchedLock(&err);    //teng
//                //printf("pend size=%d,hedit[0]=%d,hedit[1]=%d\n",msg_size,msg[0],msg[1]);
//                OSSchedUnlock(&err);  //teng
//            }
        }
        OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_PERIODIC, &err);
	}
}

//Ӳ��������ʾ
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
    u32 temp;
    int x = 0;
    u8 sbuff[50]={0};
    
//    temp=SCB->CFSR;					//fault״̬�Ĵ���(@0XE000ED28)����:MMSR,BFSR,UFSR
//    printf("CFSR:%8X\r\n",temp);	//��ʾ����ֵ
//    temp=SCB->HFSR;					//Ӳ��fault״̬�Ĵ���
//    printf("HFSR:%8X\r\n",temp);	//��ʾ����ֵ
//    temp=SCB->DFSR;					//����fault״̬�Ĵ���
//    printf("DFSR:%8X\r\n",temp);	//��ʾ����ֵ
//    temp=SCB->AFSR;					//����fault״̬�Ĵ���
//    printf("AFSR:%8X\r\n",temp);	//��ʾ����ֵ
    
    LCD_Clear(BLACK);
    LCD_Fill(0, 0, 240, 16, 0x6000);
    LCD_ShowString(20,16*x++,240,16,16,(void *)"=== HardFault_Handler ===", 1, WHITE);

//    sprintf((char *)sbuff, "SCB->CPUID:%d", SCB->CPUID);
//    LCD_ShowString(2,16*x++,240,16,16,sbuff, 1, WHITE);
    sprintf((char *)sbuff, "SCB->CFSR:%d", SCB->CFSR);
    LCD_ShowString(2,16*x++,240,16,16,sbuff, 1, WHITE);
    sprintf((char *)sbuff, "SCB->HFSR:%d", SCB->HFSR);
    LCD_ShowString(2,16*x++,240,16,16,sbuff, 1, WHITE);
    sprintf((char *)sbuff, "SCB->DFSR:%d", SCB->DFSR);
    LCD_ShowString(2,16*x++,240,16,16,sbuff, 1, WHITE);
    sprintf((char *)sbuff, "SCB->AFSR:%d", SCB->AFSR);
    LCD_ShowString(2,16*x++,240,16,16,sbuff, 1, WHITE);
//    sprintf((char *)sbuff, "SCB->ICSR:%d", SCB->ICSR);
//    LCD_ShowString(2,16*x++,240,16,16,sbuff, 1, WHITE);
//    sprintf((char *)sbuff, "SCB->VTOR:%d", SCB->VTOR);
//    LCD_ShowString(2,16*x++,240,16,16,sbuff, 1, WHITE);
    
    LCD_ShowString(2,320-16,240,16,16,(void *)">> Restart Soon...", 1, YELLOW);
    BACK_COLOR = BLACK;
    
    x = 3;//������ʾʱ��
	while (x>=0) {
		u32 i;
		LED_GREEN=!LED_GREEN;
        LCD_ShowNum(2+8*18, 320-16, x, 1, 16, 0, YELLOW);
        
        LED_RED=!LED_RED;
        for(i=0;i<0x550000;i++);//��Լ0.5s
        LED_RED=!LED_RED;
        for(i=0;i<0x550000;i++);//��Լ0.5s
        x--;
	}
    NVIC_SystemReset();
}




