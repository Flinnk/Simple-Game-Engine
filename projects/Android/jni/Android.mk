
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CPPFLAGS := -D_ANDROID
LOCAL_CPPFLAGS += -std=c++11
APP_STL := gnustl_static
TARGET_PLATFORM := 21
LOCAL_MODULE    := Engine
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../src
LOCAL_SRC_FILES := ../../../src/Engine/Platform/Android/AndroidMain.cpp \
				   ../../../src/Engine/Platform/Android/AndroidLog.cpp \
				   ../../../src/Engine/Math/Vector2.cpp \
				   ../../../src/Engine/Math/Vector3.cpp \
				   ../../../src/Engine/Math/Matrix4.cpp \
				   ../../../src/Engine/Physics/SandboxPhysics.cpp \
				   ../../../src/Engine/Utils/File.cpp \
				   ../../../src/Engine/Utils/ResourceManager.cpp \
				   ../../../src/Engine/Utils/stb_image.cpp \
				   ../../../src/Engine/Utils/Stopwatch.cpp


NDK_OUT := LOCAL_PATH/../../../bin/android/

LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_STATIC_LIBRARY) 

$(call import-module,android/native_app_glue) 
