package com.android.learning.jni;

public class NativeCallJava {

    private NativeCallback nativeCallback;

    public NativeCallJava() {
    }

    public NativeCallJava(NativeCallback nativeCallback) {
        this.nativeCallback = nativeCallback;
    }

    public void nativeString(){
        getNativeString();
    }

    native void getNativeString();

    void stringFromJNI(String jniStr) {
        nativeCallback.stringFromJNI(jniStr);
    }

    native void startAsynchronousTask(int taskId);

    int asynchronousTaskCallback(int taskId) {
        return -1;
    }
}