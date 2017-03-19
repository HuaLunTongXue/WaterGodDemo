#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
#include "data.h"
#include "serialPort.h"
#include <semaphore.h>
#include "pthread_resolveData.h"
//#include "../../../../../../../../Library/Android/sdk/ndk-bundle/platforms/android-21/arch-mips64/usr/include/jni.h"


#include <android/log.h>




#define   LOG_TAG    "LOG_TEST"
#define   LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define   LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)




sem_t event_sem_id;

void setEvent(int Id) {
    nEventID = Id;
    sem_post(&event_sem_id);
}

int getEvent() {
    sem_wait(&event_sem_id);  // 等待事件发生
    return nEventID;
}



void setPollFlag(int setValue)
{
	PollFlag = setValue;
printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%PollFlag =%d\n",PollFlag);	
}

#if 0
void PrintDebug(unsigned char *data, int len,int type)
{
    int i = 0;
    char temp[2048], buf[128],disp[10];
	
    memset(temp, 0, sizeof(temp));
	memset(disp,0,sizeof(disp));
	if(1 == type)
	    memcpy(disp,"[write]",sizeof("[write]"));
	else if(0 == type)
		memcpy(disp,"[read]",sizeof("[read]"));
	
    sprintf(temp, "\r\n%s:%d", disp, len);
    for(i = 0; i < len; i++)
    {
        if(i % 16 == 0)
        {
            strcat(temp, "\r\n");
            if(strlen(temp) >= 1024)
            {
                printf("%s", temp);
                memset(temp, 0, sizeof(temp));
            }
        }
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "%02X ", data[i]);
        strcat(temp, buf);
    }
    strcat(temp, "\r\n");
    printf("%s", temp);
}
#endif




void PrintDebug(unsigned char *data, int len,int type)
{
    int i = 0;
    char temp[2048], buf[128],disp[10];

    memset(temp, 0, sizeof(temp));
    memset(disp,0,sizeof(disp));
    if(1 == type)
        memcpy(disp,"[write]",sizeof("[write]"));
    else if(0 == type)
        memcpy(disp,"[read]",sizeof("[read]"));

    sprintf(temp, "\r\n%s:%d", disp, len);
    for(i = 0; i < len; i++)
    {
        if(i % 16 == 0)
        {
            strcat(temp, "\r\n");
            if(strlen(temp) >= 1024)
            {
                LOGI("%s", temp);
                memset(temp, 0, sizeof(temp));
            }
        }
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "%02X ", data[i]);
        strcat(temp, buf);
    }
    strcat(temp, "\r\n");
    LOGI("%s", temp);
}






void frameSendDataGenerate(unsigned char cmd, unsigned char sn, unsigned char*data,unsigned int datasize)
{	
	nFcc= 0x00;
	FrameSend[0] = START_VALUE;	
	nLen = datasize + 4; 
	LenValue[0] = nLen>> 8;
	LenValue[1] = nLen & 0xFF;	
	FrameSend[1] = LenValue[0];
	FrameSend[2] = LenValue[1];
	FrameSend[3] = cmd;	
	FrameSend[4] = sn;
	memcpy(FrameSend + 5, data, datasize);

    for(unsigned int i=0;i<nLen;i++)
        nFcc^=FrameSend[i+1];
    
    FrameSend[nLen + 1] = nFcc;
	nFrameSendLen = datasize + 6;
}

void clearData()
{	
    memset(FrameReceive,0, sizeof(FrameReceive));
	memset(FrameSend,0, sizeof(FrameSend));
	memset(DataReceive,0, sizeof(DataReceive));
	memset(DataSend,0, sizeof(DataSend));
	nDataSendLen = 0;
	PollFlag = 0;
}


void ReturnConfigIndVenderID()
{
    DataSend[0] = 0x02;
    memcpy(DataSend + 1,szVenderID , VENDERIDLENGTH);
    nDataSendLen = VENDERIDLENGTH + 1;
    frameSendDataGenerate(CONFIG_IND,SN, DataSend, nDataSendLen);
    writeData(FrameSend, nFrameSendLen);

}

void ReturnFlowControler()
{
    DataSend[0] = 0x03;
    memcpy(DataSend + 1,szFlowControler,FLOWCONTROLERLENGTH);
    nDataSendLen = FLOWCONTROLERLENGTH + 1;
    frameSendDataGenerate(CONFIG_IND, SN,DataSend, nDataSendLen);
    writeData(FrameSend, nFrameSendLen);
}

