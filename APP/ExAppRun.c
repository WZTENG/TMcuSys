#include "ExAppRun.h"
#include "DIALOG.h"
#include "EmWinHZFont.h"//teng
#include "ff.h"
#include "malloc.h"
#include "sram.h"

//�ٺ���,��PCָ���ܵ��µ�main����ȥ
dummyfun jump2app;		
//�����ŵ�ַ
extern u8 mem2base[MEM2_MAX_SIZE];	

  
//д���־ֵ
//val:��־ֵ
void exeplay_write_appmask(u16 val)
{
  	RCC->APB1ENR|=1<<28;  	//ʹ�ܵ�Դʱ��	    
	RCC->APB1ENR|=1<<27; 	//ʹ�ܱ���ʱ��	    
	PWR->CR|=1<<8;      	//ȡ��������д���� 
	BKP->DR2=val;			//���Ҫִ���ⲿ����
}
//���������ʼ��ʱ�򱻵���.
//����Ƿ���app������Ҫִ��.�����,��ֱ��ִ��.
void exeplay_app_check(void)
{
	if(BKP->DR2==0X5050) { //���DR2,���Ϊ0X5050,��˵����Ҫִ��app����
		exeplay_write_appmask(0X0000);	//д��0,��ֹ��λ���ٴ�ִ��app����.
		FSMC_SRAM_Init();				//��ʼ��SRAM,��Ϊ��Ҫ���ⲿsram�������ݵ��ڲ�sram
		mymemcpy((u8*)EXEPLAY_APP_BASE,(u8*)EXEPLAY_SRC_BASE,EXEPLAY_APP_SIZE);//����EXEPLAY_APP_SIZE�ֽ� 
		jump2app=(dummyfun)*(vu32*)(EXEPLAY_APP_BASE+4);	//�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)		
		MSR_MSP(*(vu32*)EXEPLAY_APP_BASE);			 		//��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ�Ŷ�ջ��ַ)
		jump2app();	  										//ִ��app����.
	}
}  
//������   
u8 exe_play(u8 *path)
{
  	FIL* f_exe;		 
	DIR exeplaydir;		//exeplaydirר��	  
	FILINFO exeplayinfo;	 	   
	u8 res;
	u8 rval=0;			//����ֵ	  
	u8 *pname=0;
	u8 *fn;

	//Ϊ���ļ������뻺����
 	exeplayinfo.lfsize = _MAX_LFN * 2 + 1;
    exeplayinfo.lfname = mymalloc(SRAMIN, exeplayinfo.lfsize);
	if(exeplayinfo.lfname==NULL) {
        rval=1;//�����ڴ�ʧ��
    } else {
        mymemset((u8*)exeplayinfo.lfname,0,exeplayinfo.lfsize);
    }
	f_exe=(FIL *)mymalloc(SRAMIN, sizeof(FIL));	//����FIL�ֽڵ��ڴ����� 
	if(f_exe==NULL) {
        rval=1;//����ʧ��
    }
	
   	while(rval==0) {
        fn=(u8*)(*exeplayinfo.lfname?exeplayinfo.lfname:exeplayinfo.fname);
        pname=mymalloc(SRAMIN, strlen((const char*)fn)+strlen((const char*)path)+2);//�����ڴ�
        if(pname==NULL) {
            rval=1;//����ʧ��
        } else {//by wzteng
            pname = path;
            rval=f_open(f_exe,(const TCHAR*)pname,FA_READ);	//ֻ����ʽ���ļ�
            if(rval) {
//                    MESSAGEBOX_Create_User_Modal("2", "��ʾ");
                break;	//��ʧ��
            }                    
            if(f_exe->fsize<MEM2_MAX_SIZE) {//���Էŵ���,�����û�ȷ��ִ��
                UINT br;
                mymemset(mem2base,0,f_exe->fsize);	//�����Ƭ�ڴ�
                rval=f_read(f_exe,mem2base,f_exe->fsize,(UINT*)&br);//����BIN����������       
                if(rval) {
//                        MESSAGEBOX_Create_User_Modal("3", "��ʾ");
                    break;//��ʧ��,ֱ���˳� 
                }                        
                if(((*(vu32*)(mem2base+4))&0xFF000000)==0x20000000) { //�ж��Ƿ�Ϊ0X20XXXXXX.���APP�ĺϷ��ԡ�
                    exeplay_write_appmask(0X5050);	//д���־��,��־��app��Ҫ����
                    Sys_Soft_Reset();				//����һ����λ
                } else { //�Ƿ�APP�ļ� 
//                    MESSAGEBOX_Create_User_Modal("��֤ʧ��", "��ʾ");
                    rval = 255;
                    break;
                }
            } 
        } 
//        myfree(SRAMIN, pname);	//�ͷ��ڴ�		  
	}	
 	myfree(SRAMIN, pname);			//�ͷ��ڴ�		  
 	myfree(SRAMIN, exeplayinfo.lfname);
	myfree(SRAMIN, f_exe);					   
	return rval;   
}
