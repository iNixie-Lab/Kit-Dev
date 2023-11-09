#ifndef __INIXIE_KIT_H__
#define __INIXIE_KIT_H__

#include "Common.h"

#define TUBE_NUM_OF_NIXIE   10                                          // All num of the tube

extern void iNixie_Init(void);
extern void Task_iNixie(void *Task_iNixie);
extern u8 gpubNixieLight[TUBE_NUM_OF_NIXIE];

#endif
