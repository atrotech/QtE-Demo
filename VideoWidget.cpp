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
    p.setFont(QFont("Arial", 28));

    p.drawText( width()/3 , height()/4 ,     QString(" تست درصد اختلاف ابعاد : %1  ").arg(singleMeasured[0]));
    p.drawPixmap( width()/3-50 , height()/4-35 , tickImg);

    p.drawText( width()/3 , height()/4+100 , QString(" تست درصد اختلاف رنگ : %1  ").arg(colorDiffPer));
    p.drawPixmap( width()/3-50  , height()/4+65 , noneImg);

    p.drawText( width()/3 , height()/4+200 , QString(" تست درصد اختلاف نویز : %1  ").arg(noiseDiffPer));
    p.drawPixmap( width()/3-50  , height()/4+165 , cancelImg);

    p.drawText( width()/3 , height()/4+300 , QString(" تست درصد اختلاف فریم : %1  ").arg(67));
    p.drawPixmap( width()/3-50  , height()/4+265 , processImg);

}

void TVideoWidget::videoTest(){
  singleFrameTest();
}


void TVideoWidget::singleFrameTest()
{
  float distanceAverage = 0;
  float totalColorAverage=0;
  float noise = 0;

  int difRGB[3] = {0,0,0};
  int BarsWidth[9];
  int j=1;

  int rgbAverage[3] = {0,0,0};
  int pixQuantity = 0;
  int colorRgb = 0;

// ------------------------ change color point --------------------------------
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
 // ------------------------- noise Average -----------------------------------
     printf(" BarsWidth[1]: %d \n", BarsWidth[1]);
     printf(" BarsWidth[2]: %d \n", BarsWidth[2]);
     printf(" BarsWidth[3]: %d \n", BarsWidth[3]);
     printf(" BarsWidth[4]: %d \n", BarsWidth[4]);
     printf(" BarsWidth[5]: %d \n", BarsWidth[5]);
     printf(" BarsWidth[6]: %d \n", BarsWidth[6]);
     printf(" BarsWidth[7]: %d \n", BarsWidth[7]);
     printf(" BarsWidth[8]: %d \n", BarsWidth[8]);
     printf(" BarsWidth[9]: %d \n", BarsWidth[9]);



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

// ------------------- Red Rgb Average --------------------------------------
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

// ------------------- Blue Rgb Average --------------------------------------
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

    int rgbAverage = (rgbAverage[0]+rgbAverage[1]+rgbAverage[2])/3 ;

    printf(" rgbAverage : %d \n", rgbAverage);


 // -------------------------- save to file -----------------------------------

    //ofstream MyFile("value.txt");
    //MyFile << distanceAverage << "\n" << totalColorAverage << "\n" << noise << "\n" ;
    //MyFile.close();



 // -------------------------- read from file ---------------------------------
    std::ifstream MyReadFile("value.txt");
    int ReadValue;
    int i=0;
    while(MyReadFile >> ReadValue){
      refrenceValue[i]=ReadValue;
      i++;
    }
    MyReadFile.close();


 // --------------------- difference percentage -------------------------------
    // singleMeasured[0] = distanceAverage;
    // singleMeasured[1] = totalColorAverage;
    // singleMeasured[2] = noise;

    distDiffPer = (( distanceAverage - refrenceValue[0] )/ refrenceValue[0] )*100;
    colorDiffPer = (( totalColorAverage - refrenceValue[1] )/ refrenceValue[1] )*100;
    noiseDiffPer = (( noise - refrenceValue[2] )/ refrenceValue[2] )*100;



}








void TVideoWidget::saveReportTest()
{

  printf(" saveReportTest \n " );





  QApplication::quit();
}
