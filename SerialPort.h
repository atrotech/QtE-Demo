#include <QtCore/QtGlobal>
#include <QtWidgets>
#include <sys/time.h>
#include <signal.h>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include "lib/gpio.h"
#include "lib/common.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>

using namespace cv;



class SerialPort:
{

  public:
    void functionx();



  private:
    int x=0;


};
