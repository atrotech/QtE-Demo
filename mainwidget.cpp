#include "mainwidget.h"
#include <signal.h>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include "lib/gpio.h"

using namespace cv;


int ET = 0;
VideoCapture cap(0);


TMainWidget::TMainWidget(QWidget *parent) :
    QWidget(parent)
{

    const QString qwsDisplay = QString(qgetenv("QWS_DISPLAY"));

    printf("Width: %d", width());
    printf("Height: %d", height());

    boardInit();
    exportGPIOPin(ButtonA_pin);
    exportGPIOPin(ButtonB_pin);
    exportGPIOPin(ButtonC_pin);
    exportGPIOPin(ButtonD_pin);
    setGPIODirection(ButtonA_pin,GPIO_IN);
    setGPIODirection(ButtonB_pin,GPIO_IN);
    setGPIODirection(ButtonC_pin,GPIO_IN);
    setGPIODirection(ButtonD_pin,GPIO_IN);
    exportGPIOPin(VGAPowerPin);
    exportGPIOPin(LCDPowerPin);
    exportGPIOPin(ModemAPowerPin);
    exportGPIOPin(ModemBPowerPin);
    exportGPIOPin(ModemCPowerPin);
    setGPIODirection(VGAPowerPin,GPIO_OUT);
    setGPIODirection(LCDPowerPin,GPIO_OUT);
    setGPIODirection(ModemAPowerPin,GPIO_OUT);
    setGPIODirection(ModemBPowerPin,GPIO_OUT);
    setGPIODirection(ModemCPowerPin,GPIO_OUT);
    exportGPIOPin(VGASelectPin);
    exportGPIOPin(CaptureSelectPin);
    setGPIODirection(VGASelectPin,GPIO_OUT);
    setGPIODirection(CaptureSelectPin,GPIO_OUT);

    VideoWindow->setWindowFlags(Qt::FramelessWindowHint);
    ReportWindow->setWindowFlags(Qt::FramelessWindowHint);



    mpKeepAliveTimer = new QTimer();
    mpKeepAliveTimer->setSingleShot(false);
    QObject::connect(mpKeepAliveTimer, SIGNAL(timeout()), this, SLOT(onKeepAlive()));
    mpKeepAliveTimer->start(333);

    setGPIOValue(LCDPowerPin,1);


}




void TMainWidget::resizeEvent(QResizeEvent*) {

}





void TMainWidget::onKeepAlive() {
    Mat frame;
    cap.read(frame); // read a new frame from video

    FrameMap = QPixmap::fromImage(QImage((unsigned char*) frame.data,
                                   frame.cols,
                                   frame.rows,
                                   QImage::Format_RGB888));

    if(ActiveWindow==1)VideoWindow->InputFrame = frame;
    CheckButtons();

    update();
}

void TMainWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    int SpaceHeight = 160;
    int HeightOffset = 60;

    if(ActiveWindow!=0)return;
     p.fillRect(0,0,width(),height(),QBrush(QColor(169,169,169)));

     p.drawPixmap(30, 20, FrameMap.width()*1.17, FrameMap.height()*1.17,FrameMap );


     p.drawPixmap( width()-150 , 0 * SpaceHeight + HeightOffset, btnPush);
     p.drawPixmap( width()-150 , 1 * SpaceHeight + HeightOffset, btnPush);
     p.drawPixmap( width()-150 , 2 * SpaceHeight + HeightOffset , btnPush);
     p.drawPixmap( width()-150 , 3 * SpaceHeight + HeightOffset , btnPush);

     p.drawPixmap( width()-142 , 0 * SpaceHeight + HeightOffset + 7, videoImg);
     p.drawPixmap( width()-142 , 1 * SpaceHeight + HeightOffset + 7, sourceImg);
     p.drawPixmap( width()-142 , 2 * SpaceHeight + HeightOffset + 7, reportImg);
     p.drawPixmap( width()-142 , 3 * SpaceHeight + HeightOffset + 7, powerImg);



     p.setPen(Qt::black);          //  source
     p.setFont(QFont("Arial", 18));
     p.fillRect((FrameMap.width()/2)-148, height()-15 ,300,20,QBrush(QColor(255,255,255)));
     p.drawText( width()/2.3 , height()-30 , QString("Source: %1").arg(InputSource));



     p.drawPixmap( width()-70 ,0, BatteryImg);
     p.drawText( width()-55 , 38 , QString("%1%").arg(ET));
}

char TMainWidget::CheckButtons()
{
    char btn = PushedButton();
    if(btn==0)return 0;

     if(ActiveWindow==0){
        switch(btn)
        {
            case 1:
            ActiveWindow = 1;
            VideoWindow->setWindowFlags(Qt::FramelessWindowHint);
            VideoWindow->showFullScreen();
            VideoWindow->setGeometry(0,0,width(),height());
            VideoWindow->show();
            break;
            case 2:
            ActiveWindow = 2;
            setGPIOValue(VGASelectPin,InputSource);
            setGPIOValue(CaptureSelectPin,InputSource);
            toggle = !toggle;
            break;
            case 3:
            ActiveWindow = 3;
            ReportWindow->setWindowFlags(Qt::FramelessWindowHint);
            ReportWindow->showFullScreen();
            ReportWindow->setGeometry(0,0,width(),height());
            ReportWindow->show();
            ReportWindow->updateFileList();
            break;
            case 4:
            QApplication::quit();
            break;

        }
     }
    else if(ActiveWindow==1)VideoWindow->Button = btn;
    else if(ActiveWindow==2)printf("Data %d",btn);
    else if(ActiveWindow==3)ReportWindow->Button = btn;
    if(btn==4){ActiveWindow=0;}
    while(PushedButton());
}

char TMainWidget::PushedButton()
{
    if(getGPIOValue(ButtonA_pin)==0)return 1;
    if(getGPIOValue(ButtonB_pin)==0)return 2;
    if(getGPIOValue(ButtonC_pin)==0)return 3;
    if(getGPIOValue(ButtonD_pin)==0)return 4;
    return 0;
}
