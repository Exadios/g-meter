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

#include "GPSSensor.hpp"

//-----------------------------------------------------------------------------
void
GPSSensor::Connected(JNIEnv *env, jobject obj, jint connected)
  {
  this->status = (GPSStatus )connected;
  }

//-----------------------------------------------------------------------------
void
GPSSensor::State(JNIEnv *env,
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
                 jdouble acc)
  {
  this->locker.TryLock();       // Lock or block.
  this->dirty           = true;
  this->t[b]            = time;
  this->n[b]            = n_birds;
  this->phi[b]          = phi;
  this->lambda[b]       = lambda;
  this->z_good[b]       = hasAlt;
  this->z[b]            = alt;
  this->omega_good[b]   = hasBearing;
  this->omega[b]        = bearing;
  this->s_good[b]       = hasSpeed;
  this->s[b]            = speed;
  this->epsilon_good[b] = hasError;
  this->epsilon[b]      = error;
  this->a_good[b]       = hasAcc;
  this->a[b]            = acc;
  this->locker.Unlock();
  }

//-----------------------------------------------------------------------------
GPSSensor::GPSStatus
GPSSensor::Connected() const
  {
  return this->status;
  }

//-----------------------------------------------------------------------------
long
GPSSensor::Time() const
  {
  return this->t[b_bar];
  }

//-----------------------------------------------------------------------------
int
GPSSensor::Birds() const
  {
  return this->n[b_bar];
  }

//-----------------------------------------------------------------------------
double
GPSSensor::Phi() const
  {
  return this->phi[b_bar];
  }

//-----------------------------------------------------------------------------
double
GPSSensor::Lambda() const
  {
  return this->lambda[b_bar];
  }

//-----------------------------------------------------------------------------
bool
GPSSensor::ZStatus() const
  {
  return this->z_good[b_bar];
  }

//-----------------------------------------------------------------------------
double
GPSSensor::Z() const
  {
  return this->z[b_bar];
  }

//-----------------------------------------------------------------------------
bool
GPSSensor::OmegaStatus() const
  {
  return this->omega_good[b_bar];
  }

//-----------------------------------------------------------------------------
double
GPSSensor::Omega() const
  {
  return this->omega[b_bar];
  }

//-----------------------------------------------------------------------------
bool
GPSSensor::SStatus() const
  {
  return this->s_good[b_bar];
  }

//-----------------------------------------------------------------------------
double
GPSSensor::S() const
  {
  return this->s[b_bar];
  }

//-----------------------------------------------------------------------------
bool
GPSSensor::EpsilonStatus() const
  {
  return this->epsilon_good[b_bar];
  }

//-----------------------------------------------------------------------------
double
GPSSensor::Epsilon() const
  {
  return this->epsilon[b_bar];
  }

//-----------------------------------------------------------------------------
bool
GPSSensor::AStatus() const
  {
  return this->a_good[b_bar];
  }

//-----------------------------------------------------------------------------
double
GPSSensor::A() const
  {
  return this->a[b_bar];
  }

//-----------------------------------------------------------------------------
GPSSensor::GPSSensor()
  {
  z_good[b]       = z_good[b_bar]       = false;
  omega_good[b]   = omega_good[b_bar]   = false;
  s_good[b]       = s_good[b_bar]       = false;
  epsilon_good[b] = epsilon_good[b_bar] = false;
  a_good[b]       = a_good[b_bar]       = false;
  }

