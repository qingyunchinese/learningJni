package com.android.learning.jni;

public class CallJavaInAsyncThread {

    private AsyncThreadCallback asyncThreadCallback;

    private CallJavaInAsyncThread() {

    }

    public CallJavaInAsyncThread(AsyncThreadCallback asyncThreadCallback) {
        this.asyncThreadCallback = asyncThreadCallback;
    }

    void init() {
        nativeThreadInit();
    }

    void release() {
        nativeThreadRelease();
    }

    void work(JavaBookBean javaBookBean) {
        nativeThreadWorker(javaBookBean, new AsyncThreadCallback() {
            @Override
            public void onNativeJavaBook(JavaBookBean javaBookBean) {
                asyncThreadCallback.onNativeJavaBook(javaBookBean);
            }
        });
    }

    private native void nativeThreadInit();

    private native void nativeThreadRelease();

    private native void nativeThreadWorker(JavaBookBean javaBookBean, AsyncThreadCallback asyncThreadCallback);
}
