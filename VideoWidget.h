#include <QtCore/QtGlobal>
#include <QtWidgets>


#include <sys/time.h>
#include "lib/gpio.h"
#include "lib/common.h"

class TVideoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TVideoWidget(QWidget *parent);
    ~TVideoWidget() {}
private slots:
    void onKeepAlive();
 
private:
    void paintEvent(QPaintEvent *);
private:
    QTimer* mpKeepAliveTimer;
    QPixmap FrameMap;
    QPixmap btnNormal = QPixmap(":/img/Btn.png");
    QPixmap btnPush = QPixmap(":/img/BtnFocus.png");
    QPixmap videoImg = QPixmap(":/img/video.png");
    QPixmap powerImg = QPixmap(":/img/power.png");
    QPixmap reportImg = QPixmap(":/img/report.png");
    QPixmap dataImg = QPixmap(":/img/data.png");
    QPixmap BatteryImg = QPixmap(":/img/battery.png");

    int ButtonA_pin = GPIO_PIN(7);    //GPIOD8  = pin7
    int ButtonB_pin = GPIO_PIN(11);   //GPIOB29 = pin11 
    int ButtonC_pin = GPIO_PIN(13);   //GPIOB30 = pin13 
    int ButtonD_pin = GPIO_PIN(15);   //GPIOB31 = pin15 

    

};