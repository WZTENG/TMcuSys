#include "includes.h"
#include "app.h"
#include "rtc.h"   //teng
#include "EmWinHZFont.h"//teng
#include "ff.h"//teng
#include "malloc.h"//teng
#include "appskin.h"//teng
#include "ILI93xx.h"//�����ܲ�����ԭʼlcd������ʾteng
#include "MessageBoxUser.h"
#include "tpad.h"
#include "led.h"
#include <stdlib.h>  /* for rand */
/*
*********************************************************************************************************
*                                         �궨�� 
*********************************************************************************************************
*/
#define ICONVIEW_Width     48   /* �ؼ�ICONVIEW�Ŀ� */  
#define ICONVIEW_Height    48   /* �ؼ�ICONVIEW�ĸߣ�����ͼ���Y������ */  
#define ICONVIEW_XSpace    10   /* �ؼ�ICONVIEW��X������ */ 
#define ICONVIEW_YSpace    15   /* �ؼ�ICONVIEW��Y������ */ 
#define ICONVIEW_XPos	   4    /* �ؼ�ICONVIEW��X�����������*/
#define VIRTUAL_WIN_NUM	   1    /* icon��ҳ�� */ // 2
#define ICONVIEW_ImagNum   20   /* �ؼ�ICONVIEW�е�ͼ����� */ 
#define BOTWIN_YSpace	   60   /* ��Ļ�·����ִ���Y������*/
#define MIDWIN_yPos		   20   /* �м䴰��Y������ʼλ�ü��������ֿ��ø߶�*/
#define MIDWIN_xPos		   0 	/* �м䴰��Y������ʼλ��*/

/*
*********************************************************************************************************
*                                      ����
*********************************************************************************************************
*/ 
/*ʱ��ṹ��*/
//extern struct rtc_time systmtime;
extern _calendar_obj calendar;//ʱ�ӽṹ��
//GUI_XBF_DATA XBF_Data;
//GUI_FONT     XBF_Font;

// ����������ɫ
#define TOP_BG_COLOR        0x00fd71a9
#define MID_BG_TOP_COLOR    0x00f7aac9
#define MID_BG_BOTTOM_COLOR 0x00f95d9b
#define BOTTOM_BG_COLOR     0x00ed9cbc
#define ICON_BG_ALPHA       0x80000000

/* ��������ICONVIEWͼ��Ĵ��� */
typedef struct {
  GUI_BITMAP * pBitmap;
  const char       * pText;
} BITMAP_ITEM;

typedef struct WIN_PARA{			//����ʹ�õ����û���������������ڻص�������ʹ��
	int xSizeLCD, ySizeLCD;			//LCD��Ļ�ߴ�
	int xPosWin,  yPosWin;			//���ڵ���ʼλ��
	int xSizeWin, ySizeWin;			//���ڳߴ�	
	int xSizeBM,  ySizeBM;
	int ySizeBotWin;
	
	WM_HWIN hWinBot;				//���ƴ��ڵľ�����ײ���
	WM_HWIN hWinMid;				//����ʾ���ľ�����в���
	
}WIN_PARA;
WIN_PARA WinPara;			//�û�ʹ�õĴ��ڶ�������
__IO uint8_t app_prevent_refresh = 0;  /* ��������Ƚ���Ҫ�����ڷ�ֹICON�ؼ������ʱ�ʹ����ص�������WM_PAINT��Ϣ*/
/* ��������ICONVIEW0ͼ��Ĵ��� */
static BITMAP_ITEM _aBitmapItem0[] = {
	{&bmphone,     "����" 	},
	{&bmmessages,  "����"	},
	{&bmbrowser,   "�����" 	},
	{&bmapp,  	   "Ӧ��"	},
};
/* ��������ICONVIEW1ͼ��Ĵ��� */
static BITMAP_ITEM _aBitmapItem1[] = {
	{&bmebooks,		"������"	},
	{&bmphotos,  	"���"	},  
	{&bmmusic,      "����"	},
	{&bmvideos,		"��Ƶ"	},

	{&bmclock,		"ʱ��" 	},
	{&bmexeplay, 	"������"},
	{&bmgames,   	"��Ϸ" 	},
	{&bmnotes,  	"���±�"},

	{&bmsettings, 	"����"	},  
	{&bmrecoder,  	"¼����" },
	{&bmradio,      "������" },
	{&bmcalculator,	"������"	}
};

