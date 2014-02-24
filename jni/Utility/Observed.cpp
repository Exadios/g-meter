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

#include "Observed.hpp"
#include "Observer.hpp"

//-----------------------------------------------------------------------------
Observed::Observed()
  {
  }

//-----------------------------------------------------------------------------
Observed::~Observed()
  {
  }

//-----------------------------------------------------------------------------
void
Observed::Act(long t)
  {
  for (std::vector<Observer *>::iterator i = this->observers.begin();
       i != this->observers.end();
       i++)
    (*i)->Action(t);
  }

//-----------------------------------------------------------------------------
void
Observed::Bind(Observer *observer)
  {
  this->observers.push_back(observer);
  }

//-----------------------------------------------------------------------------
void
Observed::Unbind(Observer *observer)
  {
  for (std::vector<Observer *>::iterator i = this->observers.begin();
       i != this->observers.end();
       i++)
    if (*i == observer)
      this->observers.erase(i);
  }
