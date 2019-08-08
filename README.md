1.basic variable type (基础数据对照表)

Java类型 | 本地类型（JNI）
---- | ---
boolean（布尔型） | jboolean
byte(字节型) |  jbyte
char(字符型) | jchar
short(短整型) |  jshort
int(整型) | jint
long(长整型) |  jlong
float(浮点型) | jfloat
double(双精度浮点型) |  jdouble
void(空型)| void
String|Ljava/lang/String;
Object|Ljava/lang/Object;

2.method domain descriptor (方法域描述)

 集合类型 | 本地类型（JNI）
---- | ---
boolean|Z
byte|B
char|C
short|S
int|I
long|J
float|F
double|D

3.set variable type（集合类型）

 集合类型 | 本地类型（JNI）
---- | ---
int[]|[I
int[][]|[[I

4.Method signature example（方法签名示例）

java方法 | 方法签名（JNI）
---- | ---
String stringFromJNI()|()Ljava/lang/String;
int List.size()|()I
Object List.get(int index)|(I)Ljava/lang/Object;
void setPrice(double price)|(D)V

5.字符串操作

因为Java默认使用Unicode编码，而C/C++默认使用UTF编码，所以在本地代码中操作字符串的时候，必须使用合适的JNI函数把jstring转换成C风格的字符串。
JNI支持字符串在Unicode和UTF-8两种编码之间转换，GetStringUTFChars可以把一个jstring指针（指向JVM内部的Unicode字符序列）转换成一个UTF-8格式的C字符串。

Unicode -> UTF-8 

```C++
   jstring name="hello Jni+"
   const char *namePoint=env->GetStringUTFChars(name,NULL)
   env->ReleaseStringUTFChars(name,namePoint)
```
    env：JNIEnv函数表指针
    j_str：jstring类型（Java传递给本地代码的字符串指针）
    isCopy：取值JNI_TRUE和JNI_FALSE，
            JNI_TRUE，表示返回JVM内部源字符串的一份拷贝，并为新产生的字符串分配内存空间。
           JNI_FALSE，表示返回JVM内部源字符串的指针，意味着可以通过指针修改源字符串的内容，不推荐这么做，因为这样做就打破了Java字符串不能修改的规定。
           
UTF-8 -> Unicode  
         
```C++
   const char* namePoint ="hello Jni+"
   jstring name=env->NewStringUTF(namePoint)
```

获取字符串长度

```C++
   jstring name ="hello"
   5=env->GetStringUTFLength(name)
   5=env->GetStringChars(name)
```


           
           

