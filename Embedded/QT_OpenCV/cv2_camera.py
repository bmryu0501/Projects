from PySide2.QtWidgets import *
from cv2_camera_ui import *
from PySide2.QtGui import *
from PySide2.QtCore import *
import cv2
from time import *

convertMode = 0

class MyThread(QThread):
    mySignal = Signal(QPixmap, QPixmap)

    def __init__(self):
        super().__init__()
        self.cam = cv2.VideoCapture(0)
        self.cam.set(3, 480)
        self.cam.set(4, 320)

    def run(self):
        while True:
            ret, self.img = self.cam.read()
            if ret:
                self.printImage(self.img)
            sleep(0.1)

    def printImage(self, imgBGR):
        imgRGB = cv2.cvtColor(imgBGR, cv2.COLOR_BGR2RGB)
        h, w, byte = imgRGB.shape
        imgOrigin = QImage(imgRGB, w, h, byte*w, QImage.Format_RGB888)
        pix_imgOrigin = QPixmap(imgOrigin)

        imgBlur = cv2.blur(imgBGR, (30, 30))
        imgGray = cv2.cvtColor(imgBGR, cv2.COLOR_BGR2GRAY)
        imgCanny = cv2.Canny(imgGray, 50, 100)

        if convertMode == 2:
            imgMode = QImage(imgCanny, w, h, imgCanny.strides[0], QImage.Format_Grayscale8)
        elif convertMode == 0:
            imgMode = QImage(imgBlur, w, h, byte*w, QImage.Format_RGB888)
        elif convertMode == 1:
            imgMode = QImage(imgGray, w, h, imgCanny.strides[0], QImage.Format_Grayscale8)

        pix_imgMode = QPixmap(imgMode)

        self.mySignal.emit(pix_imgOrigin, pix_imgMode)


class MyApp(QMainWindow, Ui_MainWindow):

    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.th = MyThread()
        self.main()

    def main(self):
        self.th.mySignal.connect(self.setImage)

    def setImage(self, imgOrigin, imgMode):
        self.picOrigin.setPixmap(imgOrigin)
        self.picMode.setPixmap(imgMode)

    def mode(self):
        global convertMode
        convertMode = (convertMode + 1) % 3

    def play(self):
        self.th.start()

    def closeEvent(self, envent):
        self.th.terminate()
        self.th.wait(3000)
        self.close()

    def printImage(self, imgBGR):
        imgRGB = cv2.cvtColor(imgBGR, cv2.COLOR_BGR2RGB)
        h, w, byte = imgRGB.shape
        img = QImage(imgRGB, w, h, byte*w, QImage.Format_RGB888)
        pic.setPixmap(QPixmap(img))

app = QApplication()
win = MyApp()
win.show()
app.exec_()
