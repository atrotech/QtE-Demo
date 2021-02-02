#ifndef WIDGET_H
#define WIDGET_H
#include <QtCore/QtGlobal>
#include <QtWidgets>
#include "VideoWidget.h"
#include "ReportWidget.h"
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
    char CheckButtons();
    char PushedButton();

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

    TVideoWidget *VideoWindow = new TVideoWidget(0);
    TReportWidget *ReportWindow = new TReportWidget(0);




    char ActiveWindow = 0;

    int ButtonA_pin = GPIO_PIN(7);    //GPIOD8  = pin7
    int ButtonB_pin = GPIO_PIN(11);   //GPIOB29 = pin11
    int ButtonC_pin = GPIO_PIN(13);   //GPIOB30 = pin13
    int ButtonD_pin = GPIO_PIN(15);   //GPIOB31 = pin15
    int VGAPowerPin = GPIO_PIN(18);
    int LCDPowerPin = GPIO_PIN(22);
    int ModemAPowerPin = GPIO_PIN(24);
    int ModemBPowerPin = GPIO_PIN(26);
    int ModemCPowerPin = GPIO_PIN(28);

};

#endif // WIDGET_H
