//
// Created by camdora on 18-1-24.
//
#include <jni.h>
#include "log.h"

static jclass g_cls_MainActivity = NULL;

JNIEXPORT void JNICALL helloWordBreadDown(JNIEnv *env, jobject obj){
    LOGE("helloWordBreadDown.................");

    env = 0;

    env->NewStringUTF("zhangjunling");


}

const JNINativeMethod g_methods[] = {
        {"helloWordBreadDown", "()V", (void *) helloWordBreadDown},
};


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGI("JNI_OnLoad method call begin");
    JNIEnv *env = NULL;
    jclass cls = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    // 查找要加载的本地方法Class引用
    cls = env->FindClass("example/zhangjunling/com/ndk_hellowork/DebugActivity");
    if (cls == NULL) {
        return JNI_ERR;
    }
    // 将class的引用缓存到全局变量中
    g_cls_MainActivity = (jclass) env->NewWeakGlobalRef(cls);

    env->DeleteLocalRef(cls);   // 手动删除局部引用是个好习惯

    // 将java中的native方法与本地函数绑定
    env->RegisterNatives(g_cls_MainActivity, g_methods, sizeof(g_methods) / sizeof(g_methods[0]));
    LOGI("JNI_OnLoad method call end");

    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
    LOGI("JNI_OnUnload method call begin");
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return;
    }
    env->UnregisterNatives(g_cls_MainActivity); // so被卸载的时候解除注册
    env->DeleteWeakGlobalRef(g_cls_MainActivity);

}