/* ��������ICONVIEW2ͼ��Ĵ��� */
static BITMAP_ITEM _aBitmapItem2[] = {
	{&bmcamera,  	"�����"	},
	{&bmusb,		"USB����" 	},
	{&bminternet,   "������" 	},
	{&bmwireless,   "����"		},
	
	{&bmwifi,		"WIFI"		},  
	{&bmcompass,   	"����" 		},	
	{&bmbluetooth,  "����" 		},
	{&bmgps,    	"��λ"		},
	
//	{&bmcalendar,	"����"		},  
//	{&bmxxx,   		"xxx" 		},	
//	{&bmxxx,  		"xxx" 		},
//	{&bmxxx,    	"xxx"		}
};


u8 *ICONBuff[3][12];//ͼ�껺��Ҫ������Ч,һ��ͼ���Լ9-12KB
//���ⲿ����ͼ��.bin�ļ�
//ix:��ǰͼ��
//�ĸ�����ͼ��0�ײ�1��һҳ2�ڶ�ҳ
u8 Load_ICON(u8 ix, GUI_BITMAP *pBitmapx, u8 itemx)
{
	FIL ICONFile;	  		//�ļ�1
	UINT br,bw;				//��д����
	u8 res;
//	u8 *databuf = NULL;

	res = f_open(&ICONFile, (u8*)icos_path_tbl[itemx][ix], FA_READ);     //��ͼ���ļ�
	if(res == FR_OK)
	{
		ICONBuff[itemx][ix] = (u8*)mymalloc(SRAMEX, ICONFile.fsize);     //����ͼ���С���ⲿ�ڴ�
		if(ICONBuff[itemx][ix] == NULL)
		{
			f_close(&ICONFile);                                          //����ʧ���˳�
			return 0x01;
		}
		res = f_read(&ICONFile, ICONBuff[itemx][ix], ICONFile.fsize, &br);    //��ȡͼ���ļ����뻺����
		if(res == FR_OK)
		{
			pBitmapx->pData = ICONBuff[itemx][ix];                            //����ͼ�껺��ָ��
		}
	}
	else
	{
		return res;
	}
	f_close(&ICONFile);                                                       //�ر�ͼ���ļ�
//	myfree(SRAMEX, databuf);                                                  //����ͼ����Ч�����ͷ�
	return res;
}


/*
*********************************************************************************************************
*	�� �� ��: _cbBkWindow
*	����˵��: ���洰�ڵĻص����� 
*	��    �Σ�WM_MESSAGE * pMsg
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void _cbBkWindow(WM_MESSAGE * pMsg) 
{
	char text_buffer[20]={0};
	WM_HWIN hText;
    GUI_PID_STATE pState;
	switch (pMsg->MsgId) 
	{
		case WM_TIMER://����ʱ����ʾ����Ϣ��ÿ�����޸�һ��ʱ��
			/* ��ȡtext��� */ 
            hText = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT1);
			/* ת��rtcֵ������ʱ�� */
//			RTC_TimeCovr(&systmtime);
//            RTC_Get();
			/* ת�����ַ��� */
			sprintf(text_buffer,"%02d:%02d:%02d",calendar.hour,calendar.min,calendar.sec);  //teng
			/* ���ʱ�� */
			TEXT_SetText(hText,text_buffer);
		
			/* ��ȡtext��� */      
			hText = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT2);
			sprintf(text_buffer, "CPU:%3d.%02d%%", OSStatTaskCPUUsage/100, OSStatTaskCPUUsage%100);
			/* ���CPU */
			TEXT_SetText(hText,text_buffer);
		
			WM_RestartTimer(pMsg->Data.v, 1000);
		break;
		/* �ػ���Ϣ*/
		case WM_PAINT:		
            GUI_SetBkColor(TOP_BG_COLOR);      //GUI_ORANGE
            GUI_Clear();
