//
// Created by camdora on 18-1-20.
//
#include <ctype.h>
#ifndef NDK_HELLOWORK_UTIL_H
#define NDK_HELLOWORK_UTIL_H

char *strupr(char *str){
    char *orign=str;
    for (; *str!='\0'; str++)
        *str = toupper(*str);
    return orign;
}

#endif //NDK_HELLOWORK_UTIL_H
