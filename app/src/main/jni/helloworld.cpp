#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helloworld_jni.h"
#include "util.h"
#include <android/log.h>

#define LOGE(format, ...)  __android_log_print(ANDROID_LOG_ERROR, "(>_<)", format, ##__VA_ARGS__)

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
