#include "includes.h" //teng
#include "app.h" //teng
#include "EmWinHZFont.h"//teng
#include "ff.h"//teng
#include "malloc.h"//teng
#include "exfuns.h"//teng
//#include "treenleafimage.h"//teng


#define _DF1S	0x81
#define BROWSER_FILE_NAME_LEN 	100							//�ļ������ȣ������⵽�ļ�������50 ��������ļ�

extern void setTreenFilesImage(u8 *fn,TREEVIEW_ITEM_Handle hItem,int index);
extern u8 filePathCheck(u8 *path);


/**
  * @brief  scan_files �ݹ�ɨ��sd���ڵ��ļ�
  * @param  path:��ʼɨ��·�� file_name��ָ�������洢�ļ�����һ�οռ� hFile:���ڼ�¼�ļ�·�����ļ�ָ�� hTree Ŀ¼�� hNode Ŀ¼���
	*					hTree == NULL &&	hNode == NULL �Ļ���������Ŀ¼��			
  * @retval result:�ļ�ϵͳ�ķ���ֵ
  */
static FRESULT scan_files(char* path,char* file_name,FIL *hFile,WM_HWIN hTree, TREEVIEW_ITEM_Handle hNode,int *fileNum, u8 ftype) 
{ 
    FRESULT res; 		          //�����ڵݹ���̱��޸ĵı���������ȫ�ֱ���	
    FILINFO fno; 
	unsigned int rw_num;			//�Ѷ�����д���ֽ���
//	char showname[60]={0};
    DIR dir; 
    int i; 
    char *fn; 	
	TREEVIEW_ITEM_Handle hItem=0;

#if _USE_LFN 
    static char lfn[_MAX_LFN * (_DF1S ? 2 : 1) + 1]; 	//���ļ���֧��
    fno.lfname = lfn; 
    fno.lfsize = sizeof(lfn); 
#endif 

    res = f_opendir(&dir, path);                            //��Ŀ¼
    if (res == FR_OK) 
	{ 
        i = strlen(path); 
        for (;;) 
		{ 
            res = f_readdir(&dir, &fno); 										//��ȡĿ¼�µ�����
            if (res != FR_OK || fno.fname[0] == 0) break; 	//Ϊ��ʱ��ʾ������Ŀ��ȡ��ϣ�����
#if _USE_LFN 
            fn = *fno.lfname ? fno.lfname : fno.fname; 
#else 
            fn = fno.fname; 
#endif 
            if (*fn == '.') continue; 											//���ʾ��ǰĿ¼������			
            if (fno.fattrib & AM_DIR) 
			{ 																							//Ŀ¼���ݹ��ȡ
				if(hTree != NULL &&	hNode != NULL)
				{
//					gbk2utf8(fn,showname,60);
//					hItem = TREEVIEW_ITEM_Create(TREEVIEW_ITEM_TYPE_NODE,showname,0);
					hItem = TREEVIEW_ITEM_Create(TREEVIEW_ITEM_TYPE_NODE,fn,0);						//Ŀ¼���������
					TREEVIEW_AttachItem(hTree,hItem,hNode,TREEVIEW_INSERT_FIRST_CHILD);		//�ѽ����뵽Ŀ¼����
				}								
				sprintf(&path[i], "/%s", fn); 							//�ϳ�����Ŀ¼��
                res = scan_files(path,file_name,hFile,hTree,hItem,fileNum, ftype);		//�ݹ���� 
                if (res != FR_OK) 
					break; 																		//��ʧ�ܣ�����ѭ��
                path[i] = 0; 
            } 
			else 																				//���ļ�
			{
				if( (f_typetell(fn)>>4) == (ftype>>4) )                                         //Ҫ�����ļ����͵Ĵ���
				{
					/* ����Ҫ���Ƿ񴴽�Ŀ¼�� */
					if(hTree != NULL &&	hNode != NULL)												//����Ŀ¼��
					{
//						gbk2utf8(fn,showname,60);
//						hItem = TREEVIEW_ITEM_Create(TREEVIEW_ITEM_TYPE_LEAF,showname,0);
						hItem = TREEVIEW_ITEM_Create(TREEVIEW_ITEM_TYPE_LEAF,fn,0);						//�ļ���������Ҷ
						TREEVIEW_AttachItem(hTree,hItem,hNode,TREEVIEW_INSERT_FIRST_CHILD);		//����Ҷ��ӵ�Ŀ¼��
						
						setTreenFilesImage(fn,hItem,TREEVIEW_BI_LEAF);                          //������Ҷͼ��
					
						if (strlen(path)+strlen(fn)<BROWSER_FILE_NAME_LEN)
						{
							sprintf(file_name, "%s/%s", path,fn); 	
						}			
					}
				}
			}//else
        } //for
    } 
    return res; 
} 


/**
  * @brief  Fill_FileList����ǵݹ���̣�Ȼ����õݹ麯��scan_filesɨ��Ŀ¼
	*					
  * @param  path:��ʼɨ��·��
  * @retval none
  */
void Fill_FileList(char* path,WM_HWIN hTree, TREEVIEW_ITEM_Handle hNode,int *p, u8 ftype)
{
    CPU_SR_ALLOC();
	u8 result;
	char p_path[BROWSER_FILE_NAME_LEN]={0};				//Ŀ¼�� ָ��
	char file_name[BROWSER_FILE_NAME_LEN]={0};				//���ڴ洢��Ŀ¼�ļ���
	strcpy(p_path,path);						//����Ŀ¼����ָ��
	OS_CRITICAL_ENTER();
    result = scan_files(p_path,file_name,file,hTree,hNode,p, ftype);			//�ݹ�ɨ���ļ�		
    OS_CRITICAL_EXIT();
}



