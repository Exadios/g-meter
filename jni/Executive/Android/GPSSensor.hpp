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

#ifndef GPSSENSORS_HPP
#define GPSSENSORS_HPP

#include <jni.h>
#include "Utility/DeviceInputBuffer.hpp"

/**
 * This class is a singleton. Its purpose is to handle communication to and
 * from the Android GPS systems.
 *
 * This class buffers that data in order to ensure consistancy.
 */

class GPSSensor : public DeviceInputBuffer
  {
public:
  /**
   * Get a reference to the singleton GPSSensor object. If the object does not
   * yet it exist then it is created. This is the only way that the object
   * of this class may be created.
   * @return The reference the object. This reference is always valid at the
   *         time theis function is called.
   */
  static GPSSensor& Instance()
      {
      static GPSSensor instance;
      return instance;
      }

  /**
   * GPS status. These definitions originate in the Android LocationProvider
   * API documentation.
   */
  enum GPSStatus {
                  OUT_OF_SERVICE          = 0,  // GPS disabled
                  TEMPORARILY_UNAVAILABLE = 1,  // Waiting for fix
                  AVAILABLE               = 2   // Position available
                 };
  
  /**
   * Set the GPS status.
   * @param env The JNI enviroment.
   * @param obj The JNI object.
   * @param connected The connected status: true or false.
   */
  void Connected(JNIEnv *env, jobject obj, jint connected);

  /**
   * Give the GPS connection state.
   * @return The state: OUT_OF_SERVICE - not connected,
                        TEMPORARILY_UNAVAILABLE - waiting for fix,
                        AVAILABLE - fix available.
   */
  GPSStatus Connected() const;


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

  /**
   * Give the time of the fix.
   * @return The time of the fix from the GPS unit.
   */
  long Time() const;

  /**
   * Give the number of birds.
   * @return The number of birds used to develope the fix.
   */
  int Birds() const;

  /**
   * Give the latitude of the fix.
   * @return The latitude in radians.
   */
  double Phi() const;

  /**
   * Give the longitude of the fix.
   * @return The longitude in radians.
   */
  double Lambda() const;

  /**
   * Give the status of the altitude.
   * @return If the value of Z() is good then true.
   */
  bool ZStatus() const;

  /**
   * Give the altitude above the Geod.
   * @return The altitude in meters.
   */
  double Z() const;

  /**
   * Give the status of the argument of the track.
   * @return If the value of Omega() is good then true.
   */
  bool OmegaStatus() const;

  /**
   * Give the argument of the track.
   * @return The argument in radians.
   */
  double Omega() const;

  /**
   * Give the status of the magnitude of the track.
   * @return If the value of S() is good then true.
   */
  bool SStatus() const;

  /**
   * Give the magnitude of the track.
   * @return The magnitude in meters per second.
   */
  double S() const;

  /**
   * Give the status of the error.
   * @return If the value of Epsilon() is good then true.
   */
  bool EpsilonStatus() const;

  /**
   * Give the value of the fix error.
   * @return The representative error of the fix in meters.
   */
  double Epsilon() const;

  /**
   * Give the status of the acceleration value.
   * @return If the value A() is good then true.
   */
  bool AStatus() const;

  /**
   * Give the value of the acceleration.
   * @return The acceleration in meters per second per second.
   */
  double A() const;

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

  /**
   * State.
   */
  GPSStatus status;        // GPS status from Java.
  int    n[2];             // Number of birds.
  long   t[2];             // Time of observation.
  double phi[2];           // Lat.
  double lambda[2];        // Lon.
  double z[2];             // Alt.
  bool   z_good[2];        // Z value are valid.
  double omega[2];         // Argument to track vector.
  bool   omega_good[2];    // Omega value is valid.
  double s[2];             // Magnitude of the track vector.
  bool   s_good[2];        // S value is valid.
  double epsilon[2];       // Error estimate.
  bool   epsilon_good[2];  // Epsilon value is valid.
  double a[2];             // Magnitude of acceleration.
  bool   a_good[2];        // A value is valid.
  };


#endif  /* GPSSENSORS_HPP */
