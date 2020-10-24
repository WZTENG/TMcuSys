#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//SPI���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/20
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved	
//********************************************************************************
//����˵��
//V1.1
//����SPI1��ʼ����غ���������SPI1_Init��SPI1_SetSpeed��SPI1_ReadWriteByte��								  
//////////////////////////////////////////////////////////////////////////////////

//SD��ģʽ  0ΪSDIOģʽ   1ΪSPIģʽ
#define SD_MODE    1       //teng    1,spi...0,sdio
				    
// SPI�����ٶ����� 
#define SPI_SPEED_2   		0
#define SPI_SPEED_4   		1
#define SPI_SPEED_8   		2
#define SPI_SPEED_16  		3
#define SPI_SPEED_32 		4
#define SPI_SPEED_64 		5
#define SPI_SPEED_128 		6
#define SPI_SPEED_256 		7

void SPI1_Init(void);			 //��ʼ��SPI1��
void SPI2_Init(void);			 //��ʼ��SPI2��
void SPI1_SetSpeed(u8 SpeedSet); //����SPI1�ٶ�  		 
void SPI2_SetSpeed(u8 SpeedSet); //����SPI2�ٶ�   
u8 SPI1_ReadWriteByte(u8 TxData);//SPI1���߶�дһ���ֽ�
u8 SPI2_ReadWriteByte(u8 TxData);//SPI2���߶�дһ���ֽ�


#endif

