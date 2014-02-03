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

#ifndef TIMER_HPP
#define TIMER_HPP

#include <jni.h>

/**
 * This class is a singleton. Its purpose is to handle timer communication to
 * and from the Android sensors.
 *
 * Note: This class is not thread safe.
 */

class Timer
  {
public:
  /**
   * Get a reference to the singleton Timer object. If the object does not
   * yet it exist then it is created. This is the only way that the object
   * of this class may be created.
   * @return The reference the object. This reference is always valid at the
   *         time theis function is called.
   */
  static Timer& Instance();
  
  /**
   * Entry point fow each tick.
   * @param env The JNI enviroment.
   * @param obj The JNI object.
   * @param t The up time in milliseconds.
   */
  void Tick(JNIEnv *env, jobject obj, jlong tick);

private:
  /**
   * Ctor. Called from Timer::Instance() only.
   */
  Timer();

  /**
   * Do not allow copying by any method!
   */
  Timer(const Timer&);
  Timer& operator=(const Timer&);
  };

#endif  // TIMER_HPP