void ReturnLitreTime()
{
    DataSend[0] = 0x04;
    DataSend[1] = nLitre;
    DataSend[2] = nTime;
    nDataSendLen = 3;
    frameSendDataGenerate(CONFIG_IND, SN,DataSend, nDataSendLen);
    writeData(FrameSend, nFrameSendLen);

}

void ReturnVendoutAction()
{
    DataSend[0] = 0x02;
    DataSend[1] = 0x01;
    DataSend[2] = nLitreValue;
    nDataSendLen = 3;
    frameSendDataGenerate(VENDOUT_IND,SN, DataSend, nDataSendLen);
    writeData(FrameSend, nFrameSendLen);
   // sleep(3);
}
  
int GetSelectedColumnId() {
     return nLitreValue;
}


void ReturnGetInfo()
{
    LOGI("@@@@!!!%d\n",nInfoType);
    DataSend[0] = (char)nInfoType &0xff;

    LOGI("@@@@@%d\n",DataSend[0]);
    nDataSendLen = 1;
    frameSendDataGenerate(GET_INFO,SN, DataSend, nDataSendLen);
    writeData(FrameSend, nFrameSendLen);
}

void ReturnGetStatus()
{
    DataSend[0] = nStatusType & 0xFF;
    nDataSendLen = 1;
    frameSendDataGenerate(GET_STATUS,SN, DataSend, nDataSendLen);
    writeData(FrameSend, nFrameSendLen);
}

void ReturnReset()
{
    DataSend[0] = 0x05;
    nDataSendLen = 1;
    frameSendDataGenerate(CONFIG_IND, SN,DataSend, nDataSendLen);
    writeData(FrameSend, nFrameSendLen);

}

void getMachineId(unsigned char *gMI)
{
    memcpy(gMI,szVenderID, sizeof(szVenderID));
}

//void getMaxLitreAndTime(int Litre,int Time)
//{
//    Litre=nLitre;
//    Time= nTime;
//}


void getMachineFC(unsigned char* gFC)
{
    memcpy(gFC,szFlowControler, sizeof(szFlowControler));
}


void setMachineID(unsigned char  *szSetVenderID)
{

    LOGI("@@@@@@");
    memset(szVenderID,0,sizeof(szVenderID));
    LOGI("@@@@@@111111");

//    char * t = "11111111";

//    memcpy(szVenderID,"12345678",8);
    memcpy(szVenderID,szSetVenderID,8);
//    memcpy(szVenderID,t,8);
    PollFlag = 2;
    LOGI("@@@@@@22222");
}

void setFlowControler(unsigned char* szSetFlow)
{
	memset(szFlowControler,0,sizeof(szFlowControler));
    //LOGI("1111%p,",szSetFlow[0]);
    LOGI("1111%s,",szSetFlow);


    memcpy(szFlowControler,szSetFlow,FLOWCONTROLERLENGTH);
    PollFlag = 3; 
}

void setMaxLitreAndTime(char nSetLitre,char nSetTime)
{
    nLitre = nSetLitre;
    nTime = nSetTime;
    PollFlag = 4;
}

void SetReset()
{
    PollFlag = 8;
}



void setVenderAction(int nSetLitreValue)
{
    nLitreValue = nSetLitreValue;
    LOGI("#########出水%d\n",nLitreValue);
    PollFlag = 5;
}

void getInfo(int nSetInfoType)
{
	nInfoType = nSetInfoType;

    LOGI("!@!@!@!@%d\n",nInfoType);
	PollFlag = 6;
}

void getStatus(int nSetStatusType)
{
   nStatusType = nSetStatusType;
   PollFlag = 7;

}



int getRpt(int m_type, unsigned char *gR) 
{
    if (2 == m_type)
    {
        memcpy(gR, vmcConfigVenderID, sizeof(vmcConfigVenderID));
        return sizeof(vmcConfigVenderID);
    }
    else if (3 == m_type)
    {
        memcpy(gR, vmcConfigVenderVersion, sizeof(vmcConfigVenderVersion));
        return sizeof(vmcConfigVenderVersion);
    }
    else if (4 == m_type)
    {
        memcpy(gR, vmcConfigVenderPulse, sizeof(vmcConfigVenderPulse));
        return sizeof(vmcConfigVenderPulse);
    }
    else if (5 == m_type)
    {
        memcpy(gR, vmcConfigVenderMaxLitre, sizeof(vmcConfigVenderMaxLitre));
        return sizeof(vmcConfigVenderMaxLitre);
    }
    else if (6 == m_type)
    {
        memcpy(gR, vmcConfigVenderTotalLitre, sizeof(vmcConfigVenderTotalLitre));
        return sizeof(vmcConfigVenderTotalLitre);
    }
    else if (7 == m_type)
    {
        memcpy(gR, vmcConfigVenderWaitTime, sizeof(vmcConfigVenderWaitTime));
        return sizeof(vmcConfigVenderWaitTime);
    }
    else if (8 == m_type)
    {
        memcpy(gR, vmcPumpingTime, sizeof(vmcPumpingTime));
        return sizeof(vmcPumpingTime);
    }
    else if (9 == m_type)
    {
        memcpy(gR, vmcConfigVenderDetails, sizeof(vmcConfigVenderDetails));
        return sizeof(vmcConfigVenderDetails);
    }
}

