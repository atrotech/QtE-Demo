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
    if(Button==4){}
    if(Button==1){
      StatusIcon1 = processImg;
      StatusIcon2 = processImg;
      StatusIcon3 = processImg;
      StatusIcon4 = processImg;
      StatusIcon5 = processImg;
      StatusIcon6 = processImg;
      StatusIcon7 = processImg;
    }
    if(Button==2){}
    if(Button==3){}

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
    p.drawText( width()/3+40 , height()/1.5+10   , QString(" %1 ").arg("none"));
    p.drawText( width()/2+60 , height()/1.5+10   , QString(" %1 ").arg("none"));
    p.drawPixmap( width()/15  , height()/1.55  , StatusIcon6);
// ----------------------
    p.drawText( width()/6 , height()/1.2    , QString(" %1 ").arg("none"));
    p.drawText( width()/3+40 , height()/1.2 , QString(" %1 ").arg("none"));
    p.drawText( width()/2+60 , height()/1.2 , QString(" %1 ").arg("none"));
    p.drawText( width()/1.3-20 , height()/1.2 , QString(" %1 ").arg("none"));
    p.drawPixmap( width()/15  , height()/1.27 , StatusIcon7);


    if(MessageString[0]!=0)
    {
      int w = 450;
      int h = 150;
      p.fillRect( width()/2-(w/2), height()/2-(h/2),w,h,QBrush(QColor(130,230,130)));
      p.drawText( width()/2-(w/2)+70 , height()/2-10, QString(MessageString));
      p.drawText( width()/2-(w/2)+150 , height()/2+30, QString("ذخیره شد"));

      t++;
      if(t>30)
      {
        MessageString[0]=0;
        t=0;
      }
    }

    if(Button==1)
    {
      Button=0;
      //SerialWriteLine("A");
      SourceDelay();
      videoTest();
      //DataTest();
    }
    if(Button==2){Button=0;saveReportTest();}
    if(Button==3){Button=0;FlashSave();}
    if(Button==4){this->hide();Button=0;MessageString[0]=0;}


}

// ---------------------------- Save to flash ---------------------------------

void TVideoWidget::FlashSave()
{
  system("sudo mount -t vfat -o uid=pi,gid=pi /dev/sda1 /media/usb");
  system("ls /media/usb");
  system("sudo umount /media/usb");

}






// ---------------------------- Source Delay ----------------------------------

void TVideoWidget::SourceDelay()
{
  unsigned int FrameCount = 0;
  setGPIOValue(CaptureSelectPin,0);
  while (CheckBlackColor()==false )
  {
    FrameCount++;
  }
  printf("black frame resived ( %d )\n",FrameCount);

}





bool TVideoWidget::CheckBlackColor()
{
  int CheckColor[3];
  int pixQuantity = 0;
  IsFrameUpdated = false;
  for (int x=50; x<InputFrame.cols-50; x++)
  {
    for (int y=50; y<InputFrame.rows-50; y++)
    {
      while (!IsFrameUpdated);
      IsFrameUpdated=false;
      cv::Vec3b rgb = InputFrame.at<cv::Vec3b>(y,x);
      CheckColor[0]+=rgb[0];
      CheckColor[1]+=rgb[1];
      CheckColor[2]+=rgb[2];
      pixQuantity++;
    }
  }
  CheckColor[0] /= pixQuantity;
  CheckColor[1] /= pixQuantity;
  CheckColor[2] /= pixQuantity;
  if ( ((CheckColor[0]+CheckColor[1]+CheckColor[2])/3) < 30 )
  {
    printf("Black screen checked ✅\n");
    return true;
  }
  else return false;

}







// ------------------------------ Data Test -----------------------------------
void TVideoWidget::DataTest()
{

  int fs = SerialOpen();
  SerialWriteLine("B");
  unsigned char chr = 0;
  int i = 0;
  int j = 0;
  bool isReciving = true;
  while (isReciving)
  {
    if(read(fs, &chr, 1)==1)
    {
      if(chr=='#')
      {
        isReciving = false;
      }
      else if(chr==',')
      {
        str[i][j] = '\0';
        i++;
        j=0;
        printf("new value\n");
      }
      else
      {
        str[i][j] = chr;
        j++;
        printf("%d,%d\n",i,j);
      }
    }
  }
  printf("Recived Complete\n");

  printf("Serial-1 Error: %s\n",str[0]);
  printf("Serial-2 Error: %s\n",str[1]);
  printf("Max Current: %s\n",str[2]);
  printf("pick time: %s\n",str[3]);
  printf("Avg Current: %s\n",str[4]);
  printf("Voltage: %s\n",str[5]);


  SerialClose();
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


  if(measuredError[0]<5)StatusIcon1 = tickImg;
  else StatusIcon1 = cancelImg;

  if(measuredError[1]<5)StatusIcon2 = tickImg;
  else StatusIcon2 = cancelImg;

  if(measuredError[2]<5)StatusIcon3 = tickImg;
  else StatusIcon3 = cancelImg;



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
    sprintf (fileName, "%d-%d-%d-%d-%d-%d.csv", 1900+ltm->tm_year, 1+ltm->tm_mon, ltm->tm_mday, 4+ltm->tm_hour, 1+ltm->tm_min, 1+ltm->tm_sec);
    sprintf (pathDir, "reports/%s", fileName);
    ofstream MyFile(pathDir);
    MyFile << refrenceValue[0] << "," << totalMeasured[0] << "," << measuredError[0] << "\n";
    MyFile << refrenceValue[1] << "," << totalMeasured[1] << "," << measuredError[1] << "\n";
    MyFile << refrenceValue[2] << "," << totalMeasured[2] << "," << measuredError[2] << "\n";
    MyFile << InputFrame.data;
    MyFile.close();
    sprintf(MessageString,"%s",fileName);


}
