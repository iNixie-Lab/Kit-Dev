#include "WiFi.h"
#include "Network.h"

const char *SSID = "XXXXXXXX";                  // 需要连接到的WiFi名
const char *PSWD = "XXXXXXXX";                  // 连接的WiFi密码

void Network_Init(void)
{
    COMMON_SERIAL.print("WIFI Mode: ");
    COMMON_SERIAL.println(WiFi.getMode());      // 显示当前WIFI的模式
    COMMON_SERIAL.print("Connecting to ");
    COMMON_SERIAL.println(SSID);

    WiFi.begin(SSID, PSWD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        COMMON_SERIAL.print(".");
    }

    COMMON_SERIAL.println("");
    COMMON_SERIAL.println("WiFi connected.");   // WIFI 已经连接
    COMMON_SERIAL.print("IP address: ");
    COMMON_SERIAL.println(WiFi.localIP());      // 显示连接WIFI后的IP地址
    COMMON_SERIAL.print("RSSI: ");
    COMMON_SERIAL.println(WiFi.RSSI());
    COMMON_SERIAL.print("WIFI Mode: ");
    COMMON_SERIAL.println(WiFi.getMode());      // 显示当前WIFI的模式
}
