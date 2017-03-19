#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include "serialPort.h"
#include "pthread_resolveData.h"
#include "data.h"



#include <android/log.h>
#define   LOG_TAG    "LOG_TEST"
#define   LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define   LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)



const unsigned char portName[]="/dev/ttyS0";
unsigned int baudRate =19200;

pthread_t id_get_event,
          id_resolve_data;

void ReleaseResource(int signo)
{
 //   pthread_cancel (id_get_event);
//    pthread_cancel (id_resolve_data);
    exit(0);
}

//The enterance of function
int startProtocol()
{
    LOGI("log test mainentance");
    int nRet;
    nRet = serialPortInitialize();
    if(0 != nRet)
        return -2;
   //nRet = pthread_create(&id_get_event,0,pthread_getEvent,NULL);
   // if(0 == nRet)
   //     printf("*********pthread_getEvent create successful!*************\n");

    LOGI("log test 22222ntance");
  nRet = pthread_create(&id_resolve_data,0,pthread_resolveData,NULL);

    if(0 == nRet)
        printf("*********pthread_resolveData create successful!**********\n");
    
//    pthread_join (id_get_event, NULL);
//    printf ("g1\n");
//    pthread_join (id_resolve_data, NULL);
//    printf ("g2\n");
	
    /*Ctrl + C create SIGINT signal function*/ 
	signal (SIGINT, ReleaseResource);
    return 0;
}

