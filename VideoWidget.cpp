#include "VideoWidget.h"



using namespace cv;
using namespace std;

TVideoWidget::TVideoWidget(QWidget *parent) :
    QWidget(parent)
{
    const QString qwsDisplay = QString(qgetenv("QWS_DISPLAY"));

    mpKeepAliveTimer = new QTimer();
    mpKeepAliveTimer->setSingleShot(false);
    QObject::connect(mpKeepAliveTimer, SIGNAL(timeout()), this, SLOT(onKeepAlive()));
    mpKeepAliveTimer->start(100);

    MessageString[0]=0;

}



void TVideoWidget::onKeepAlive() {
    update();
}

void TVideoWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    int SpaceHeight = 160;
    int HeightOffset = 60;
    if(Button==4){this->hide();Button=0;MessageString[0]=0;}
    if(Button==1){Button=0;videoTest();}
    if(Button==2){Button=0;saveReportTest();}
    if(Button==3){Button=0;saveReportTest();}

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
    p.setFont(QFont("Arial", 24));

    p.drawPixmap( width()/9 , height()/8 , tableImg);

    p.drawText( width()/6 , height()/3+10 ,  QString(" %1 ").arg(measuredError[0]));
    p.drawText( width()/3-40 , height()/3+10 ,  QString(" %1 ").arg(totalMeasured[0]));
    p.drawText( width()/2-20 , height()/3+10 ,  QString(" %1 ").arg(refrenceValue[0]));
    p.drawPixmap( width()/1.3-15  , height()/3-35 , tickImg);

    p.drawText( width()/6 , height()/2-20 , QString(" %1 ").arg(measuredError[1]));
    p.drawText( width()/3-40 , height()/2-20 ,  QString(" %1 ").arg(totalMeasured[1]));
    p.drawText( width()/2-20 , height()/2-20 ,  QString(" %1 ").arg(refrenceValue[1]));
    p.drawPixmap( width()/1.3-15   , height()/2-50 , noneImg);

    p.drawText( width()/6 , height()/1.65 , QString(" %1 ").arg(measuredError[2]));
    p.drawText( width()/3-40 , height()/1.65 ,  QString(" %1 ").arg(totalMeasured[2]));
    p.drawText( width()/2-20 , height()/1.65 ,  QString(" %1 ").arg(refrenceValue[2]));
    p.drawPixmap( width()/1.3-15  , height()/1.7-10 , cancelImg);

    p.drawText( width()/6 , height()/1.3-10 , QString(" %1 ").arg("none"));
    p.drawText( width()/3-40 , height()/1.3-10 , QString(" %1 ").arg("none"));
    p.drawText( width()/2-20 , height()/1.3-10 , QString(" %1 ").arg("none"));
    p.drawPixmap( width()/1.3-15  , height()/1.4 , processImg);

    if(MessageString[0]!=0)
    {
      int w = 450;
      int h = 150;
      p.fillRect( width()/2-(w/2), height()/2-(h/2),w,h,QBrush(QColor(130,230,130)));
      p.drawText( width()/2-(w/2)+70 , height()/2, QString(MessageString));
      p.drawText( width()/2-(w/2)+150 , height()/2+35, QString("ذخیره شد"));

      t++;
      if(t>30)
      {
        MessageString[0]=0;
        t=0;
      }
    }

}


void TVideoWidget::videoTest()
{
// --------------------------- Total Measured ---------------------------------
  for (int x = 0; x<500; x++)
  {
    singleFrameTest();
    totalMeasured[0] += singleMeasured[0] ;
    totalMeasured[1] += singleMeasured[1] ;
    totalMeasured[2] += singleMeasured[2] ;
  }
  totalMeasured[0]  /= 500;
  totalMeasured[1]  /= 500;
  totalMeasured[2]  /= 500;

// -------------------------- read from file ----------------------------------
  std::ifstream MyReadFile("value.txt");
  float ReadValue;
  int i=0;
  while(MyReadFile >> ReadValue){
    refrenceValue[i]=ReadValue; i++;
  }
  MyReadFile.close();

// --------------------- difference percentage - error ------------------------
  measuredError[0] = abs((( totalMeasured[0] - refrenceValue[0] )/ refrenceValue[0] )*100);
  measuredError[1] = abs((( totalMeasured[1] - refrenceValue[1] )/ refrenceValue[1] )*100);
  measuredError[2] = abs((( totalMeasured[2] - refrenceValue[2] )/ refrenceValue[2] )*100);

  measuredError[0]= (int)(measuredError[0]*100.0)/100.0;
  measuredError[1]= (int)(measuredError[1]*100.0)/100.0;
  measuredError[2]= (int)(measuredError[2]*100.0)/100.0;

}





