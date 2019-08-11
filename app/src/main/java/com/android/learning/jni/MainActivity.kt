package com.android.learning.jni

import android.annotation.SuppressLint
import android.os.Bundle
import android.os.Looper
import android.util.Log
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*
import java.util.concurrent.atomic.AtomicInteger

class MainActivity : AppCompatActivity(), UINativeCallback, AsyncThreadCallback {

    private val javaCallNative: JavaCallNative by lazy {
        JavaCallNative()
    }

    private val callJavaInUIThread: CallJavaInUIThread by lazy {
        CallJavaInUIThread(this)
    }

    private val nCallJInAsyncThread: CallJavaInAsyncThread by lazy {
        CallJavaInAsyncThread(this)
    }

    private val atomicInteger: AtomicInteger by lazy {
        AtomicInteger()
    }

    init {
        nCallJInAsyncThread.init()
    }

    companion object {
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
        Log.v(Constants.ANDROID_LOG, "--------bubbleSort--------")
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
        Log.v(Constants.ANDROID_LOG, bufferingLog.toString())
    }

    private fun jniNewObject() {
        Log.v(Constants.ANDROID_LOG, "--------jniNewObject--------")
        val javaBookBean = javaCallNative.newJavaBookBean("Android Studio", "James", 9.87)
        if (javaBookBean == null) {
            Log.v(Constants.ANDROID_LOG, "failure")
        } else {
            Log.v(Constants.ANDROID_LOG, javaBookBean.toString())
        }
    }

    private fun jniChangeObject() {
        Log.v(Constants.ANDROID_LOG, "--------jniChangeObject--------")
        val javaBookBean = JavaBookBean("Android Studio", "James", 9.87)
        javaCallNative.changeJavaBookName(javaBookBean)
        Log.v(Constants.ANDROID_LOG, javaBookBean.toString())
    }

    private fun jniGetListObject() {
        Log.v(Constants.ANDROID_LOG, "--------jniGetListObject--------")
        val bookList = mutableListOf<JavaBookBean>()
        for (i in 1..5) {
            bookList.add(JavaBookBean("bookName$i", "James$i", i.plus(0.53)))
        }
        bookList.forEach {
            Log.v(Constants.ANDROID_LOG, it.toString())
        }
        javaCallNative.unityJavaBookPrice(bookList.toList())
        bookList.forEach {
            Log.v(Constants.ANDROID_LOG, it.toString())
        }
    }

    fun jniCallJavaString(view: View) {
        callJavaInUIThread.nativeString()
    }

    override fun stringFromJNI(jniStr: String?) {
        jniStr?.let {
            showMessageDialog(jniStr)
        }
    }

    fun jniThread(view: View) {
        val id = atomicInteger.incrementAndGet()
        val javaBookBean = JavaBookBean("bookName$id", "James$id", id.plus(0.53))
        nCallJInAsyncThread.work(javaBookBean)
    }

    override fun onNativeJavaBook(javaBookBean: JavaBookBean?) {
        Log.v(Constants.ANDROID_LOG, "UIThread.currentThread().id:" + Looper.getMainLooper().thread.id)
        Log.v(Constants.ANDROID_LOG, "Thread.currentThread().id:" + Thread.currentThread().id)
        val asyncThreadId = Thread.currentThread().id
        val asyncThreadName = Thread.currentThread().name
        javaBookBean?.let {
            runOnUiThread {
                showMessageDialog("UIThread.id:${Looper.getMainLooper().thread.id}(${Looper.getMainLooper().thread.name})\nAsyncThread.id:$asyncThreadId($asyncThreadName)")
                Log.v(Constants.ANDROID_LOG, javaBookBean.toString())
            }
        }
    }

    override fun onDestroy() {
        nCallJInAsyncThread.release()
        super.onDestroy()
    }

}
