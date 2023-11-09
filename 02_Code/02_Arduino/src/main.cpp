#include "BLE.h"
#include "Proj.h"
#include "RX8025.h"
#include "Network.h"
#include "iNixieKit.h"

void setup()
{
	COMMON_SERIAL.begin(115200);
	iNixie_Init();
	RX8025_Init();
	Network_Init();

	xTaskCreatePinnedToCore(Task_iNixie,    "Task_iNixie",	4096, NULL, 3, NULL, 0);
	xTaskCreatePinnedToCore(Task_Proj,  	"Task_iNixie",	4096, NULL, 2, NULL, 0);
	xTaskCreatePinnedToCore(Task_BLE,   	"Task_ble",		4096, NULL, 1, NULL, 0);
}

void loop()
{
	delay(1000);
}
