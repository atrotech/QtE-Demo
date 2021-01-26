# include <stdio.h>
# include <stdlib.h>
# include <termio.h>
# include <unistd.h>
# include <fcntl.h>


class SerialPort{

public:
bool Open(int ComPortNum);
void Close();
int baudrate = 38400;
bool WriteLine(char inArray[]);
int ReadLine(char* outArray);

private:
  void SerialPort::WaitFdWriteable(int Fd);
  speed_t SerialPort::changeSpeed(int speed);
  int SerialFileStream = -1;

};
