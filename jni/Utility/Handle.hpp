/*
Copyright_License {

  G-Meter INU.
  Copyright (C) 2000-2015 The XCSoar Project and Peter F Bradshaw
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

#ifndef XCSOAR_THREAD_HANDLE_HPP
#define XCSOAR_THREAD_HANDLE_HPP

#include "Compiler.h"

#include <pthread.h>

/**
 * A low-level handle for a thread.  Designed to work with existing
 * threads, such as the main thread.  Mostly useful for debugging
 * code.
 */
class ThreadHandle
  {
  pthread_t handle;

public:
  /**
   * No initialisation.
   */
  ThreadHandle() = default;

  constexpr ThreadHandle(pthread_t _handle):handle(_handle) {}

  static const ThreadHandle GetCurrent()
    {
    return pthread_self();
    }

  gcc_pure
  bool operator==(const ThreadHandle &other) const
    {
    return pthread_equal(handle, other.handle);
    }

  /**
   * Check if this thread is the current thread.
   */
  bool IsInside() const
    {
    return *this == GetCurrent();
    }
  };

#endif