//			GUI_DrawBitmap(&bmlogo,1,1);
            if (GUI_TOUCH_GetState(&pState)==0) {
                ICONVIEW_SetSel(WM_GetDialogItem(WinPara.hWinMid, GUI_ID_ICONVIEW2),-1);
                ICONVIEW_SetSel(WM_GetDialogItem(WinPara.hWinMid, GUI_ID_ICONVIEW1),-1);
                ICONVIEW_SetSel(WM_GetDialogItem(WinPara.hWinBot, GUI_ID_ICONVIEW0),-1);
            }
		break;
			
	 default:
		WM_DefaultProc(pMsg);
		break;
	}
}
/*
*********************************************************************************************************
*	�� �� ��: _cbMidWin
*	����˵��: 
*	��    �Σ�WM_MESSAGE * pMsg
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void _cbMidWin(WM_MESSAGE * pMsg) 
{
	int NCode, Id;
	WM_MOTION_INFO * pInfo;
	switch (pMsg->MsgId) 
	{
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
			NCode = pMsg->Data.v;                 /* Notification code */
			switch (Id) 
			{
				case GUI_ID_ICONVIEW1:
					switch (NCode) 
					{
						/* ICON�ؼ������Ϣ */
						case WM_NOTIFICATION_CLICKED:
							app_prevent_refresh = 1;
							break;
						
						/* ICON�ؼ��ͷ���Ϣ */
						case WM_NOTIFICATION_RELEASED: 
							
							/* ����Ӧѡ�� */
							switch(ICONVIEW_GetSel(pMsg->hWinSrc))
							{
								case 0:	
                                    MESSAGEBOX_Create_User_Modal("������", "��ʾ");                                
									break;	
								case 1:
                                    MESSAGEBOX_Create_User_Modal("ͼƬ:Flash����,�����ڴ�����ȡ��ע��", "��ʾ");
//                                    CreatePicture();//��Ҫ�޸�malloc.h����ռ�С��
									break;
								case 2:
                                    CreateMusic();
									break;
								case 3:
                                    MESSAGEBOX_Create_User_Modal("��Ƶ:Flash����,�����ڴ�����ȡ��ע��", "��ʾ"); 
//                                    CreateVideo();
									break;
								case 4:
                                    CreateDateTime();
									break;
								case 5:
                                    CreateExAppRun();
									break;
								case 6:
                                    MESSAGEBOX_Create_User_Modal("��Ϸ:Flash����,�����ڴ�����ȡ��ע��", "��ʾ");                                    
//                                    CreateNesGame();// ��Ϸ
									break;
								case 7:
                                    MESSAGEBOX_Create_User_Modal("���±�", "��ʾ");
									break;
								case 8:
                                    CreateSetting();
									break;
								case 9:
                                    MESSAGEBOX_Create_User_Modal("¼����", "��ʾ");
									break;
								case 10:
                                    MESSAGEBOX_Create_User_Modal("������", "��ʾ");
									break;
								case 11:
                                    CreateCalculator();
									break;
								default:break;
								}
							 break;
						}
					break;
				case GUI_ID_ICONVIEW2:
					switch (NCode) 
					{
						/* ICON�ؼ������Ϣ */
						case WM_NOTIFICATION_CLICKED:
							app_prevent_refresh = 1;
							break;
						
						/* ICON�ؼ��ͷ���Ϣ */
						case WM_NOTIFICATION_RELEASED: 
							
							/* ����Ӧѡ�� */
							switch(ICONVIEW_GetSel(pMsg->hWinSrc))
							{			
								case 0:
                                    MESSAGEBOX_Create_User_Modal("�����", "��ʾ");
									break;
								case 1:
                                    MESSAGEBOX_Create_User_Modal("USB����", "��ʾ");
									break;
								case 2:
                                    MESSAGEBOX_Create_User_Modal("������", "��ʾ");
									break;
								case 3:
                                    MESSAGEBOX_Create_User_Modal("����", "��ʾ");
									break;
								case 4:
                                    MESSAGEBOX_Create_User_Modal("WIFI", "��ʾ");
									break;
								case 5:
                                    MESSAGEBOX_Create_User_Modal("����", "��ʾ");
									break;
								case 6:
                                    MESSAGEBOX_Create_User_Modal("����", "��ʾ");
									break;
								case 7:
                                    MESSAGEBOX_Create_User_Modal("GPS", "��ʾ");
									break;
								default:break;
							}	
						 break;
					}
				break;
			}
			break;
		
		case WM_MOTION:
			 pInfo = (WM_MOTION_INFO *)pMsg->Data.p;
			 if (pInfo) 
			 {
				//printf("mooton_message=%d\n",pInfo->Cmd);
				 switch (pInfo->Cmd) 
				 {				    
					case WM_MOTION_INIT:
						pInfo->SnapX = WinPara.xSizeLCD;		//���ض���
						pInfo->SnapY = 0;
						//pInfo->Flags = WM_CF_MOTION_X | WM_MOTION_MANAGE_BY_WINDOW;
						//pInfo->Period = 500;
					break;
					
					case WM_MOTION_MOVE:
						WM_DisableWindow(WM_GetDialogItem(pMsg->hWin,GUI_ID_ICONVIEW1));
						WM_DisableWindow(WM_GetDialogItem(pMsg->hWin,GUI_ID_ICONVIEW2));
					break;							
					case WM_MOTION_GETPOS:
//						printf("\n dx = %d",pInfo->dx);
//						printf(" xpos = %d\n",pInfo->xPos);
//						printf(" da = %d\n",pInfo->da);
//						printf(" SnapX = %d\n",pInfo->SnapX);
					break;								
					default:
						break;						
				  }
				/* �ƶ����� */
				if (pInfo->FinalMove || pInfo->dx==0) {
					WM_EnableWindow(WM_GetDialogItem(pMsg->hWin,GUI_ID_ICONVIEW1));
					WM_EnableWindow(WM_GetDialogItem(pMsg->hWin,GUI_ID_ICONVIEW2));
				}
			 }	
			
			break;
			
		/* �ػ���Ϣ*/
		case WM_PAINT:
			{
				GUI_DrawGradientV(0, 0, WinPara.xSizeWin, WinPara.ySizeWin, MID_BG_TOP_COLOR, MID_BG_BOTTOM_COLOR);
			//	GUI_DrawGradientV(0,0,WinPara.xSizeWin,WinPara.ySizeWin,GUI_ORANGE+0x303000,GUI_LIGHTYELLOW-0x303000);
			//	GUI_SetBkColor(GUI_RED);
			//	GUI_Clear();
			}			
		break;			
	 default:
		WM_DefaultProc(pMsg);
		break;
	}
}


