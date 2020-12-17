
#ifndef WIDGET_H
#define WIDGET_H
#include <QtCore/QtGlobal>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#else
#include <QtGui>
#endif

#include <sys/time.h>
#include "gpio.h"

class TMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TMainWidget(QWidget *parent);
    ~TMainWidget() {}
private slots:
    void onKeepAlive();
 
private:
    void resizeEvent(QResizeEvent*);
    void paintEvent(QPaintEvent *);
    void customEvent(QEvent*);
private:
    QTimer* mpKeepAliveTimer;
    QPixmap FrameMap;
    bool transparent;
    QString sourceCodeUrl;

    int progresses[3];
    struct timeval startTime;

    int ButtonA_pin = 104;  //GPIOD8  = pin7
    int ButtonB_pin = 61;   //GPIOB29 = pin11 
    int ButtonC_pin = 62;   //GPIOB30 = pin13 
    int ButtonD_pin = 63;   //GPIOB31 = pin15 

};

#endif // WIDGET_H
