# include <stdio.h>
# include <stdlib.h>
# include <termio.h>
# include <unistd.h>
# include <fcntl.h>


class SerialPort{

    public:
    bool Open(byte ComPortNum);
    bool Close();
    int baudrate = 38400;
    bool WriteLine(char inArray[]);
    int ReadLine(char* outArray);

    private:
    static inline void WaitFdWriteable(int Fd);
    int SerialFileStream = -1;
};
