#include "mainwidget.h"
#include <signal.h>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
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

    for (unsigned int i=0; i<sizeof(progresses)/sizeof(int); i++) {
        progresses[i]=0;
    }
    
    boardInit();
    exportGPIOPin(ButtonA_pin);
    exportGPIOPin(ButtonB_pin);
    exportGPIOPin(ButtonC_pin);
    exportGPIOPin(ButtonD_pin);
    setGPIODirection(ButtonA_pin,GPIO_IN);
    setGPIODirection(ButtonB_pin,GPIO_IN);
    setGPIODirection(ButtonC_pin,GPIO_IN);
    setGPIODirection(ButtonD_pin,GPIO_IN);

    mpKeepAliveTimer = new QTimer();
    mpKeepAliveTimer->setSingleShot(false);
    QObject::connect(mpKeepAliveTimer, SIGNAL(timeout()), this, SLOT(onKeepAlive()));
    mpKeepAliveTimer->start(100);
        
    gettimeofday(&startTime,NULL);
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
    
    update();
}

void TMainWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);


    int SpaceHeight = 160;
    int HeightOffset = 40;
    
    ET=0;
    if(getGPIOValue(ButtonA_pin)==0)ET=1;
    if(getGPIOValue(ButtonB_pin)==0)ET=2;
    if(getGPIOValue(ButtonC_pin)==0)ET=3;
    if(getGPIOValue(ButtonD_pin)==0)ET=4;
    
     p.fillRect(0,0,width(),height(),QBrush(QColor(169,169,169)));
     
     p.drawPixmap(30, 20, FrameMap.width()*1.17, FrameMap.height()*1.17,FrameMap );
     
    
     if(getGPIOValue(ButtonA_pin)==0){p.drawPixmap( width()-150 , 0 * SpaceHeight + HeightOffset, btnNormal);}
     else{p.drawPixmap( width()-150 , 0 * SpaceHeight + HeightOffset, btnPush);}
    
     if(getGPIOValue(ButtonB_pin)==0){p.drawPixmap( width()-150 , 1 * SpaceHeight + HeightOffset, btnNormal);}
     else{p.drawPixmap( width()-150 , 1 * SpaceHeight + HeightOffset, btnPush);}
    
     if(getGPIOValue(ButtonC_pin)==0){p.drawPixmap( width()-150 , 2 * SpaceHeight + HeightOffset, btnNormal);}
     else{p.drawPixmap( width()-150 , 2 * SpaceHeight + HeightOffset , btnPush);}
    
     if(getGPIOValue(ButtonD_pin)==0){p.drawPixmap( width()-150 , 3 * SpaceHeight + HeightOffset , btnNormal);}
     else{p.drawPixmap( width()-150 , 3 * SpaceHeight + HeightOffset , btnPush);}
    

    
    
    p.setPen(Qt::red);                      //  source
    p.setFont(QFont("Arial", 18));
    p.fillRect((FrameMap.width()/2)-148, height()-22 ,300,20,QBrush(QColor(255,255,255)));
    p.drawText((FrameMap.width()/2)-150, height()-2 , " Source: IN");
    
    
    QPixmap battery("img/battery.png");  //  battery
    p.drawPixmap( width()-110 ,10, battery);
    p.drawText( width()-170 , 40 , QString("%1%").arg(ET));
   
    
 


}

static inline double time_diff(struct timeval _tstart,struct timeval _tend) {
  double t1 = 0.;
  double t2 = 0.;

  t1 = ((double)_tstart.tv_sec * 1000 + (double)_tstart.tv_usec/1000.0) ;
  t2 = ((double)_tend.tv_sec * 1000 + (double)_tend.tv_usec/1000.0) ;

  return t2-t1;
}

void TMainWidget::customEvent()
{

}


