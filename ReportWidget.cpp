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
    if(Button==3){Button=0;}

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

     p.drawText( width()/6 , height()/3+10 ,  QString(" report "));



     std::vector<std::string> get_directories(const std::string& s)
     {
       std::vector<std::string> r;
       for(auto& p : std::filesystem::recursive_directory_iterator(s)){
         if (p.is_directory())
         r.push_back(p.path().string());
       }
       return r;
       printf("%s\n", r);
     }




}
