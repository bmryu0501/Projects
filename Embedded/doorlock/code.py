from gpiozero import AngularServo
from gpiozero import LED, Button
from time import sleep
from signal import pause

LED_GREEN = LED(19)
LED_RED = LED(13)

password = '1010'
input_password = ''

btn0 = Button(21)
btn1 = Button(20)

servo = AngularServo(2, min_angle=0, max_angle=90)
servo.angle = 0

def correct():
    LED_GREEN.on()
    servo.angle = 90
    sleep(1)
    LED_GREEN.off()
    servo.angle = 0
    
def wrong():
    LED_RED.on()
    sleep(1)
    LED_RED.off()

def check():
    print('checking...')
    global password, input_password
    if password == input_password:
        correct()
    else:
        wrong()
    input_password = ''

def press0():
    global input_password
    input_password = input_password + '0'
    print("input now: ", input_password)
    if len(input_password) == 4:
        check()

def press1():
    global input_password
    input_password = input_password + '1'
    print("input now: ", input_password)
    if len(input_password) == 4:
        check()
    
btn0.when_pressed = press0
btn1.when_pressed = press1

pause()