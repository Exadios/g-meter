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

#ifndef GPSSENSORS_HPP
#define GPSSENSORS_HPP

#include <jni.h>

/**
 * This class is a singleton. Its purpose is to handle communication to and
 * from the Android sensors.
 *
 * Note: This class is not thread safe.
 */

class GPSSensor
  {
public:
  /**
   * Get a reference to the singleton GPSSensor object. If the object does not
   * yet it exist then it is created. This is the only way that the object
   * of this class may be created.
   * @return The reference the object. This reference is always valid at the
   *         time theis function is called.
   */
  static GPSSensor& Instance();
  
  /**
   * Set the GPS status.
   * @param env The JNI enviroment.
   * @param obj The JNI object.
   * @param connected The connected status: true or false.
   */
  void Connected(JNIEnv *env, jobject obj, jint connected);

  /**
   * Set the GPS state.
   * @param env The JNI enviroment.
   * @param obj The JNI object.
   * @param time GPS time.
   * @param n_birds Number of birds in view.
   * @param lambda GPS lambda.
   * @param phi GPS phi.
   * @param hasAlt Valid GPS altitude: true or false.
   * @param alt GPS altitude in meters.
   * @param hasBearing Valid GPS bearing: true or false.
   * @param bearing GPS bearing.
   * @param hasSpeed Valid speed: true or false.
   * @param speed GPS speed.
   * @param hasError Valid GPS error: true or false.
   * @param error GPS error.
   * @param hasAcc Valid GPS acceleration: true or false.
   * @param acc GPS acceleration.
   */
  void State(JNIEnv *env,
             jobject obj,
             jlong time,
             jint n_birds,
             jdouble lambda,
             jdouble phi,
             jboolean hasAlt,
             jdouble alt,
             jboolean hasBearing,
             jdouble bearing,
             jboolean hasSpeed,
             jdouble speed,
             jboolean hasError,
             jdouble error,
             jboolean hasAcc,
             jdouble acc);

private:
  /**
   * Ctor. Called from GPSSensor::Instance() only.
   */
  GPSSensor();

  /**
   * Do not allow copying by any method!
   */
  GPSSensor(const GPSSensor&);
  GPSSensor& operator=(const GPSSensor&);
  };


#endif  /* GPSSENSORS_HPP */
