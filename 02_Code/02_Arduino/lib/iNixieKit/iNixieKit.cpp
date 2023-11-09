#include "iNixieKit.h"

const u8 gpubNixiePin[TUBE_NUM_OF_NIXIE] = {10, 4, 5, 19, 6, 18, 7, 3, 9, 0};
u8 gpubNixieLight[TUBE_NUM_OF_NIXIE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void iNixie_Init(void)
{
    for (u8 i = 0; i < TUBE_NUM_OF_NIXIE; i++)
    {
        pinMode(gpubNixiePin[i], OUTPUT);
        digitalWrite(gpubNixiePin[i], 0);
    }
}

void Task_iNixie(void *Task_iNixie)
{
    u8 ubCnt = 0;
    while (1)
    {
        for (u8 i = 0; i < TUBE_NUM_OF_NIXIE; i++) // 10 num
        {
            if (ubCnt >= gpubNixieLight[i] || 0 == gpubNixieLight[i])
            {
                digitalWrite(gpubNixiePin[i], 0);
            }
            else
            {
                digitalWrite(gpubNixiePin[i], 1);
            }
        }

        if (++ubCnt >= CONST_10) // light: 0 - 9
        {
            ubCnt = 0;
        }
        delay(1);
    }
}
