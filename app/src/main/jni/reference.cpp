//
// Created by camdora on 18-1-23.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "reference_jni.h"
#include "util.h"
#include "log.h"

static jclass g_cls_MainActivity = NULL;
static jstring mGlobalString;

jobjectArray getStrings(JNIEnv *env, jobject obj, jint count, jstring sample) {
    jobjectArray str_array = NULL;
    jclass cls_string = NULL;
    jmethodID mid_string_init;
    jobject obj_str = NULL;
    const char *c_str_sample = NULL;
    char buff[256];
    int i;

    // 保证至少可以创建3个局部引用（str_array，cls_string，obj_str）
    if (env->EnsureLocalCapacity(3) != JNI_OK) {
        return NULL;
    }

    c_str_sample = env->GetStringUTFChars(sample, NULL);
    if (c_str_sample == NULL) {
        return NULL;
    }

    cls_string = env->FindClass("java/lang/String");
    if (cls_string == NULL) {
        return NULL;
    }

    // 获取String的构造方法
    mid_string_init = env->GetMethodID(cls_string, "<init>", "()V");
    if (mid_string_init == NULL) {
        env->DeleteLocalRef(cls_string);
        return NULL;
    }
    obj_str = env->NewObject(cls_string, mid_string_init);
    if (obj_str == NULL) {
        env->DeleteLocalRef(cls_string);
        return NULL;
    }

    // 创建一个字符串数组
    str_array = env->NewObjectArray(count, cls_string, obj_str);
    if (str_array == NULL) {
        env->DeleteLocalRef(cls_string);
        env->DeleteLocalRef(obj_str);
        return NULL;
    }


    // 给数组中每个元素赋值
    for (i = 0; i < count; ++i) {
        memset(buff, 0, sizeof(buff));   // 初始一下缓冲区
        sprintf(buff, c_str_sample,i);
        jstring newStr = env->NewStringUTF(buff);
        env->SetObjectArrayElement(str_array, i, newStr);
        //在一个本地方法中，如果使用了大量的局部引用而没有及时释放的话，随时都有可能造成程序崩溃的现象
        env->DeleteLocalRef(newStr);
    }

    // 释放模板字符串所占的内存
    env->ReleaseStringUTFChars(sample, c_str_sample);

    // 释放局部引用所占用的资源
    env->DeleteLocalRef(cls_string);
    env->DeleteLocalRef(obj_str);

    return str_array;
}


void  initGlobalReference(JNIEnv *env, jobject obj){
    jstring globalString = env->NewStringUTF("Global Reference.");
    mGlobalString = (jstring)env->NewGlobalRef(globalString);
}

jstring callGlobalReference(JNIEnv *env, jobject obj){
    return mGlobalString;
}

const JNINativeMethod g_methods[] = {
        {"getStrings", "(ILjava/lang/String;)[Ljava/lang/String;", (void *) getStrings},
        {"initGlobalReference","()V",(void*) initGlobalReference},
        {"callGlobalReference","()Ljava/lang/String;",(void*) callGlobalReference},
};


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    LOGI("JNI_OnLoad method call begin");
    JNIEnv* env = NULL;
    jclass cls = NULL;
    if(vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    // 查找要加载的本地方法Class引用
    cls = env->FindClass("example/zhangjunling/com/ndk_hellowork/ReferenceJniActivity");
    if(cls == NULL) {
        return JNI_ERR;
    }
    // 将class的引用缓存到全局变量中
    g_cls_MainActivity = (jclass)env->NewWeakGlobalRef(cls);

    env->DeleteLocalRef(cls);   // 手动删除局部引用是个好习惯

    // 将java中的native方法与本地函数绑定
    env->RegisterNatives(g_cls_MainActivity, g_methods, sizeof(g_methods) / sizeof(g_methods[0]));
    LOGI("JNI_OnLoad method call end");

    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved)
{
    LOGI("JNI_OnUnload method call begin");
    JNIEnv *env = NULL;
    if(vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        return;
    }
    env->UnregisterNatives(g_cls_MainActivity); // so被卸载的时候解除注册
    env->DeleteWeakGlobalRef(g_cls_MainActivity);

    env->DeleteGlobalRef(mGlobalString);
}

