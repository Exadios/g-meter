/* Copyright_License {

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
#ifndef INU_HPP
#define INU_HPP

/**
 * \ingroup Engine_INU
 * @{
 */

#include <valarray>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

typedef boost::numeric::ublas::matrix<float> IMUmatrix;
typedef boost::numeric::ublas::vector<float> IMUvector;
//typedef Kalman::KVector<float, false> IMUvector;
//typedef Kalman::KMatrix<float, false> IMUmatrix;

/**
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
  Inu(float dt);

  /**
   * Ctor.
   * @param dt The IMU sample rate in seconds.
   * @param x Rotation about the \f$x\f$ axis, Radians.
   * @param y Rotation about the \f$y\f$ axis, Radians.
   * @param z Rotation about the \f$z\f$ axis, Radians.
   */
  Inu(float dt, float x, float y, float z);

  /**
   * Ctor.
   * @param dt The IMU sample rate in seconds.
   * @param R The initial rotation matrix from the body basis to the ECEF basis.
   */
  Inu(float dt, IMUmatrix R);

  /**
   * Set the initial rotation matrix from the body basis to the ECEF basis.
   * @param x Roatation about the \f$x\f$ axis, Radians.
   * @param y Roatation about the \f$y\f$ axis, Radians.
   * @param z Roatation about the \f$z\f$ axis, Radians.
   */
  void R0(float x, float y, float z);

  /**
   * Set the initial rotation matrix from the body basis to the ECEF basis.
   * @param R The initial rotation matrix from the body basis to the ECEF basis.
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
  bool Update(IMUvector& w, IMUvector& f, IMUvector& v, float gx);

  /**
   * Give the body angular velocities, \f$\Omega_{eb}^b\f$, in the body basis.
   * @return The \f$b\f$ basis velocity matrix.
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
  float gfh(float h) const;

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
  float dt;

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
  const float omega_ie;
  };

/*
 * \@}
 */
#endif // INU_HPP
