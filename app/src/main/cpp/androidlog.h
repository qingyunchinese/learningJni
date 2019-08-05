#ifndef ANDROID_LOG_H
#define ANDROID_LOG_H
#include <android/log.h>

#define TAG "Android-JNI-C++"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)

#endif