/**
  * @brief  _cbBotWin,�������ص�����
  * @param  none
  * @retval none
  */
static void _cbBotWin(WM_MESSAGE * pMsg)
{
	int NCode, Id;
	switch (pMsg->MsgId) 
	{			 		 
		case WM_PAINT:	                             //�ػ汳��	
			GUI_SetBkColor(BOTTOM_BG_COLOR);         //GUI_LIGHTYELLOW
			GUI_Clear();
		break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
			NCode = pMsg->Data.v;                 /* Notification code */
            switch (Id) 
            {
                case GUI_ID_ICONVIEW0:
                    switch (NCode) 
                    {
                        /* ICON�ؼ������Ϣ */
                        case WM_NOTIFICATION_CLICKED:
                            app_prevent_refresh = 1;
                            break;
                        
                        /* ICON�ؼ��ͷ���Ϣ */
                        case WM_NOTIFICATION_RELEASED: 
                            
                            /* ����Ӧѡ�� */
                            switch(ICONVIEW_GetSel(pMsg->hWinSrc))
                            {
                                case 0:	
                                    CreatePerfMon();
                                    break;	
                                case 1:
                                    MESSAGEBOX_Create_User_Modal("��ʾ��ɶ", "��ʾ");
                                    break;
                                case 2:
                                    CreateBrowser();
                                    break;
                                case 3:
                                    MESSAGEBOX_Create_User_Modal("д��ɶ", "��ʾ");
                                    break;
                            }	
                        break;
                    }
                break;
            }
        break;		
        default:		
            WM_DefaultProc(pMsg);
        break;		 
	}
}

/**
  * @brief  CreateTopWin�����������Ĵ���
  * @param  none
  * @retval none
  */
static void CreateTopWin(void)
{
	WM_HWIN hText;
	/* �������ı� */
	hText = TEXT_CreateEx(3, 2, 60 , 16, WM_HBKWIN, WM_CF_SHOW, GUI_TA_LEFT|TEXT_CF_VCENTER, GUI_ID_TEXT0, "WZTENG");
	TEXT_SetFont(hText,GUI_FONT_10_ASCII);
	TEXT_SetTextColor(hText,GUI_DARKGRAY);
	
//	GUI_DrawBitmap(&bmlogo,1,1);
	
	/* ״̬����ʱ����ʾ�ı� */
	hText = TEXT_CreateEx(WinPara.xSizeLCD/2-25,2,50,16,WM_HBKWIN,WM_CF_SHOW,GUI_TA_HCENTER|TEXT_CF_VCENTER,GUI_ID_TEXT1,"11:01:29");
	//TEXT_SetBkColor(hText,GUI_INVALID_COLOR);
	TEXT_SetTextColor(hText,GUI_DARKGRAY);
	TEXT_SetFont(hText,GUI_FONT_10_ASCII);
	
	/* ״̬����CPU��ʾ�ı� */
	hText = TEXT_CreateEx(170,2,70,16,WM_HBKWIN,WM_CF_SHOW,TEXT_CF_VCENTER,GUI_ID_TEXT2,"CPU:000.00%");
	//TEXT_SetBkColor(hText,GUI_INVALID_COLOR);
	TEXT_SetTextColor(hText,GUI_DARKGRAY);
	TEXT_SetFont(hText,GUI_FONT_10_ASCII);
}
/**
  * @brief  CreateMidWin�������м�Ĵ���
  * @param  none
  * @retval none
  */
