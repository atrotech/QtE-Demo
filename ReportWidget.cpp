#include "ReportWidget.h"

using namespace cv;
using namespace std;


TReportWidget::TReportWidget(QWidget *parent) :
    QWidget(parent)
{

    const QString qwsDisplay = QString(qgetenv("QWS_DISPLAY"));


    mpKeepAliveTimer = new QTimer();
    mpKeepAliveTimer->setSingleShot(false);
    QObject::connect(mpKeepAliveTimer, SIGNAL(timeout()), this, SLOT(onKeepAlive()));
    mpKeepAliveTimer->start(100);

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
    if(Button==1){Button=0;}
    if(Button==3){Button=0;showReports();}

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
     p.setFont(QFont("Arial", 40));








void TVideoWidget::showReports()
{
  using std::cout; using std::cin;
  using std::endl; using std::vector;

  DIR *dir; struct dirent *diread;
  vector<char *> files;
  if ((dir = opendir("/home/pi/QtE-Demo/reports")) != nullptr) {
    while ((diread = readdir(dir)) != nullptr) {
      files.push_back(diread->d_name);
    }
    closedir (dir);
  }
  for (auto file : files)
  {
    p.drawText(width()/6, height()/3+10, QString(file));
  }

}





}
