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

#include "NonGPSSensors.hpp"

//-----------------------------------------------------------------------------
void
NonGPSSensors::Acceleration(JNIEnv *env, jobject obj,
                            jlong t, jfloat x, jfloat y, jfloat z)

  {
  this->a_t = t;
  this->a_x = x;
  this->a_y = y;
  this->a_z = z;
  }

//-----------------------------------------------------------------------------
void
NonGPSSensors::Rotation(JNIEnv *env, jobject obj,
                        jlong t, jfloat x, jfloat y, jfloat z)
  {
  this->r_t = t;
  this->r_x = x;
  this->r_y = y;
  this->r_z = z;
  }

//-----------------------------------------------------------------------------
void
NonGPSSensors::MagneticField(JNIEnv *env, jobject obj,
                             jlong t, jfloat x, jfloat y, jfloat z)
  {
  this->m_t = t;
  this->m_x = x;
  this->m_y = y;
  this->m_z = z;
  }

//-----------------------------------------------------------------------------
void
NonGPSSensors::BarometricPressure(JNIEnv *env, jobject obj, 
                                  jlong t, jfloat p, jfloat v)
  {
  this->b_t = t;
  this->b_p = p;
  this->b_v = v;
  }

//-----------------------------------------------------------------------------
long
NonGPSSensors::A_t() const
  {
  return this->a_t;
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::A_x() const
  {
  return this->a_x;
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::A_y() const
  {
  return this->a_y;
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::A_z() const
  {
  return this->a_z;
  }

//-----------------------------------------------------------------------------
long
NonGPSSensors::R_t() const
  {
  return this->r_t;
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::R_x() const
  {
  return this->r_x;
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::R_y() const
  {
  return this->r_y;
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::R_z() const
  {
  return this->r_z;
  }

//-----------------------------------------------------------------------------
long
NonGPSSensors::M_t() const
  {
  return this->m_t;
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::M_x() const
  {
  return m_x;
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::M_y() const
  {
  return m_y;
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::M_z() const
  {
  return this->m_z;
  }

//-----------------------------------------------------------------------------
long
NonGPSSensors::B_t() const
  {
  return this->b_t;
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::B_p() const
  {
  return this->b_p;
  }

//-----------------------------------------------------------------------------
float
NonGPSSensors::B_v() const
  {
  return this->b_v;
  }
