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

#include "SerialLink.hpp"
#include "Executive.hpp"
#include <queue>
#include <string>

extern std::queue<std::string> serial_deliver;
extern std::queue<std::string> serial_receive;
extern Executive *executive;

//------------------------------------------------------------------------------
SerialLink::SerialLink(boost::asio::io_service& io, const std::string tty)
  : UpstreamSession(io, tty)
  {
  }

//------------------------------------------------------------------------------
SerialLink::~SerialLink()
  {
  }

//------------------------------------------------------------------------------
void
SerialLink::ReadNotify()
  {
  ::executive->SerialReadHandled();
  }

//------------------------------------------------------------------------------
std::queue<std::string>&
SerialLink::ReceiveQueue() const
  {
  return ::serial_receive;
  }

//------------------------------------------------------------------------------
std::queue<std::string>&
SerialLink::DeliverQueue() const
  {
  return ::serial_deliver;
  }
