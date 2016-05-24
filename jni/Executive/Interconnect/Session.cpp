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

#include "Session.hpp"
#include <queue>

class Executive;
extern Executive *executive;
extern std::queue<std::string> xcsoar_deliver;
extern std::queue<std::string> xcsoar_receive;
extern std::queue<std::string> ins_deliver;
extern std::queue<std::string> ins_receive;
extern std::queue<std::string> serial_deliver;
extern std::queue<std::string> serial_receive;

//------------------------------------------------------------------------------
Session::Session(asio::io_service& io)
  : io(io)
  {
  }

//------------------------------------------------------------------------------
Session::~Session()
  {
  }
