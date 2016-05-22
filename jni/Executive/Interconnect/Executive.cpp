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

#include "Executive.hpp"

extern std::queue<std::string> xcsoar_deliver;
extern std::queue<std::string> xcsoar_receive;
extern std::queue<std::string> ins_deliver;
extern std::queue<std::string> ins_receive;
extern std::queue<std::string> serial_deliver;
extern std::queue<std::string> serial_receive;

//------------------------------------------------------------------------------
Executive::Executive(boost::asio::io_service& io,
                     int xcsoar_port,
                     int ins_port,
                     const std::string& tty)
  : io(io),
    xcsoar_link(io, xcsoar_port),
    ins_link(io, ins_port),
    serial_link(io, tty)
  {
  }

//------------------------------------------------------------------------------
Executive::~Executive()
  {
  }

//------------------------------------------------------------------------------
void
Executive::Run()
  {
  this->serial_link.Receive();  // Start with a receive on the serial port.
  this->io.run();               // Run the queue.
  }

//------------------------------------------------------------------------------
void
Executive::CloseIns()
  {
  this->ins_link.~InsLink();
  }

//------------------------------------------------------------------------------
void
Executive::CloseXcsoar()
  {
  this->xcsoar_link.~XcsoarLink();
  }

//------------------------------------------------------------------------------
void
Executive::CloseSerial()
  {
  this->serial_link.~SerialLink();
  }

//------------------------------------------------------------------------------
void
Executive::Terminate()
  {
  this->CloseSerial();
  this->CloseXcsoar();
  this->CloseIns();
  }

//------------------------------------------------------------------------------
void 
Executive::XcsoarReadHandled()
  {
  ::serial_deliver.push(::xcsoar_receive.front());
  ::xcsoar_receive.pop();
  }

//------------------------------------------------------------------------------
void
Executive::InsReadHandled()
  {
  ::ins_receive.pop();
  }

//------------------------------------------------------------------------------
void 
Executive::SerialReadHandled()
  {
  ::xcsoar_deliver.push(::serial_receive.front());
  ::ins_deliver.push(::serial_receive.front());
  ::serial_receive.pop();
  }
