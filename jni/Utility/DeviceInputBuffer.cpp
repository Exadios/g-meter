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

#include "DeviceInputBuffer.hpp"

//-----------------------------------------------------------------------------
DeviceInputBuffer::DeviceInputBuffer()
  : b(0),
    b_bar(1),
    dirty(false)
  {
  }

//-----------------------------------------------------------------------------
DeviceInputBuffer::~DeviceInputBuffer()
  {
  }

//-----------------------------------------------------------------------------
void
DeviceInputBuffer::Clock()
  {
  this->locker.TryLock();     // Lock or block.
  if (this->dirty == true)
    {
    this->b     = this->b == 0 ? 1 : 0;
    this->b_bar = this->b == 0 ? 1 : 0;
    this->dirty = false;
    }
  this->locker.Unlock();
  }

//-----------------------------------------------------------------------------
bool
DeviceInputBuffer::Dirty()
  {
  bool rtn;

  this->locker.TryLock();
  rtn = this->dirty;
  this->locker.Unlock();
  return rtn;
  }


