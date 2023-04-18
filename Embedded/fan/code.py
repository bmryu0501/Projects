from gpiozero import LED, Button
from gpiozero import PWMLED
from signal import pause
from time import sleep

step=(LED(26),LED(19),LED(13))
but=(Button(21),Button(20),Button(16))
motor=PWMLED(2)
s=(0,0.3,0.6,0.9)
speed=0
start=0
def led():
    global speed
    for i in range(3):
        if i<speed :
            step[i].on()
        else : step[i].off()

def speedUp():
    global speed, s, start
    if not start : return
    if speed+1>3: speed=3
    else : speed+=1
    motor.value=s[speed]
    print("current speed : ",speed)
    led()
    
def slow():
    global speed, s, start
    if not start : return
    if speed-1<1 : speed=1
    else : speed-=1
    motor.value=s[speed]
    print("current speed : ",speed)
    led()
    
def power():
    global speed, s, start
    if start :
        speed=0
        start=0
    else :
        speed=1
        start=1
    motor.value=s[speed]
    led()
    
but[0].when_pressed=speedUp
but[1].when_pressed=slow
but[2].when_pressed=power