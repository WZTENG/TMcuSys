#ifndef __COMMON_H
#define __COMMON_H 	
#include "sys.h"
#include "touch.h"	 
#include "includes.h"


//Ӳ��ƽ̨��Ӳ���汾����	   	
#define HARDWARE_VERSION	   		20		//Ӳ���汾,�Ŵ�10��,��1.0��ʾΪ10
#define SOFTWARE_VERSION	    	629		//����汾,�Ŵ�100��,��1.00,��ʾΪ100
//Ӳ��V2.0
//1������TVS��Դ������
//2�������Դ����DCDC��Դ��������������ѹ������
//Ӳ��V2.2
//1��˿ӡλ����΢�仯.
//2��������ά��.
//V2.25  20121027
//����3.5���ֱ���LCD֧��
//V2.26  20131124
//1,���Ӷ�NT35310��������֧��
//2,�������µ�SYSTEM�ļ���,֧��MDK3~MDK4.
//3,ȫ�����V3.5��ͷ�ļ�.
//4,USMART�������µ�V3.1�汾,֧�ֺ���ִ��ʱ��鿴.


//ϵͳ���ݱ����ַ			  
#define SYSTEM_PARA_SAVE_BASE 		100		//ϵͳ��Ϣ�����׵�ַ.��100��ʼ.		    

extern const u8 APP_WZTENG_ICO[168];	//��������ͼ��,�����flash

/////////////////////////////////////////////////////////////////////////																		    
void app_srand(u32 seed);
//��ȡα�����
//���Բ���0~RANDOM_MAX-1�������
//seed:����
//max:���ֵ	  		  
//����ֵ:0~(max-1)�е�һ��ֵ 		
u32 app_get_rand(u32 max);
//m^n����
long long gui_pow(u8 m,u8 n);
//�õ����ֵ�λ��
//num:����
//dir:0,�Ӹ�λ����λ.1,�ӵ�λ����λ.
//����ֵ:���ֵ�λ��.(���Ϊ10λ)
//ע:0,��λ��Ϊ0λ.
u8 app_get_numlen(long long num,u8 dir);
//��ʾ��ɫͼ��
//x,y,width,height:���꼰�ߴ�.
//icosbase:����λ��
//color:�������ɫ.
//bkcolor:����ɫ
void app_show_mono_icos(u16 x,u16 y,u8 width,u8 height,u8 *icosbase,u16 color,u16 bkcolor);			   
//�õ�STM32�����к�
//sn0,sn1,sn2:3���������к�
void app_getstm32_sn(u32 *sn0,u32 *sn1,u32 *sn2);
//��ӡSN
void app_usmart_getsn(void);
//�õ��汾��Ϣ
//buf:�汾������(������Ҫ6���ֽ�,�籣��:V1.00)
//ver:�汾�궨��
//len:�汾λ��.1,����ֻ��1��λ�İ汾,V1;2,����2��λ�汾,V1.0;3,����3��λ�汾,V1.00;
void app_get_version(u8*buf,u32 ver,u8 len);


#endif



