/* Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000-2012 The XCSoar Project
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
#ifndef INU_HPP
#define INU_HPP

/**
 * \ingroup Engine_Navigation_INU
 * @{
 */

#include <valarray>
#include <Math/fixed.hpp>
#include <Math/kalman/kalman/kvector.hpp>
#include <Math/kalman/kalman/kmatrix.hpp>

typedef Kalman::KVector<fixed, false> IMUvector;
typedef Kalman::KMatrix<fixed, false> IMUmatrix;

/**
 * @file
 * A class to implement a Inertial Navigation Unit (INU) using gyros and
 * accelerometers (typically MEMS devices) found on many Android platforms.
 */

class Inu
  {
public:
  
  /**
   * Ctor. The initial rotation matrix from the body basis to the ECEF basis is
   * set to (0, 0, 0)
   * @param dt The IMU sample rate in seconds.
   */
  Inu(fixed dt);

  /**
   * Ctor.
   * @param dt The IMU sample rate in seconds.
   * @x Roatation about the $x$ axis, Radians.
   * @y Roatation about the $y$ axis, Radians.
   * @z Roatation about the $z$ axis, Radians.
   */
  Inu(fixed dt, fixed x, fixed y, fixed z);

  /**
   * Ctor.
   * @param dt The IMU sample rate in seconds.
   * @R The initial rotation matrix from the body basis to the ECEF basis.
   */
  Inu(fixed dt, IMUmatrix R);

  /**
   * Set the initial rotation matrix from the body basis to the ECEF basis.
   * @x Roatation about the $x$ axis, Radians.
   * @y Roatation about the $y$ axis, Radians.
   * @z Roatation about the $z$ axis, Radians.
   */
  void R0(fixed x, fixed y, fixed z);

  /**
   * Set the initial rotation matrix from the body basis to the ECEF basis.
   * @R The initial rotation matrix from the body basis to the ECEF basis.
   */
  void R0(IMUmatrix R);

  /**
   * Dtor.
   */
  virtual ~Inu();

  /**
   * Update the state of the INS. To be called once every IMU sample, \deltaT.
   * @param w The vector of the gyro rotation velocities in the 'b'
   *          domain.
   * @param f The vector of the accelerometer forces in the 'b' domain.
   * @param v The vector of the velocities in the 'e' domain.
   * @param gx The value of gravity, G, at our current position in the
   *           'e' domain.
   * @result If a result can be computed then true, false otherwise.
   */
  bool Update(IMUvector& w, IMUvector& f, IMUvector& v, fixed gx);

  /**
   * Give the body angular velocities, $\Omega_{eb}^b$, in the body basis.
   * @return The $b$ basis velocity matrix.
   */
  IMUmatrix Omega_sub_eb_super_b() const;

  /**
   * Give the Direction Cosine Matrix of the $b$ basis to the $e$ basis.
   * @return The Direction Cosine Matrix.
  */
  IMUmatrix R_sub_b_super_e() const;

  /**
   * Give the accelerations in the 'e' domain.
   * @return The 'e' domain acceleration vector.
   */
  IMUvector v_dot_super_e() const;

  /**
   * Compute an approximate gravitational force ans a function of height
   * above the Geod.
   * @param h Height above the Geog in meters.
   * @return Gravitational acceleration at h.
   */
  fixed gfh(fixed h) const;

private:
     
  /**
   * Multiply two 3x3 matrices.
   * @param A The L.H. matrix.
   * @param B The R.H. matrix.
   * @return The result matrix.
   */
  inline IMUmatrix multiply(const IMUmatrix& A, const IMUmatrix& B)
    {
    int i, j;
    IMUmatrix R;

    for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
        R(i, j) = A(i, 0) * B(0, j) + A(i, 1) * B(1, j) + A(i, 2) * B(2, j);
    return R;
    }

  /**
   * The IMU sample rate in seconds.
   */
  fixed dt;

  /**
   * The attitude state in the 'e' domain.
   */
  IMUmatrix R;

  /**
   * The acceleration state in the 'e' domain.
   */
  IMUvector a;
     
  /**
   * The attitude rate in the 'e' domain.
   */
  IMUmatrix Omega;

  /**
   * Has Compute been initialized by one, or more, sample(s).
   */
  bool init;

  /**
   * The value of the instrinsic earth rotation rate.
   */
  const fixed omega_ie;
  };

/*
 * \@}
 */
#endif // INU_HPP
