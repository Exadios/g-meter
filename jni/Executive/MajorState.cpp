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
#include "Android/Timer.hpp"
#include "Android/GPSSensor.hpp"
#include <assert.h>

//-----------------------------------------------------------------------------
void
MajorState::Reset()
  {
  if (this->state != INITIAL)
    {
    // Do whatever is necessary to revert from the current state to the INITIAL
    // state.
    switch (this->state)
      {
      case FINAL:
        // Nothing to be done.
        break;
      case OPERATE:
        // Do actions to switch to INITIAL.
        break;
      case ALIGN:
      case PRE_ALIGN:
        // Shut down IMU.
        this->state = AQUIRE_GPS;
      case AQUIRE_GPS:
        // Shut down GPS.
        this->state = STARTUP;
      case STARTUP:
        this->StopAccelerometers();
        this->StopGyros();
        this->StopGPS();
        break;
      case INITIAL:
        break;
      }
    this->state = INITIAL;
    }
  }

//-----------------------------------------------------------------------------
void
MajorState::Action(long)
  {
  switch (this->state)
    {
    case INITIAL:
      this->state = STARTUP;
      break;
    case STARTUP:
      this->StartAccelerometers();
      this->StartGyros();
      this->state = (this->StartGPS() == true) ? STARTUP : AQUIRE_GPS;
      break;
    case AQUIRE_GPS:
      this->state = (StabilizeGPS() == true) ? PRE_ALIGN : AQUIRE_GPS;
      break;
    case PRE_ALIGN:
      this->state = (Pre_Align_Program() == true) ? ALIGN : PRE_ALIGN;
      break;
    case ALIGN:
      this->state = (Align_Program() == true) ? OPERATE : PRE_ALIGN;
      break;
    case OPERATE:
      break;
    case FINAL:
      break;
    default:  // A big problem!
      assert(false);
    }
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
  Timer::Instance().Bind(this);
  }

//-----------------------------------------------------------------------------
void
MajorState::StartAccelerometers()
  {
  return;
  }

//-----------------------------------------------------------------------------
void
MajorState::StopAccelerometers()
  {
  return;
  }

//-----------------------------------------------------------------------------
void
MajorState::StartGyros()
  {
  return;
  }

//-----------------------------------------------------------------------------
void
MajorState::StopGyros()
  {
  return;
  }

//-----------------------------------------------------------------------------
bool
MajorState::StartGPS()
  {
  // The GPS is already started in Java. Just wait for the fixes.
  if (GPSSensor::Instance().Connected() == GPSSensor::AVAILABLE)
    return true;
  else
    return false;
  }

//-----------------------------------------------------------------------------
void
MajorState::StopGPS()
  {
  return;
  }

//-----------------------------------------------------------------------------
bool
MajorState::StabilizeGPS()
  {
  // Make this trivial for now.
  return true;
  }

//-----------------------------------------------------------------------------
bool
MajorState::Pre_Align_Program()
  {
  return false;
  }

//-----------------------------------------------------------------------------
bool
MajorState::Align_Program()
  {
  return false;
  }
