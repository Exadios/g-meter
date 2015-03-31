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

#include "NonGPSSensors.hpp"

//-----------------------------------------------------------------------------
void
NonGPSSensors::Acceleration(JNIEnv *env, jobject obj,
                            jlong t, jfloat x, jfloat y, jfloat z)

  {
  this->locker.TryLock();
  this->dirty = true;
  this->a_t[b] = t;
  this->a_x[b] = x;
  this->a_y[b] = y;
  this->a_z[b] = z;
  this->locker.Unlock();
  }

//-----------------------------------------------------------------------------
void
NonGPSSensors::Rotation(JNIEnv *env, jobject obj,
                        jlong t, jfloat x, jfloat y, jfloat z)
  {
  this->locker.TryLock();
  this->dirty = true;
  this->r_t[b] = t;
  this->r_x[b] = x;
  this->r_y[b] = y;
  this->r_z[b] = z;
  this->locker.Unlock();
  }

//-----------------------------------------------------------------------------
void
NonGPSSensors::MagneticField(JNIEnv *env, jobject obj,
                             jlong t, jfloat x, jfloat y, jfloat z)
  {
  this->locker.TryLock();
  this->dirty = true;
  this->m_t[b] = t;
  this->m_x[b] = x;
  this->m_y[b] = y;
  this->m_z[b] = z;
  this->locker.Unlock();
  }

//-----------------------------------------------------------------------------
void
NonGPSSensors::BarometricPressure(JNIEnv *env, jobject obj, 
                                  jlong t, jfloat p, jfloat v)
  {
  this->locker.TryLock();
  this->dirty = true;
  this->b_t[b] = t;
  this->b_p[b] = p;
  this->b_v[b] = v;
  this->locker.Unlock();
  }

//-----------------------------------------------------------------------------
long
NonGPSSensors::A_t() const
  {
  return this->a_t[b_bar];
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::A_x() const
  {
  return this->a_x[b_bar];
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::A_y() const
  {
  return this->a_y[b_bar];
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::A_z() const
  {
  return this->a_z[b_bar];
  }

//-----------------------------------------------------------------------------
long
NonGPSSensors::R_t() const
  {
  return this->r_t[b_bar];
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::R_x() const
  {
  return this->r_x[b_bar];
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::R_y() const
  {
  return this->r_y[b_bar];
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::R_z() const
  {
  return this->r_z[b_bar];
  }

//-----------------------------------------------------------------------------
long
NonGPSSensors::M_t() const
  {
  return this->m_t[b_bar];
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::M_x() const
  {
  return m_x[b_bar];
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::M_y() const
  {
  return m_y[b_bar];
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::M_z() const
  {
  return this->m_z[b_bar];
  }

//-----------------------------------------------------------------------------
long
NonGPSSensors::B_t() const
  {
  return this->b_t[b_bar];
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::B_p() const
  {
  return this->b_p[b_bar];
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::B_v() const
  {
  return this->b_v[b_bar];
  }

//-----------------------------------------------------------------------------
NonGPSSensors::NonGPSSensors()
  {
  }
