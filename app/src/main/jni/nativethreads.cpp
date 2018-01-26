//
// Created by camdora on 18-1-25.
//
#include "nativethreads_jni.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <jni.h>

//通过信号量控制POSIX线程的同步
#include <semaphore.h>

static jmethodID onNativeMessage;
static pthread_mutex_t pthread_mutex;
static jobject gObj;
static JavaVM *javaVM;

static sem_t pthread_sem;

struct MessageArgs{
    int threadsCount;
    int iterations;
};

JNIEXPORT void JNICALL Java_example_zhangjunling_com_ndk_1hellowork_ThreadActivity_nativeInit
(JNIEnv *env, jobject obj){

    if (0 != pthread_mutex_init(&pthread_mutex, NULL)) {
        jclass execeptionClass = env->FindClass("java/lang/RuntimeException");
        env->ThrowNew(execeptionClass, "init mutex error.");
        goto exit;
    }
//    sem_init(&pthread_sem, 0, 1);

    if(NULL == gObj){
        gObj = env->NewGlobalRef(obj);
        if (NULL == gObj) {
            goto exit;
        }
    }
    if(NULL == onNativeMessage){
        jclass clazz = env->GetObjectClass(obj);
        onNativeMessage = env->GetMethodID(clazz, "onNativeMessage", "(Ljava/lang/String;)V");
        if(NULL == onNativeMessage){
            jclass exceptonClass = env->FindClass("java/lang/RuntimeException");
            env->ThrowNew(exceptonClass, "Can't Find onNativeMessage Method.");
        }
    }

    exit:
        return;
}

JNIEXPORT void JNICALL Java_example_zhangjunling_com_ndk_1hellowork_ThreadActivity_nativeFree
(JNIEnv *env, jobject obj){
    if(NULL != onNativeMessage){
        onNativeMessage = NULL;
    }
    if(0 != pthread_mutex_destroy(&pthread_mutex)){
        jclass exceptionClass = env->FindClass("java/lang/RuntimeException");
        env->ThrowNew(exceptionClass, "Unable destroy mutext.");
    }
//    sem_destroy(&pthread_sem);

    if (NULL != gObj) {
        env->DeleteGlobalRef(gObj);
        gObj = NULL;
    }
}

JNIEXPORT void JNICALL Java_example_zhangjunling_com_ndk_1hellowork_ThreadActivity_nativeWork
(JNIEnv *env, jobject obj, jint threadsCount, jint iterations){

    if(0 != pthread_mutex_lock(&pthread_mutex)){
        jclass exceptionClass = env->FindClass("java/lang/RuntimeException");
        env->ThrowNew(exceptionClass, "Unable lock mutext.");
    }

//    sem_wait(&pthread_sem);

    for(int i = 0; i < iterations; i++){
        char message[64] = {0};
        sprintf(message, "Worker %d: iteration %d",threadsCount,i);
        env->CallVoidMethod(obj, onNativeMessage, env->NewStringUTF(message));

        if (NULL != env->ExceptionOccurred()) {
            break;
        }
        sleep(1);
    }

   if(0 !=  pthread_mutex_unlock(&pthread_mutex)){
       jclass exceptionClass = env->FindClass("java/lang/RuntimeException");
       env->ThrowNew(exceptionClass, "Unable unlock mutext.");
   }
//    sem_post(&pthread_sem);

}

void* nativeWorkerThread(void* nativeMessage){
    JNIEnv *env = NULL;
    if(0 == javaVM->AttachCurrentThread(&env, NULL)){
        MessageArgs *messageArgs = (MessageArgs*)nativeMessage;
        Java_example_zhangjunling_com_ndk_1hellowork_ThreadActivity_nativeWork(env, gObj,
                                                                               messageArgs->threadsCount,
                                                                               messageArgs->iterations);
        delete messageArgs;
        javaVM->DetachCurrentThread();
    }
    return (void*)1;
}

JNIEXPORT void JNICALL Java_example_zhangjunling_com_ndk_1hellowork_ThreadActivity_posixThreads
        (JNIEnv *env, jobject obj, jint threadsCount, jint iterations){

    pthread_t threadHandler[threadsCount];
    for (int i = 0; i < threadsCount; i++) {
        MessageArgs *messageArgs = new MessageArgs();
        messageArgs->threadsCount = i;
        messageArgs->iterations = iterations;
        if(0 != pthread_create(&threadHandler[i], NULL, nativeWorkerThread,messageArgs)){
            jclass exceptionClass = env->FindClass("java/lang/RuntimeException");
            env->ThrowNew(exceptionClass, "Unable create thread.");
            goto exit;
        }
    }

    //这里会导致主线程一直等待到其他线程执行完后才会继续执行,所有会有卡住效果;
    //该方法这行完后,才会继续执行Java端message的输出;
    for (int i = 0; i < threadsCount; i++) {
        void* result = NULL;
        if (0 != pthread_join(threadHandler[i], &result)) {
            jclass exceptionClass = env->FindClass("java/lang/RuntimeException");
            env->ThrowNew(exceptionClass, "Unable to join thread.");
            goto exit;
        }else{
            char message[56];
            sprintf(message, "Worked Thread %d returned %d", i, result);
            jstring javaString = env->NewStringUTF(message);
            env->CallVoidMethod(gObj, onNativeMessage, javaString);
            if(NULL != env->ExceptionOccurred()){
                goto exit;
            }
        }
    }

exit:
    return;
}

jint JNI_OnLoad (JavaVM* vm, void* reserved)
{
    // Cache the JavaVM interface pointer
    javaVM = vm;

    return JNI_VERSION_1_4;
}
