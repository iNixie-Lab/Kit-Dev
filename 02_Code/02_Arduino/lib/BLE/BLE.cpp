#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "Network.h"
#include "BLE2902.h"
#include "BLE.h"

BLEServer *pServer = NULL;
BLECharacteristic *pTxCharacteristic = NULL;

st_ble_info_t gstBleInfo;

// ***********************************************************************
//	@ 函数名称： BLEServerCallbacks()
//	@ 函数功能： BLE服务的回调函数
//	@ 函数输入： 无
//	@ 函数输出： 无
//	@ 注意事项： 无
// ***********************************************************************
class MyServerCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)
    {
        gstBleInfo.boBleConnectStatue = TRUE;
    }

    void onDisconnect(BLEServer *pServer)
    {
        gstBleInfo.boBleConnectStatue = FALSE;
    }
};

// ***********************************************************************
//	@ 函数名称： BLECharacteristicCallbacks()
//	@ 函数功能： BLE服务的通信函数
//	@ 函数输入： 无
//	@ 函数输出： 无
//	@ 函数调用： BLE_ShowRxInfo()
//	@ 注意事项： 无
// ***********************************************************************
class MyCallbacks : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic)
    {
        std::string gstrRxValue = pCharacteristic->getValue();
        gstBleInfo.ubRxLength = gstrRxValue.length();

        if (gstBleInfo.ubRxLength > CONST_0)
        {
            for (u8 i = 0; i < gstBleInfo.ubRxLength; i++)
            {
                gstBleInfo.ubRxBuffer[i] = gstrRxValue[i];
            }
            BLE_ShowRxInfo();
        }
    }
};

void BLE_ShowRxInfo(void)
{
    COMMON_SERIAL.printf("Rx len: %d, buffer: ", gstBleInfo.ubRxLength);
    for (u8 i = 0; i < gstBleInfo.ubRxLength; i++)
    {
        COMMON_SERIAL.printf("0x%02x, ", gstBleInfo.ubRxBuffer[i]);
    }
    COMMON_SERIAL.println("");
}

// ***********************************************************************
//	@ 函数名称： BLE_Init()
//	@ 函数功能： BLE服务的初始化
//	@ 函数输入： 无
//	@ 函数输出： 无
//	@ 注意事项： 无
// ***********************************************************************
void BLE_Init()
{
    MemSetU8((u8 *)&gstBleInfo, 0x00, sizeof(gstBleInfo));

    BLEDevice::init("iNixie-Kit");

    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    BLEService *pService = pServer->createService(SERVICE_UUID);

    pTxCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID_TX,
        BLECharacteristic::PROPERTY_NOTIFY);

    pTxCharacteristic->addDescriptor(new BLE2902());

    BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID_RX,
        BLECharacteristic::PROPERTY_WRITE);

    pRxCharacteristic->setCallbacks(new MyCallbacks());

    // Start the service
    pService->start();

    // Start advertising
    pServer->getAdvertising()->start();
    COMMON_SERIAL.println("Waiting a client connection to notify...");
}

// ***********************************************************************
//	@ 函数名称： User_Task_BLE(void *User_Task_BLE)
//	@ 函数功能： BLE通信的线程函数
//	@ 函数输入： *User_Task_BLE(固定的形式)
//	@ 函数输出： 无
//	@ 注意事项： 无
// ***********************************************************************
void Task_BLE(void *User_Task_BLE)
{
    BLE_Init();
    while (1)
    {
        // gstBleInfo.boBleConnectStatue  已连接
        if (gstBleInfo.boBleConnectStatue)
        {
            pTxCharacteristic->setValue(gstBleInfo.ubTxBuffer, gstBleInfo.ubTxLength);
            pTxCharacteristic->notify();                // 广播
            vTaskDelay(CONST_200 / portTICK_PERIOD_MS); // 如果有太多包要发送，蓝牙会堵塞
        }

        // disconnecting    断连
        if (!gstBleInfo.boBleConnectStatue && gstBleInfo.boBleConnectStaBak)
        {
            COMMON_SERIAL.printf("Start broadcast...\r\n");
            vTaskDelay(CONST_200 / portTICK_PERIOD_MS); // 留时间给蓝牙缓冲
            pServer->startAdvertising();                // 重新广播
            gstBleInfo.boBleConnectStaBak = gstBleInfo.boBleConnectStatue;
        }

        // connecting       正在连接
        if (gstBleInfo.boBleConnectStatue && !gstBleInfo.boBleConnectStaBak)
        {
            // do stuff here on connecting
            COMMON_SERIAL.printf("Ble connected!\r\n");
            gstBleInfo.boBleConnectStaBak = gstBleInfo.boBleConnectStatue;
        }
        delay(100);
    }
}