int getStatusRpt(int m_type, unsigned char *gR)
{
    if (2 == m_type)
    {
        memcpy(gR, vmcConfigVenderStatus, sizeof(vmcConfigVenderStatus));
        return sizeof(vmcConfigVenderStatus);
    }
    else if (3 == m_type)
    {
        memcpy(gR, vmcConfigVenderSensor, sizeof(vmcConfigVenderSensor));
        return sizeof(vmcConfigVenderSensor);
    }
    else if (4 == m_type)
    {
        memcpy(gR, vmcConfigVenderLiquid, sizeof(vmcConfigVenderLiquid));
        return sizeof(vmcConfigVenderLiquid);
    }
    else if (5 == m_type)
    {
        memcpy(gR, vmcConfigVenderPressure, sizeof(vmcConfigVenderPressure));
        return sizeof(vmcConfigVenderPressure);
    }
    else if (6 == m_type)
    {
        memcpy(gR, vmcConfigVenderF2BreakUp, sizeof(vmcConfigVenderF2BreakUp));
        return sizeof(vmcConfigVenderF2BreakUp);
    }
    else if (7 == m_type)
    {
        memcpy(gR, vmcConfigVenderOutput1, sizeof(vmcConfigVenderOutput1));
        return sizeof(vmcConfigVenderOutput1);
    }
    else if (8 == m_type)
    {
        memcpy(gR, vmcConfigVenderOutput2, sizeof(vmcConfigVenderOutput2));
        return sizeof(vmcConfigVenderOutput2);
    }

}

//int getVenderActionStatus(unsigned char *gR)
//{
//   memcpy(gR,vendoutRptReceived,sizeof(vendoutRptReceived));
//    return sizeof(vendoutRptReceived);
//
//}

