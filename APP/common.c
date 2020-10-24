#include "common.h"
#include "ILI93xx.h"
#include "ff.h"

const u8 APP_WZTENG_ICO[168]=
{
    0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
    0X00,0X00,0X00,0X00,0X00,0X00,0X01,0XC0,0X00,0X03,0X80,0X00,0X00,0X07,0XE1,0X81,
    0X87,0XE0,0X00,0X00,0X1F,0XC1,0XC3,0X83,0XF8,0X00,0X00,0X7F,0X80,0XFF,0X01,0XFE,
    0X00,0X01,0XFF,0X80,0XBD,0X01,0XFF,0X80,0X03,0XFF,0X81,0X99,0X81,0XFF,0XC0,0X07,
    0XFF,0XE3,0XFF,0XC7,0XFF,0XE0,0X0F,0XFF,0XFF,0XFF,0XFF,0XFF,0XF0,0X1F,0XFF,0XFF,
    0XFF,0XFF,0XFF,0XF8,0X3F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X7F,0XFF,0XFF,0XFF,0XFF,
    0XFF,0XFE,0X7F,0XFF,0XFF,0XFF,0XFF,0XFF,0XFE,0XF0,0XFF,0XFF,0XFF,0XFF,0XFF,0X0F,
    0XC0,0X1F,0XFF,0XFF,0XFF,0XF8,0X03,0X00,0X07,0XFF,0XFF,0XFF,0XE0,0X00,0X00,0X03,
    0XFF,0XFF,0XFF,0XC0,0X00,0X00,0X03,0X83,0XFF,0XC1,0XC0,0X00,0X00,0X01,0X00,0XFF,
    0X00,0X80,0X00,0X00,0X00,0X00,0X3C,0X00,0X00,0X00,0X00,0X00,0X00,0X18,0X00,0X00,
    0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};
////////////////////////////////α����������취////////////////////////////////
u32 random_seed=1;
void app_srand(u32 seed)
{
	random_seed=seed;
}
//��ȡα�����
//���Բ���0~RANDOM_MAX-1�������
//seed:����
//max:���ֵ	  		  
//����ֵ:0~(max-1)�е�һ��ֵ 		
u32 app_get_rand(u32 max)
{			    	    
	random_seed=random_seed*22695477+1;
	return (random_seed)%max; 
}  

//m^n����
long long gui_pow(u8 m,u8 n)
{
	long long result=1;	 
	while(n--)result*=m;    
	return result;
}

//�õ����ֵ�λ��
//num:����
//dir:0,�Ӹ�λ����λ.1,�ӵ�λ����λ.
//����ֵ:���ֵ�λ��.(���Ϊ10λ)
//ע:0,��λ��Ϊ0λ.
u8 app_get_numlen(long long num,u8 dir)
{
#define MAX_NUM_LENTH		10		//�������ֳ���
	u8 i=0,j;
	u8 temp=0;  
	if(dir==0)//�Ӹߵ���
	{
		i=MAX_NUM_LENTH-1;
		while(1)
		{
			temp=(num/gui_pow(10,i))%10;
			if(temp||i==0)break;
			i--;
		}
	}else	//�ӵ͵���
	{
		j=0;
 		while(1)
		{
			if(num%10)
			{
				i=app_get_numlen(num,0);    
				return i;
			}
			if(j==(MAX_NUM_LENTH-1))break;	 
			num/=10;
			j++;
		}
	}
	if(i)return i+1;
	else if(temp)return 1;
	else return 0;	
}

//��ʾ��ɫͼ��
//x,y,width,height:���꼰�ߴ�.
//icosbase:����λ��
//color:�������ɫ.
//bkcolor:����ɫ
void app_show_mono_icos(u16 x,u16 y,u8 width,u8 height,u8 *icosbase,u16 color,u16 bkcolor)
{
	u16 rsize;
	u8 i,j;
	u8 temp;
	u8 t=0;
	u16 x0=x;//����x��λ��
	rsize=width/8+((width%8)?1:0);//ÿ�е��ֽ���
 	for(i=0;i<rsize*height;i++)
	{
		temp=icosbase[i];
		for(j=0;j<8;j++)
		{
	        if(temp&0x80)LCD_Fast_DrawPoint(x,y,color);  
			else LCD_Fast_DrawPoint(x,y,bkcolor);  	 
			temp<<=1;
			x++;
			t++;			//��ȼ�����
			if(t==width)
			{
				t=0;
				x=x0;
				y++;  
				break;
			}
		}
	}				
}				   


//�õ�STM32�����к�
//sn0,sn1,sn2:3���������к�
void app_getstm32_sn(u32 *sn0,u32 *sn1,u32 *sn2)
{
	*sn0=*(vu32*)(0x1FFFF7E8);
	*sn1=*(vu32*)(0x1FFFF7EC);
	*sn2=*(vu32*)(0x1FFFF7F0);    
}
//��ӡSN
void app_usmart_getsn(void)
{
	u32 sn0,sn1,sn2;
	app_getstm32_sn(&sn0,&sn1,&sn2);
	printf("\r\nSerial Number:%X%X%X\r\n",sn0,sn1,sn2);
}
//�õ��汾��Ϣ
//buf:�汾������(������Ҫ6���ֽ�,�籣��:V1.00)
//ver:�汾�궨��
//len:�汾λ��.1,����ֻ��1��λ�İ汾,V1;2,����2��λ�汾,V1.0;3,����3��λ�汾,V1.00;
void app_get_version(u8*buf,u32 ver,u8 len)
{
	u8 i=0;
	buf[i++]='V';
	if(len==1)
	{
		buf[i++]=ver%10+'0';
	}else if(len==2)
	{ 	
		buf[i++]=(ver/10)%10+'0';
		buf[i++]='.';
		buf[i++]=ver%10+'0';
	}else
	{
		buf[i++]=(ver/100)%10+'0';
		buf[i++]='.';
		buf[i++]=(ver/10)%10+'0';
		buf[i++]=ver%10+'0';	 
	}
	buf[i]=0;//���������	 			   
}

