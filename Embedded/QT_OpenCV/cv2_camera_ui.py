# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'cv2_camera.ui'
##
## Created by: Qt User Interface Compiler version 6.5.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide2.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide2.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide2.QtWidgets import (QApplication, QGridLayout, QLabel, QMainWindow,
    QMenuBar, QPushButton, QSizePolicy, QStatusBar,
    QWidget)

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(1032, 804)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.gridLayoutWidget = QWidget(self.centralwidget)
        self.gridLayoutWidget.setObjectName(u"gridLayoutWidget")
        self.gridLayoutWidget.setGeometry(QRect(10, 10, 1011, 741))
        self.gridLayout = QGridLayout(self.gridLayoutWidget)
        self.gridLayout.setObjectName(u"gridLayout")
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.picOrigin = QLabel(self.gridLayoutWidget)
        self.picOrigin.setObjectName(u"picOrigin")
        self.picOrigin.setStyleSheet(u"background-color: rgb(0, 170, 255);")

        self.gridLayout.addWidget(self.picOrigin, 0, 0, 1, 1)

        self.picMode = QLabel(self.gridLayoutWidget)
        self.picMode.setObjectName(u"picMode")
        self.picMode.setStyleSheet(u"background-color: rgb(255, 0, 127);")

        self.gridLayout.addWidget(self.picMode, 0, 1, 1, 1)

        self.btnPlay = QPushButton(self.gridLayoutWidget)
        self.btnPlay.setObjectName(u"btnPlay")

        self.gridLayout.addWidget(self.btnPlay, 1, 0, 1, 2)

        self.btnMode = QPushButton(self.gridLayoutWidget)
        self.btnMode.setObjectName(u"btnMode")

        self.gridLayout.addWidget(self.btnMode, 2, 0, 1, 2)

        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 1032, 22))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        self.btnPlay.clicked.connect(MainWindow.play)
        self.btnMode.clicked.connect(MainWindow.mode)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.picOrigin.setText("")
        self.picMode.setText("")
        self.btnPlay.setText(QCoreApplication.translate("MainWindow", u"Play", None))
        self.btnMode.setText(QCoreApplication.translate("MainWindow", u"Mode", None))
    # retranslateUi