static void CreateMidWin(void)
{
	uint8_t i=0;
	WM_HWIN MIDWIN;
	WinPara.hWinMid= WM_CreateWindowAsChild(
											WinPara.xPosWin,											
											WinPara.yPosWin,
											WinPara.xSizeWin,
											WinPara.ySizeWin,	
											WM_HBKWIN, 
											WM_CF_SHOW | WM_CF_MOTION_X, 
											_cbMidWin, 
											sizeof(WIN_PARA *)
											);
/*-------------------------------------------------------------------------------------*/
	/*��ָ��λ�ô���ָ���ߴ��ICONVIEW1 С����*/
	MIDWIN=ICONVIEW_CreateEx(
							 ICONVIEW_XPos, 					/* С���ߵ��������أ��ڸ������У�*/
							 0, 								/* С���ߵ��������أ��ڸ������У�*/
							 WinPara.xSizeLCD-ICONVIEW_XPos,	/* С���ߵ�ˮƽ�ߴ磨��λ�����أ�*/
							 3*(WinPara.ySizeBM+30), 			/* С���ߵĴ�ֱ�ߴ磨��λ�����أ�*/
							 WinPara.hWinMid, 				    /* �����ڵľ�������Ϊ0 ������С���߽���Ϊ���棨�������ڣ����Ӵ��� */
							 WM_CF_SHOW | WM_CF_HASTRANS,       /* ���ڴ�����ǡ�ΪʹС���������ɼ���ͨ��ʹ�� WM_CF_SHOW */ 
							 0,//ICONVIEW_CF_AUTOSCROLLBAR_V, 	/* Ĭ����0�����������ʵ������������ֱ������ */
							 GUI_ID_ICONVIEW1, 			        /* С���ߵĴ���ID */
							 ICONVIEW_Width, 				    /* ͼ���ˮƽ�ߴ� */
							 ICONVIEW_Height+13);				/* ͼ��Ĵ�ֱ�ߴ� */
											 
	/* ��ICONVIEW С���������ͼ�� */
	for (i = 0; i < GUI_COUNTOF(_aBitmapItem1); i++) 
	{
		Load_ICON(i, _aBitmapItem1[i].pBitmap, 1);
		ICONVIEW_AddBitmapItem(MIDWIN, _aBitmapItem1[i].pBitmap,_aBitmapItem1[i].pText);
	}
    ICONVIEW_SetTextColor(MIDWIN,ICONVIEW_CI_UNSEL,GUI_DARKGRAY);
    ICONVIEW_SetTextColor(MIDWIN,ICONVIEW_CI_SEL,GUI_BLUE);
	/* ����С���ߵı���ɫ 32 λ��ɫֵ��ǰ8 λ������alpha��ϴ���Ч��*/
	ICONVIEW_SetBkColor(MIDWIN, ICONVIEW_CI_SEL, GUI_WHITE | ICON_BG_ALPHA);
	/* �������� */
//	ICONVIEW_SetFont(MIDWIN, &GUI_Font10_ASCII);
	ICONVIEW_SetFont(MIDWIN, &GUI_FontHZ12);
	/* ���ó�ʼѡ���ͼ��Ϊ -1 (��ʾ��δѡ��)*/
	ICONVIEW_SetSel(MIDWIN,-1);
	/* ����ͼ����x ��y �����ϵļ�ࡣ*/
	ICONVIEW_SetSpace(MIDWIN, GUI_COORD_X, ICONVIEW_XSpace);
	ICONVIEW_SetSpace(MIDWIN, GUI_COORD_Y, ICONVIEW_YSpace);
//	ICONVIEW_SetSpace(hWin, GUI_COORD_Y, ICONVIEW_YSpace);
	/* ���ö��뷽ʽ ��5.22�汾�����¼���� */
	ICONVIEW_SetIconAlign(MIDWIN, ICONVIEW_IA_HCENTER|ICONVIEW_IA_TOP);
	
    //teng
    if (VIRTUAL_WIN_NUM <= 1) {
        // ����ʱֻŪһҳ����
        return;
    }
/*-------------------------------------------------------------------------------------*/
	/*��ָ��λ�ô���ָ���ߴ��ICONVIEW2С����*/
	MIDWIN=ICONVIEW_CreateEx(
							 WinPara.xSizeLCD+ICONVIEW_XPos,	/* С���ߵ��������أ��ڸ������У�*/
							 0, 								/* С���ߵ��������أ��ڸ������У�*/
							 WinPara.xSizeLCD-ICONVIEW_XPos,	/* С���ߵ�ˮƽ�ߴ磨��λ�����أ�*/
							 2*(WinPara.ySizeBM+30),			/* С���ߵĴ�ֱ�ߴ磨��λ�����أ�*/
							 WinPara.hWinMid, 				    /* �����ڵľ�������Ϊ0 ������С���߽���Ϊ���棨�������ڣ����Ӵ��� */
							 WM_CF_SHOW | WM_CF_HASTRANS,       /* ���ڴ�����ǡ�ΪʹС���������ɼ���ͨ��ʹ�� WM_CF_SHOW */ 
							 0,//ICONVIEW_CF_AUTOSCROLLBAR_V, 	/* Ĭ����0�����������ʵ������������ֱ������ */
							 GUI_ID_ICONVIEW2, 			        /* С���ߵĴ���ID */
							 ICONVIEW_Width, 				    /* ͼ���ˮƽ�ߴ� */
							 ICONVIEW_Height+13);				/* ͼ��Ĵ�ֱ�ߴ� */
	/*-------------------------------------------------------------------------------------*/						 
//	WM_EnableMemdev(WinPara.hWinMid); //teng
	/* ��ICONVIEW С���������ͼ�� */
	for (i = 0; i < GUI_COUNTOF(_aBitmapItem2); i++) 
	{
		Load_ICON(i, _aBitmapItem2[i].pBitmap, 2);
		ICONVIEW_AddBitmapItem(MIDWIN, _aBitmapItem2[i].pBitmap,_aBitmapItem2[i].pText);
	}
    ICONVIEW_SetTextColor(MIDWIN,ICONVIEW_CI_UNSEL,GUI_DARKGRAY);
    ICONVIEW_SetTextColor(MIDWIN,ICONVIEW_CI_SEL,GUI_BLUE);
	/* ����С���ߵı���ɫ 32 λ��ɫֵ��ǰ8 λ������alpha��ϴ���Ч��*/
	ICONVIEW_SetBkColor(MIDWIN, ICONVIEW_CI_SEL, GUI_WHITE | ICON_BG_ALPHA);
	/* �������� */
//	ICONVIEW_SetFont(MIDWIN, &GUI_Font10_ASCII);
	ICONVIEW_SetFont(MIDWIN, &GUI_FontHZ12);
	/* ���ó�ʼѡ���ͼ��Ϊ -1 (��ʾ��δѡ��)*/
	ICONVIEW_SetSel(MIDWIN,-1);
	/* ����ͼ����x ��y �����ϵļ�ࡣ*/
	ICONVIEW_SetSpace(MIDWIN, GUI_COORD_X, ICONVIEW_XSpace);
	ICONVIEW_SetSpace(MIDWIN, GUI_COORD_Y, ICONVIEW_YSpace);
//	ICONVIEW_SetSpace(hWin, GUI_COORD_Y, ICONVIEW_YSpace);
	/* ���ö��뷽ʽ ��5.22�汾�����¼���� */
	ICONVIEW_SetIconAlign(MIDWIN, ICONVIEW_IA_HCENTER|ICONVIEW_IA_TOP);
}
/**
  * @brief  CreateBotWin�������ײ��Ĵ���
  * @param  none
  * @retval none
  */
