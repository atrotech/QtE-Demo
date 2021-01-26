#include "SerialPort.h"

SerialPort::SerialPort()
{


}

SerialPort::Open(int ComPortNum)
{
    int CommFd;
    int DeviceSpeed = B38400;
    struct termios port_settings;
    
    const char *DeviceName = "/dev/ttyAMA3";
    CommFd = open(DeviceName, O_RDWR, 0);
    if (fcntl(CommFd, F_SETFL, O_NONBLOCK) < 0)return false;
    //Cau hinh tham so com port
    //baudrate 9600, 8N1
    cfsetispeed(&port_settings, B9600);
    cfsetospeed(&port_settings, B9600);

    port_settings.c_cflag &= ~PARENB;   //Set no parity
    port_settings.c_cflag &= ~CSTOPB;   //Set 1 stop bit
    port_settings.c_cflag &= ~CSIZE;    //Set 8 bit data using mask bit
    port_settings.c_cflag |= CS8;
    port_settings.c_cflag &= ~CRTSCTS;  //No hadware hanshaking

    tcsetattr(fd, TCSANOW, &port_settings); // apply the settings to the port
    return true;
}

SerialPort::WriteLine(char* outArray){
    char* chr = outArray;
    for (; *chr != '\0'; ++chr)
    {
        WaitFdWriteable(CommFd);
        if (write(CommFd, &chr, 1) < 0)return false;
    }
    return true;
}

SerialPort::ReadLine(char* outArray){
    char chr = 0;
    int index = 0;
     while (read(CommFd, &chr, 1) == 1)
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
    if (select(Fd + 1, NULL, &WriteSetFD, NULL, NULL) < 0) {
	  printf("%s",strerror(errno));
    }
}


