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

#include "MajorState.hpp"

//-----------------------------------------------------------------------------
void
MajorState::Reset()
  {
  // Do whatever os necessary to revert from the current state to the INITIAL
  // state.
  }

//-----------------------------------------------------------------------------
void
MajorState::Action(long)
  {
  // Operate the clock in the context of the current state.
  }

//-----------------------------------------------------------------------------
MajorState::StateVector
MajorState::State() const
  {
  return this->state;
  }

//-----------------------------------------------------------------------------
MajorState::MajorState()
  : state(INITIAL)
  {
  }
