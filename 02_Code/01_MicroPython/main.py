import ble
import bluetooth
import utime
import inixie_kit
import wifi
from rx8025t import RX8025T
from machine import SoftI2C, Pin

print("Welecome to iNixieLab")
wifi.do_connect()
inixie_kit.pin_init()
rr = RX8025T(SoftI2C(scl=Pin(2),sda=Pin(8)))

b = bluetooth.BLE()                     # create a new object
p = ble.BLESimplePeripheral(b)          # import class
aa=b.config('mac')                      # read mac addr

def on_rx(v):                           # rx data
    print(v)
    print("Receive_data:", str(v))
p.on_write(on_rx)

while 1:
    inixie_kit.play_num()
    if p.is_connected():
        p.notify('ble data form mpy')   # notify info
    print(rr.datetime())
    utime.sleep_ms(1000)
