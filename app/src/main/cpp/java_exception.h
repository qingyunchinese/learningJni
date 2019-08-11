#ifndef JAVA_EXCEPTION_H
#define JAVA_EXCEPTION_H

#include <jni.h>

void throwRuntimeException(JNIEnv *env, const char *exceptionMessage) {
    jclass exceptionClass = env->FindClass("java/lang/RuntimeException");
    env->ThrowNew(exceptionClass, exceptionMessage);
}

#endif