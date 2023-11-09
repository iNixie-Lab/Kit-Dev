from machine import Pin

NUM_PIN_MAP = [10, 4, 5, 19, 6, 18, 7, 3, 9, 0]
ALL_NUM = 10
PIN_OBJ = []
show_num = 0

def pin_init():
    for i in range(ALL_NUM):
        PIN_OBJ.append(Pin(NUM_PIN_MAP[i], Pin.OUT))

def set_num(n):
    for i in range(ALL_NUM):
        if n == i:
            PIN_OBJ[i].value(1)
        else:
            PIN_OBJ[i].value(0)

def play_num():
    global show_num
    set_num(show_num)

    show_num += 1
    if show_num > 9:
        show_num = 0
