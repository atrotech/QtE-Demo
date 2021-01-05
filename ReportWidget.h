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
#include <dirent.h>



using namespace cv;

class TReportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TReportWidget(QWidget *parent);
    ~TReportWidget() {}
    int Button = 0;
    Mat InputFrame;

private slots:
    void onKeepAlive();
private:
    void paintEvent(QPaintEvent *);

private:
    QTimer* mpKeepAliveTimer;

    QPixmap btnNormal = QPixmap(":/img/Btn.png");
    QPixmap btnPush = QPixmap(":/img/BtnFocus.png");
    QPixmap BatteryImg = QPixmap(":/img/battery.png");
    QPixmap flashImg = QPixmap(":/img/flash-disk.png");
    QPixmap returnImg = QPixmap(":/img/return.png");
    QPixmap upImg = QPixmap(":/img/up.png");
    QPixmap downImg = QPixmap(":/img/down.png");
    QPixmap tapImg = QPixmap(":/img/tap.png");





};
