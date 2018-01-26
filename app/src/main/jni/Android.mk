LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := helloworld
LOCAL_SRC_FILES := helloworld.cpp
LOCAL_LDLIBS := -llog
LOCAL_CPPFLAGS += -std=c++11
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := exception
LOCAL_SRC_FILES := exception.cpp
LOCAL_LDLIBS := -llog
LOCAL_CPPFLAGS += -std=c++11
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := reference
LOCAL_SRC_FILES := reference.cpp
LOCAL_LDLIBS := -llog
LOCAL_CPPFLAGS += -std=c++11
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := breakdown
LOCAL_SRC_FILES := breakdown.cpp
LOCAL_LDLIBS := -llog
LOCAL_CPPFLAGS += -std=c++11
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := bionic
LOCAL_SRC_FILES := bionic.cpp
LOCAL_LDLIBS := -llog
LOCAL_CPPFLAGS += -std=c++11
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := nativethreads
LOCAL_SRC_FILES := nativethreads.cpp
LOCAL_LDLIBS := -llog
LOCAL_CPPFLAGS += -std=c++11
include $(BUILD_SHARED_LIBRARY)

