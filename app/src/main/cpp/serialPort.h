#ifndef  _SERIALPORT_H_
#define  _SERIALPORT_H_

int serialPortInitialize();
void readData(unsigned char* buf,unsigned int bufSize);
void writeData(unsigned char const* buf, unsigned int bufSize);

#endif

