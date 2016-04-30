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

#include "Interconnect.test.hpp"
#include <boost/bind.hpp>

//------------------------------------------------------------------------------
XCSoarSession::XCSoarSession(boost::asio::io_service& io, int port)
  : 
    io(io),
    port(port),
    s(io)
  {
  boost::asio::ip::tcp::resolver r(io);
  boost::asio::ip::tcp::resolver::query q("4352");
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
  this->in.open("xcsoar.in");
  this->out.open("xcsoar.out");
  }

//------------------------------------------------------------------------------
void
XCSoarSession::Run()
  {
  }

//------------------------------------------------------------------------------
void
XCSoarSession::DownstreamDeliver()
  {
  std::string record;
  std::getline(this->in, record);
  boost::asio::async_write(this->s,
                           boost::asio::buffer(record, record.size()),
                           boost::bind(&XCSoarSession::DownstreamDelivered,
                                       this,
                                       boost::asio::placeholders::error)
                          );

  }

//------------------------------------------------------------------------------
void
XCSoarSession::DownstreamReceive()
  {
  boost::asio::async_read_until(
                                this->s,
                                this->downstream_buf,
                                std::string("\r\n"),  // Delimeter.
                                boost::bind(&XCSoarSession::DownstreamReceived,
                                            this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred)
                               );
  }

//------------------------------------------------------------------------------
void
XCSoarSession::DownstreamDelivered(boost::system::error_code ec)
  {
  if (!ec)
    {
    this->DownstreamDeliver();
    }
  }

//------------------------------------------------------------------------------
void
XCSoarSession::DownstreamReceived(const boost::system::error_code ec,
                                  std::size_t n)
  {
  std::istream input(&(this->downstream_buf));
  std::string  record;
  std::getline(input, record);
  this->out << record;
  }

//------------------------------------------------------------------------------
void
XCSoarSession::UpstreamDeliver()
  {
  boost::asio::async_write(this->s,
                           this->upstream_buf,
                           boost::bind(&XCSoarSession::UpstreamDelivered,
                                       this,
                                       boost::asio::placeholders::error)
                          );

  }

//------------------------------------------------------------------------------
void
XCSoarSession::UpstreamReceive()
  {
  boost::asio::async_read_until(
                                this->s,
                                this->upstream_buf,
                                std::string("\r\n"),  // Delimeter.
                                boost::bind(&XCSoarSession::UpstreamReceived,
                                            this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred)
                               );
  }

//------------------------------------------------------------------------------
void
XCSoarSession::UpstreamDelivered(const boost::system::error_code ec)
  {
  if (!ec)
    this->UpstreamDeliver();
  }

//------------------------------------------------------------------------------
void
XCSoarSession::UpstreamReceived(const boost::system::error_code ec,
                                  std::size_t n)
  {
  std::istream input(&(this->upstream_buf));
  std::string  record;
  std::getline(input, record);
  this->out << record;
  this->UpstreamReceive();
  }

//------------------------------------------------------------------------------
void
XCSoarSession::Connected(const boost::system::error_code& ec)
  {
  }

//------------------------------------------------------------------------------
int
main()
  {
  return 0;
  }
