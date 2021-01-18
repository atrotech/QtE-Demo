
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
HEADERS += lib/common.h lib/gpio.h mainwidget.h VideoWidget.h TestViewerWidget.h ReportWidget.h 
SOURCES += lib/common.cpp lib/gpio.cpp main.cpp mainwidget.cpp VideoWidget.cpp TestViewerWidget.cpp ReportWidget.cpp
RESOURCES += main.qrc
