# Servo 모터를 이용하여 도어락 만들기
Servo 모터를 이용해 도어락을 만든다.

- 0과 1로 구성된 비밀번호 네 자리를 누르면 잠금장치가 풀린다.
- 버튼 2개
    - 버튼1: 숫자 0
    - 버튼2: 숫자1

- 네 자리 비밀번호를 정확히 눌렀을 때
    - 녹색 LED가 켜지며, Servo Motor가 동작한다.
    - 1초 후 Servo Motor가 제자리로 돌아오며 녹색 LED가 꺼진다.

- 네 자리 비밀번호를 모두 눌렀지만, 비밀번호가 틀렸을 때
    - 빨강 LED가 켜지며, 1초 후 빨강 LED가 꺼진다.

## 데모 영상
![demo](./demo/demo.gif)

## 코드
```python
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
```