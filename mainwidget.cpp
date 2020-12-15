#include "mainwidget.h"
#include <signal.h>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include "lib/includes/libfahw-gpio.h"

#define DRIVER_MODULE "matrix_gpio_int"

using namespace cv;


VideoCapture cap(0);

TMainWidget::TMainWidget(QWidget *parent, bool transparency, const QString& surl) :
    QWidget(parent),transparent(transparency),sourceCodeUrl(surl)
{
    //FrameMap = new QPixmap();     
    const QString qwsDisplay = QString(qgetenv("QWS_DISPLAY"));

    for (unsigned int i=0; i<sizeof(progresses)/sizeof(int); i++) {
        progresses[i]=0;
    }


    mpKeepAliveTimer = new QTimer();
    mpKeepAliveTimer->setSingleShot(false);
    QObject::connect(mpKeepAliveTimer, SIGNAL(timeout()), this, SLOT(onKeepAlive()));
    mpKeepAliveTimer->start(1500);
        
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
    //FrameMap = FrameMap.scaledToHeight(height());
    
    update();
}

void TMainWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);


    
     p.fillRect(0,0,width(),height(),QBrush(QColor(169,169,169)));
     //p.drawPixmap(0, 0, width(), height(), bg);
     p.drawPixmap(0, 0, FrameMap.width(), height(),FrameMap );

    
    QPixmap video("img/video.png");  // video testing
    p.drawPixmap( width()-150 , height()/5-(height()/5)/2 , 150 , 150 , video);
    
    QPixmap data("img/data.png");  // data testing
    p.drawPixmap( width()-150 , 2*height()/5-(height()/5)/2 , 150 , 150 , data);
    
    QPixmap report("img/report.png");  // report 
    p.drawPixmap( width()-150 , 3*height()/5-(height()/5)/2 , 150 , 150 , report);
    
    QPixmap power("img/power.png");  //  power
    p.drawPixmap( width()-150 , 4*height()/5-(height()/5)/2 , 150 , 150 , power);
    
    
    p.setPen(Qt::black);                      //  source
    p.setFont(QFont("Arial", 18));
    p.drawText( FrameMap.width()/2 , FrameMap.height()-40 , " Source: test test ");
    
    
    QPixmap battery("img/battery.png");  //  battery
    p.drawPixmap( width()-110 , height()/200 , 90 , 90 , battery);
    p.drawText( width()-170 , height()/200+58 , " 45% ");
   
    
    
    //QPixmap source("battery.png");  //  source
    //p.drawPixmap( width()-60 , height()/100 , 90 , 90 , source);


    
    //p.setPen(QPen(QColor(255,255,255)));
    //p.drawText(space,*0,width()-space*2,itemHeight,Qt::AlignLeft | Qt::AlignVCenter,QString("CPU: %1/T%2").arg(34).arg(200));




}

static inline double time_diff(struct timeval _tstart,struct timeval _tend) {
  double t1 = 0.;
  double t2 = 0.;

  t1 = ((double)_tstart.tv_sec * 1000 + (double)_tstart.tv_usec/1000.0) ;
  t2 = ((double)_tend.tv_sec * 1000 + (double)_tend.tv_usec/1000.0) ;

  return t2-t1;
}

void TMainWidget::customEvent(QEvent *e)
{

}
