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
    mpKeepAliveTimer->start(10);




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
 if(filesCount<10)LastListIndex = filesCount;
  closedir (dir);

}



void TReportWidget::onKeepAlive() {
    update();
}



void TReportWidget::ViewDataTable()
{

  TestViewerWindow->setWindowFlags(Qt::FramelessWindowHint);
  TestViewerWindow->setWindowFlags(Qt::FramelessWindowHint);
  TestViewerWindow->showFullScreen();
  TestViewerWindow->setGeometry(0,0,width(),height());
  TestViewerWindow->show();
  ViewerIsOpen = true;

  char FileName[60];
  sprintf (FileName, "reports/%s", files[SelectedIndex]);

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


  printf("printf 0: %s\n", SelectedValue[0);

  std::cout << 0 <<": " << SelectedValue[0] << '\n';
  std::cout << 1 <<": " << SelectedValue[1] << '\n';
  std::cout << 2 <<": " << SelectedValue[2] << '\n';
  std::cout << 3 <<": " << SelectedValue[3] << '\n';
  std::cout << 4 <<": " << SelectedValue[4] << '\n';
  std::cout << 5 <<": " << SelectedValue[5] << '\n';
  std::cout << 6 <<": " << SelectedValue[6] << '\n';
  std::cout << 7 <<": " << SelectedValue[7] << '\n';
  std::cout << 8 <<": " << SelectedValue[8] << '\n';
  std::cout << 9 <<": " << SelectedValue[9] << '\n';






}



void TReportWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    int SpaceHeight = 160;
    int HeightOffset = 60;
    if(Button==4)
    {
      this->hide();
      Button=0;
      if(ViewerIsOpen){TestViewerWindow->hide();ViewerIsOpen=false;}
    }
    if(Button==3)
    {
      Button=0;
      if(!ViewerIsOpen){ViewDataTable();}
    }
    if(Button==1)
    {
      Button=0;
      if(SelectedIndex>0)
      {
        SelectedIndex--;
        if(SelectedIndex<StartListIndex){LastListIndex--;StartListIndex--;}
      }
    }
    if(Button==2)
    {
      Button=0;
      if(SelectedIndex<filesCount-1)
      {
        SelectedIndex++;
        if(SelectedIndex>LastListIndex){LastListIndex++;StartListIndex++;}
      }
    }


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
     p.setFont(QFont("Arial", 20));

     p.drawPixmap( width()/6 , height()/8 , testTableImg);



    char str[20];
    for (int i=StartListIndex;i<=LastListIndex;i++)
    {
        if(i==SelectedIndex){p.setPen(Qt::red);}else{p.setPen(Qt::black);}
        p.drawText(width()/4, (height()/4)+((i-StartListIndex)*42)+10, QString(files[i]));

    }



}
