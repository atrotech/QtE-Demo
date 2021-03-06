#include "TestViewerWidget.h"


using namespace std;
using std::vector;



TTestViewerWidget::TTestViewerWidget(QWidget *parent) :
    QWidget(parent)
{
    const QString qwsDisplay = QString(qgetenv("QWS_DISPLAY"));

    mpKeepAliveTimer = new QTimer();
    mpKeepAliveTimer->setSingleShot(false);
    QObject::connect(mpKeepAliveTimer, SIGNAL(timeout()), this, SLOT(onKeepAlive()));
    mpKeepAliveTimer->start(100);
    update();
}






void TTestViewerWidget::UpdateTable()
{
  std::ifstream file(FileName);
  std::string Value;
  int j=0;
  while (std::getline(file, Value)) {
    std::istringstream ss(Value);
    std::string token;
    while(std::getline(ss, token, ',')) {
        SelectedValue[j]=token;
        j++;
    }
  }
}





void TTestViewerWidget::onKeepAlive() {
  if(Button==4){this->hide();Button=0;}
  if(Button==1){this->hide();Button=0;remove(FileName);}
  if(Button==2){Button=0;}
  if(Button==3){Button=0;}
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

   p.drawPixmap( width()-142 , 0 * SpaceHeight + HeightOffset + 7, removeImg);
   p.drawPixmap( width()-142 , 1 * SpaceHeight + HeightOffset + 7, printImg);
   p.drawPixmap( width()-142 , 2 * SpaceHeight + HeightOffset + 7, flashImg);
   p.drawPixmap( width()-142 , 3 * SpaceHeight + HeightOffset + 7, returnImg);


  p.setPen(Qt::black);
  p.setFont(QFont("Arial", 18));

  p.drawPixmap( width()/9 , height()/8 , tableImg);
// ----------------------
  p.drawText( width()/6 , height()/4    ,  QString(" %1 ").arg(SelectedValue[2].data()));
  p.drawText( width()/3+40 , height()/4 ,  QString(" %1 ").arg(SelectedValue[1].data()));
  p.drawText( width()/2+60 , height()/4 ,  QString(" %1 ").arg(SelectedValue[0].data()));

  p.drawText( width()/6 , height()/3-10    ,  QString(" %1 ").arg(SelectedValue[5].data()));
  p.drawText( width()/3+40 , height()/3-10 ,  QString(" %1 ").arg(SelectedValue[4].data()));
  p.drawText( width()/2+60 , height()/3-10 ,  QString(" %1 ").arg(SelectedValue[3].data()));

  p.drawText( width()/6 , height()/3+45    ,  QString(" %1 ").arg(SelectedValue[8].data()));
  p.drawText( width()/3+40 , height()/3+45 ,  QString(" %1 ").arg(SelectedValue[7].data()));
  p.drawText( width()/2+60 , height()/3+45 ,  QString(" %1 ").arg(SelectedValue[6].data()));

  p.drawText( width()/6 , height()/2-20    , QString(" %1 ").arg("none"));
  p.drawText( width()/3+40 , height()/2-20 , QString(" %1 ").arg("none"));
  p.drawText( width()/2+60 , height()/2-20 , QString(" %1 ").arg("none"));
// ----------------------
  p.drawText( width()/6 , height()/1.7+20    , QString(" %1 ").arg("none"));
  p.drawText( width()/3+40 , height()/1.7+20 , QString(" %1 ").arg("none"));
  p.drawText( width()/2+60 , height()/1.7+20 , QString(" %1 ").arg("none"));

  p.drawText( width()/6 , height()/1.5+10    , QString(" %1 ").arg("none"));
  p.drawText( width()/3+40 , height()/1.5+10   , QString(" %1 ").arg("none"));
  p.drawText( width()/2+60 , height()/1.5+10   , QString(" %1 ").arg("none"));
// ----------------------
  p.drawText( width()/6 , height()/1.2    , QString(" %1 ").arg("none"));
  p.drawText( width()/3+40 , height()/1.2 , QString(" %1 ").arg("none"));
  p.drawText( width()/2+60 , height()/1.2 , QString(" %1 ").arg("none"));
  p.drawText( width()/1.3-20 , height()/1.2 , QString(" %1 ").arg("none"));
}
