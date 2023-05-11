# 라즈베리파이 카메라와 OpenCV

라즈베리파이에 카메라를 설치하고, OpenCV 라이브러리를 사용하여 영상을 띄워봤다.

# 작동 설명
## 사용된 기술 스택
- Python
- Pyside6
- RaspberryPi
- OpenCV

## 구성
1. cv2_camera_ui.py 에서 GUI를 구성한다.
    - picOrigin: 카메라로 들어온 Original 영상을 띄워준다.
    - picMode: Original 영상에 Mode가 적용된 영상을 띄워준다.
    - Play 버튼: 영상을 시작한다.
    - Mode 버튼: 모드가 바뀐다. (총 3가지 모드로, Blur, Gray, Canny가 있다.)

2. lighting.py 에서 동작을 실행한다.
    - 1 에서 만들어진 GUI창을 띄워준다.
    - 쓰레드를 만들어 0.1초 마다 영상을 받아 Mode를 적용하고 영상을 띄워준다.

# 데모
![demo](./demo/demo.gif)