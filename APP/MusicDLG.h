#ifndef	_MUSIC_DLG_H_
#define	_MUSIC_DLG_H_

//#include "sys.h"

typedef struct musiclist MUSIC_LIST;
struct musiclist {
    char *music_name;//��ʾ������
    char *music_path;//����·��
    char blrc;//�Ƿ��и���ļ�
    char *lrc_path;//���·��
    MUSIC_LIST *nextMusic;//��һ��
    MUSIC_LIST *preMusic;//��һ��
};


#endif
