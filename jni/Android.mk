LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Ins

LOCAL_SRC_FILES := Engine/INU/Inu.cpp \
                   Engine/INU/INUKalman.cpp \
                   Engine/Kalman/kstatics.cpp

include $(BUILD_SHARED_LIBRARY)

