#include "Wire.h"
#include "RX8025.h"

st_time_struct gstRTC, gstRtcBak;                           // 定义当前的时间
static u8 gpubRX8025Buffer[CONST_7];                        // 建立一个全局的Buffer

// ***********************************************************************
// @ 函数名称： setRtcTime
// @ 函数功能： 设置芯片的时间
// @ 函数输入： 无
// @ 函数输出： 无
// @ 注意事项： 星期日： 0， 星期一-星期六：1-6
// ***********************************************************************
void RX8025_SetTime(u16 uwYear, u8 ubMonth, u8 ubDate, u8 ubWeek, u8 ubHour, u8 ubMin, u8 ubSec)
{
    if (uwYear < 2000)                                      // 输入的值不正确直接退出
    {
        RX8025_PRINTF("RTC Year error!!!\r\n");
        return;
    }

    Wire.beginTransmission(RX8025_ADDR);
    Wire.write(0x00);
    Wire.write(Bin2Bcd(ubSec));
    Wire.write(Bin2Bcd(ubMin));
    Wire.write(Bin2Bcd(ubHour));
    Wire.write(Bin2Bcd(ubWeek));
    Wire.write(Bin2Bcd(ubDate));
    Wire.write(Bin2Bcd(ubMonth));
    Wire.write(Bin2Bcd(uwYear - 2000));
    Wire.endTransmission();

    Wire.beginTransmission(RX8025_ADDR);                    // clear power on reset flag, set to 24hr format
    Wire.write(0x1F);
    Wire.write(0x00);
    Wire.endTransmission();
}

// ***********************************************************************
// @ 函数名称： getRtcTime
// @ 函数功能： 读取芯片的时间
// @ 函数输入： 无
// @ 函数输出： 无
// @ 注意事项： 无
// ***********************************************************************
void RX8025_GetTime(void)
{
    u8 i = 0;
    Wire.beginTransmission(RX8025_ADDR);

    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(RX8025_ADDR, 7);

    while (Wire.available())
    {
        gpubRX8025Buffer[i++] = Wire.read();
    }
    Wire.endTransmission();

    gstRTC.uwYear   = Bcd2Bin(gpubRX8025Buffer[6] & 0xff) + 2000;
    gstRTC.ubMonth  = Bcd2Bin(gpubRX8025Buffer[5] & 0x1f);
    gstRTC.ubDay    = Bcd2Bin(gpubRX8025Buffer[4] & 0x3f);
    gstRTC.ubWeek   = Bcd2Bin(gpubRX8025Buffer[3] & 0x07);
    gstRTC.ubHour   = Bcd2Bin(gpubRX8025Buffer[2] & 0x3f);
    gstRTC.ubMin    = Bcd2Bin(gpubRX8025Buffer[1] & 0x7f);
    gstRTC.ubSec    = Bcd2Bin(gpubRX8025Buffer[0] & 0x7f);
}

// ***********************************************************************
// @ 函数名称： RX8025_init
// @ 函数功能： 时间芯片的初始化
// @ 函数输入： 无
// @ 函数输出： 无
// @ 注意事项： 无
// ***********************************************************************
void RX8025_Init(void)
{
    Wire.begin(RX8025_IO_SDA, RX8025_IO_SCL);
    Wire.beginTransmission(RX8025_ADDR);        // clear power on reset flag, set to 24hr format

    Wire.write(0xe0);
    Wire.write(0x20);
    Wire.write(0x00);
    Wire.endTransmission();

    delay(1);
    RX8025_GetTime();

    // 如果是错误的时间，就给一个默认的时间
    if( (gstRTC.ubMonth > CONST_12  ) ||
        (gstRTC.ubDay   > CONST_31  ) ||
        (gstRTC.ubWeek  > CONST_7   ) ||
        (gstRTC.ubHour  > CONST_23  ) ||
        (gstRTC.ubMin   > CONST_59  ) ||
        (gstRTC.ubSec   > CONST_59  ) )
    {
        delay(1);
        RX8025_SetTime(2020, 8, 19, 3, 0, 0, 0);
    }
    // RX8025_SetTime(2022, 10, 27, 4, 1, 05, 30);                      // Set time once for debug

    delay(1);
    RX8025_GetTime();                                                   // Read time again
    MemCpyU8((u8 *)(&gstRTC), (u8 *)(&gstRtcBak), CONST_8);
}

// ***********************************************************************
//  @ 函数名称： judgeWeek(int year,int month, int day)
//  @ 函数功能： 利用日期获取周几的信息
//  @ 函数输入： 年，月，日
//  @ 函数输出： 周日：0
//  @ 注意事项： 无
// ***********************************************************************
u8 judgeWeek(u16 uwYear, u8 ubMonth, u8 ubDay)
{
    if (ubMonth == 1 || ubMonth == 2)
    {
        ubMonth += 12;
        uwYear--;
    }
    return ((ubDay + (ubMonth << 1) + 3 * (ubMonth + 1) / 5 + uwYear + (uwYear >> 2) - uwYear / 100 + uwYear / 400)) % 7 + 1;
}
