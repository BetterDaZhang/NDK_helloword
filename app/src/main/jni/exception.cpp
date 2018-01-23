//
// Created by camdora on 18-1-23.
//
#include "exception_jni.h"
#include "log.h"
#include "util.h"


JNIEXPORT jstring JNICALL Java_example_zhangjunling_com_ndk_1hellowork_ExceptionJniActivity_exceptionHelloWord
        (JNIEnv *env, jobject obj){
    return env->NewStringUTF("Jni Exceptoin .");
}

JNIEXPORT void JNICALL Java_example_zhangjunling_com_ndk_1hellowork_ExceptionJniActivity_doExceptionTest
        (JNIEnv *env, jobject obj){
    jclass objClass = env->GetObjectClass(obj);
    jmethodID objMethodId = env->GetStaticMethodID(objClass, "exceptionCallback", "()V");
    env->CallStaticVoidMethod(objClass, objMethodId);

    if(env->ExceptionCheck()){
        env->ExceptionDescribe();
        env->ExceptionClear();
        ThrowExceptionByPackageName(env, "java/lang/Exception", "Jni 抛出了异常.");
        LOGE("发生异常了...................");
        return;
    }
    jmethodID normalMethodId = env->GetStaticMethodID(objClass, "normalCallback", "()V");
    env->CallStaticVoidMethod(objClass, normalMethodId);
}
