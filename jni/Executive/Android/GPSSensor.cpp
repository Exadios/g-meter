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
GPSSensor&
GPSSensor::Instance()
  {
  static GPSSensor instance;
  return instance;
  }

//-----------------------------------------------------------------------------
void
GPSSensor::Connected(JNIEnv *env, jobject obj, jint connected)
  {
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
  }

//-----------------------------------------------------------------------------
GPSSensor::GPSSensor()
  {
  }
