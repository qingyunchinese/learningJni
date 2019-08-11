#include "java_call_native.h"
#include "androidlog.h"
#include <iostream>

int JavaCallNative::sunTwoNumber(int a, int b) {
    return a + b;
}

void JavaCallNative::bubbleSort(int *array, int arrayLength) {
    if (array == nullptr) {
        return;
    }
    int *p = array;
    LOGD("########## p=%d", p[0]);
    for (int i = 0; i < arrayLength; i++) {
        int flag = p[i];
        bool doSwitchArray = true;
        for (int j = i + 1; j < arrayLength; j++) {
            if (flag > p[j]) {
                int temp = p[j];
                p[j] = p[i];
                p[i] = temp;
                doSwitchArray = false;
            }
            flag = p[i];
        }
        if (doSwitchArray) {
            break;
        }
    }
}