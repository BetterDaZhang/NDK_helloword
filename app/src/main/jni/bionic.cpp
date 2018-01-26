//
// Created by camdora on 18-1-25.
//
#include "bionic_jni.h"
#include "log.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


JNIEXPORT void JNICALL Java_example_zhangjunling_com_ndk_1hellowork_BionicActivity_processInteractoin
        (JNIEnv *env, jobject obj){
    int result;
    result = system("mkdir /data/data/example.zhangjunling.com.ndk_hellowork/zjl");
    if(-1 == result || 127 == result){
        LOGE("zjl 文件夹创建失败!");
    }else{
        LOGE("zjl 文件夹创建成功!");
    }

    FILE* stream;
    stream = popen("ls", "r");
    if (NULL == stream) {
        LOGE("Unable to execute the command.");
    }else{
        char buffer[1024];
        int status;

        while(NULL != fgets(buffer,1024,stream)){
            LOGE("read:%s", buffer);
        }
        status = pclose(stream);
        LOGE("process exited with status %d",status);
    }

    uid_t uid;
    uid = getuid();
    LOGI("Application User ID is %u",uid);

    gid_t gid;
    gid = getgid();
    LOGI("Application Group ID is %u",gid);

    char* userName;
    userName = getlogin();
    LOGI("Applicaton user name is %s",userName);

}