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

#include "Support.test.hpp"
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
TestSession::TestSession(asio::io_service& io,
                         const std::string& test_file)
  : io(io)
  {
  this->in.open(test_file + ".in");
  this->out.open(test_file + ".out");
  }

//------------------------------------------------------------------------------
TestSession::~TestSession()
  {
  this->in.close();
  this->out.close();
  }

//------------------------------------------------------------------------------
void
TestSession::Run()
  {
  this->io.run();
  }

//------------------------------------------------------------------------------
void
TestSession::Delivered(sys::error_code ec)
  {
  if (!ec)
    {
    this->Deliver();
    }
  }

//------------------------------------------------------------------------------
void
TestSession::Received(const sys::error_code ec, std::size_t n)
  {
  std::istream input(&(this->downstream_buf));
  std::string  record;
  std::getline(input, record);
  this->out << record;
  }

//------------------------------------------------------------------------------
TcpCommon::TcpCommon(asio::io_service& io, const std::string& test_file)
  : TestSession(io, test_file),
    s(io)
  {
  }

//------------------------------------------------------------------------------
TcpCommon::~TcpCommon()
  {
  }

//------------------------------------------------------------------------------
void
TcpCommon::Connected(const sys::error_code& ec)
  {
  }
