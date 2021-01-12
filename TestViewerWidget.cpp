#include "TestViewerWidget.h"

using namespace cv;
using namespace std;



TTestViewerWidget::TTestViewerWidget(QWidget *parent) :
    QWidget(parent)
{
    const QString qwsDisplay = QString(qgetenv("QWS_DISPLAY"));

    mpKeepAliveTimer = new QTimer();
    mpKeepAliveTimer->setSingleShot(false);
    QObject::connect(mpKeepAliveTimer, SIGNAL(timeout()), this, SLOT(onKeepAlive()));
    mpKeepAliveTimer->start(100);

}



void TTestViewerWidget::onKeepAlive() {
    update();
}


void TTestViewerWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);


    int SpaceHeight = 160;
    int HeightOffset = 60;

     p.fillRect(0,0,width(),height(),QBrush(QColor(169,150,169)));

     p.drawPixmap( width()-150 , 0 * SpaceHeight + HeightOffset, btnPush);
     p.drawPixmap( width()-150 , 1 * SpaceHeight + HeightOffset, btnPush);
     p.drawPixmap( width()-150 , 2 * SpaceHeight + HeightOffset , btnPush);
     p.drawPixmap( width()-150 , 3 * SpaceHeight + HeightOffset , btnPush);

     p.drawPixmap( width()-142 , 0 * SpaceHeight + HeightOffset + 7, playImg);
     p.drawPixmap( width()-142 , 1 * SpaceHeight + HeightOffset + 7, saveImg);
     p.drawPixmap( width()-142 , 2 * SpaceHeight + HeightOffset + 7, flashImg);
     p.drawPixmap( width()-142 , 3 * SpaceHeight + HeightOffset + 7, returnImg);


    p.setPen(Qt::black);
    p.setFont(QFont("Arial", 18));

    p.drawPixmap( width()/9 , height()/8 , tableImg);
// ----------------------
    p.drawText( width()/6 , height()/4    ,  QString(" %1 ").arg(measuredError[0]));
    p.drawText( width()/3+40 , height()/4 ,  QString(" %1 ").arg(totalMeasured[0]));
    p.drawText( width()/2+60 , height()/4 ,  QString(" %1 ").arg(refrenceValue[0]));
    p.drawPixmap( width()/15  , height()/4.8 , StatusIcon1);

    p.drawText( width()/6 , height()/3-10    ,  QString(" %1 ").arg(measuredError[1]));
    p.drawText( width()/3+40 , height()/3-10 ,  QString(" %1 ").arg(totalMeasured[1]));
    p.drawText( width()/2+60 , height()/3-10 ,  QString(" %1 ").arg(refrenceValue[1]));
    p.drawPixmap( width()/15  , height()/3.6 , StatusIcon2);

    p.drawText( width()/6 , height()/3+45    ,  QString(" %1 ").arg(measuredError[2]));
    p.drawText( width()/3+40 , height()/3+45 ,  QString(" %1 ").arg(totalMeasured[2]));
    p.drawText( width()/2+60 , height()/3+45 ,  QString(" %1 ").arg(refrenceValue[2]));
    p.drawPixmap( width()/15  , height()/2.8 , StatusIcon3);

    p.drawText( width()/6 , height()/2-20    , QString(" %1 ").arg("none"));
    p.drawText( width()/3+40 , height()/2-20 , QString(" %1 ").arg("none"));
    p.drawText( width()/2+60 , height()/2-20 , QString(" %1 ").arg("none"));
    p.drawPixmap( width()/15  , height()/2.3 , StatusIcon4);
// ----------------------
    p.drawText( width()/6 , height()/1.7+20    , QString(" %1 ").arg("none"));
    p.drawText( width()/3+40 , height()/1.7+20 , QString(" %1 ").arg("none"));
    p.drawText( width()/2+60 , height()/1.7+20 , QString(" %1 ").arg("none"));
    p.drawPixmap( width()/15  , height()/1.82 , StatusIcon5);

    p.drawText( width()/6 , height()/1.5+10    , QString(" %1 ").arg("none"));
    p.drawText( width()/3+40 , height()/1.5+10   , QString(" %1 ").arg("mone"));
    p.drawText( width()/2+60 , height()/1.5+10   , QString(" %1 ").arg("none"));
    p.drawPixmap( width()/15  , height()/1.55  , StatusIcon6);
// ----------------------
    p.drawText( width()/6 , height()/1.2    , QString(" %1 ").arg("none"));
    p.drawText( width()/3+40 , height()/1.2 , QString(" %1 ").arg("none"));
    p.drawText( width()/2+60 , height()/1.2 , QString(" %1 ").arg("none"));
    p.drawText( width()/1.3-20 , height()/1.2 , QString(" %1 ").arg("none"));
    p.drawPixmap( width()/15  , height()/1.27 , StatusIcon7);



    if(Button==4){this->hide();Button=0;}
    if(Button==1){Button=0;}
    if(Button==2){Button=0;}
    if(Button==3){Button=0;}



}
