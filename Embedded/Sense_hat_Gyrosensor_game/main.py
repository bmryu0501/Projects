from sense_hat import SenseHat, ACTION_PRESSED, ACTION_RELEASED
from signal import pause
from path_finder import showPath, getPath

from time import sleep

sense=SenseHat()
X = [255, 0, 0]
O = [0, 0, 0]
P = [0, 255, 0]
"""
map = [
    O, X, O, O, O, O, O, O,
    O, X, X, X, X, O, X, O,
    O, O, O, O, O, O, O, O,
    O, X, X, X, X, O, X, O,
    O, O, X, O, O, O, X, O,
    O, O, X, O, X, X, X, O,
    O, X, X, O, O, O, O, O,
    O, O, O, O, X, X, X, O]
"""
map = [
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 1, 0]
y=0
x=0

goal = (7, 7)
def win():
    sense.clear()
    blue = [(0, 0, 255) for i in range(64)]
    sense.set_pixels(blue)
    sleep(1)
    sense.clear()
    sleep(1)
    sense.set_pixels(blue)
    sleep(1)
    sense.clear()
    
    exit(0)

def update(map):
    global y,x
    sense.clear()
    newMap = map.copy()
    for i in range(8):
        for j in range(8):
            if newMap[i*8+j] == 0: newMap[i*8+j] = O
            elif newMap[i*8+j] == 1: newMap[i*8+j] = X
            elif newMap[i*8+j] == 9: newMap[i*8+j] = P
    sense.set_pixels(newMap)
    sense.set_pixel(x,y,255,255,255)
    if(y == goal[0] and x == goal[1]): win()
    
def check(row, col):
    global y,x
    a=0
    b=0
    
    r=0 # 0 right 1 left 
    c=0 # 0 up 1 down
    skip=0 # row skip
    if 0<=col<=20 or 340<=col<=360:
        skip=1 # col skip
    
    if skip==1:
        if 181<row:
            a=360-row
            r=1
        elif 20<row:
            a=row
            r=-1
    else :
        if 181<col:
            b=360-col
            c=-1
        elif 20<col:
            b=col
            c=1
            
    if a>b : x+=r
    else : y+=c
        
        
update(map)
while True:
    sleep(0.1)
  
    ori= sense.get_orientation_degrees()

    row=ori["pitch"]
    col=ori["roll"]
    print("row :",row," col : ",col)

    # sleep(0.01)
    if (0<=row<=20 or 340<=row<=360) and (0<=col<=20 or 340<=col<=360): continue

    print("test")
    temp_y=y
    temp_x=x
    check(row,col)
    if y<0 or y>7 or x<0 or x>7:
        y=temp_y
        x=temp_x
    if map[y*8+x]==1:
        y=temp_y
        x=temp_x
        
    newMap = showPath(map, y, x)
        
    update(newMap)
    print()