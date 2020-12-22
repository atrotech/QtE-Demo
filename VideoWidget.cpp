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
    if(Button==1){Button=0;videoTest();}

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
    p.setFont(QFont("Arial", 28));

    p.drawText( width()/3 , height()/4 ,     QString(" تست ابعاد : %1  ").arg(Button));
    p.drawPixmap( width()/3-50 , height()/4-35 , tickImg);

    p.drawText( width()/3 , height()/4+100 , QString(" تست رنگ : %1  ").arg(67));
    p.drawPixmap( width()/3-50  , height()/4+65 , noneImg);

    p.drawText( width()/3 , height()/4+200 , QString(" تست نویز  : %1  ").arg(67));
    p.drawPixmap( width()/3-50  , height()/4+165 , cancelImg);

    p.drawText( width()/3 , height()/4+300 , QString(" تست فریم  : %1  ").arg(67));
    p.drawPixmap( width()/3-50  , height()/4+265 , processImg);

}


void TVideoWidget::videoTest()
{

  //  area test

  puint8_t* pixelPtr = (uint8_t*)InputFrame.data;
  int cn = InputFrame.channels();
  Scalar_<uint8_t> bgrPixel;

  for(int i = 0; i < InputFrame.rows; i++)
  {
      for(int j = 0; j < InputFrame.cols; j++)
      {
          bgrPixel.val[0] = pixelPtr[i*InputFrame.cols*cn + j*cn + 0]; // B
          bgrPixel.val[1] = pixelPtr[i*InputFrame.cols*cn + j*cn + 1]; // G
          bgrPixel.val[2] = pixelPtr[i*InputFrame.cols*cn + j*cn + 2]; // R

          print("R%d G%d B%d",bgrPixel.val[2],bgrPixel.val[1],bgrPixel.val[0])
      }
  }



  //  color test





  //  noise test


  //  frame test


  QApplication::quit();
}