static void CreateBotWin(void)
{
	uint8_t i;
	WM_HWIN BOTWIN;
	WinPara.hWinBot= WM_CreateWindowAsChild(
											0,											
											WinPara.ySizeLCD-WinPara.ySizeBotWin,	//�ײ�λ��
											WinPara.xSizeLCD,
											WinPara.ySizeBotWin,	//�ײ�ʣ����
											WM_HBKWIN, 
											WM_CF_SHOW,
											_cbBotWin, 
											sizeof(WIN_PARA *)
											);
	/*��ָ��λ�ô���ָ���ߴ��ICONVIEW С����*/
	BOTWIN=ICONVIEW_CreateEx(
							 ICONVIEW_XPos, 					/* С���ߵ��������أ��ڸ������У�*/
							 0, 								/* С���ߵ��������أ��ڸ������У�*/
							 WinPara.xSizeLCD-ICONVIEW_XPos,	/* С���ߵ�ˮƽ�ߴ磨��λ�����أ�*/
							 WinPara.ySizeBotWin,				/* С���ߵĴ�ֱ�ߴ磨��λ�����أ�*/
							 WinPara.hWinBot, 				    /* �����ڵľ�������Ϊ0 ������С���߽���Ϊ���棨�������ڣ����Ӵ��� */
							 WM_CF_SHOW | WM_CF_HASTRANS,       /* ���ڴ�����ǡ�ΪʹС���������ɼ���ͨ��ʹ�� WM_CF_SHOW */ 
							 0,//ICONVIEW_CF_AUTOSCROLLBAR_V, 	/* Ĭ����0�����������ʵ������������ֱ������ */
							 GUI_ID_ICONVIEW0, 			        /* С���ߵĴ���ID */
							 ICONVIEW_Width, 				    /* ͼ���ˮƽ�ߴ� */
							 ICONVIEW_Height);					/* ͼ��Ĵ�ֱ�ߴ� */
	WM_BringToTop(WinPara.hWinBot);
	/* ��ICONVIEW С���������ͼ�� */
	for (i = 0; i < GUI_COUNTOF(_aBitmapItem0); i++) 
	{
		Load_ICON(i, _aBitmapItem0[i].pBitmap, 0);
		ICONVIEW_AddBitmapItem(BOTWIN, _aBitmapItem0[i].pBitmap,"");
	}	
	/* ����С���ߵı���ɫ 32 λ��ɫֵ��ǰ8 λ������alpha��ϴ���Ч��*/
	ICONVIEW_SetBkColor(BOTWIN, ICONVIEW_CI_SEL, GUI_WHITE | ICON_BG_ALPHA);
	/* �������� */
//	ICONVIEW_SetFont(hWinicon0, &GUI_Font10_ASCII);
	/* ���ó�ʼѡ���ͼ��Ϊ -1 (��ʾ��δѡ��)*/
	ICONVIEW_SetSel(BOTWIN,-1);
	/* ����ͼ����x ��y �����ϵļ�ࡣ*/
	ICONVIEW_SetSpace(BOTWIN, GUI_COORD_X, ICONVIEW_XSpace);
//	ICONVIEW_SetSpace(hWin, GUI_COORD_Y, ICONVIEW_YSpace);
	/* ���ö��뷽ʽ ��5.22�汾�����¼���� */
	ICONVIEW_SetIconAlign(BOTWIN, ICONVIEW_IA_HCENTER|ICONVIEW_IA_TOP);
}

