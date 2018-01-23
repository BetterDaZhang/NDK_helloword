#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helloworld_jni.h"
#include "util.h"
#include "log.h"

JNIEXPORT jstring JNICALL Java_example_zhangjunling_com_ndk_1hellowork_HelloWordJniActivity_getStringFromJni
(JNIEnv *env, jobject obj){
    return env->NewStringUTF("zhangjunling welcome to Jni.");
}

JNIEXPORT jstring JNICALL Java_example_zhangjunling_com_ndk_1hellowork_HelloWordJniActivity_operatorData
        (JNIEnv *env, jobject obj, jstring data){
    jboolean isCopy;
    const char* javaData = env->GetStringUTFChars(data,&isCopy);
    char *data2 = (char*)malloc(env->GetStringLength(data)+1);
    memset(data2, 0, env->GetStringLength(data) + 1);
    memcpy(data2, javaData, env->GetStringLength(data));

    LOGE("data len:%d",env->GetStringLength(data));
    env->ReleaseStringUTFChars(data, javaData);
    return env->NewStringUTF(strupr(data2));
}

JNIEXPORT jintArray JNICALL Java_example_zhangjunling_com_ndk_1hellowork_HelloWordJniActivity_getIntArrayFromJni
        (JNIEnv *env, jobject obj){
    jintArray intArray;
    jboolean isCopy = false;
    jint* data;
    intArray = env->NewIntArray(10);
    if(intArray != 0){
        LOGE("intArray != 0");
        data = env->GetIntArrayElements(intArray, &isCopy);
        for(int i = 0; i < 10; i++){
//            *(data + i) = i;
            data[i] = i;
        }
        for(int i = 0; i < 10; i++){
//            *(data + i) = i;
            LOGE("data:%d", *(data + i));
        }
    }
    env->ReleaseIntArrayElements(intArray, data, 0);
    return intArray;
}

JNIEXPORT jintArray JNICALL Java_example_zhangjunling_com_ndk_1hellowork_HelloWordJniActivity_setIntArrayToJni
        (JNIEnv *env, jobject obj, jintArray javaArray){
    jint *data = NULL;
    jboolean isCopy;
    data = env->GetIntArrayElements(javaArray, &isCopy);
    jsize arrayLen = env->GetArrayLength(javaArray);
    if (0 != data) {
        for (int i = 0; i < arrayLen; i++) {
            *(data + i) = 8;
        }
    }
    env->ReleaseIntArrayElements(javaArray, data, 0);
    return javaArray;
}

JNIEXPORT jintArray JNICALL Java_example_zhangjunling_com_ndk_1hellowork_HelloWordJniActivity_getRegionArrayFromJin
        (JNIEnv *env, jobject obj){
    jintArray javaArray;
    javaArray = env->NewIntArray(10);
    jint nativeArray[10];
    if (0 != javaArray) {
        env->GetIntArrayRegion(javaArray, 0, 10, nativeArray);
    }
    for (int i = 0; i < 10; i++) {
        nativeArray[i] = 8;
    }
    env->SetIntArrayRegion(javaArray, 0, 10, nativeArray);
    return javaArray;
}

JNIEXPORT jobject JNICALL Java_example_zhangjunling_com_ndk_1hellowork_HelloWordJniActivity_getDirectByteBufferFromJni
        (JNIEnv *env, jobject obj){
    jobject directBuffer = NULL;
    unsigned char* buffer = (unsigned char*)malloc(128);
    for(int i=0; i<128; i++){
        buffer[i] = i;
    }

    directBuffer = env->NewDirectByteBuffer(buffer, 128);
    return directBuffer;
}

JNIEXPORT void JNICALL Java_example_zhangjunling_com_ndk_1hellowork_HelloWordJniActivity_setDirectByteBufferToJni
        (JNIEnv *env, jobject obj, jobject byteBuffer){
    unsigned char* data;
    int dataLen = env->GetDirectBufferCapacity(byteBuffer);
    data = (unsigned char*)env->GetDirectBufferAddress(byteBuffer);
    for(int i = 0; i<dataLen; i++){
        LOGE("native data:%d", data[i]);
    }

}

JNIEXPORT jstring JNICALL Java_example_zhangjunling_com_ndk_1hellowork_HelloWordJniActivity_getJavaFieldString
        (JNIEnv *env, jobject obj){
    jclass objClass = env->GetObjectClass(obj);
    jfieldID objFieldId = env->GetFieldID(objClass, "mJavaData", "Ljava/lang/String;");
    jstring javaData = (jstring) env->GetObjectField(obj, objFieldId);
    jboolean isCopy;
    LOGE("javaData:%s",env->GetStringUTFChars(javaData,&isCopy));

    return javaData;
}

JNIEXPORT void JNICALL Java_example_zhangjunling_com_ndk_1hellowork_HelloWordJniActivity_setJavaFieldString
        (JNIEnv *env, jobject obj){
    jclass objClass = env->GetObjectClass(obj);
    jfieldID objFieldId = env->GetFieldID(objClass, "mJavaData", "Ljava/lang/String;");

    jstring nativeString = env->NewStringUTF("native create jstring.");
    env->SetObjectField(obj, objFieldId, nativeString);
}

JNIEXPORT jstring JNICALL Java_example_zhangjunling_com_ndk_1hellowork_HelloWordJniActivity_getJavaStaticFieldString
        (JNIEnv *env, jobject obj){
    jclass objStaticClass = env->GetObjectClass(obj);
    jfieldID objStaticFieldId = env->GetStaticFieldID(objStaticClass, "mStaticField", "Ljava/lang/String;");
    jstring javaStaticString = (jstring)env->GetStaticObjectField(objStaticClass, objStaticFieldId);
    return javaStaticString;
}

JNIEXPORT void JNICALL Java_example_zhangjunling_com_ndk_1hellowork_HelloWordJniActivity_setJavaStaticFieldString
        (JNIEnv *env, jobject obj){
    jclass objStaticClass = env->GetObjectClass(obj);
    jfieldID objStaticFieldId = env->GetStaticFieldID(objStaticClass, "mSetStaticField", "Ljava/lang/String;");

    env->SetStaticObjectField(objStaticClass, objStaticFieldId, env->NewStringUTF("Java Static Set Field"));
}

JNIEXPORT void JNICALL Java_example_zhangjunling_com_ndk_1hellowork_HelloWordJniActivity_callFieldMethod
        (JNIEnv *env, jobject obj){
    jclass fieldMethodClass = env->GetObjectClass(obj);
    jmethodID fieldMethodId = env->GetMethodID(fieldMethodClass, "onNativeSuccess", "(Ljava/lang/String;)V");

    env->CallVoidMethod(obj, fieldMethodId, env->NewStringUTF("JiWenTing I Love You !"));
}

JNIEXPORT void JNICALL Java_example_zhangjunling_com_ndk_1hellowork_HelloWordJniActivity_callStaticMethod
        (JNIEnv *env, jobject obj){
    jclass staticMethodClass = env->GetObjectClass(obj);
    jmethodID staticMethodId = env->GetStaticMethodID(staticMethodClass,"onNativeStaticCallback","(Ljava/lang/String;)V");

    env->CallStaticVoidMethod(staticMethodClass, staticMethodId,env->NewStringUTF("Native Call Static Method. lalalala"));
}