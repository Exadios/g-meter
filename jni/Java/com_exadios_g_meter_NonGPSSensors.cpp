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

#include "Native/com_exadios_g_meter_NonGPSSensors.h"
#include "Executive/Android/NonGPSSensors.hpp"

/*
 * Class:     com_exadios_g_meter_NonGPSSensors
 * Method:    setAcceleration
 * Signature: (FFF)V
 */
JNIEXPORT void JNICALL Java_com_exadios_g_1meter_NonGPSSensors_setAcceleration
  (JNIEnv *env, jobject obj, jfloat x, jfloat y, jfloat z)
  {
  NonGPSSensors::Instance().Acceleration(env, obj, x, y, z);
  }

/*
 * Class:     com_exadios_g_meter_NonGPSSensors
 * Method:    setRotation
 * Signature: (FFF)V
 */
JNIEXPORT void JNICALL Java_com_exadios_g_1meter_NonGPSSensors_setRotation
  (JNIEnv *env, jobject obj, jfloat x, jfloat y, jfloat z)
  {
  NonGPSSensors::Instance().Rotation(env, obj, x, y, z);
  }

/*
 * Class:     com_exadios_g_meter_NonGPSSensors
 * Method:    setMagneticField
 * Signature: (FFF)V
 */
JNIEXPORT void JNICALL Java_com_exadios_g_1meter_NonGPSSensors_setMagneticField
  (JNIEnv *env, jobject obj, jfloat x, jfloat y, jfloat z)
  {
  NonGPSSensors::Instance().MagneticField(env, obj, x, y, z);
  }

/*
 * Class:     com_exadios_g_meter_NonGPSSensors
 * Method:    setBarometricPressure
 * Signature: (FF)V
 */
JNIEXPORT void JNICALL Java_com_exadios_g_1meter_NonGPSSensors_setBarometricPressure
  (JNIEnv *env, jobject obj, jfloat p, jfloat v)
  {
  NonGPSSensors::Instance().BarometricPressure(env, obj, p, v);
  }

