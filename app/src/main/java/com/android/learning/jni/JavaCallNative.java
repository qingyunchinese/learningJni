package com.android.learning.jni;

import java.util.List;

public class JavaCallNative {
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    native String stringFromJNI();

    native int sumTwoNumber(int a, int b);

    native void bubbleSort(int[] array, int arrayLength);

    native JavaBookBean newJavaBookBean(String bookName, String author, double price);

    native void changeJavaBookName(JavaBookBean javaBookBean);

    native void unityJavaBookPrice(List<JavaBookBean> javaBookBeanList);
}