extern u8 nesruning;//nes_main.c����
extern u8 videoruning;//videoplayer.c
#define SCREEN_TIME 10000
static void _cbScreenWin(WM_MESSAGE *pMsg);
/*
*********************************************************************************************************
*	�� �� ��: MainAPP
*	����˵��: GUI������ 
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void MainAPP(void)
{
//    GUI_HWIN activeWin;
    int show_screen = 0;
    int no_touch_count = 0;
    GUI_PID_STATE pState;
    WM_HWIN screenWin;
    WM_HTIMER screenTimer;
    
    app_prevent_refresh = 0;
	//׼������3�����ڣ�������ʹ�õ����û���������������ڻص�������ʹ��
	WinPara.xSizeLCD = LCD_GetXSize();				//LCD��Ļ�ߴ�
	WinPara.ySizeLCD = LCD_GetYSize();				//LCD��Ļ�ߴ�
	WinPara.xSizeBM  = ICONVIEW_Width;				//ͼ����
	WinPara.ySizeBM  = ICONVIEW_Height;				//ͼ��߶�
	WinPara.ySizeBotWin = BOTWIN_YSpace;			//�����·����ڸ߶�
	WinPara.xSizeWin = WinPara.xSizeLCD * VIRTUAL_WIN_NUM;						//���ڳߴ�
	WinPara.ySizeWin = WinPara.ySizeLCD - WinPara.ySizeBotWin - WinPara.yPosWin;	//���ڳߴ�
	WinPara.xPosWin	 = MIDWIN_xPos;							//���ڵ���ʼλ��
	WinPara.yPosWin  = MIDWIN_yPos;							//���ڵ���ʼλ��
    
	WM_SetSize(WM_HBKWIN, WinPara.xSizeLCD, WinPara.ySizeLCD);//���ñ������ڴ�С����֤�м䴰���ƶ�Ч��
	/***************************����Ĭ��Ƥ��ɫ*****************************/