void TVideoWidget::singleFrameTest()
{

// ---------------------------- variables -------------------------------------
  int difRGB[3] = {0,0,0};
  int BarsWidth[9];
  int j=1;
  int rgbAverage[3] = {0,0,0};
  int pixQuantity = 0;
  int colorRgb = 0;

  singleMeasured[0] = 0 ;
  singleMeasured[1] = 0 ;
  singleMeasured[2] = 0 ;

// ------------------------ change color points -------------------------------
   BarsWidth[0]=0;
   for (int x = 1; x<InputFrame.cols; x++)
   {
      cv::Vec3b currentRGB = InputFrame.at<cv::Vec3b>(100,x);
      cv::Vec3b prevRGB = InputFrame.at<cv::Vec3b>(100,x-1);

      difRGB[0] = abs(prevRGB[0]-currentRGB[0]);
      difRGB[1] = abs(prevRGB[1]-currentRGB[1]);
      difRGB[2] = abs(prevRGB[2]-currentRGB[2]);
      if( difRGB[0]>50 || difRGB[1]>50 || difRGB[2]>50){BarsWidth[j++]=x;x+=10;}
    }

 // ---------------------- Distance Average -----------------------------------
    for(int x=0; x<7; x++){singleMeasured[0] += (BarsWidth[x+1] - BarsWidth[x]);}
    singleMeasured[0] /= 7;
    singleMeasured[0]= (int)(singleMeasured[0]*100.0)/100.0;

// ------------------- Green Rgb Average --------------------------------------
    for (int x = BarsWidth[3]; x<BarsWidth[4]; x++)
    {
      for (int y = 50; y<InputFrame.rows-50; y++)
      {
        cv::Vec3b rgb = InputFrame.at<cv::Vec3b>(y,x);
        colorRgb += rgb[1]; pixQuantity++ ;
      }
    }
    rgbAverage[1] = colorRgb/pixQuantity ;

// --------------------- Red Rgb Average --------------------------------------
    colorRgb = 0; pixQuantity = 0;
    for (int x = BarsWidth[6]; x<BarsWidth[7]; x++)
    {
      for (int y = 50; y<InputFrame.rows-50; y++)
      {
        cv::Vec3b rgb = InputFrame.at<cv::Vec3b>(y,x);
        colorRgb += rgb[0]; pixQuantity++ ;
      }
    }
    rgbAverage[0] = colorRgb/pixQuantity ;

// ---------------------- Blue Rgb Average ------------------------------------
    colorRgb = 0; pixQuantity = 0;
    for (int x = BarsWidth[5]; x<BarsWidth[6]; x++)
    {
      for (int y = 50; y<InputFrame.rows-50; y++)
      {
        cv::Vec3b rgb = InputFrame.at<cv::Vec3b>(y,x);
        colorRgb += rgb[2]; pixQuantity++ ;
      }
    }
    rgbAverage[2] = colorRgb/pixQuantity ;

    singleMeasured[1] = (rgbAverage[0]+rgbAverage[1]+rgbAverage[2])/3 ;
    singleMeasured[1]= (int)(singleMeasured[1]*100.0)/100.0;

// ----------------------- black area noise -----------------------------------
    colorRgb = 0; pixQuantity = 0;
    for (int x = BarsWidth[7]; x<InputFrame.cols; x++)
    {
      for (int y = 50; y<InputFrame.rows-50; y++)
      {
        cv::Vec3b rgb = InputFrame.at<cv::Vec3b>(y,x);
        colorRgb += ((rgb[0] + rgb[1] + rgb[2])/3); pixQuantity++ ;
      }
    }
    singleMeasured[2] = colorRgb/pixQuantity ;
    singleMeasured[2]= (int)(singleMeasured[2]*100.0)/100.0;

}



void TVideoWidget::saveReportTest()
{
// -------------------------- save to file -----------------------------------
    time_t now = time(0); tm *ltm = localtime(&now);      // https://www.isip.piconepress.com/courses/temple/ece_3822/resources/tutorials/cpp/cpp_date_time.pdf
    char pathDir[40];
    char fileName[30];
    sprintf (fileName, "%d-%d-%d-%d:%d:%d.csv", 1900+ltm->tm_year, 1+ltm->tm_mon, ltm->tm_mday, 4+ltm->tm_hour, 1+ltm->tm_min, 1+ltm->tm_sec);
    sprintf (pathDir, "reports/%s", fileName);
    ofstream MyFile(pathDir);
    MyFile << refrenceValue[0] << "," << totalMeasured[0] << "," << measuredError[0] << "\n";
    MyFile << refrenceValue[1] << "," << totalMeasured[1] << "," << measuredError[1] << "\n";
    MyFile << refrenceValue[2] << "," << totalMeasured[2] << "," << measuredError[2] << "\n";
    MyFile << InputFrame.data;
    MyFile.close();
    sprintf(MessageString,"%s",fileName);


}
