#ifndef	_EX_APP_RUN_H_
#define	_EX_APP_RUN_H_

#include "GUI.h"
#include "DIALOG.h"
#include "sys.h"

#define EXEPLAY_APP_SIZE	60*1024					//app��������ߴ�.����Ϊ60K�ֽڣ���������SRAM��ʵ���ϲ���������60K�Ĵ��룩.
#define EXEPLAY_APP_BASE	0x20001000				//appִ�д����Ŀ�ĵ�ַ,Ҳ���ǽ�Ҫ���еĴ����ŵĵ�ַ
#define	EXEPLAY_SRC_BASE	0x68000000				//appִ�д����Դ��ַ,Ҳ������λ֮ǰ,app�����ŵĵ�ַ


typedef  void (*dummyfun)(void);	//����һ����������.
extern dummyfun jump2app;			//�ٺ���,��PCָ���ܵ��µ�main����ȥ
void exeplay_write_appmask(u16 val);
void exeplay_app_check(void);
u8 exe_play(u8 *path);	


#endif
