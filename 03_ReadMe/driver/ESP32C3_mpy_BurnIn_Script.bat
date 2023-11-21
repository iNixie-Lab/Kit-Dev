@echo off
reg query "HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM"
echo ----------------------Select serial port num----------------------------------
set /p comno=
echo ----------------------The port of you select: COM%comno%----------------------
echo ----------------------Ready to erase ESP32-C3---------------------------------
esptool --chip ESP32-C3 --port COM%comno% erase_flash
echo ----------------------Erase done, ready to burn in!---------------------------
esptool --chip ESP32-C3 --port COM%comno% --baud 460800 write_flash -z 0x00 firmware.bin
echo ----------------------Firmware info: -----------------------------------------
esptool --chip esp32-c3 --port COM%comno% flash_id
echo ----------------------Process done, press any key to exit!--------------------
pause