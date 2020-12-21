#include "VideoWidget.h"




TVideoWidget::TVideoWidget(QWidget *parent) :
    QWidget(parent)
{

    const QString qwsDisplay = QString(qgetenv("QWS_DISPLAY"));





    mpKeepAliveTimer = new QTimer();
    mpKeepAliveTimer->setSingleShot(false);
    QObject::connect(mpKeepAliveTimer, SIGNAL(timeout()), this, SLOT(onKeepAlive()));
    mpKeepAliveTimer->start(100);

}



void TVideoWidget::onKeepAlive() {

    update();
}

void TVideoWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    int SpaceHeight = 160;
    int HeightOffset = 60;
    if(Button==4){this->hide();Button=0;}

     p.fillRect(0,0,width(),height(),QBrush(QColor(169,0,169)));

     p.drawPixmap(30, 20, FrameMap.width()*1.17, FrameMap.height()*1.17,FrameMap );


     p.drawPixmap( width()-150 , 0 * SpaceHeight + HeightOffset, btnPush);
     p.drawPixmap( width()-150 , 1 * SpaceHeight + HeightOffset, btnPush);
     p.drawPixmap( width()-150 , 2 * SpaceHeight + HeightOffset , btnPush);
     p.drawPixmap( width()-150 , 3 * SpaceHeight + HeightOffset , btnPush);

     p.drawPixmap( width()-142 , 0 * SpaceHeight + HeightOffset + 7, playImg);
     p.drawPixmap( width()-142 , 1 * SpaceHeight + HeightOffset + 7, saveImg);
     p.drawPixmap( width()-142 , 2 * SpaceHeight + HeightOffset + 7, flashImg);
     p.drawPixmap( width()-142 , 3 * SpaceHeight + HeightOffset + 7, returnImg);



    p.setPen(Qt::red);                      //  source
    p.setFont(QFont("Arial", 18));
    p.fillRect((FrameMap.width()/2)-148, height()-22 ,300,20,QBrush(QColor(255,255,255)));
    p.drawText((FrameMap.width()/2)-150, height()-2 , " Source: IN");



    p.drawPixmap( width()-110 ,10, BatteryImg);
    p.drawText( width()-110 , 10 , QString("%1%").arg(Button));


    p.setPen(Qt::black);
    p.setFont(QFont("Arial", 28));
    p.drawText( width()/3 , height()/4 ,     QString(" تست ابعاد : %1  %2 ").arg(67).arg(" "));
    p.drawText( width()/3 , height()/4+100 , QString("  تست رنگ : %1  %2 ").arg(67).arg(" "));
    p.drawText( width()/3 , height()/4+200 , QString(" تست نویز  : %1  %2 ").arg(67).arg(" "));
    p.drawText( width()/3 , height()/4+300 , QString(" test abaad : %1  %2 ").arg(67).arg(" "));

}
