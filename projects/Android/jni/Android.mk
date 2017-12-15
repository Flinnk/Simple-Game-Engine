
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CPPFLAGS := -D_ANDROID
LOCAL_CFLAGS += -std=gnu++11
TARGET_PLATFORM := 21
LOCAL_MODULE    := Engine
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../src
LOCAL_SRC_FILES := 

NDK_OUT := LOCAL_PATH/../../../bin/android/

LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_STATIC_LIBRARY) 

$(call import-module,android/native_app_glue) 
