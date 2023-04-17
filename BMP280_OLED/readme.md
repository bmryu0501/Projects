# 온도계 시계
BMP280 센서와 OLED를 활용하여 현재 온도와 시간을 출력하는 시계

### 데모 영상
![demo](./demo/demo.mp4)

### Code
```python
#!/usr/bin/python
# -*- coding:utf-8 -*-

import sys
import os
picdir = os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'pic')
libdir = os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'lib')
if os.path.exists(libdir):
    sys.path.append(libdir)

import logging    
import time
from time import sleep
import traceback
from waveshare_OLED import OLED_0in96
from PIL import Image,ImageDraw,ImageFont
logging.basicConfig(level=logging.DEBUG)

#time
from datetime import datetime

#bmp280
from bmp280 import BMP280
from smbus import SMBus
bus = SMBus(1)
bmp280 = BMP280(i2c_dev=bus)

try:
    disp = OLED_0in96.OLED_0in96()

    logging.info("\r 0.96inch OLED ")
    # Initialize library.
    disp.Init()
    # Clear display.
    logging.info("clear display")
    disp.clear()

    # Create blank image for drawing.
    image1 = Image.new('1', (disp.width, disp.height), "WHITE")
    draw = ImageDraw.Draw(image1)
    font1 = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 18)
    font2 = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 24)

    while True:
        draw.rectangle((0, 0, 127, 63), outline=255, fill=255)
        temperature = bmp280.get_temperature()
        draw.text((23, 20), f'{temperature:2.1f} *C', font=font2, fill=0)
        image11 = image1.rotate(180)
        disp.ShowImage(disp.getbuffer(image11))
        sleep(5)
        
        for i in range(5) :
            draw.rectangle((0, 0, 127, 63), outline=255, fill=255)
            now = datetime.now()
            draw.text((23, 20), now.strftime('%H:%M:%S'), font=font2, fill=0)
            image11 = image1.rotate(180)
            disp.ShowImage(disp.getbuffer(image11))
            sleep(1)

    logging.info("ending...")
    OLED_0in96.config.module_exit()
    
except IOError as e:
    logging.info(e)
    
except KeyboardInterrupt:    
    logging.info("ctrl + c:")
    OLED_0in96.config.module_exit()
    exit()
```