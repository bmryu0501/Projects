from PySide2.QtWidgets import *
from lighting_ui import Ui_MainWindow
from sense_emu import SenseHat
from time import sleep


class myApp(QWidget, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        Ui_MainWindow.setupUi(self, self)
        self.main()

    def main(self):
        self.sense = SenseHat()

    def flash(self):
        for x in range(8):
            for y in range(8):
                self.sense.set_pixel(x, 7-y, self.sliderR.value(), self.sliderG.value(), self.sliderB.value())

    def clear(self):
        self.sense.clear()

    def click(self, x, y):
        self.sense.set_pixel(x, 7-y, self.sliderR.value(), self.sliderG.value(), self.sliderB.value())

    def rslide(self, val):
        pass

    def gslide(self, val):
        pass

    def bslide(selfself, val):
        pass


app = QApplication()
win = myApp()
win.show()
app.exec_()
