package com.android.learning.jni;

import android.os.Parcel;
import android.os.Parcelable;

public class JavaBookBean implements Parcelable {
    private String name;
    private String author;
    private double price;

    public JavaBookBean(String name, String author, double price) {
        this.name = name;
        this.author = author;
        this.price = price;
    }

    public String getName() {
        return name;
    }

    public String getAuthor() {
        return author;
    }

    public double getPrice() {
        return price;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(this.name);
        dest.writeString(this.author);
        dest.writeDouble(this.price);
    }

    protected JavaBookBean(Parcel in) {
        this.name = in.readString();
        this.author = in.readString();
        this.price = in.readDouble();
    }

    public static final Parcelable.Creator<JavaBookBean> CREATOR = new Parcelable.Creator<JavaBookBean>() {
        @Override
        public JavaBookBean createFromParcel(Parcel source) {
            return new JavaBookBean(source);
        }

        @Override
        public JavaBookBean[] newArray(int size) {
            return new JavaBookBean[size];
        }
    };

    @Override
    public String toString() {
        return "JavaBookBean{" +
                "name='" + name + '\'' +
                ", author='" + author + '\'' +
                ", price=" + price +
                '}';
    }
}
