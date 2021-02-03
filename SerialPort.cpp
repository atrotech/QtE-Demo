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

unsigned char SerialRead(){
    unsigned char chr;
    while (read(SerialFileStream, &chr, 1)!=0);
    return chr;
}

void SerialReadLine(){
// Read up to 255 characters from the port if they are there
		unsigned char rx_buffer[256];
		int rx_length = read(SerialFileStream, (void*)rx_buffer, 255);		//Filestream, buffer to store in, number of bytes to read (max)
		if (rx_length < 0)
		{
			//An error occured (will occur if there are no bytes)
		}
		else if (rx_length == 0)
		{
			//No data waiting
		}
		else
		{
			//Bytes received
			rx_buffer[rx_length] = '\0';
			printf("%i bytes read : %s\n", rx_length, rx_buffer);
		}

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
