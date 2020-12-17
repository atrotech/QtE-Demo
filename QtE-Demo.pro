####### tft28lcd.h###############################################################
# Automatically generated by qmake (2.01a) Fri Jan 1 10:13:19 2016
######################################################################

TEMPLATE = app
TARGET = QtE-Demo
CONFIG += c++11
DEPENDPATH += .
QT += widgets
DESTDIR = $$PWD
INCLUDEPATH += /usr/local/include/opencv4 \
    ./resources


# -lopencv_cudaimgproc -lopencv_cudaobjdetect

LIBS += -L/usr/local/lib -I/usr/local/include/opencv -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_objdetect -lopencv_video -lopencv_videoio -lopencv_videostab

# Input
HEADERS += mainwidget.h lib/gpio.h lib/common.h
SOURCES += main.cpp mainwidget.cpp lib/gpio.c lib/common.c
RESOURCES += main.qrc
