#ifndef SIMPLE_THREAD_H
#define SIMPLE_THREAD_H

#include <jni.h>
#include <pthread.h>
#include <cstdlib>

#include "simaple_thread.h"
#include "jni_load.h"
#include "java_exception.h"

static pthread_t threadPoint;
static jobject gJavaBookBean = NULL;
static jobject gAsyncThreadCallback = NULL;

void *nativeWorkerThread(void *args);

extern "C"
JNIEXPORT void JNICALL
Java_com_android_learning_jni_CallJavaInAsyncThread_nativeThreadInit(JNIEnv *env, jobject instance) {

}

extern "C"
JNIEXPORT void JNICALL
Java_com_android_learning_jni_CallJavaInAsyncThread_nativeThreadRelease(JNIEnv *env, jobject instance) {
    void *pVoid = NULL;
    pthread_join(threadPoint, &pVoid);
    if (pVoid != NULL) {
        free(pVoid);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_android_learning_jni_CallJavaInAsyncThread_nativeThreadWorker(JNIEnv *env, jobject instance, jobject javaBookBean,jobject asyncThreadCallback) {
    gJavaBookBean = env->NewGlobalRef(javaBookBean);
    if (gJavaBookBean == 0) {
        LOGD("########## gJavaBookBean NewGlobalRef failed");
        return;
    }
    gAsyncThreadCallback = env->NewGlobalRef(asyncThreadCallback);
    if (gAsyncThreadCallback == 0) {
        LOGD("########## gAsyncThreadCallback NewGlobalRef failed");
        return;
    }
    pthread_attr_t pthreadAttr;
    pthread_attr_init(&pthreadAttr);  //初始化线程属性
    pthread_attr_setdetachstate(&pthreadAttr, PTHREAD_CREATE_DETACHED);
    int result = pthread_create(&threadPoint, &pthreadAttr, nativeWorkerThread,NULL);
    if (0 != result) {
        throwRuntimeException(env, "Unable to create thread");
    }
}

void *nativeWorkerThread(void *args) {
    int status;
    JNIEnv *env;
    bool isAttached = false;
    status = globeJavaVM->GetEnv((void **) &env, JNI_VERSION_1_4);
    if (status < 0) {
        status = globeJavaVM->AttachCurrentThread(&env, NULL);
        if (status < 0)
            return NULL;
        isAttached = true;
    }
    jclass callBackClass = env->GetObjectClass(gAsyncThreadCallback);
    if (callBackClass == 0) {
        LOGD("########## GetObjectClass  failed");
        return NULL;
    }
    jmethodID onNativeJavaBookMethodId = env->GetMethodID(callBackClass, "onNativeJavaBook", "(Lcom/android/learning/jni/JavaBookBean;)V");
    if (onNativeJavaBookMethodId == 0) {
        LOGD("########## javaCallbackMethodId  failed");
        return NULL;
    }
    env->CallVoidMethod(gAsyncThreadCallback, onNativeJavaBookMethodId, gJavaBookBean);
    if (isAttached) {
        globeJavaVM->DetachCurrentThread();
    }
    LOGD("########## DetachCurrentThread");
    env->DeleteGlobalRef(gJavaBookBean);
    env->DeleteGlobalRef(gAsyncThreadCallback);
    LOGD("########## pthread_exit");
    pthread_exit(0);
}


#endif