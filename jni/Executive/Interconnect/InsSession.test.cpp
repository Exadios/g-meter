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

#include "InsSession.test.hpp"
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
InsSession::InsSession(asio::io_service& io, const std::string& port)
  : TcpCommon(io, "ins")
  {
  asio::ip::tcp::resolver r(io);
  asio::ip::tcp::resolver::query q(port);
  asio::ip::tcp::resolver::iterator i = r.resolve(q);
  asio::async_connect(this->s,
                      i,
                      boost::bind(&InsSession::Connected,
                                  this,
                                  asio::placeholders::error)
                     );
  }

//------------------------------------------------------------------------------
InsSession::~InsSession()
  {
  }

//------------------------------------------------------------------------------
void
InsSession::Deliver()
  {
  std::string record;
  std::getline(this->in, record);
  asio::async_write(this->s,
                    asio::buffer(record, record.size()),
                    boost::bind(&InsSession::Delivered,
                                this,
                                asio::placeholders::error)
                   );

  }

//------------------------------------------------------------------------------
void
InsSession::Receive()
  {
  boost::asio::async_read_until(this->s,
                                this->downstream_buf,
                                std::string("\r\n"),  // Delimeter.
                                boost::bind(&InsSession::Received,
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
