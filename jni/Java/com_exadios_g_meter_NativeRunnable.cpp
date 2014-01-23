/*
Copyright_License {

  G-Meter INU.
  Copyright (C) 2013-2014 Peter F Bradshaw
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#include "Native/com_exadios_g_meter_NativeRunnable.h"

//-----------------------------------------------------------------------------
JNIEXPORT jboolean
JNICALL Java_com_exadios_g_1meter_NativeRunnable_initializeNative(JNIEnv *env,
                                                                  jobject obj,
                                                                  jint,
                                                                  jstring)
  {
  return false;
  }

//-----------------------------------------------------------------------------
JNIEXPORT void
JNICALL Java_com_exadios_g_1meter_NativeRunnable_runNative(JNIEnv *env,
                                                           jobject obj)
  {
  }

//-----------------------------------------------------------------------------
JNIEXPORT void
JNICALL Java_com_exadios_g_1meter_NativeRunnable_deinitializeNative(JNIEnv *env,
                                                                    jobject obj)
  {
  }

//-----------------------------------------------------------------------------
JNIEXPORT void
JNICALL Java_com_exadios_g_1meter_NativeRunnable_pauseNative(JNIEnv *env,
                                                             jobject obj)
  {
  }

//-----------------------------------------------------------------------------
JNIEXPORT void
JNICALL Java_com_exadios_g_1meter_NativeRunnable_resumeNative(JNIEnv *env,
                                                              jobject obj)
  {
  }

//-----------------------------------------------------------------------------
JNIEXPORT void
JNICALL Java_com_exadios_g_1meter_NativeRunnable_setBatteryPercent
  (JNIEnv *env, jobject obj, jint, jint)
  {
  }

//-----------------------------------------------------------------------------
JNIEXPORT void
JNICALL Java_com_exadios_g_1meter_NativeRunnable_setHapticFeedback
  (JNIEnv *env, jobject obj, jboolean)
  {
  }

//-----------------------------------------------------------------------------
JNIEXPORT void JNICALL Java_com_exadios_g_1meter_NativeRunnable_onCreateNative
  (JNIEnv *, jobject)
  {
  }

//-----------------------------------------------------------------------------
JNIEXPORT void
JNICALL Java_com_exadios_g_1meter_NativeRunnable_onDestroyNative(JNIEnv *env,
                                                                 jobject obj)
  {
  }

//-----------------------------------------------------------------------------
JNIEXPORT void
JNICALL Java_com_exadios_g_1meter_NativeRunnable_onStartNative(JNIEnv *env,
                                                               jobject obj)
  {
  }

