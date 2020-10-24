#ifndef __VIDEOPLAYER_H
#define __VIDEOPLAYER_H 
#include "avi.h"
#include "ff.h"

#define AVI_AUDIO_BUF_SIZE    1024*5		//����avi����ʱ,��Ƶbuf��С. 5
#define AVI_VIDEO_BUF_SIZE    1024*35		//����avi����ʱ,��Ƶbuf��С. 60


u8 video_play_mjpeg(u8 *pname); 
void video_time_show(FIL *favi,AVI_INFO *aviinfo);
u8 video_info_show(AVI_INFO *aviinfo);
u8 video_seek(FIL *favi,AVI_INFO *aviinfo,u8 *mbuf);

#endif

