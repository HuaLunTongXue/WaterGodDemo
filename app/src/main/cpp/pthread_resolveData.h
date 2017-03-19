#ifndef  _RESOLVE_H_
#define  _RESOLVE_H_

void* pthread_resolveData(void *arg);




extern int startProtocol(void);

extern int getEvent();

extern void getStatus(int nSetStatusType);

extern void getInfo(int nSetInfoType);

extern void setVenderAction(int nSetLitreValue);

extern void setMachineID(unsigned char *szSetVenderID);

extern int getRpt(int m_type, unsigned char *gR);

extern int getStatusRpt(int m_type, unsigned char *gR);

extern void setFlowControler(unsigned char* szSetFlow);

extern void setMaxLitreAndTime(char nSetLitre,char nSetTime);

extern void SetReset();

extern void getMachineId(unsigned char* gMI);

extern void getMachineFC(unsigned char* gFC);

//extern void getMaxLitreAndTime(char Litre,char Time);

extern void getVenderActionStatus(unsigned char *gR);
#endif

