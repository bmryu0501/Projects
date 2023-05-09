from PySide6.QtWidgets import *
from myUI import Ui_MainWindow
from mouseTraining import Ui_Form
from PySide6.QtCore import *
import random

''' myUI
class MyApp(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

    def up(self):
        print("UP")

    def down(self):
        print("DOWN")

app = QApplication()
win = MyApp()
win.show()
app.exec()
'''


class MyApp(QWidget, Ui_Form):
    score = 0

    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.main()

    def main(self):
        self.timer = QBasicTimer()
        self.timer.start(600, self)

    def timerEvent(self, e):
        x = random.randint(0, self.frame.size().width() - self.name.width())
        y = random.randint(0, self.frame.size().height() - self.name.height())
        self.name.move(x, y)

    def changeColor(self):
        color = QColorDialog.getColor()
        if(color.isValid()):
            self.name.setStyleSheet("background-color:%s" %color.name())

    def changeName(self):
        name, ok = QInputDialog.getText(self, "이름 입력", "너의 이름은?")
        if ok:
            self.name.setText(name)

    def reset(self):
        self.score = 0
        self.labelScore.setText("Score: " + str(self.score))

    def showDiagram(self):
        sender = self.sender()
        if sender.text() == "Change Name":
            self.changeName()
        elif sender.text() == "Change Color":
            self.changeColor()

    def mousePressEvent(self, e):
        x = e.x()
        y = e.y()

        tx = self.name.x()
        ty = self.name.y()

        if tx <= x <= tx + self.name.width():
            if ty <= y <= ty + self.name.height():
                self.score += 1
                self.labelScore.setText("Score: " + str(self.score))

                # msg = QMessageBox()
                # msg.setText("성공")
                # msg.exec()

app = QApplication()
win = MyApp()

win.show()
app.exec()