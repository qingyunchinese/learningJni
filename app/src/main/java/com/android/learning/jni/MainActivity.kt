package com.android.learning.jni

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    private val javaCallNative: JavaCallNative by lazy {
        JavaCallNative()
    }

    companion object {
        const val ANDROID_LOG = "Android-JNI-java"

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    override fun onResume() {
        super.onResume()
        runOnUiThread {
            helloWord()
            sumTwoNumber(10, 6)
            bubbleSort()
            jniNewObject()
            jniChangeObject()
            jniGetListObject()
        }
    }

    private fun helloWord() {
        // Example of a call to a native method
        helloWord.text = javaCallNative.stringFromJNI()
    }

    @SuppressLint("SetTextI18n")
    private fun sumTwoNumber(a: Int, b: Int) {
        // Example of a call to a native method
        val sum = javaCallNative.sumTwoNumber(a, b)
        sumTwoNumber.text = "$a+$b=$sum"
    }

    private fun bubbleSort() {
        Log.v(ANDROID_LOG, "--------bubbleSort--------")
        javaCallNative.bubbleSort(null, 0)
        val intArray = intArrayOf(3, 4, 5, 0, 1, 2, 6, 7, 10)
        javaCallNative.bubbleSort(intArray, intArray.size)
        val bufferingLog = StringBuilder()
        intArray.forEach {
            if (bufferingLog.isEmpty()) {
                bufferingLog.append("$it")
            } else {
                bufferingLog.append(",$it")
            }
        }
        Log.v(ANDROID_LOG, bufferingLog.toString())
    }

    private fun jniNewObject() {
        Log.v(ANDROID_LOG, "--------jniNewObject--------")
        val javaBookBean = javaCallNative.newJavaBookBean("Android Studio", "James", 9.87)
        if (javaBookBean == null) {
            Log.v(ANDROID_LOG, "failure")
        } else {
            Log.v(ANDROID_LOG, javaBookBean.toString())
        }
    }

    private fun jniChangeObject() {
        Log.v(ANDROID_LOG, "--------jniChangeObject--------")
        val javaBookBean=JavaBookBean("Android Studio", "James", 9.87)
        javaCallNative.changeJavaBookName(javaBookBean)
        Log.v(ANDROID_LOG, javaBookBean.toString())
    }

    private fun jniGetListObject(){
        Log.v(ANDROID_LOG, "--------jniGetListObject--------")
        val bookList= mutableListOf<JavaBookBean>()
        for(i in 1..5){
            bookList.add(JavaBookBean("bookName$i", "James$i", i.plus(0.53)))
        }
        bookList.forEach {
            Log.v(ANDROID_LOG, it.toString())
        }
        javaCallNative.unityJavaBookPrice(bookList.toList())
        bookList.forEach {
            Log.v(ANDROID_LOG, it.toString())
        }
    }

}
