#include "Proj.h"
#include "RX8025.h"
#include "iNixieKit.h"

st_proj_info gstProjInfo;

void Proj_NumDemo(void)
{
    static u8 ubLight = 0, ubNum = 0;
    for (u8 i = 0; i < TUBE_NUM_OF_NIXIE; i++)
    {
        if (ubNum == i)
        {
            gpubNixieLight[i] = ubLight;
        }
        else
        {
            gpubNixieLight[i] = 0;
        }
    }

    if (++ubLight >= 10)
    {
        ubLight = 0;

        ubNum += 1;
        if (ubNum >= 10)
        {
            ubNum = 0;
        }
    }
}

void Proj_TimeCtrl(void)
{
    MemCpyU8((u8 *)(&gstRTC), (u8 *)(&gstRtcBak), CONST_8);
    RX8025_GetTime();

    gstProjInfo.boTimeTick1s = (gstRTC.ubSec  != gstRtcBak.ubSec );
    gstProjInfo.boTimeTick1m = (gstRTC.ubMin  != gstRtcBak.ubMin );
    gstProjInfo.boTimeTick1h = (gstRTC.ubHour != gstRtcBak.ubHour);

    if (gstProjInfo.boTimeTick1s)
    {
        RX8025_PRINTF("%04d-%02d-%02d, %02d:%02d:%02d\r\n", gstRTC.uwYear, gstRTC.ubMonth, gstRTC.ubDay, gstRTC.ubHour, gstRTC.ubMin, gstRTC.ubSec);
    }
}

void Task_Proj(void *Task_Process)
{
    u8 ubLight = 0, ubNum = 0;
    MemSetU8((u8 *)&gstProjInfo, 0x00, sizeof(st_proj_info));

    while (1)
    {
        Proj_TimeCtrl();
        Proj_NumDemo();
        delay(499);
    }
}
