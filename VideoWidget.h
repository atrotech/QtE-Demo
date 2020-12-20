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
    char Button = 0;
};