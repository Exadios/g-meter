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

#include "DownstreamSession.hpp"
#include "IoQueues.hpp"
#include "Executive.hpp"
#include <boost/bind.hpp>
#include <boost/system/error_code.hpp>
#include <string>
#include <iostream>

extern Executive *executive;

//------------------------------------------------------------------------------
DownstreamSession::DownstreamSession(asio::io_service& io, int port)
    :  Session(io),
       socket(io),
       acceptor(io, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
  {
  this->Accept();
  }

//------------------------------------------------------------------------------
DownstreamSession::~DownstreamSession()
  {
  this->Shutdown();
  }

//------------------------------------------------------------------------------
void
DownstreamSession::Deliver()
  {
  if (this->DeliverQueue().empty() != false)
    {
    this->Write();
    }
  }

//------------------------------------------------------------------------------
void
DownstreamSession::Receive()
  {
  asio::async_read_until(
                         this->socket,
                         this->b,
                         std::string("\r\n"),  // Delimeter.
                         boost::bind(&DownstreamSession::ReadHandler,
                                     this,
                                     asio::placeholders::error,
                                     asio::placeholders::bytes_transferred)
                        );
  }

//------------------------------------------------------------------------------
void
DownstreamSession::Write()
  {
  std::queue<std::string> q = this->DeliverQueue();
  asio::async_write(this->socket,
                    asio::buffer(q.front(), q.front().length()),
                    bind(&DownstreamSession::WriteHandler,
                         this,
                         asio::placeholders::error)
                   );
  }

//------------------------------------------------------------------------------
void
DownstreamSession::ReadHandler(const sys::error_code ec, std::size_t n)
  {
  if (!ec)
    {
    std::istream input(&(this->b));
    std::string record;
    std::getline(input, record);
    this->ReceiveQueue().push(record);
    this->b.consume(n);
    this->ReadNotify();
    this->Receive();
    }
  else
    ::executive->Terminate();
  }

//------------------------------------------------------------------------------
void
DownstreamSession::WriteHandler(sys::error_code ec)
  {
  if (!ec)
    {
    this->DeliverQueue().pop();
    }
  else
    {
    sys::system_error e(ec);
    std::cerr << "DownstreamSession::WriteHandler: " << e.what() << std::endl;
    ::executive->Terminate();
    }
  }

//------------------------------------------------------------------------------
void
DownstreamSession::Accept()
  {
  this->acceptor.async_accept(this->socket,
                              boost::bind(&DownstreamSession::AcceptHandler,
                                          this,
                                          asio::placeholders::error)
                             );
  }

//------------------------------------------------------------------------------
void
DownstreamSession::AcceptHandler(sys::error_code ec)
  {
  if (!ec)
    {
    this->Receive();
    }
  else
    {
    sys::system_error e(ec);
    std::cerr << "DownstreamSession::AcceptHandler: " << e.what() << std::endl;
    ::executive->Terminate();
    }
  }

//------------------------------------------------------------------------------
void
DownstreamSession::Shutdown()
  {
  this->socket.shutdown(asio::ip::tcp::socket::shutdown_both);
  }
