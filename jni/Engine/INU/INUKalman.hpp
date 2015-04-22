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
#ifndef INUKALMAN_HPP
#define INUKALMAN_HPP

/**
 * \ingroup Engine_INU
 * @{
 */

#include "bayesclasses-bayes/BayesFilter/SIRFlt.hpp"
#include "bayesclasses-bayes/BayesFilter/models.hpp"
#include "bayesclasses-bayes/Test/random.hpp"
#include <cmath>
#include <boost/boost/numeric/ublas/io.hpp>

/**
 * A class designed to take INU and GPS data and merge those two data in an
 * optimal manner.
 */

typedef boost::numeric::ublas::vector<float> INUKalmanState;
typedef boost::numeric::ublas::vector<float> INUUpdate;
typedef boost::numeric::ublas::vector<float> INUObservation;
typedef boost::numeric::ublas::matrix<float> INUSystemMatrix;

class INUKalman
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

private:

  /**
   * Random generator for SIR.
   */
  class Boost_random : public Bayesian_filter::SIR_random,
                       public Bayesian_filter_test::Boost_random
    {
  public:
    using Bayesian_filter_test::Boost_random::normal;

    /**
     * Normal distribution.
     */
	  void normal (Bayesian_filter_matrix::DenseVec& v)
	    {
		  Bayesian_filter_test::Boost_random::normal(v);
	    }
	  using Bayesian_filter_test::Boost_random::uniform_01;

    /**
     * White?
     */
	  void uniform_01 (Bayesian_filter_matrix::DenseVec& v)
	    {
		  Bayesian_filter_test::Boost_random::uniform_01(v);
	    }
    };

  /**
   * Filter observation algorithm.
   */
  class Observe : public Bayesian_filter::General_LiUnAd_observe_model
    {
  public:
    Observe();
    };

  /**
   * Filter prediction algorithm.
   */
  class Predict : public Bayesian_filter::Sampled_LiInAd_predict_model
    {
  public:
    Predict(float dT, int m, Boost_random& rnd);

  private:
    const float q_G;
    const float q_A;
    INUSystemMatrix Propagate;
    INUSystemMatrix Update;
    };

private:
  /**
   * No default Ctor.
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

  float dT;
  int m;
  int s;
  };

/*
 * @}
 */
#endif // INUKALMAN_HPP
