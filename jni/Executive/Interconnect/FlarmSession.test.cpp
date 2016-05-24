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

#include "FlarmSession.test.hpp"
#include <boost/config/compiler/gcc.hpp>
#include <boost/bind.hpp>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//------------------------------------------------------------------------------
FlarmSession::FlarmSession(asio::io_service& io)
  : TestSession(io, "flarm"),
    serial_port(io)
  {
  this->serial_port.open("/dev/ttyUSB0"); // Loopback port.
  struct termios driver;
  cfmakeraw(&driver);                   // Turn off cannonical etc.
  cfsetspeed(&driver, B19200);
  driver.c_iflag &= ~IXOFF;             // No flow control.
  driver.c_iflag |= IGNPAR | IGNBRK ;   // No parity or break. 
  driver.c_cflag &= ~(CSTOPB | PARENB); // One stop and no parity.
  tcsetattr(this->serial_port.native_handle(), TCSANOW, &driver);
  }

//------------------------------------------------------------------------------
FlarmSession::~FlarmSession()
  {
  this->serial_port.close();
  }

//------------------------------------------------------------------------------
void
FlarmSession::Deliver()
  {
  std::string record;
  std::getline(this->in, record);
  asio::async_write(this->serial_port,
                    asio::buffer(record, record.size()),
                    boost::bind(&FlarmSession::Delivered,
                                this,
                                asio::placeholders::error)
                   );
  }

//------------------------------------------------------------------------------
void
FlarmSession::Receive()
  {
  asio::async_read_until(this->serial_port,
                         this->downstream_buf,
                         std::string("\r\n"),  // Delimeter.
                         boost::bind(&FlarmSession::Received,
                                     this,
                                     asio::placeholders::error,
                                     asio::placeholders::bytes_transferred)
                       );
  }

//------------------------------------------------------------------------------
int
main()
  {
  return 0;
  }
