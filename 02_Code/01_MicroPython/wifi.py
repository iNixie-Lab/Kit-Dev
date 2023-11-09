import network

# Wi-Fi info
ssid = "XXXXXXXX"
pswd = "XXXXXXXX"

def do_connect():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        print("connecting to network...")
        wlan.connect(ssid, pswd)
        while not wlan.isconnected():
            pass
    print("network config:", wlan.ifconfig())
