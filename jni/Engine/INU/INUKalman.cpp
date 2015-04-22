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

#include <limits>
#include <float.h>
#include "Inu.hpp"
#include "INUKalman.hpp"

//static INUKalman::Predict::q_G = 1.0;
//static INUKalman::Predict::q_A = 1.0;

//------------------------------------------------------------------------------
INUKalman::INUKalman(float dT, int m)
  : dT(dT),
    m(m),
    s(0)
  {
  }

//------------------------------------------------------------------------------
INUKalman::~INUKalman()
  {
  }

//------------------------------------------------------------------------------
INUKalman::Observe::Observe()
  : General_LiUnAd_observe_model(14, 1)
  {
  }

//------------------------------------------------------------------------------
INUKalman::Predict::Predict(float dT, int m, Boost_random& rnd)
  : Bayesian_filter::Sampled_LiInAd_predict_model(14, 1, rnd),
    q_G(1.0),
    q_A(1.0)
  {
  int i, j;

  this->Propagate.resize(14, 14);
  this->Update.resize(14, 14);

  for (i = 0; i < 14; i++)
    for (j = 0; j < 14; j++)
      this->Propagate(i, j) = Update(i, j) = 0.0;

  // A_{11}
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      {
      if (i == j)
        this->Propagate(i, j) = this->Update(i, j) = 1.0;
      else if (j == (i + 4))
        this->Propagate(i, j) = this->Update(i, j) = dT;
      }
  // Finish A_{11}

  // A_{12}
  for (i = 4; i < 7; i++)
    for (j = 8; j < 14; j++)
      {
      if (i == (j - 4))
        this->Update(i, j) = m * dT;
      else if (i == (j - 7))
        this->Update(i, j) = m * m * dT * dT;
      }
  // Finish A_{12}

  // A_{22}  
  for (i = 8; i < 11; i++)
    for (j = 8; j < 11; j++)
      {
      if (i == j)
        this->Update(i, j) = this->q_G;
      }

  for (i = 11; i < 14; i++)
    for(j = 11; j < 14; j++)
      {
      if (i == j)
        this->Update(i, j) = this->q_A;
      }
  // Finish A_{22}
  
  this->Fx = this->Propagate;
  }
