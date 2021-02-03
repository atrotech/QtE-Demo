# include <stdio.h>
# include <stdlib.h>
# include <termio.h>
# include <unistd.h>
# include <fcntl.h>



int SerialOpen();
void SerialClose();
bool SerialWriteLine(char inArray[]);
char* SerialReadLine();
void WaitFdWriteable(int Fd);
