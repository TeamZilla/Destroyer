# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(LOCAL_PATH)/Platform.mk

include $(CLEAR_VARS)
LOCAL_MODULE := libopenal
LOCAL_SRC_FILES := ../../ext/lib/android/libopenal.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libsndfile
LOCAL_SRC_FILES := ../../ext/lib/android/libsndfile.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := uthengine
LOCAL_SRC_FILES := main.cpp \
../../vs2013/Destroyer/source/Background.cpp \
../../vs2013/Destroyer/source/BackgroundManager.cpp \
../../vs2013/Destroyer/source/Button.cpp \
../../vs2013/Destroyer/source/EnemyFactory.cpp \
../../vs2013/Destroyer/source/ExplosionEmitter.cpp \
../../vs2013/Destroyer/source/FireBreath.cpp \
../../vs2013/Destroyer/source/FlameEmitter.cpp \
../../vs2013/Destroyer/source/GameScene.cpp \
../../vs2013/Destroyer/source/GameStats.cpp \
../../vs2013/Destroyer/source/Health.cpp \
../../vs2013/Destroyer/source/Heli.cpp \
../../vs2013/Destroyer/source/Missile.cpp \
../../vs2013/Destroyer/source/Player.cpp \
../../vs2013/Destroyer/source/Pickup.cpp \
../../vs2013/Destroyer/source/Road.cpp \
../../vs2013/Destroyer/source/RoadBlock.cpp \
../../vs2013/Destroyer/source/TankBullet.cpp \
../../vs2013/Destroyer/source/TitleScene.cpp
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 -lOpenSLES
LOCAL_STATIC_LIBRARIES := android_native_app_glue engine
LOCAL_SHARED_LIBRARIES :=
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../vs2013/Destroyer/include/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../include/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../ext/include/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../ext/include/freetype_include/

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
