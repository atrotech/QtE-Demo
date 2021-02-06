#include <QtCore/QtGlobal>
#include <QtWidgets>
#include <sys/time.h>
#include <signal.h>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
#include "SerialPort.h"


using namespace cv;



class TVideoWidget : public QWidget
{

  Q_OBJECT

public:
    explicit TVideoWidget(QWidget *parent);
    ~TVideoWidget() {}
    int Button = 0;
    Mat InputFrame;

private slots:
    void onKeepAlive();
private:
    void paintEvent(QPaintEvent *);
    void videoTest();
    void saveReportTest();
    void singleFrameTest();
    void DataTest();
    void SourceDelay();
private:
    QTimer* mpKeepAliveTimer;

    QPixmap btnNormal = QPixmap(":/img/Btn.png");
    QPixmap btnPush = QPixmap(":/img/BtnFocus.png");
    QPixmap BatteryImg = QPixmap(":/img/battery.png");
    QPixmap saveImg = QPixmap(":/img/diskette.png");
    QPixmap flashImg = QPixmap(":/img/flash-disk.png");
    QPixmap playImg = QPixmap(":/img/play.png");
    QPixmap returnImg = QPixmap(":/img/return.png");
    QPixmap cancelImg = QPixmap(":/img/cancel.png");
    QPixmap noneImg = QPixmap(":/img/none.png");
    QPixmap tickImg = QPixmap(":/img/tick.png");
    QPixmap processImg = QPixmap(":/img/process.png");
    QPixmap tableImg = QPixmap(":/img/table.png");

    QPixmap StatusIcon1 = QPixmap(noneImg);
    QPixmap StatusIcon2 = QPixmap(noneImg);
    QPixmap StatusIcon3 = QPixmap(noneImg);
    QPixmap StatusIcon4 = QPixmap(noneImg);
    QPixmap StatusIcon5 = QPixmap(noneImg);
    QPixmap StatusIcon6 = QPixmap(noneImg);
    QPixmap StatusIcon7 = QPixmap(noneImg);

    float refrenceValue[3]={0,0,0};
    float singleMeasured[3]={0,0,0};
    double totalMeasured[3]={0,0,0};
    float measuredError[3]={0,0,0};

    char MessageString[40];
    int t = 0; // time for delay popup

    unsigned char str[6][5]={"0","0","0","0","0","0"};

};
