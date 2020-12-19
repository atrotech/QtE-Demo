#include "VideoWidget.h"




TVideoWidget::TVideoWidget(QWidget *parent) :
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
    
  
    if(getGPIOValue(ButtonD_pin)==0)this->hide();
    
     p.fillRect(0,0,width(),height(),QBrush(QColor(169,0,169)));
     
     p.drawPixmap(30, 20, FrameMap.width()*1.17, FrameMap.height()*1.17,FrameMap );
     
    
     if(getGPIOValue(ButtonA_pin)==0){p.drawPixmap( width()-150 , 0 * SpaceHeight + HeightOffset, btnNormal);}
     else{p.drawPixmap( width()-150 , 0 * SpaceHeight + HeightOffset, btnPush);}
    
     if(getGPIOValue(ButtonB_pin)==0){p.drawPixmap( width()-150 , 1 * SpaceHeight + HeightOffset, btnNormal);}
     else{p.drawPixmap( width()-150 , 1 * SpaceHeight + HeightOffset, btnPush);}
    
     if(getGPIOValue(ButtonC_pin)==0){p.drawPixmap( width()-150 , 2 * SpaceHeight + HeightOffset, btnNormal);}
     else{p.drawPixmap( width()-150 , 2 * SpaceHeight + HeightOffset , btnPush);}
    
     if(getGPIOValue(ButtonD_pin)==0){p.drawPixmap( width()-150 , 3 * SpaceHeight + HeightOffset , btnNormal);}
     else{p.drawPixmap( width()-150 , 3 * SpaceHeight + HeightOffset , btnPush);}
     
     p.drawPixmap( width()-142 , 0 * SpaceHeight + HeightOffset + 7, videoImg);
     p.drawPixmap( width()-142 , 1 * SpaceHeight + HeightOffset + 7, dataImg);
     p.drawPixmap( width()-142 , 2 * SpaceHeight + HeightOffset + 7, reportImg);
     p.drawPixmap( width()-142 , 3 * SpaceHeight + HeightOffset + 7, powerImg);

    
    
    p.setPen(Qt::red);                      //  source
    p.setFont(QFont("Arial", 18));
    p.fillRect((FrameMap.width()/2)-148, height()-22 ,300,20,QBrush(QColor(255,255,255)));
    p.drawText((FrameMap.width()/2)-150, height()-2 , " Source: IN");
    
    
    
    p.drawPixmap( width()-110 ,10, BatteryImg);
    p.drawText( width()-110 , 10 , QString("%1%").arg(100));
   
    
 


}



