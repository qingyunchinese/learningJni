#include "jni_load.h"

JavaVM *globeJavaVM=NULL;

jint JNI_OnLoad(JavaVM *javaVm, void *reserved) {
    LOGD("########## JNI_OnLoad");
    JNIEnv *env;
    if (javaVm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    globeJavaVM = javaVm;
    return JNI_VERSION_1_4;
}

void JNI_OnUnload(JavaVM *vm, void *reserved) {
    LOGD("########## JNI_OnUnload");
}