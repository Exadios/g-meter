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

#ifndef XCSOAR_THREAD_LOCAL_HXX
#define XCSOAR_THREAD_LOCAL_HXX

#include <pthread.h>

#include <stddef.h>

/**
 * This class provides an interface to Thread Local Storage (TLS).
 */
class ThreadLocal
  {
private:
  pthread_key_t key;

public:
  ThreadLocal()
    {
    ::pthread_key_create(&key, NULL);
    }

  ~ThreadLocal()
    {
    ::pthread_key_delete(key);
    }

  void *Get() const
    {
    return ::pthread_getspecific(key);
    }

  void Set(void *value) 
    {
    ::pthread_setspecific(key, value);
    }

  ThreadLocal(const ThreadLocal &other) = delete;
  ThreadLocal &operator=(const ThreadLocal &other) = delete;

  operator void*() const
    {
    return Get();
    }

  void *operator =(void *value)
    {
    Set(value);
    return value;
    }
  };

/**
 * A wrapper for #ThreadLocal which manages a user specified type.
 */
template<class T>
class ThreadLocalObject : private ThreadLocal
  {
public:
  const T Get() const
    {
    return (T)(size_t)ThreadLocal::Get();
    }

  void Set(const T value)
    {
    ThreadLocal::Set((void *)(size_t)value);
    }

  operator T() const
    {
    return Get();
    }

  const T operator =(const T value)
    {
    Set(value);
    return value;
    }
  };

/**
 * A wrapper for #ThreadLocal which manages a user specified type.
 */
class ThreadLocalInteger : public ThreadLocalObject<int>
  {
public:
  int operator ++()
    {
    int value = Get();
    Set(++value);
    return value;
    }

  int operator --()
    {
    int value = Get();
    Set(--value);
    return value;
    }
  };

#endif
