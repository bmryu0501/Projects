# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'mouseTraining.ui'
##
## Created by: Qt User Interface Compiler version 6.5.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QFrame, QGridLayout, QLabel,
    QPushButton, QSizePolicy, QWidget)

class Ui_Form(object):
    def setupUi(self, Form):
        if not Form.objectName():
            Form.setObjectName(u"Form")
        Form.resize(586, 392)
        self.gridLayoutWidget = QWidget(Form)
        self.gridLayoutWidget.setObjectName(u"gridLayoutWidget")
        self.gridLayoutWidget.setGeometry(QRect(10, 10, 571, 361))
        self.gridLayout = QGridLayout(self.gridLayoutWidget)
        self.gridLayout.setObjectName(u"gridLayout")
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.changeNameButton = QPushButton(self.gridLayoutWidget)
        self.changeNameButton.setObjectName(u"changeNameButton")

        self.gridLayout.addWidget(self.changeNameButton, 2, 0, 1, 1)

        self.changeColorButton = QPushButton(self.gridLayoutWidget)
        self.changeColorButton.setObjectName(u"changeColorButton")

        self.gridLayout.addWidget(self.changeColorButton, 2, 1, 1, 1)

        self.buttonReset = QPushButton(self.gridLayoutWidget)
        self.buttonReset.setObjectName(u"buttonReset")

        self.gridLayout.addWidget(self.buttonReset, 2, 2, 1, 1)

        self.frame = QFrame(self.gridLayoutWidget)
        self.frame.setObjectName(u"frame")
        self.frame.setStyleSheet(u"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 0, 0, 255), stop:0.166 rgba(255, 255, 0, 255), stop:0.333 rgba(0, 255, 0, 255), stop:0.5 rgba(0, 255, 255, 255), stop:0.666 rgba(0, 0, 255, 255), stop:0.833 rgba(255, 0, 255, 255), stop:1 rgba(255, 0, 0, 255));")
        self.frame.setFrameShape(QFrame.StyledPanel)
        self.frame.setFrameShadow(QFrame.Raised)
        self.name = QLabel(self.frame)
        self.name.setObjectName(u"name")
        self.name.setGeometry(QRect(250, 160, 81, 20))
        self.name.setScaledContents(True)
        self.name.setAlignment(Qt.AlignCenter)
        self.name.setWordWrap(False)
        self.labelScore = QLabel(self.frame)
        self.labelScore.setObjectName(u"labelScore")
        self.labelScore.setGeometry(QRect(480, 10, 71, 21))
        self.labelScore.setStyleSheet(u"background-color: rgb(255, 255, 255);")

        self.gridLayout.addWidget(self.frame, 1, 0, 1, 3)


        self.retranslateUi(Form)
        self.changeNameButton.clicked.connect(Form.showDiagram)
        self.changeColorButton.clicked.connect(Form.showDiagram)
        self.buttonReset.clicked.connect(Form.reset)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"Form", None))
        self.changeNameButton.setText(QCoreApplication.translate("Form", u"Change Name", None))
        self.changeColorButton.setText(QCoreApplication.translate("Form", u"Change Color", None))
        self.buttonReset.setText(QCoreApplication.translate("Form", u"Reset", None))
        self.name.setText(QCoreApplication.translate("Form", u"Don't click me", None))
        self.labelScore.setText(QCoreApplication.translate("Form", u"Score: 0", None))
    # retranslateUi

