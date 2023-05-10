# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'lighting.ui'
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
from PySide2.QtWidgets import (QAbstractItemView, QApplication, QHeaderView, QMainWindow,
    QMenuBar, QPushButton, QSizePolicy, QSlider,
    QStatusBar, QTableWidget, QTableWidgetItem, QVBoxLayout,
    QWidget)

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(320, 460)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.verticalLayoutWidget = QWidget(self.centralwidget)
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayoutWidget.setGeometry(QRect(10, 10, 301, 391))
        self.verticalLayout = QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.table = QTableWidget(self.verticalLayoutWidget)
        if (self.table.columnCount() < 8):
            self.table.setColumnCount(8)
        if (self.table.rowCount() < 8):
            self.table.setRowCount(8)
        self.table.setObjectName(u"table")
        self.table.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.table.setSelectionMode(QAbstractItemView.NoSelection)
        self.table.setShowGrid(True)
        self.table.setRowCount(8)
        self.table.setColumnCount(8)
        self.table.horizontalHeader().setVisible(False)
        self.table.horizontalHeader().setDefaultSectionSize(36)
        self.table.verticalHeader().setVisible(False)

        self.verticalLayout.addWidget(self.table)

        self.sliderR = QSlider(self.verticalLayoutWidget)
        self.sliderR.setObjectName(u"sliderR")
        self.sliderR.setMaximum(255)
        self.sliderR.setValue(128)
        self.sliderR.setOrientation(Qt.Horizontal)

        self.verticalLayout.addWidget(self.sliderR)

        self.sliderG = QSlider(self.verticalLayoutWidget)
        self.sliderG.setObjectName(u"sliderG")
        self.sliderG.setMaximum(255)
        self.sliderG.setValue(128)
        self.sliderG.setOrientation(Qt.Horizontal)

        self.verticalLayout.addWidget(self.sliderG)

        self.sliderB = QSlider(self.verticalLayoutWidget)
        self.sliderB.setObjectName(u"sliderB")
        self.sliderB.setMaximum(255)
        self.sliderB.setValue(128)
        self.sliderB.setOrientation(Qt.Horizontal)

        self.verticalLayout.addWidget(self.sliderB)

        self.buttonFlash = QPushButton(self.verticalLayoutWidget)
        self.buttonFlash.setObjectName(u"buttonFlash")

        self.verticalLayout.addWidget(self.buttonFlash)

        self.buttonClear = QPushButton(self.verticalLayoutWidget)
        self.buttonClear.setObjectName(u"buttonClear")

        self.verticalLayout.addWidget(self.buttonClear)

        #MainWindow.setCentralWidget(self.centralwidget)
        #self.menubar = QMenuBar(MainWindow)
        #self.menubar.setObjectName(u"menubar")
        #self.menubar.setGeometry(QRect(0, 0, 320, 22))
        #MainWindow.setMenuBar(self.menubar)
        #self.statusbar = QStatusBar(MainWindow)
        #self.statusbar.setObjectName(u"statusbar")
        #MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        self.buttonFlash.clicked.connect(MainWindow.flash)
        self.buttonClear.clicked.connect(MainWindow.clear)
        self.sliderR.valueChanged.connect(MainWindow.rslide)
        self.sliderG.valueChanged.connect(MainWindow.gslide)
        self.sliderB.valueChanged.connect(MainWindow.bslide)
        self.table.cellEntered.connect(MainWindow.click)
        self.table.cellPressed.connect(MainWindow.click)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.buttonFlash.setText(QCoreApplication.translate("MainWindow", u"Flash", None))
        self.buttonClear.setText(QCoreApplication.translate("MainWindow", u"Clear", None))
    # retranslateUi

