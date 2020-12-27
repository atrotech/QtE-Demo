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

    int distanceAverage = 0;
    int noise = 0;
    int totalRgbAverage=0;


};
