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
#include "Navigation/INU/Inu.hpp"

//-----------------------------------------------------------------------------
Inu::Inu(fixed dt)
  : omega_ie(0.00007292115) // Rads / sec
  {
  this->dt = dt;
  this->init = false;
  this->R.resize(3, 3);
  this->a.resize(3);
  this->Omega.resize(3, 3);
  this->R0(0, 0, 0);
  for (size_t i = 0; i < 3; i++)
    {
    this->a(i) = 0.0;
    for (size_t j = 0; j < 3; j++)
      this->Omega(i, j) = 0.0;
    }
  }

//-----------------------------------------------------------------------------
Inu::Inu(fixed dt, fixed x, fixed y, fixed z)
  : omega_ie(0.00007292115) // Rads / sec
  {
  this->dt = dt;
  this->init = false;
  this->R.resize(3, 3);
  this->a.resize(3);
  this->Omega.resize(3, 3);
  this->R0(x, y, z);
  for (size_t i = 0; i < 3; i++)
    {
    this->a(i) = 0.0;
    for (size_t j = 0; j < 3; j++)
      this->Omega(i, j) = 0.0;
    }
  }

//-----------------------------------------------------------------------------
Inu::Inu(fixed dt, IMUmatrix R)
  : omega_ie(0.00007292115) // Rads / sec
  {
  this->dt = dt;
  this->init = false;
  this->R.resize(3, 3);
  this->a.resize(3);
  this->Omega.resize(3, 3);
  this->R0(R);
  for (size_t i = 0; i < 3; i++)
    {
    this->a(i) = 0.0;
    for (size_t j = 0; j < 3; j++)
      this->Omega(i, j) = 0.0;
    }
  }

//-----------------------------------------------------------------------------
void
Inu::R0(fixed x, fixed y, fixed z)
  {
  this->R(0, 0) = cos(z) * cos(y);
  this->R(0, 1) = sin(z) * cos(x) + cos(y) * sin(y) * sin(x);
  this->R(0, 2) = sin(z) * sin(x) - cos(z) * sin(y) * cos(x);
  this->R(1, 0) = -cos(z) * cos(y);
  this->R(1, 1) = cos(z) * cos(x) - sin(z) * sin(y) * sin(x);
  this->R(1, 2) = cos(z) * cos(x);
  this->R(2, 0) = sin(y);
  this->R(2, 1) = -sin(x) * cos(y);
  this->R(2, 2) = cos(y) * cos(x);
  }

//-----------------------------------------------------------------------------
void
Inu::R0(IMUmatrix R)
  {
  this->R = R;
  }

//-----------------------------------------------------------------------------
Inu::~Inu()
  {
  }

