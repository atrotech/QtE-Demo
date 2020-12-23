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


};







if( pixColor[0] == previousPixColor[0] && pixColor[1] == previousPixColor[1] && pixColor[2] == previousPixColor[2] )
{
  printf("y: %d (%d %d %d) \n " , y, pixColor[0], pixColor[1], pixColor[2]);
}
else
{
  printf("--y: %d \n " , y);
}





for (int y = 0; y<InputFrame.cols; y++)
{
   cv::Vec3b rgb = InputFrame.at<cv::Vec3b>(100,y);
   int pixColor[3] = {rgb[0]/100 , rgb[1]/100 , rgb[2]/100};

   printf("y: %d (%d %d %d) \n " , y, pixColor[0], pixColor[1], pixColor[2]);
   previousPixColor[0] = pixColor[0] ;
   previousPixColor[1] = pixColor[1] ;
   previousPixColor[2] = pixColor[2] ;
   printf("-y: %d (%d %d %d) \n " , y, previousPixColor[0], previousPixColor[1], previousPixColor[2]);
}
