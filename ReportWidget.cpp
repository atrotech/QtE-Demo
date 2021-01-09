#include "ReportWidget.h"

using namespace cv;
using namespace std;

using std::vector;


TReportWidget::TReportWidget(QWidget *parent) :
    QWidget(parent)
{

    const QString qwsDisplay = QString(qgetenv("QWS_DISPLAY"));


    mpKeepAliveTimer = new QTimer();
    mpKeepAliveTimer->setSingleShot(false);
    QObject::connect(mpKeepAliveTimer, SIGNAL(timeout()), this, SLOT(onKeepAlive()));
    mpKeepAliveTimer->start(100);




}

void TReportWidget::updateFileList(){


  DIR *dir; struct dirent *diread;
  filesCount = 0;
  if ((dir = opendir("/home/pi/QtE-Demo/reports")) == nullptr) {closedir (dir);return;}
  while ((diread = readdir(dir)) != nullptr) {
    if(diread->d_type == DT_REG)
    {
      sprintf(files[filesCount],"%s",diread->d_name);
      filesCount++;
    }
  }
  closedir (dir);

}



void TReportWidget::onKeepAlive() {
    update();
}

void TReportWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    int SpaceHeight = 160;
    int HeightOffset = 60;
    if(Button==4){this->hide();Button=0;}
    if(Button==1){Button=0;SelectedIndex--;}
    if(Button==2){Button=0;SelectedIndex++;}

     p.fillRect(0,0,width(),height(),QBrush(QColor(169,150,169)));


     p.drawPixmap( width()-150 , 0 * SpaceHeight + HeightOffset, btnPush);
     p.drawPixmap( width()-150 , 1 * SpaceHeight + HeightOffset, btnPush);
     p.drawPixmap( width()-150 , 2 * SpaceHeight + HeightOffset , btnPush);
     p.drawPixmap( width()-150 , 3 * SpaceHeight + HeightOffset , btnPush);

     p.drawPixmap( width()-142 , 0 * SpaceHeight + HeightOffset + 7, upImg);
     p.drawPixmap( width()-142 , 1 * SpaceHeight + HeightOffset + 7, downImg);
     p.drawPixmap( width()-142 , 2 * SpaceHeight + HeightOffset + 7, tapImg);
     p.drawPixmap( width()-142 , 3 * SpaceHeight + HeightOffset + 7, returnImg);

     p.setPen(Qt::black);
     p.setFont(QFont("Arial", 25));




    int i = 0;
    for (int i=0;i<filesCount;i++)
    {
      if(i==SelectedIndex){p.setPen(Qt::red);}else{p.setPen(Qt::black);}
      printf(str,"%s",files[i]);
      p.drawText(width()/6, (height()/4)+(i*50)+10, QString(str));
    }




}
