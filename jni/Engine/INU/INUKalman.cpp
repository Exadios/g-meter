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

#include <limits>
#include <float.h>
#include "Engine/Navigation/INU/Inu.hpp"
#include "Engine/Navigation/INU/INUKalman.hpp"

//------------------------------------------------------------------------------
INUKalman::INUKalman(fixed dT, int m)
  : dT(dT),
    m(m),
    s(0)
  {
  this->x.resize(14);
  this->R.resize(14, 14);
  this->P.resize(14, 14);
  this->Q.resize(14, 14);
  this->K.resize(14, 14);
  this->DT = this->m * this->dT;
  }

//------------------------------------------------------------------------------
INUKalman::~INUKalman()
  {
  }

//------------------------------------------------------------------------------
void
INUKalman::makeBaseA()
  {
  size_t i, j;

  for (i = 0; i < 14; i++)
    for (j = 0; j < 14; j++)
      this->A(i, j) = fixed(0);
  for (i = 0; i < 8; i++)
    this->A(i, i) = fixed(1.0);
  for (i = 0; i < 4; i++)
    this->A(i, i + 4) = this->dT;
  }

//------------------------------------------------------------------------------
void
INUKalman::makeBaseH()
  {
  for (size_t i = 0; i < 14; i++)
    for (size_t j = 0; j < 14; j++)
      H(i, j) = fixed(0.0);
  for (size_t i = 0; i < 8; i++)
    H(i, i) = fixed(1.0);
  }

//------------------------------------------------------------------------------
void
INUKalman::makeBaseV()
  {
  }

//------------------------------------------------------------------------------
void
INUKalman::makeBaseR()
  {
  }

//------------------------------------------------------------------------------
void
INUKalman::makeBaseW()
  {
  }

//------------------------------------------------------------------------------
void
INUKalman::makeBaseQ()
  {
  // Need to make some measurements to evaluate some real values for w.
  Vector w;
	w.resize(8);
  for (size_t i = 0; i < 4; i++)
    w(i) = fixed(0.1);
  for (size_t i = 4; i < 8; i++)
    w(i) = fixed(0.5);
  for (size_t i = 0; i < 8; i++)
    for (size_t j = 0; j < 8; j++)
      Q(i, j) = w(i) * w(j);
  }

//------------------------------------------------------------------------------
void
INUKalman::makeA()
  {
  }

//------------------------------------------------------------------------------
void
INUKalman::makeH()
  {
  }

//------------------------------------------------------------------------------
void
INUKalman::makeR()
  {
	// Get some stats from the GPS system to make an R matrix.
	}

//------------------------------------------------------------------------------
void
INUKalman::makeProcess()
  {
  Vector x(this->x.size());

  x(0) = this->x(0) + this->x(4) * this->dT;
  x(1) = this->x(1) + this->x(5) * this->dT;
  x(2) = this->x(2) + this->x(6) * this->dT;
  x(3) = this->x(3) + this->x(7) * this->dT;
  x(4) = this->x(4) + this->u(0) * this->dT;
  x(5) = this->x(5) + this->u(1) * this->dT;
  x(6) = this->x(6) + this->u(2) * this->dT;
  if (this->s == this->m)
    {    // A GPS update.
    x(4)  += this->x(8)  * this->DT + this->x(11) * this->DT * this->DT;
    x(5)  += this->x(9)  * this->DT + this->x(12) * this->DT * this->DT;
    x(6)  += this->x(10) * this->DT + this->x(13) * this->DT * this->DT;
    x(8)   = this->x(8)  + this->x(8)  * this->DT;  // * QG
    x(9)   = this->x(9)  + this->x(9)  * this->DT;  // * QG
    x(10)  = this->x(10) + this->x(10) * this->DT;  // * QG
    x(11)  = this->x(11) + this->x(11) * this->DT;  // * QA
    x(12)  = this->x(12) + this->x(12) * this->DT;  // * QA
    x(13)  = this->x(13) + this->x(13) * this->DT;  // * QA
    this->s = 1;
    }
  else
    {    // An INU only update.
    this->s++;
    }
  this->x.swap(x);
  }

//------------------------------------------------------------------------------
void
INUKalman::makeMeasure()
  {
  for (size_t i = 0; i < 8; i++)
    z(i) = x(i);
  for (size_t i = 8; i < 14; i++)
    z(i) = fixed(0.0);
  }

