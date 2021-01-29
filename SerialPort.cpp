#include "SerialPort.h"


extern int SerialFileStream = -1;

bool SerialOpen()
{

    char *DeviceName = "/dev/ttyAMA3";

    SerialFileStream = open(DeviceName, O_RDWR | O_NOCTTY | O_NDELAY);

    if (fcntl(SerialFileStream, F_SETFL, O_NONBLOCK) < 0)return false;

    struct termios options;
    tcgetattr(SerialFileStream, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;		//<Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(SerialFileStream, TCIFLUSH);
    tcsetattr(SerialFileStream, TCSANOW, &options);

    return true;
}

bool SerialWriteLine(char inArray[]){
    int i = 0;
    while(inArray[i]!=0)
    {
        WaitFdWriteable(SerialFileStream);
        if (write(SerialFileStream, &inArray[i], 1) < 0)return false;
        i++;
    }
    return true;
}

char* SerialReadLine(){
    char chr[100] = 0;
    int i = 0;
     while (chr[i]!='\n')
      {
        if(read(SerialFileStream, &chr[i], 1)==1)i++;
      }
    return chr;
}

void WaitFdWriteable(int Fd)
{
    fd_set WriteSetFD;
    FD_ZERO(&WriteSetFD);
    FD_SET(Fd, &WriteSetFD);
    if (select(Fd + 1, NULL, &WriteSetFD, NULL, NULL) < 0) { }
}

void SerialClose(){
    close(SerialFileStream);
}
