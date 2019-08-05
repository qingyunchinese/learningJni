#include <jni.h>
#include <string>
#include <random>
#include <cstdlib>
#include "androidlog.h"
#include "java_call_native.h"

using namespace std;

extern "C" JNIEXPORT jstring JNICALL
Java_com_android_learning_jni_JavaCallNative_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    string hello = "Hello from JNI C++ 11";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_android_learning_jni_JavaCallNative_sumTwoNumber(JNIEnv *env, jobject instance, jint a, jint b) {
    LOGD("########## sumTwoNumber a = %d", a);
    LOGD("########## sumTwoNumber b = %d", b);
    auto *javaCallNative = new JavaCallNative();
    int sum = javaCallNative->sunTwoNumber(a, b);
    delete javaCallNative;
    LOGD("########## sumTwoNumber a+b = %d", sum);
    return sum;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_android_learning_jni_JavaCallNative_bubbleSort(JNIEnv *env, jobject instance, jintArray intArray,
                                                        jint arrayLength) {
    if (intArray == nullptr) {
        LOGD("########## bubbleSort array NULL");
        return;
    }
    jint *array = env->GetIntArrayElements(intArray, nullptr);
    auto *javaCallNative = new JavaCallNative();
    javaCallNative->bubbleSort(array, arrayLength);
    delete javaCallNative;
    env->ReleaseIntArrayElements(intArray, array, 0);
}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_android_learning_jni_JavaCallNative_newJavaBookBean(JNIEnv *env, jobject instance, jstring bookName,
                                                             jstring author, jdouble price) {
    const char *bookNamePoint = env->GetStringUTFChars(bookName, 0);
    const char *authorPoint = env->GetStringUTFChars(author, 0);
    LOGD("########## bookName %s", bookNamePoint);
    LOGD("########## author %s", authorPoint);
    LOGD("########## price %f", price);
    jclass javaBookBeanClass = env->FindClass("com/android/learning/jni/JavaBookBean");
    if (javaBookBeanClass == NULL) {
        LOGD("########## not found JavaBookBean class ");
        return NULL;
    }
    const char *constructorMethodName = "<init>";
    jmethodID constructorMethodID = env->GetMethodID(javaBookBeanClass, constructorMethodName,
                                                     "(Ljava/lang/String;Ljava/lang/String;D)V");
    if (constructorMethodID == NULL) {
        LOGD("########## not found JavaBookBean class constructor Method ");
        return NULL;
    }
    jobject javaBookBeanInstance = env->NewObject(javaBookBeanClass, constructorMethodID, bookName, author,
                                                  price);
//    env->ReleaseStringUTFChars(bookName, bookNamePoint);
//    env->ReleaseStringUTFChars(author, authorPoint);
    return javaBookBeanInstance;
}