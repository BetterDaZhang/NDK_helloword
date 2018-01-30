//
// Created by camdora on 18-1-30.
//
/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class example_zhangjunling_com_ndk_hellowork_socket_EchoClientActivity */

#ifndef NDK_HELLOWORK_ECHO_JNI_H
#define NDK_HELLOWORK_ECHO_JNI_H
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     example_zhangjunling_com_ndk_hellowork_socket_EchoClientActivity
 * Method:    nativeStartTcpClient
 * Signature: (Ljava/lang/String;ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_example_zhangjunling_com_ndk_1hellowork_socket_EchoClientActivity_nativeStartTcpClient
        (JNIEnv *, jobject, jstring, jint, jstring);

/*
 * Class:     example_zhangjunling_com_ndk_hellowork_socket_EchoClientActivity
 * Method:    nativeStartUdpClient
 * Signature: (Ljava/lang/String;ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_example_zhangjunling_com_ndk_1hellowork_socket_EchoClientActivity_nativeStartUdpClient
        (JNIEnv *, jobject, jstring, jint, jstring);

/*
 * Class:     example_zhangjunling_com_ndk_hellowork_socket_EchoServerActivity
 * Method:    nativeStartTcpServer
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_example_zhangjunling_com_ndk_1hellowork_socket_EchoServerActivity_nativeStartTcpServer
        (JNIEnv *, jobject, jint);

/*
 * Class:     example_zhangjunling_com_ndk_hellowork_socket_EchoServerActivity
 * Method:    nativeStartUdpServer
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_example_zhangjunling_com_ndk_1hellowork_socket_EchoServerActivity_nativeStartUdpServer
        (JNIEnv *, jobject, jint);


/*
 * Class:     example_zhangjunling_com_ndk_hellowork_socket_LocalEchoActivity
 * Method:    nativeStartLocalServer
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_example_zhangjunling_com_ndk_1hellowork_socket_LocalEchoActivity_nativeStartLocalServer
        (JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif //NDK_HELLOWORK_ECHO_JNI_H