void* pthread_resolveData(void *arg)
{
	int i;


    LOGI("log test ok");
	memset(FrameReceive,0,sizeof(FrameReceive));
    while(1)
    {
        int n = 7;
		readData(FrameReceive + START_ADDRESS, 1);  // read data from serial
		if (START_VALUE == FrameReceive[START_ADDRESS])
		{  // check the first byte is 0x58		
			readData(FrameReceive + 1, 2);	//LEN			
			nLen = (unsigned int) FrameReceive[1] * 256	+ (unsigned int) FrameReceive[2];	//cal int_value of LEN
			readData(FrameReceive + 3, nLen-1);	//read the left						
			frame_len = nLen + 2;						
			DataReceiveLen = nLen - 4;					
			PrintDebug(FrameReceive, frame_len, 0);		//print Log		
			CMD = FrameReceive[3];   //CMD
			SN = FrameReceive[4];   //SN
			memcpy(DataReceive, FrameReceive + 5, DataReceiveLen); //get data in receive	
			switch (CMD)		
			{  		
		        case GET_UPDATA:  
			    if (1 == DataReceive[0])			//type=1				
			    {					
				    DataSend[0] = 0x01;									
			        nDataSendLen = 1;					
			        frameSendDataGenerate(UPDATA_DAT, SN, DataSend, nDataSendLen);					
			        writeData(FrameSend, nFrameSendLen);					
			        PrintDebug(FrameSend, nFrameSendLen, 1);					
			        clearData();					
			        break;				
			    }
				else					//type=2
				    break;		
				
				case ACTION_RPT:	
				    nType = DataReceive[0];			
					nStandby = DataReceive[1];	
					if(2 == nType)
					{
                        if(1 == nStandby)
						{
							printf("----------VMC startup  finished---------\n");	
						    nVenderTag = 1;
							setEvent(ACTION_RPT_VMCSTRAT);
						}		
					}	
					frameSendDataGenerate(ACK, SN, DataSend, nDataSendLen);	//ACK				
					writeData(FrameSend, nFrameSendLen);			
					PrintDebug(FrameSend, nFrameSendLen, 1);					
					clearData();				
					break;
				  case INFO_RPT:							
					if(2 == DataReceive[0]) {
                        memset(vmcConfigVenderID, 0, sizeof(vmcConfigVenderID));
                        memcpy(vmcConfigVenderID, DataReceive, DataReceiveLen);
                        setEvent(VMC_VENDERID);
                    }
					else if(3 == DataReceive[0])		
					{
                         memset(vmcConfigVenderVersion, 0, sizeof(vmcConfigVenderVersion));
                         memcpy(vmcConfigVenderVersion, DataReceive, DataReceiveLen);
                         setEvent(VMC_VENDERVERSION);   
                         printf("----------VMC  Vender VERSION----------\n");
					}
                    else if(4 == DataReceive[0])
                    {
                         memset(vmcConfigVenderPulse, 0, sizeof(vmcConfigVenderPulse));
                         memcpy(vmcConfigVenderPulse, DataReceive, DataReceiveLen);
                         setEvent(VMC_VENDERPULSE);   
                         printf("----------VMC  Vender PULSE----------\n");
                    }
                    else if(5 == DataReceive[0])
                    {
                         memset(vmcConfigVenderMaxLitre, 0, sizeof(vmcConfigVenderMaxLitre));
                         memcpy(vmcConfigVenderMaxLitre, DataReceive, DataReceiveLen);
                         setEvent(VMC_VENDERLIMITLITRE);   
                         printf("----------VMC  Vender LIMITLITRE----------\n");
                    }
					else if(6 == DataReceive[0])
					{
                         memset(vmcConfigVenderTotalLitre, 0, sizeof(vmcConfigVenderTotalLitre));
                         memcpy(vmcConfigVenderTotalLitre, DataReceive, DataReceiveLen);
                         setEvent(VMC_VENDERTOTALLITRE);   
                         printf("----------VMC  Vender TOTALLITRE----------\n");
					}
					else if(7 == DataReceive[0])
					{
                         memset(vmcConfigVenderWaitTime, 0, sizeof(vmcConfigVenderWaitTime));
                         memcpy(vmcConfigVenderWaitTime, DataReceive, DataReceiveLen);
                         setEvent(VMC_VENDERWAITTIME);   
                         printf("----------VMC  Vender WAITTIME----------\n");
					}

                    else if(8 == DataReceive[0])
                    {
                        memset(vmcPumpingTime, 0, sizeof(vmcPumpingTime));
                        memcpy(vmcPumpingTime, DataReceive, DataReceiveLen);
                        setEvent(VMC_VENDERDETAILS);
                        printf("----------VMC  Vender DEATILS----------\n");
                    }
                    else if(9 == DataReceive[0])
                    {
                         memset(vmcConfigVenderDetails, 0, sizeof(vmcConfigVenderDetails));
                         memcpy(vmcConfigVenderDetails, DataReceive, DataReceiveLen);
                         setEvent(VMC_VENDERDETAILS);   
                         printf("----------VMC  Vender DEATILS----------\n");
                    }

                    frameSendDataGenerate(ACK, SN, DataSend, nDataSendLen);	//ACK				
					writeData(FrameSend, nFrameSendLen);			
					PrintDebug(FrameSend, nFrameSendLen, 1);
					clearData();	
                    break;

				case STATUS_RPT:		//VMC status report	
                     if (2 == DataReceive[0])
                     {
                         memset(vmcConfigVenderStatus, 0, sizeof(vmcConfigVenderStatus));
                         memcpy(vmcConfigVenderStatus, DataReceive, DataReceiveLen);
                         setEvent(VMC_VENDERSTATUS);   
                         printf("----------VMC  Vender STATUS----------\n");
                     }
                     else if(3 == DataReceive[0])
                     {
                         memset(vmcConfigVenderSensor, 0, sizeof(vmcConfigVenderSensor));
                         memcpy(vmcConfigVenderSensor, DataReceive, DataReceiveLen);
                         setEvent(VMC_VENDERSENSOR);   
                         printf("----------VMC  Vender SENSOR----------\n");
                     }
                     else if(4 == DataReceive[0])
                     {
                         memset(vmcConfigVenderLiquid, 0, sizeof(vmcConfigVenderLiquid));
                         memcpy(vmcConfigVenderLiquid, DataReceive, DataReceiveLen);
                         setEvent(VMC_VENDERLIQUID);   
                         printf("----------VMC  Vender LIQUID----------\n");
                     }
                     else if(5 == DataReceive[0])
                     {
                         memset(vmcConfigVenderPressure,0,sizeof(vmcConfigVenderPressure));
                         memcpy(vmcConfigVenderPressure, DataReceive, DataReceiveLen);
                         setEvent(VMC_VENDERPRESSURE);   
                         printf("----------VMC  Vender PRESSURE----------\n");
                     }
                     else if(6 == DataReceive[0])
                     {
                         memset(vmcConfigVenderF2BreakUp,0,sizeof(vmcConfigVenderF2BreakUp));
                         memcpy(vmcConfigVenderF2BreakUp, DataReceive, DataReceiveLen);
                         setEvent(VMC_VENDERF2BREAKUP);   
                         printf("----------VMC  Vender F2BREAKUP----------\n");
                     }
                     else if(7 == DataReceive[0])
                     {
                         memset(vmcConfigVenderOutput1,0,sizeof(vmcConfigVenderOutput1));
                         memcpy(vmcConfigVenderOutput1, DataReceive, DataReceiveLen);
                         setEvent(VMC_VENDEROUTPUT1);   
                         printf("----------VMC  Vender OUTPUT1----------\n");
                     }
                     else if(8 == DataReceive[0])
                     {
                         memset(vmcConfigVenderOutput2,0,sizeof(vmcConfigVenderOutput2));
                         memcpy(vmcConfigVenderOutput2, DataReceive, DataReceiveLen);
                         setEvent(VMC_VENDEROUTPUT2);   
                         printf("----------VMC  Vender OUTPUT2----------\n");

                     }

					frameSendDataGenerate(ACK, SN, DataSend, nDataSendLen);	//ACK				
					writeData(FrameSend, nFrameSendLen);			
					PrintDebug(FrameSend, nFrameSendLen, 1);				
					clearData();			
					break;
				case VENDOUT_RPT:	
                    //nStatus = DataReceive[0];
                    memset(vendoutRptReceived, 0, sizeof(vendoutRptReceived));
                    memcpy(vendoutRptReceived, DataReceive, DataReceiveLen);
                    setEvent(ACTION_RPT_VMCSTRAT);
					frameSendDataGenerate(ACK, SN, DataSend, nDataSendLen);	//ACK				
					writeData(FrameSend, nFrameSendLen);			
					PrintDebug(FrameSend, nFrameSendLen, 1);
					clearData();				
					break;
				case POLL:
				    if(1 == nVenderTag)
				    {
						if (1== PollFlag)					
						{																
							ReturnGetInfo();			
							PrintDebug(FrameSend, nFrameSendLen, 1);							
							clearData();	
							nVenderTag = 0;					
							break;					
						}
					}
                         if (2 == PollFlag)        //setting vender ID
                        {
printf("111111111111111111111111111111111111111111111111111111\n");                        	
                            ReturnConfigIndVenderID();
                            PrintDebug(FrameSend, nFrameSendLen, 1);
                            clearData();
                            break;
                        }

                        else if(3 == PollFlag)
                        {
                            ReturnFlowControler();
                            PrintDebug(FrameSend, nFrameSendLen, 1);
                            clearData();
                            break;
                        }
                       else if(4 == PollFlag)
                       {
                           ReturnLitreTime();
                           PrintDebug(FrameSend, nFrameSendLen, 1);
                           clearData();
                           break;

                       }
                       else if(5 == PollFlag)
                       {
                           LOGI("$$$$$$$$出水action\n");
                           ReturnVendoutAction();
                           PrintDebug(FrameSend, nFrameSendLen, 1);
                           clearData();
                           break; 
                       }
                       else if(6 == PollFlag)
                       {
                            ReturnGetInfo();
                            PrintDebug(FrameSend, nFrameSendLen, 1);
                            clearData();
                            break; 
                       }
                       else if(7 == PollFlag)
                       {
                           ReturnGetStatus();
                           PrintDebug(FrameSend, nFrameSendLen, 1);
                           clearData();
                           break; 
                       }
                      else if(8 == PollFlag)
                      {
                         ReturnReset();
                         PrintDebug(FrameSend, nFrameSendLen, 1);
                         clearData();
                         break;

                     }
					else
					{					
					    frameSendDataGenerate(ACK, SN, DataSend, nDataSendLen);	//ACK				
						writeData(FrameSend, nFrameSendLen);					
						PrintDebug(FrameSend, nFrameSendLen, 1);				
						clearData();				
					}				
					break;
					case ACK:			
                        break;
					case NAK:				
						break;
			  	 

			}		
		}
	}
}




