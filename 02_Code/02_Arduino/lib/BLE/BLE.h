#ifndef __USER_TASK_H__
#define __USER_TASK_H__

#include "Common.h"

#define SERVICE_UUID                    "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX          "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX          "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

typedef struct
{
    u8  ubTxBuffer[20];                                 // BLE发送的Buffer，安卓端一次最多20个Byte
    u8  ubRxBuffer[20];                                 // BLE接受的Buffer
    u8  ubBleDelayCnt;                                  // BLE延迟发送的帧数

    u8  ubTxLength                      : 6;            // 发送的长度
    u8                                  : 2;
    u8  ubRxLength                      : 6;            // 接受的长度
    u8  boBleConnectStatue              : 1;            // 当前的BLE连接状态
    u8  boBleConnectStaBak              : 1;            // 上一次BLE的连接状态
} st_ble_info_t;

extern st_ble_info_t gstBleInfo;
extern void BLE_ShowRxInfo();
extern void Task_BLE(void *User_Task_BLE);

#endif
