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

#include <boost/config/compiler/gcc.hpp>
#include "Interconnect.test.hpp"
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
TestSession::TestSession(boost::asio::io_service& io,
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
TestSession::Delivered(boost::system::error_code ec)
  {
  if (!ec)
    {
    this->Deliver();
    }
  }

//------------------------------------------------------------------------------
void
TestSession::Received(const boost::system::error_code ec, std::size_t n)
  {
  std::istream input(&(this->downstream_buf));
  std::string  record;
  std::getline(input, record);
  this->out << record;
  }

//------------------------------------------------------------------------------
TcpCommon::TcpCommon(boost::asio::io_service& io, const std::string& test_file)
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
TcpCommon::Connected(const boost::system::error_code& ec)
  {
  }

//------------------------------------------------------------------------------
XCSoarSession::XCSoarSession(boost::asio::io_service& io,
                             const std::string& port)
  : TcpCommon(io, "xcsoar")
  {
  boost::asio::ip::tcp::resolver r(io);
  boost::asio::ip::tcp::resolver::query q(port);
  boost::asio::ip::tcp::resolver::iterator i = r.resolve(q);
  boost::asio::async_connect(this->s,
                             i,
                             boost::bind(&XCSoarSession::Connected,
                                         this,
                                         boost::asio::placeholders::error)
                            );
  }

//------------------------------------------------------------------------------
XCSoarSession::~XCSoarSession()
  {
  }

//------------------------------------------------------------------------------
void
XCSoarSession::Deliver()
  {
  std::string record;
  std::getline(this->in, record);
  boost::asio::async_write(this->s,
                           boost::asio::buffer(record, record.size()),
                           boost::bind(&XCSoarSession::Delivered,
                                       this,
                                       boost::asio::placeholders::error)
                          );

  }

//------------------------------------------------------------------------------
void
XCSoarSession::Receive()
  {
  boost::asio::async_read_until(this->s,
                                this->downstream_buf,
                                std::string("\r\n"),  // Delimeter.
                                boost::bind(&XCSoarSession::Received,
                                            this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred)
                               );
  }

//------------------------------------------------------------------------------
InsSession::InsSession(boost::asio::io_service& io,
                             const std::string& port)
  : TcpCommon(io, "ins")
  {
  boost::asio::ip::tcp::resolver r(io);
  boost::asio::ip::tcp::resolver::query q(port);
  boost::asio::ip::tcp::resolver::iterator i = r.resolve(q);
  boost::asio::async_connect(this->s,
                             i,
                             boost::bind(&InsSession::Connected,
                                         this,
                                         boost::asio::placeholders::error)
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
  boost::asio::async_write(this->s,
                           boost::asio::buffer(record, record.size()),
                           boost::bind(&InsSession::Delivered,
                                       this,
                                       boost::asio::placeholders::error)
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
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred)
                               );
  }

//------------------------------------------------------------------------------
FlarmSession::FlarmSession(boost::asio::io_service& io)
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
  boost::asio::async_write(this->serial_port,
                           boost::asio::buffer(record, record.size()),
                           boost::bind(&FlarmSession::Delivered,
                                       this,
                                       boost::asio::placeholders::error)
                          );
  }

//------------------------------------------------------------------------------
void
FlarmSession::Receive()
  {
  boost::asio::async_read_until(this->serial_port,
                                this->downstream_buf,
                                std::string("\r\n"),  // Delimeter.
                                boost::bind(&FlarmSession::Received,
                                            this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred)
                               );
  }

//------------------------------------------------------------------------------
int
main()
  {
  return 0;
  }