//----------------------------------------------------------------------------
bool
Inu::Update(IMUvector& w, IMUvector &f, IMUvector &v, fixed gx)
  {
  // For clarity write out the system in full and let the optimizer do
  // its work.

  // Compute eqn 3.11- Omega_{eb}^b
  this->Omega(1, 2) = -(this->Omega(2, 1) = w(0) - this->R(0, 1) * omega_ie);
  this->Omega(2, 0) = -(this->Omega(0, 2) = w(1) - this->R(1, 1) * omega_ie);
  this->Omega(0, 1) = -(this->Omega(1, 0) = w(2) - this->R(2, 1) * omega_ie);
  // Done with eqn 2.11

  // Compute eqn 3.13 - \dot(v)(t_k)
  this->a(0) = this->R(0, 0) * f(0) +
               this->R(0, 1) * f(1) +
               this->R(0, 2) * f(2) -
               fixed(2) *
               (this->Omega(0, 0) * v(0) +
                this->Omega(0, 1) * v(1) +
                this->Omega(0, 2) * v(2)) +
               gx;
  this->a(1) = this->R(1, 0) * f(1) +
               this->R(1, 1) * f(1) +
               this->R(1, 2) * f(2) -
               fixed(2) *
               (this->Omega(1, 0) * v(0) +
                this->Omega(1, 1) * v(1) +
                this->Omega(1, 2) * v(2)) +
               gx;
  this->a(2) = this->R(2, 0) * f(1) +
               this->R(2, 1) * f(1) +
               this->R(2, 2) * f(2) -
               fixed(2) *
               (this->Omega(2, 0) * v(0) +
                this->Omega(2, 1) * v(1) +
                this->Omega(2, 2) * v(2)) +
               gx;
  // Done with eqn 3.13

  // Compute eqn 3.12 - R(t_k + 1)
  IMUmatrix Num(3, 3), Inv(3, 3);
  Num(0, 0) = fixed(2) + this->Omega(0, 0) * this->dt;
  Num(0, 1) = fixed(0) + this->Omega(0, 1) * this->dt;
  Num(0, 2) = fixed(0) + this->Omega(0, 2) * this->dt;
  Num(1, 0) = fixed(0) + this->Omega(1, 0) * this->dt;
  Num(1, 1) = fixed(2) + this->Omega(1, 1) * this->dt;
  Num(1, 2) = fixed(0) + this->Omega(1, 2) * this->dt;
  Num(2, 0) = fixed(0) + this->Omega(2, 0) * this->dt;
  Num(2, 1) = fixed(0) + this->Omega(2, 1) * this->dt;
  Num(2, 2) = fixed(2) + this->Omega(2, 2) * this->dt;
  Inv(0, 0) = fixed(2) - this->Omega(0, 0) * this->dt;
  Inv(0, 1) = fixed(0) - this->Omega(0, 1) * this->dt;
  Inv(0, 2) = fixed(0) - this->Omega(0, 2) * this->dt;
  Inv(1, 0) = fixed(0) - this->Omega(1, 0) * this->dt;
  Inv(1, 1) = fixed(2) - this->Omega(1, 1) * this->dt;
  Inv(1, 2) = fixed(0) - this->Omega(1, 2) * this->dt;
  Inv(2, 0) = fixed(0) - this->Omega(2, 0) * this->dt;
  Inv(2, 1) = fixed(0) - this->Omega(2, 1) * this->dt;
  Inv(2, 2) = fixed(2) - this->Omega(2, 2) * this->dt;

  // Check for non sigularity.
  fixed D = Inv(0, 0) * (Inv(1, 1) * Inv(2, 2) - Inv(2, 1) * Inv(1, 2)) -
            Inv(0, 1) * (Inv(1, 0) * Inv(2, 2) - Inv(2, 0) * Inv(1, 2)) +
            Inv(0, 2) * (Inv(1, 0) * Inv(2, 1) - Inv(2, 0) * Inv(1, 2));
  if ((double )fabs(D) < (10 * DBL_MIN))
    return false;  // Woops! A singularity or, at least, ill conditioned.

  // Compute the transform of the cofactors, C^T.
  IMUmatrix CT(3, 3);
  CT(0, 0) = ( Inv(1, 1) * Inv(2, 2) - Inv(2, 1) * Inv(1, 2)) / D;
  CT(1, 0) = (-Inv(1, 0) * Inv(2, 2) + Inv(2, 0) * Inv(1, 2)) / D;
  CT(2, 0) = ( Inv(1, 0) * Inv(2, 1) - Inv(2, 0) * Inv(1, 1)) / D;
  CT(0, 1) = (-Inv(0, 1) * Inv(2, 2) + Inv(2, 1) * Inv(0, 2)) / D;
  CT(1, 1) = ( Inv(0, 0) * Inv(2, 2) - Inv(2, 0) * Inv(0, 2)) / D;
  CT(2, 1) = (-Inv(0, 0) * Inv(2, 1) + Inv(2, 0) * Inv(0, 1)) / D;
  CT(0, 2) = ( Inv(0, 1) * Inv(1, 2) - Inv(1, 1) * Inv(0, 2)) / D;
  CT(1, 2) = (-Inv(0, 0) * Inv(2, 2) + Inv(1, 0) * Inv(0, 2)) / D;
  CT(2, 2) = ( Inv(0, 0) * Inv(1, 1) - Inv(1, 0) * Inv(0, 1)) / D;

  // Compute the Pade approximation.
  IMUmatrix P(3, 3);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      P(i, j) = Num(i, 0) * CT(0, j) +
                Num(i, 1) * CT(1, j) +
                Num(i, 2) * CT(2, j);

  // Compute the update of R(t_k + 1).
  IMUmatrix R(3, 3);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      R(i, j) = this->R(i, 0) * P(0, j) +
                this->R(i, 1) * P(1, j) +
                this->R(i, 2) * P(2, j);
  this->R = R;
  // Done with eqn 3.12

  return true;
  }

//-----------------------------------------------------------------------------
IMUmatrix
Inu::Omega_sub_eb_super_b() const
  {
  return this->Omega;
  }

//-----------------------------------------------------------------------------
IMUmatrix
Inu::R_sub_b_super_e() const
  {
  return this->R;
  }

//------------------------------------------------------------------------------
IMUvector
Inu::v_dot_super_e() const
  {
  return this->a;
  }

//------------------------------------------------------------------------------
#define G_0 fixed(9.80665)   // m/s^2
#define R_m fixed(6371009)   // m
fixed
Inu::gfh(fixed h) const
  {
  return fixed(G_0) * (R_m / (h + R_m)) * (R_m / (h + R_m));
  }
