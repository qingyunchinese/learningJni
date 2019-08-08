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