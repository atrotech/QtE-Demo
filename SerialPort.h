# include <stdio.h>
# include <stdlib.h>
# include <termio.h>
# include <unistd.h>
# include <fcntl.h>


    bool SerialOpen(int ComPortNum);
    void SerialClose();
    int baudrate = 38400;
    bool SerialWriteLine(char inArray[]);
    int SerialReadLine(char* outArray);

    void WaitFdWriteable(int Fd);
    speed_t SerialChangeSpeed(int speed);
    int SerialFileStream = -1;

