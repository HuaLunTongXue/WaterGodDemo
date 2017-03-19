#include <termios.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>


#include <android/log.h>
#define   LOG_TAG    "LOG_TEST"
#define   LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define   LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


int fd;


int serialInitialization(const unsigned char* portName,unsigned int baudRate);

int serialPortInitialize()
{
    char portName[20]={0};
    int fd;
    char c;
    char buf[20]={0};
    int baudRate = 0;
    int i;


    memcpy(portName, "/dev/", 5);
    if (-1 == (fd = open("/sdcard/VMC/config.ini", O_RDONLY))) {  // 读取配置文件，获取串口号，波特率
        printf("open config error\n");
        return -1;
    }
    read(fd, &c, 1);
    while (c != 10) {
        i = 0;
        while (c != '=') {
            buf[i++] = c;
            read(fd, &c, 1);
        }
        i = 0;
        if (!memcmp("commport", buf, 8)) {
            read(fd, &c, 1);
            while (c != 10) {
                portName[5 + i] = c;
                i++;
                read(fd, &c, 1);
            }
            portName[5 + i] = 0;  // 串口号
        } else if (!memcmp("baudrate", buf, 8)) {
            read(fd, &c, 1);
            while (c != 10) {
                baudRate = baudRate * 10 + c - 48;  // 波特率
                read(fd, &c, 1);
            }
        } else if (!memcmp("debug", buf, 5)) {
            read(fd, &c, 1);
            i = 0;
            while (c != 10) {
                buf[i++] = c;
                read(fd, &c, 1);
            }
            // if (!memcmp("true", buf, 4))
            //      debug = true;
            //  else
            //      debug = false;
        }
        read(fd, &c, 1);
    }
    if (-1 == close(fd)) {
        printf("close config error");
        return -2;
    }

    serialInitialization(portName, baudRate);


}


int serialInitialization(const unsigned char* portName,unsigned int baudRate)
{
    struct termios Opt;
    speed_t s;
    LOGI("3333333333");
    fd = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);	
    printf("fd=%d\n",fd);
    LOGI("44444444");

    if (fd >0) 
        printf("serial open successful\n");
    else 
    {
        printf("serial open error\n");
        return -1;
    }
    if (0 == fcntl(fd, F_SETFL, 0)) 
        printf("serial fcntl successful\n");
    else
    {
        printf("serial fcntl error\n");
        return -1;
    }
    if (0 == tcgetattr(fd, &Opt)) 
        printf("serial tcgetattr successful\n");
    else
    {
        printf("serial tcgetattr error\n");  
        return -1;     
    }
    switch (baudRate) {
    case 115200 :
        s = B115200;
        break;
    case 38400 :
        s = B38400;
        break;
    case 19200 :
        s = B19200;
        break;
    case 9600:
        s = B9600;
        break;
    default :
       printf("serial baudRate error\n");
    }
    LOGI("55555555");
    cfsetispeed(&Opt, s); 					
    cfsetospeed(&Opt, s);
    LOGI("666666666");

//Opt.c_cflag &= ~CSTOPB;  // one stop bit
//Opt.c_cflag |= (CLOCAL | CREAD);

//Opt.c_cflag &= ~PARENB;     //no
//Opt.c_cflag &= ~CSTOPB;    //one stop bit
//Opt.c_cflag &= ~CSIZE;
//Opt.c_cflag |= CS8;       //length

	// raw input/output
cfmakeraw(&Opt);  // no parity, Mask the character size bits, 8 bit
  //  Opt.c_cflag |= PARENB;     
  //  Opt.c_cflag &= ~PARODD; 
  //  Opt.c_iflag |= (INPCK /*| ISTRIP*/);     
	//Opt.c_cc[VMIN] = 1;		
	//Opt.c_cc[VTIME] = 0;

    LOGI("7777777777");
    tcflush(fd, TCIOFLUSH);
    LOGI("88888888888");
    if (tcsetattr(fd, TCSANOW, &Opt) != 0)
       printf("serial tcsetattr error\n");  
    else
        printf("serial tcsetattr successful\n");

    LOGI("999999999999");
    return 0;
}





void readData(unsigned char* buf,unsigned int bufSize)
{ 
    unsigned int len = 0;
    int len1;

    while (len < bufSize) {
        len1 = read(fd, (char*)(buf + len), bufSize - len);       
        if (-1 == len1) {
            printf("serial read error\n");
        }
        else 
            printf("serial read successful\n");
        len += len1;
    }

}

void writeData(unsigned char const* buf, unsigned int bufSize)
{
	unsigned int len = 0;
	int len1;

	while (len < bufSize) {
		len1 = write(fd, (char*)(buf + len), bufSize - len);
		if (-1 == len1) {
			printf("serial write error\n");
		}
		len += len1;
	}

}



