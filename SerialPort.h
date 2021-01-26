#include <QtCore/QtGlobal>

# include <stdio.h>
# include <stdlib.h>
# include <termio.h>
# include <unistd.h>
# include <fcntl.h>
# include <getopt.h>
# include <time.h>
# include <errno.h>
# include <string.h>

class SerialPort{

    public:
    bool Open(int ComPortNum);
    bool Close();
    int baudrate = 38400;
    bool WriteLine(char inArray[]);
    int ReadLine(char* outArray);
    private:
    static inline void WaitFdWriteable(int Fd);

}