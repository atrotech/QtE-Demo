# include <stdio.h>
# include <stdlib.h>
# include <termio.h>
# include <unistd.h>
# include <fcntl.h>


    bool SerialOpen();
    void SerialClose();
    bool SerialWriteLine(char inArray[]);
    int SerialReadLine(char* outArray);

    void WaitFdWriteable(int Fd);
  

