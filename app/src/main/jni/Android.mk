LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := helloworld
LOCAL_SRC_FILES := helloworld.cpp

LOCAL_LDLIBS := -llog
LOCAL_CPPFLAGS += -std=c++11
include $(BUILD_SHARED_LIBRARY)