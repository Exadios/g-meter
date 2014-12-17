/*
Copyright_License {

  G-Meter INU.
  Copyright (C) 2013-2015 Peter F Bradshaw
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

#ifndef NONGPSSENSORS_HPP
#define NONGPSSENSORS_HPP

#include <jni.h>
#include "Utility/DeviceInputBuffer.hpp"

/**
 * This class is a singleton. Its purpose is to handle communication to and
 * from the non GPS sensors.
 *
 * Note: This class is not thread safe.
 *
 */
class NonGPSSensors : public DeviceInputBuffer
  {
public:
  /**
   * Get a reference to the singleton NonGPSSensor object. If the object does
   * not yet it exist then it is created. This is the only way that the object
   * of this class may be created.
   * @return The reference the object. This reference is always valid at the
   *         time theis function is called.
   */
   static NonGPSSensors& Instance()
    {
    static NonGPSSensors instance;
    return instance;
    }


   /**
    * Set acceleration.
    * @param env The JNI enviroment.
    * @param obj The JNI object.
    * @param timestamp The timestamp of the observation in nano seconds,
    *                  arbitary timestamp.
    * @param x Acceleration in the body's x axis.
    * @param y Acceleration in the body's y axis.
    * @param z Acceleration in the body's z axis.
    */
   void Acceleration(JNIEnv *env, jobject obj,
                     jlong timestamp, jfloat x, jfloat y, jfloat z);

   /**
    * Set rotational velocity.
    * @param env The JNI enviroment.
    * @param obj The JNI object.
    * @param timestamp The timestamp of the observation in nano seconds,
    *                  arbitary timestamp.
    * @param x Rotation velocty about the body's x axis.
    * @param y Rotation velocty about the body's y axis.
    * @param z Rotation velocty about the body's z axis.
    */
   void Rotation(JNIEnv *env, jobject obj,
                 jlong timestamp, jfloat x, jfloat y, jfloat z);

   /**
    * Set magnetic field.
    * @param env The JNI enviroment.
    * @param obj The JNI object.
    * @param timestamp The timestamp of the observation in nano seconds,
    *                  arbitary timestamp.
    * @param x Magnetic field in the body's x axis.
    * @param y Magnetic field in the body's y axis.
    * @param z Magnetic field in the body's z axis.
    */
   void MagneticField(JNIEnv *env, jobject obj,
                      jlong timestamp, jfloat x, jfloat y, jfloat z);

   /**
    * Set barometric pressure.
    * @param env The JNI enviroment.
    * @param obj The JNI object.
    * @param timestamp The timestamp of the observation in nano seconds,
    *                  arbitary timestamp.
    * @param p The pressure.
    * @param v The variance of the observations.
    */
   void BarometricPressure(JNIEnv *env, jobject obj,
                           jlong timestamp, jfloat p, jfloat v);

   /**
    * Get the accelerometer measurement time.
    * @return The time in microseconds and arbitary epoch.
    */
   long A_t() const;

   /**
    * Get the accelerometer x variable.
    * @return The x variable in radians.
    */
   float A_x() const;

   /**
    * Get the accelerometer y variable.
    * @return The y variable in radians.
    */
   float A_y() const;

   /**
    * Get the accelerometer z variable.
    * @return The z variable in radians.
    */
   float A_z() const;

   /**
    * Get the gyro measurement time.
    * @return The time in microseconds and arbitary epoch.
    */
   long R_t() const;

   /**
    * Get the gyro rotation about the x axis.
    * @return The x variable in radians per second.
    */
   float R_x() const;

   /**
    * Get the gyro rotation about the y axis.
    * @return The y variable in radians per second.
    */
   float R_y() const;

   /**
    * Get the gyro rotation about the z axis.
    * @return The x variable in radians per second.
    */
   float R_z() const;

   /**
    * Get the magnetic field measurement time.
    * @return The time in microseconds and arbitary epoch.
    */
   long M_t() const;

   /**
    * Get the magnetic field the x axis.
    * @return The x variable in Gauss.
    */
   float M_x() const;

   /**
    * Get the magnetic field the y axis.
    * @return The y variable in Gauss.
    */
   float M_y() const;

   /**
    * Get the magnetic field the z axis.
    * @return The x variable in Gauss.
    */
   float M_z() const;

   /**
    * Get the barometric measurement time.
    * @return The time in microseconds and arbitary epoch.
    */
   long B_t() const;

   /**
    * Get the barometric pressure.
    * @return The pressure in hPa.
    */
   float B_p() const;

   /**
    * Get the barometric sea level pressure.
    * @return The pressure in hPa.
    */
   float B_v() const;

private:
  /**
   * Ctor. Called from NonGPSSensors::Instance() only.
   */
  NonGPSSensors();

  /**
   * Do not allow copying by any method!
   */
  NonGPSSensors(const NonGPSSensors&);
  NonGPSSensors& operator=(const NonGPSSensors&);

  /**
   * State variables.
   */
  long  a_t[2];
  float a_x[2], a_y[2], a_z[2];
  long  r_t[2];
  float r_x[2], r_y[2], r_z[2];
  long  m_t[2];
  float m_x[2], m_y[2], m_z[2];
  long  b_t[2];
  float b_p[2], b_v[2];

  };

#endif  /* NONGPSSENSORS_HPP */
