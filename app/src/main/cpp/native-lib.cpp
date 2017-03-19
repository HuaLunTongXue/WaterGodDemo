#include <jni.h>
#include <string>
#include <android/log.h>

extern "C" {
#include "pthread_resolveData.h"
}

#define   LOG_TAG    "LOG_TEST"
#define   LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define   LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


//JNIEXPORT void JNICALL
//Java_com_example_myapplication3_watergod_setMaxLitre(JNIEnv *env, jobject instance,
//                                                     jbyte waterLitre) {
//
//    setMaxLitre(waterLitre);
//
//}


//JNIEXPORT jbyteArray JNICALL
//Java_com_example_myapplication3_watergod_getMaxLitreAndTime(JNIEnv *env, jobject instance) {
//
//    jbyte Litre;
//    jbyte Time;
//    getMaxLitreAndTime(Litre,Time);
//
//}
//



//extern "C"
//JNIEXPORT void JNICALL
//Java_com_example_myapplication3_watergod_getVenderOutStatus(JNIEnv *env, jobject instance) {
//
//
//
//    jbyte gR[200];
//    jint len = getVenderOutStatus((unsigned char*)gR);
//    jbyteArray ret=(*env).NewByteArray(len);
//    (*env).SetByteArrayRegion(ret,0,len,gR);
//    return ret;
//
//}


//extern "C"
//JNIEXPORT void JNICALL
//Java_com_example_myapplication3_watergod_setFlowControler(JNIEnv *env, jobject instance,
//                                                          jstring waterFlow_) {
//    const char *waterFlow = env->GetStringUTFChars(waterFlow_, 0);
//
//    LOGI("1111111111111111\n");
//    setFlowControler((unsigned char *)waterFlow_);
//    LOGI("2222222\n");
//
//    env->ReleaseStringUTFChars(waterFlow_, waterFlow);
//}






extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_kevin_1zhuang_watergoddemo_MainActivity_getFlowControler(JNIEnv *env, jobject instance) {

    jbyteArray ret =(*env).NewByteArray(2);
    jbyte gFC[2];
    getMachineFC((unsigned char*)gFC);
    (*env).SetByteArrayRegion(ret,0,2,gFC);

}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_kevin_1zhuang_watergoddemo_MainActivity_getMachineId(JNIEnv *env, jobject instance) {

    jbyte gMI[8];
    jbyteArray ret =(*env).NewByteArray(8);
    getMachineId((unsigned char*)gMI);
    (*env).SetByteArrayRegion(ret,0,8,gMI);
    return ret;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_kevin_1zhuang_watergoddemo_MainActivity_setMaxLitreAndTime(JNIEnv *env, jobject instance,
                                                            jbyte Litre, jbyte waterTime) {
    setMaxLitreAndTime(Litre,waterTime);

}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_kevin_1zhuang_watergoddemo_MainActivity_SetReset(JNIEnv *env, jobject instance) {

    SetReset();
}



extern "C"
JNIEXPORT void JNICALL
Java_com_example_kevin_1zhuang_watergoddemo_MainActivity_setVenderAction(JNIEnv *env, jobject instance,
                                                         jint nLitre) {
    LOGI("@@@@@@@@@@@@@@@出水%d\n",nLitre);
    setVenderAction(nLitre);

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_kevin_1zhuang_watergoddemo_MainActivity_startProtocol(JNIEnv *env, jobject instance) {

    LOGI("log test main");

    startProtocol();

    return 0;
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_kevin_1zhuang_watergoddemo_MainActivity_getStatusRpt(JNIEnv *env, jobject instance,
                                                      jint rpt_type) {
    jbyte gR[200];
    jint len = getStatusRpt(rpt_type,(unsigned char*)gR);
    jbyteArray ret=(*env).NewByteArray(len);
    (*env).SetByteArrayRegion(ret,0,len,gR);
    return ret;

}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_kevin_1zhuang_watergoddemo_MainActivity_getRpt(JNIEnv *env, jobject instance, jint rpt_type) {

    jbyte gR[200];
    jint len = getRpt(rpt_type,(unsigned char*)gR);
    jbyteArray ret=(*env).NewByteArray(len);
    (*env).SetByteArrayRegion(ret,0,len,gR);
    return ret;

}


//extern "C"
//JNIEXPORT void JNICALL
//Java_com_example_kevin_1zhuang_watergoddemo_MainActivity_setLitreTime(JNIEnv *env, jobject instance,
//                                                      jbyte waterLitre, jbyte waterTime) {
//setLitreTime(waterLitre,waterTime);
//
//}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_kevin_1zhuang_watergoddemo_MainActivity_setFlowControler(JNIEnv *env, jobject instance,
                                                          jbyteArray waterFlow_) {
    jbyte *waterFlow = env->GetByteArrayElements(waterFlow_, NULL);

    LOGI("1111111111111111\n");

    setFlowControler((unsigned char *)waterFlow);

    env->ReleaseByteArrayElements(waterFlow_, waterFlow, 0);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_kevin_1zhuang_watergoddemo_MainActivity_setMachineID(JNIEnv *env, jobject instance,
                                                      jbyteArray machine_id_) {

    jbyte *machine_id = env->GetByteArrayElements(machine_id_, NULL);

    LOGI("机器编号 %s\n",(char*)machine_id);

    LOGI("%%%%%%%%%%\n");

    setMachineID((unsigned char *)machine_id);


    env->ReleaseByteArrayElements(machine_id_, machine_id, 0);
}





extern "C"
JNIEXPORT void JNICALL
Java_com_example_kevin_1zhuang_watergoddemo_MainActivity_getInfo(JNIEnv *env, jobject instance, jint m_type) {

    getInfo(m_type);

}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_kevin_1zhuang_watergoddemo_MainActivity_getStatus(JNIEnv *env, jobject instance, jint m_type) {

    LOGI("$$$$$$$$$$$$$$$$$$$$$$$\n");
    getStatus(m_type);
    LOGI("%d\n",m_type);

}


extern "C"
JNIEXPORT jint JNICALL
Java_com_example_kevin_1zhuang_watergoddemo_MainActivity_getEvent(JNIEnv *env, jobject instance) {

    return getEvent();

}















