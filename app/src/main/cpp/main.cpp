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
    const char *bookNamePoint = env->GetStringUTFChars(bookName, NULL);
    const char *authorPoint = env->GetStringUTFChars(author, NULL);
    LOGD("########## bookName %s", bookNamePoint);
    LOGD("########## author %s", authorPoint);
    LOGD("########## price %f", price);
    jclass javaBookBeanClass = env->FindClass("com/android/learning/jni/JavaBookBean");
    if (javaBookBeanClass == NULL) {
        LOGD("########## not found JavaBookBean class ");
        return nullptr;
    }
    const char *constructorMethodName = "<init>";
    jmethodID constructorMethodID = env->GetMethodID(javaBookBeanClass, constructorMethodName,
                                                     "(Ljava/lang/String;Ljava/lang/String;D)V");
    if (constructorMethodID == NULL) {
        LOGD("########## not found JavaBookBean class constructor Method ");
        return nullptr;
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
    const char *name = env->GetStringUTFChars(nameObject, NULL);
    LOGD("########## JavaBookBean name=%s", name);

    jmethodID setNameMethodId = env->GetMethodID(clazz, "setName", "(Ljava/lang/String;)V");
    if (setNameMethodId == nullptr) {
        LOGD("########## not found JavaBookBean class setName Method");
        return;
    }
    jsize length = env->GetStringUTFLength(nameObject);
    LOGD("########## strlen(name)= %d", length);
    char newName[strlen(name)];
    memset(newName, '\0', strlen(name));
    strcpy(newName, name);
    env->ReleaseStringUTFChars(nameObject, name);
    LOGD("########## newName= %s", newName);
    string jni = "-jni";
    jstring jniUTF = env->NewStringUTF(jni.c_str());
    const char *jniPoint = env->GetStringUTFChars(jniUTF, NULL);
    strcat(newName, jniPoint);
    env->ReleaseStringUTFChars(jniUTF, jniPoint);
    const char *pName = newName;
    jstring newNameString = env->NewStringUTF(pName);
    env->CallVoidMethod(javaBookBean, setNameMethodId, newNameString);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_android_learning_jni_JavaCallNative_unityJavaBookPrice(JNIEnv *env, jobject instance,
                                                                jobject bookList) {

    jclass javaBookBeanListClass = env->GetObjectClass(bookList);
    jmethodID methodGet = env->GetMethodID(javaBookBeanListClass, "get",
                                           "(I)Ljava/lang/Object;");
    jmethodID methodSize = env->GetMethodID(javaBookBeanListClass, "size", "()I");
    jint len = env->CallIntMethod(bookList, methodSize);
    LOGD("########## listSize= %d", len);

    for (int i = 0; i < len; i++) {

        jobject bookObject = env->CallObjectMethod(bookList, methodGet, i);
        jclass bookClass = env->GetObjectClass(bookObject);

        jmethodID setPriceMethodId = env->GetMethodID(bookClass, "setPrice", "(D)V");
        if (setPriceMethodId == nullptr) {
            LOGD("########## not found JavaBookBean class setPrice Method");
            return;
        }

        env->CallVoidMethod(bookObject, setPriceMethodId, 9.0);
    }
}