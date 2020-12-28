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

    p.drawText( width()/3 , height()/4 ,     QString(" تست ابعاد : %1  ").arg(distanceAverage));
    p.drawPixmap( width()/3-50 , height()/4-35 , tickImg);

    p.drawText( width()/3 , height()/4+100 , QString(" تست رنگ : %1 ").arg(totalColorAverage));
    p.drawPixmap( width()/3-50  , height()/4+65 , noneImg);

    p.drawText( width()/3 , height()/4+200 , QString(" تست نویز  : %1  ").arg(noise));
    p.drawPixmap( width()/3-50  , height()/4+165 , cancelImg);

    p.drawText( width()/3 , height()/4+300 , QString(" تست فریم  : %1  ").arg(67));
    p.drawPixmap( width()/3-50  , height()/4+265 , processImg);

}



void TVideoWidget::videoTest()
{

  int previousPixColor[3] = {0 , 0 , 0};
  int previousX = 0;
  int pixQuantity = 0;

  int blackRgbAverage[3] = {0 , 0 , 0};
  int greenRgbAverage[3] = {0 , 0 , 0};
  int blueRgbAverage[3] = {0 , 0 , 0};
  int redRgbAverage[3] = {0 , 0 , 0};



     for (int x = 0; x<InputFrame.cols; x++)
     {
        cv::Vec3b rgb = InputFrame.at<cv::Vec3b>(100,x);
        int pixColor[3] = {rgb[0]/100 , rgb[1]/100 , rgb[2]/100};

        if( pixColor[0] == previousPixColor[0] && pixColor[1] == previousPixColor[1] && pixColor[2] == previousPixColor[2] )
        {
        //  printf("x: %d (%d %d %d) \n " , x, pixColor[0], pixColor[1], pixColor[2]);
        }
        else
        {
          if(x-previousX < 5)
          {
          // printf("x: %d (%d %d %d) \n " , x, pixColor[0], pixColor[1], pixColor[2]);
          }
          else
          {
          //  printf("x: %d (%d %d %d)   *change color point ( distance: %d ) \n " , x, pixColor[0], pixColor[1], pixColor[2], x-previousX );
            distanceAverage = distanceAverage + (x-previousX);
          }
          previousX = x;
        }
        previousPixColor[0]=pixColor[0], previousPixColor[1]=pixColor[1], previousPixColor[2]=pixColor[2] ;
     }
     distanceAverage=distanceAverage/7;
     // printf(" \n Distance Average: %d \n ", distanceAverage);
     // printf(" \n --------------------- \n ");



// ------------------ Black Rgb Average ---------------------------------------
     for (int x = 660; x<InputFrame.cols-50; x++)
     {
       for (int y = 100; y<InputFrame.rows-50; y++)
       {
         cv::Vec3b rgb = InputFrame.at<cv::Vec3b>(y,x);
         blackRgbAverage[0]+=rgb[0] , blackRgbAverage[1]+=rgb[1] , blackRgbAverage[2]+=rgb[2] ;
         pixQuantity++ ;
       }
     }
     noise = ( (blackRgbAverage[0]/pixQuantity) + (blackRgbAverage[1]/pixQuantity) + (blackRgbAverage[2]/pixQuantity) )/3;
     // printf("Black RGB Average: (%d %d %d) \n " ,blackRgbAverage[0]/pixQuantity ,blackRgbAverage[1]/pixQuantity ,blackRgbAverage[2]/pixQuantity );
     // printf(" \n --------------------- \n ");



// ------------------- Green Rgb Average --------------------------------------
     pixQuantity = 0;
     for (int x = 280; x<340; x++)
     {
       for (int y = 100; y<InputFrame.rows-50; y++)
       {
         cv::Vec3b rgb = InputFrame.at<cv::Vec3b>(y,x);
         greenRgbAverage[0]+=rgb[0] , greenRgbAverage[1]+=rgb[1] , greenRgbAverage[2]+=rgb[2] ;
         pixQuantity++ ;
       }
     }
     int gGreen = greenRgbAverage[1]/pixQuantity ;
     //printf("Green RGB Average: (%d %d %d) \n " ,greenRgbAverage[0]/pixQuantity ,greenRgbAverage[1]/pixQuantity ,greenRgbAverage[2]/pixQuantity );
     //printf(" \n --------------------- \n ");


 // ----------------- Red Rgb Average -----------------------------------------
     pixQuantity = 0;
     for (int x = 560; x<620; x++)
     {
       for (int y = 100; y<InputFrame.rows-50; y++)
       {
         cv::Vec3b rgb = InputFrame.at<cv::Vec3b>(y,x);
         redRgbAverage[0]+=rgb[0] , redRgbAverage[1]+=rgb[1] , redRgbAverage[2]+=rgb[2] ;
         pixQuantity++ ;
       }
     }
     int rRed = redRgbAverage[0]/pixQuantity ;
     //printf("Red RGB Average: (%d %d %d) \n " ,redRgbAverage[0]/pixQuantity ,redRgbAverage[1]/pixQuantity ,redRgbAverage[2]/pixQuantity );
     //printf(" \n --------------------- \n ");


// --------------- Blue Rgb Average -------------------------------------------
     pixQuantity = 0;
     for (int x = 470; x<520; x++)
     {
       for (int y = 100; y<InputFrame.rows-50; y++)
       {
         cv::Vec3b rgb = InputFrame.at<cv::Vec3b>(y,x);
         blueRgbAverage[0]+=rgb[0] , blueRgbAverage[1]+=rgb[1] , blueRgbAverage[2]+=rgb[2] ;
         pixQuantity++ ;
       }
     }
     int bBlue = blueRgbAverage[2]/pixQuantity ;
     //printf("Blue RGB Average: (%d %d %d) \n " ,blueRgbAverage[0]/pixQuantity ,blueRgbAverage[1]/pixQuantity ,blueRgbAverage[2]/pixQuantity );
     //printf(" \n --------------------- \n ");




// --------------- Total color RGB Average ------------------------------------
     totalColorAverage = ( rRed + gGreen + bBlue )/3 ;







 // ------------------ save to file --------------------

    // ofstream MyFile("value.txt");
    // MyFile << distanceAverage << "\n" << totalColorAverage << "\n" << noise << "\n" ;
    // MyFile.close();

    std::ifstream MyReadFile("value.txt");
    int ReadValue;

    MyReadFile >> ReadValue;
    int distError = (distanceAverage - ReadValue);
    MyReadFile >> ReadValue;
    int colorError = (totalColorAverage - ReadValue);
    MyReadFile >> ReadValue;
    int noiseError = (noise - ReadValue);

    printf("Distance Error (distanceAverage) = %d %d \n",distError, distanceAverage);
    printf("Color Error (totalColorAverage) = %d %d \n",colorError, totalColorAverage);
    printf("Noise Error (noise) = %d %d \n",noiseError, noise);
    MyReadFile.close();






}









void TVideoWidget::saveReportTest()
{

  printf(" saveReportTest \n " );





  QApplication::quit();
}
