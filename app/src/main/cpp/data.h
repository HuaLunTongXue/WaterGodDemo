#ifndef _DATA_H_
#define _DATA_H_



#define true 1
#define false 0


typedef   unsigned char isbool;


#define RECEIVE_BUF  1024
unsigned char FrameReceive[RECEIVE_BUF];

#define START_VALUE  0x58 
#define START_ADDRESS 0   
#define STX_LEN 1
#define VALID_LENGTH 2
#define SN_LEN   1
#define COMMAND_TYPE 1
#define COMMAND_STANDBY 1
#define START_COMMOND_ADDRESS (START_ADDRESS + STX_LEN + VALID_LENGTH)
#define START_SN_ADDRESS (START_COMMOND_ADDRESS + SN_LEN)
#define START_COMMOND_TYPE (START_SN_ADDRESS + COMMAND_TYPE)
#define START_COMMOND_STANDBY (START_COMMOND_TYPE + COMMAND_STANDBY)
#define VENDERIDLENGTH 8
#define FLOWCONTROLERLENGTH 2

unsigned int nLen;  
unsigned char nFcc;
unsigned int nFrameSendLen;
unsigned int nDataSendLen;
unsigned int DataReceiveLen;
unsigned int nStandby;
unsigned int nType;
unsigned char szFCC;
static unsigned char LenValue[2]={0};
static unsigned char FccValue[2]={0};
static unsigned char DataReceive[RECEIVE_BUF] = {0};   //value of DATA
static unsigned char DataSend[RECEIVE_BUF] = {0};
static unsigned char FrameSend[RECEIVE_BUF] ={0};


unsigned int frame_len;		
unsigned DataReceive_len ;
unsigned char CMD;
unsigned char SN;

unsigned int nVenderID;
unsigned int nVenderIDLen;
static unsigned char szVenderID[8+1]={0};
static unsigned char szFlowControler[2+1]={0};
static unsigned char vendoutRptReceived[10]={0};
static unsigned char vmcConfigVenderID[8+1]={0};
static unsigned char vmcConfigVenderVersion[2+1]={0};
static unsigned char vmcConfigVenderPulse[2+1]={0};
static unsigned char vmcConfigVenderMaxLitre[1+1];
static unsigned char vmcConfigVenderTotalLitre[4+1]={0};
static unsigned char vmcConfigVenderWaitTime[1+1];
static unsigned char vmcPumpingTime[1+1];
static unsigned char vmcConfigVenderDetails[10] = {0};


static unsigned char vmcConfigVenderStatus[10] = {0};
static unsigned char vmcConfigVenderSensor[10] = {0};
static unsigned char vmcConfigVenderLiquid[10] = {0};
static unsigned char vmcConfigVenderPressure[10] = {0};
static unsigned char vmcConfigVenderF2BreakUp[10] ={0};
static unsigned char vmcConfigVenderOutput1[10] = {0};
static unsigned char vmcConfigVenderOutput2[10] ={0};


static int nLitre;
static int nTime;
static int nLitreValue;
static int nInfoType;
static int nStatusType;
static int nSetInfoType;
//static int nSetVenderID; 


/********general command**************/
#define ACK     0xA0
#define NAK     0xA1
#define POLL    0xA2
/*********VMC command*****************/
//#define SERVICE_RPT  0XE0
#define ACTION_RPT   0XE0
#define INFO_RPT     0XE1
#define VENDOUT_RPT  0XE2
#define STATUS_RPT   0XE3
#define GET_UPDATA   0XE4
/*********PC command******************/
#define CONFIG_IND   0XF0
#define VENDOUT_IND  0XF1
#define GET_INFO     0XF2
#define GET_STATUS   0XF3
#define UPDATA_DAT   0XF4






#define VMC_VENDERID          0xA1
#define VMC_VENDERVERSION     0xA2
#define VMC_VENDERPULSE       0xA3
#define VMC_VENDERLIMITLITRE  0xA4
#define VMC_VENDERTOTALLITRE  0xA5
#define VMC_VENDERWAITTIME    0xA6
#define VMC_VENDERDETAILS     0xA7

#define VMC_VENDERSTATUS      0xB1
#define VMC_VENDERSENSOR      0xB2
#define VMC_VENDERLIQUID      0xB3
#define VMC_VENDERPRESSURE    0xB4
#define VMC_VENDERF2BREAKUP   0xB5
#define VMC_VENDEROUTPUT1     0xB6
#define VMC_VENDEROUTPUT2     0xB7

#define ACTION_RPT_VMCSTRAT   0xC1


void setIsScreenShopping(isbool  value);

void setEventID(int nEventID);
void setPollFlag(int setValue);
void setVenderID(unsigned char * szVenderID);




static int nVenderTag =0;
static int PollFlag = 0;
static int nEventID = 0;

#endif

