#ifndef __PROJ_H__
#define __PROJ_H__

#include "Common.h"

typedef struct
{
//  Type        Name                            // Addd Info
    u16         uwHue;
    u8          boTimeTick1s                    : 1;
    u8          boTimeTick1m                    : 1;
    u8          boTimeTick1h                    : 1;
    u8                                          : 5;
} st_proj_info;

extern void Task_Proj(void *Task_Process);
extern st_proj_info gstProjInfo;

#endif
