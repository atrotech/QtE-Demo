#include "SerialPort.h"

SerialPort::SerialPort()
{


}

static inline speed_t changeSpeed(int speed)
{
    switch (speed)
    {
        case 0:return B0;
        case 1200:return B1200;
        case 2400:return B2400;
        case 4800:return B4800;
        case 9600:return B9600;
        case 38400:return B38400;
        case 115200:return B115200;
        case 250000:return B250000;
        default:B9600
    }
}

bool SerialPort::Open(byte ComPortNum)
{
    speed_t baudStruct = changeSpeed(baudrate);

    char *DeviceName = "/dev/ttyAMA";
    sprintf(DeviceName,"%s%d",DeviceName,ComPortNum);

    SerialFileStream = open(DeviceName, O_RDWR | O_NOCTTY | O_NDELAY);

    if (fcntl(SerialFileStream, F_SETFL, O_NONBLOCK) < 0)return false;
    

    struct termios options;
    tcgetattr(SerialFileStream, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;		//<Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    cfsetospeed(options,baudStruct);
    cfsetispeed(options,baudStruct);
    tcflush(SerialFileStream, TCIFLUSH);
    tcsetattr(SerialFileStream, TCSANOW, &options);

    return true;
}

bool SerialPort::WriteLine(char* outArray){
    char* chr = outArray;
    for (; *chr != '\0'; ++chr)
    {
        WaitFdWriteable(SerialFileStream);
        if (write(SerialFileStream, &chr, 1) < 0)return false;
    }
    return true;
}

int SerialPort::ReadLine(char* outArray){
    char chr = 0;
    int index = 0;
     while (read(SerialFileStream, &chr, 1) == 1)
      {
        outArray[index] = chr;
        index++;
        if(chr=='\n')return index;
      }
    return -1;
}

static inline void WaitFdWriteable(int Fd)
{
    fd_set WriteSetFD;
    FD_ZERO(&WriteSetFD);
    FD_SET(Fd, &WriteSetFD);
    if (select(Fd + 1, NULL, &WriteSetFD, NULL, NULL) < 0) { }
}

void SerialPort::Close(){
    close(SerialFileStream);
}

