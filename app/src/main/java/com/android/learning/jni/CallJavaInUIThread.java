package com.android.learning.jni;

public class CallJavaInUIThread {

    private UINativeCallback uiNativeCallback;

    private CallJavaInUIThread() {
    }

    public CallJavaInUIThread(UINativeCallback uiNativeCallback) {
        this.uiNativeCallback = uiNativeCallback;
    }

    public void nativeString() {
        getNativeString();
    }

    native void getNativeString();

    @SuppressWarnings("UNUSED")
    void stringFromJNI(String jniStr) {
        uiNativeCallback.stringFromJNI(jniStr);
    }
}