//	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
//	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
//	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
//	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
//	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
//	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
//	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
//	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
//	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
//	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);
//	MENU_SetDefaultSkin(MENU_SKIN_FLEX);
//	SPINBOX_SetDefaultSkin(SPINBOX_SKIN_FLEX);
	/***************************�����Զ���Ƥ��**********************************/
    setAppCustomSkin(0);
    /***************************����Ĭ������**********************************/
	GUI_SetDefaultFont(&GUI_FontHZ16);
	/*************************************************************************/
	WM_Activate();//5.32������òŻ���ʾ���棬����һ���ˡ�����
	WM_MOTION_Enable(1);
	WM_MOTION_SetDefaultPeriod(250);
	WM_SetCallback(WM_HBKWIN, _cbBkWindow);
	WM_CreateTimer(WM_HBKWIN, 0, 1000, 0);
	/* ������������ ״̬������������������*/
	CreateMidWin();
	CreateTopWin();
	CreateBotWin();
    
	while(1) {
		GUI_Delay(30);
        
//        if (TPAD_Scan(0)) {
//            if (WinPara.hWinBot != activeWin && WinPara.hWinMid != activeWin) {
//                GUI_EndDialog(activeWin, 0);
//            }
//        }
        
        // ��������
        if (GUI_TOUCH_GetState(&pState)==0) {// û����Ļ
            no_touch_count++;
        } else {
            no_touch_count = 0;
        }
        if (no_touch_count>(1800*3) && show_screen==0 && nesruning==0 && videoruning==0) {// ��ʱ��û����Ļ���һ�û��ʾ
            show_screen = 1;
            screenWin = WM_CreateWindow(0,0,lcddev.width,lcddev.height,WM_CF_SHOW|WM_CF_STAYONTOP,_cbScreenWin,0);
            WM_SelectWindow(screenWin);
            screenTimer = WM_CreateTimer(screenWin, 0, 1000, 0);
            TIM_SetCompare2(TIM8, 3);
        } else if (show_screen==1 && GUI_TOUCH_GetState(&pState)==1) {// ������ʾ��������������Ļ
            show_screen = 0;
            WM_DeleteTimer(screenTimer);
            WM_SetCallback(screenWin, NULL);
            WM_DeleteWindow(screenWin);
            screenWin = 0;
            TIM_SetCompare2(TIM8, 15);
            GUI_Delay(300);
        }
	}
}

static void _cbScreenWin(WM_MESSAGE *pMsg)
{
	int NCode, Id;
    char text_buffer[20]={0};
    u8 r, g, b;
    const u8 count=30;
    int xa[count], ya[count], ra[count], i;
	switch (pMsg->MsgId) 
	{
        case WM_INIT_DIALOG:
            GUI_SetFont(&GUI_FontHZ12);
            break;
        case WM_TIMER:
//            r = rand()%256;
//            g = rand()%256;
//            b = rand()%256;
//            GUI_SetBkColor((r<<16)|(g<<8)|b);
            GUI_SetBkColor(GUI_BLACK);
			GUI_Clear();
        
            for (i=0;i<count;i++) {
                do {
                    xa[i] = rand()%lcddev.width;
                } while(xa[i]<=0 && xa[i]>=lcddev.width);
            }
            for (i=0;i<count;i++) {
                do {
                    ya[i] = rand()%lcddev.height;
                } while(ya[i]<=0 && ya[i]>=lcddev.height);
            }
            for (i=0;i<count;i++) {
                do {
                    ra[i] = rand()%15;
                } while(ra[i]<=0 && ra[i]>=15);
            }
            for (i=0;i<count;i++) {
                r = rand()%256;
                g = rand()%256;
                b = rand()%256;
                GUI_SetColor((r<<16)|(g<<8)|b);
                GUI_FillCircle(xa[i], ya[i], ra[i]);
            }
        
            GUI_SetFont(&GUI_FontHZ12);
            GUI_SetTextMode(GUI_TM_XOR);
            GUI_DispStringHCenterAt("�����Ļ�˳�", lcddev.width/2, lcddev.height-17);
            GUI_SetFont(&GUI_Font16_ASCII);
            sprintf(text_buffer,"%d/%02d/%02d %02d:%02d",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min);
            GUI_DispStringHCenterAt(text_buffer, lcddev.width/2, lcddev.height-40);
            GUI_SetTextMode(GUI_TM_NORMAL);
            WM_RestartTimer(pMsg->Data.v, SCREEN_TIME);
            break;
		case WM_PAINT:	                             //�ػ汳��	
			GUI_SetBkColor(GUI_BLACK);
			GUI_Clear();
            GUI_SetColor(GUI_WHITE);
            GUI_SetFont(&GUI_FontHZ12);
            GUI_SetTextMode(GUI_TM_XOR);
            GUI_DispStringHCenterAt("�����Ļ�˳�", lcddev.width/2, lcddev.height-17);
            GUI_SetFont(&GUI_Font16_ASCII);
            sprintf(text_buffer,"%d/%02d/%02d %02d:%02d",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min);
            GUI_DispStringHCenterAt(text_buffer, lcddev.width/2, lcddev.height-40);
            GUI_SetTextMode(GUI_TM_NORMAL);
            break;
        default:		
            WM_DefaultProc(pMsg);
            break;		 
	}
}
