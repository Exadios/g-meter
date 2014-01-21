/* Copyright_License {

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
#ifndef INUKALMAN_HPP
#define INUKALMAN_HPP

/**
 * \ingroup Engine_INU
 * @{
 */

#include "Utility/Mutex.hpp"
#include "Engine/Kalman/kalman/kvector.hpp"
#include "Engine/Kalman/kalman/kmatrix.hpp"
#include "Engine/Kalman/kalman/kfilter.hpp"

/**
 * @file
 * A class designed to take INU and GPS data and merge those two data in an
 * optimal manner.
 */

typedef Kalman::KVector<float, false> INUKalmanState;
typedef Kalman::KVector<float, false> INUUpdate;
typedef Kalman::KVector<float, false> INUObservation;
typedef Kalman::KMatrix<float, false> INUSystemMatrix;

class INUKalman : public Kalman::KFilter<float, false, false, false>
  {
  public:
    /**
     * Ctor.
     * @param dT the IMU sample period in seconds.
     * @param m The ratio between the IMU sample period and the GPS sample rate.
     */
    INUKalman(float dT, int m);

    /**
     * Dtor.
     */
    virtual ~INUKalman();

  protected:
    void makeBaseA();
    void makeBaseH();
    void makeBaseV();
    void makeBaseR();
    void makeBaseW();
    void makeBaseQ();

    void makeA();
    void makeH();
		void makeR();
    void makeProcess();
    void makeMeasure();

  private:
    /**
     * Not default Ctor.
     */
    INUKalman();

    /**
     * No copy Ctor.
     */
    INUKalman(const INUKalman &rhs);

    /**
     * No copy operator.
     */
    INUKalman &operator=(const INUKalman &rhs);
    INUKalman operator=(const INUKalman &rhs) const;

    /**
     * The system state vector, \f$\hat{x} \left( t_k \right) \f$.
     */
    INUKalmanState x;

    /**
     * The error covariance matrix, \$P \left( t_k \right) \f$.
     */
    INUSystemMatrix P;

    /**
     * The plant noise covariance matrix, \f$Q\f$.
     */
    INUSystemMatrix Q;

    /**
     * The Kalman gain, \f$K \left( t_k \right) \f$.
     */
    INUSystemMatrix K;

    /**
     * The IMU sample period, \f$\delta T\f$.
     */
    float dT;

    /**
     * The integer ratio (assuming synchronous sampling) between the IMU sample
     * period, \f$\delta T\f$, and the GPS sample period, \f$\Delta T\f$.
     *
     * \f$m = \Delta T / \delta t \f$
     */
    int m;

    /**
     * The GPS sample period, \f$\Delta T\f$.
     */
    float DT;

    /**

     * IMU sample counter.
     */
    int s;

    /**
     * A guard for 's' above
     */
    Mutex sl;
  };

/*
 * @}
 */
#endif // INUKALMAN_HPP
