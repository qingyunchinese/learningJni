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
    const char *bookNamePoint = env->GetStringUTFChars(bookName, JNI_FALSE);
    const char *authorPoint = env->GetStringUTFChars(author, JNI_FALSE);
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
    env->ReleaseStringUTFChars(bookName, bookNamePoint);
    env->ReleaseStringUTFChars(author, authorPoint);
    return javaBookBeanInstance;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_android_learning_jni_JavaCallNative_changeJavaBookName(JNIEnv *env, jobject instance, jobject javaBookBean) {
    // TODO
    jclass clazz = env->GetObjectClass(javaBookBean);
    jfieldID priceFiled = env->GetFieldID(clazz, "price", "D");
    if (priceFiled == nullptr) {
        LOGD("########## not found JavaBookBean class price filed");
        return;
    }
    jdouble price = env->GetDoubleField(javaBookBean, priceFiled);
    LOGD("########## JavaBookBean price=%f", price);

    jmethodID getNameMethodId = env->GetMethodID(clazz, "getName", "()Ljava/lang/String;");
    if (getNameMethodId == nullptr) {
        LOGD("########## not found JavaBookBean class getName Method");
        return;
    }
    auto nameObject = (jstring) env->CallObjectMethod(javaBookBean, getNameMethodId);
    const char *name = env->GetStringUTFChars(nameObject, JNI_FALSE);
    LOGD("########## JavaBookBean name=%s", name);

    jmethodID setNameMethodId = env->GetMethodID(clazz, "setName", "(Ljava/lang/String;)V");
    if (setNameMethodId == nullptr) {
        LOGD("########## not found JavaBookBean class setName Method");
        return;
    }
    LOGD("########## strlen(name)= %d", strlen(name));
    char newName[strlen(name)];
    memset(newName, '\0', strlen(name));
    strcpy(newName, name);
    env->ReleaseStringUTFChars(nameObject, name);
    LOGD("########## newName= %s", newName);
    strcat(newName, "-jni");
    const char *pName = newName;
    jstring newNameString = env->NewStringUTF(pName);
    env->CallVoidMethod(javaBookBean, setNameMethodId, newNameString);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_android_learning_jni_JavaCallNative_unityJavaBookPrice(JNIEnv *env, jobject instance,
                                                                jobject javaBookBeanList) {

    // TODO

}