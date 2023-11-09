#ifndef __RX8025_H__
#define __RX8025_H__

#include "Common.h"

#define RX8025_DEBUG            1
#define RX8025_ADDR             0x32

#define RX8025_IO_SDA           8
#define RX8025_IO_SCL           2

#if RX8025_DEBUG
    #define RX8025_PRINTF                   SERIAL_PRINTF
#else
    #define RX8025_PRINTF
#endif

typedef enum                                // ET7208的数据的地址
{
    RX8025_SEC                  = 0x00,
    RX8025_MIN                  = 0x01,
    RX8025_HR                   = 0x02,
    RX8025_WEEK                 = 0x03,
    RX8025_DATE                 = 0x04,
    RX8025_MTH                  = 0x05,
    RX8025_YR                   = 0x06,
    RX8025_RAM                  = 0x07,
    RX8025_ALARM_MIN            = 0x08,
    RX8025_ALARM_HOUR           = 0x09,
    RX8025_ALARM_WEEK_DAY       = 0x0A,
    RX8025_TIMER_CNT_0          = 0x0B,
    RX8025_TIMER_CNT_1          = 0x0C,
    RX8025_EXT_REG              = 0x0D,
    RX8025_FLAG_REG             = 0x0D,
    RX8025_CTL_REG              = 0x0F,
} em_ex8025_data_address_t;

extern st_time_struct gstRTC, gstRtcBak;

void RX8025_Init(void);
void RX8025_GetTime(void);
void RX8025_SetTime(u16 uwYear, u8 ubMonth, u8 ubDate, u8 ubWeek, u8 ubHour, u8 ubMin, u8 ubSec);
u8  judgeWeek(u16 uwYear, u8 ubMonth, u8 ubDay);

#endif
