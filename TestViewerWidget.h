#include <QtCore/QtGlobal>
#include <QtWidgets>
#include <sys/time.h>
#include <signal.h>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include "lib/gpio.h"
#include "lib/common.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>

using namespace cv;



class TTestViewerWidget : public QWidget
{

  Q_OBJECT

public:
    explicit TTestViewerWidget(QWidget *parent);
    ~TTestViewerWidget() {}
    int Button = 0;
    Mat InputFrame;

    float refrenceValue[3]={0,0,0};
    float singleMeasured[3]={0,0,0};
    double totalMeasured[3]={0,0,0};
    float measuredError[3]={0,0,0};

private slots:
    void onKeepAlive();
private:
    void paintEvent(QPaintEvent *);

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




};
