# include <stdio.h>
# include <stdlib.h>
# include <termio.h>
# include <unistd.h>
# include <fcntl.h>



bool SerialOpen();
void SerialClose();
bool SerialWriteLine(char inArray[]);
void SerialReadLine();
void WaitFdWriteable(int Fd);
unsigned char SerialRead();