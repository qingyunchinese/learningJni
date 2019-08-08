package com.android.learning.jni

import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity

fun AppCompatActivity.showMessageDialog(message: String) {
    val builder = AlertDialog.Builder(this)
    builder.setTitle("Title")
    builder.setMessage(message)
    builder.setPositiveButton(android.R.string.yes) { dialog, which ->
        dialog.dismiss()
    }
    builder.setNegativeButton(android.R.string.no) { dialog, which ->
        dialog.dismiss()
    }
    builder.show()
}