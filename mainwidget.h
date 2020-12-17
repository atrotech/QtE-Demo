
#ifndef WIDGET_H
#define WIDGET_H
#include <QtCore/QtGlobal>
#include <QtWidgets>


#include <sys/time.h>
#include "lib/gpio.h"
#include "lib/common.h"

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
    void customEvent();
private:
    QTimer* mpKeepAliveTimer;
    QPixmap FrameMap;
    QPixmap BtnNormal;
    QPixmap BtnPush;

    int progresses[3];
    struct timeval startTime;

    int ButtonA_pin = GPIO_PIN(7);    //GPIOD8  = pin7
    int ButtonB_pin = GPIO_PIN(11);   //GPIOB29 = pin11 
    int ButtonC_pin = GPIO_PIN(13);   //GPIOB30 = pin13 
    int ButtonD_pin = GPIO_PIN(15);   //GPIOB31 = pin15 

};

#endif // WIDGET_H
