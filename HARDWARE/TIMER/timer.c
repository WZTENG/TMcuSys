#include "timer.h"
#include "led.h"
#include "GUI.h"
#include "usart.h"
#include "vs10xx.h"//teng
#include "ili93xx.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK ս��������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/13
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//����TIM3ʱ�� 

	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;   //��Ƶֵ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;	   //����ģʽ
	TIM_TimeBaseInitStructure.TIM_Period=arr;		   //�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;  //����ʱ�ӷָ�
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//��������ж�

	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM3,ENABLE);		  //ʹ��TIM3
}


__IO int32_t OS_TimeMS;  //teng
//volatile GUI_TIMER_TIME OS_TimeMS;     //teng
static u8 Timesn = 0;
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET) {	
		OS_TimeMS++;
		Timesn++;
		if(Timesn == 10) {
			GUI_TOUCH_Exec();
			Timesn = 0;
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}

//������ʱ��6�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��6!
void TIM6_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE); //��ʱ��6ʱ��ʹ��
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //���÷�Ƶֵ��10khz�ļ���Ƶ��
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_Period=arr;  //�Զ���װ��ֵ ������5000Ϊ500ms
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0; //ʱ�ӷָ�:TDS=Tck_Tim
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM6,TIM_IT_Update|TIM_IT_Trigger,ENABLE); //ʹ��TIM6�ĸ����ж�

	NVIC_InitStructure.NVIC_IRQChannel=TIM6_IRQn; //TIM6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //ʹ��ͨ��
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM6,ENABLE); //��ʱ��6ʹ��
}

//video
u16 frame;
vu8 frameup; 
vu8 framecnt;		//ͳһ��֡������
vu8 framecntout;	//ͳһ��֡�������������

void TIM6_IRQHandler(void)
{
    OSIntEnter();
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)!=RESET)
	{
		nes_vs10xx_feeddata();//������� nes
        frameup=1;//video
        framecntout=framecnt;//sms
 		framecnt=0;//sms
	}
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update); //����жϱ�־λ
    OSIntExit();
}


//nes
vu8 frame_cnt=0;//nes game 1sһ��
//��ʱ��7�жϷ������		    
void TIM7_IRQHandler(void)
{ 	
	if(TIM7->SR&0X01) {	 			   
		frame_cnt = 0;//nes
        
        frame = 0;//video
        framecntout=framecnt;//video test
		framecnt=0;//video test
	}
    TIM7->SR&=~(1<<0);		//����жϱ�־λ
} 
//������ʱ��7�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM7_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);//����TIM3ʱ�� 

	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;   //��Ƶֵ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;	   //����ģʽ
	TIM_TimeBaseInitStructure.TIM_Period=arr;		   //�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;  //����ʱ�ӷָ�
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);//��������ж�

	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM7,ENABLE);		  //ʹ��TIM3									 
}


//LCD ����PWM�����ʼ��
//PB0
//��ʼ���������Ϊ:PWM����Ƶ��Ϊ80Khz
//0,�;250,�.
void LCD_PWM_Init(u16 pwm)
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB2ENR|=1<<13; 	//TIM8ʱ��ʹ��    
	RCC->APB2ENR|=1<<3;    	//ʹ��PORTBʱ��	 			 
	  	
	GPIOB->CRL&=0XFFFFFFF0;	//PB0���
	GPIOB->CRL|=0X0000000B;	//���ù������ 	  
	GPIOB->ODR|=1<<0;		//PB0����	 

	TIM8->ARR=110;			//�趨�������Զ���װֵΪ110.Ƶ��Ϊ654Khz 
	TIM8->PSC=0;			//Ԥ��Ƶ������Ƶ
	
	TIM8->CCMR1|=7<<12; 	//CH2 PWM2ģʽ		 
	TIM8->CCMR1|=1<<11; 	//CH2Ԥװ��ʹ��	   

	TIM8->CCER|=1<<6;   	//OC2�������ʹ��	   
 	TIM8->CCER|=1<<7;   	//OC2N�͵�ƽ��Ч	   
	TIM8->BDTR|=1<<15;   	//MOE�����ʹ��	   

	TIM8->CR1=0x0080;   	//ARPEʹ�� 
	TIM8->CR1|=0x01;    	//ʹ�ܶ�ʱ��8

    TIM_SetCompare2(TIM8, pwm);
}



