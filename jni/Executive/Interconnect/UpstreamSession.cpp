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

#include "UpstreamSession.hpp"
#include "IoQueues.hpp"
#include "Executive.hpp"
#include <boost/bind.hpp>
#include <boost/system/system_error.hpp>
#include <string>
#include <iostream>

extern Executive *executive;

//------------------------------------------------------------------------------
UpstreamSession::UpstreamSession(boost::asio::io_service& io,
                                 const std::string port)
  : Session(io),
    serial_port(io)
  {
  this->serial_port.open(port);
  }

//------------------------------------------------------------------------------
UpstreamSession::~UpstreamSession()
  {
  this->Shutdown();
  }

//------------------------------------------------------------------------------
void
UpstreamSession::Receive()
  {
  boost::asio::async_read_until(this->serial_port,
                                this->b,
                                std::string("\r\n"),  // Delimeter
                                boost::bind(&UpstreamSession::ReadHandler,
                                            this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred)
                               );
  }

//------------------------------------------------------------------------------
void
UpstreamSession::Deliver()
  {
    if (this->DeliverQueue().empty() != false)
    {
    this->Write();
    }
  }

//------------------------------------------------------------------------------
void
UpstreamSession::ReadHandler(const boost::system::error_code ec, std::size_t n)
  {
  if (!ec)
    {
    this->b.commit(n);
    std::istream input(&this->b);
    std::string record;
    std::getline(input, record);
    this->ReceiveQueue().push(record);
    this->b.consume(n);
    this->ReadNotify();
    this->Receive();
    }
  else
    {
    boost::system::system_error e(ec);
    std::cerr << "UpstreamSession::ReadHandler: " <<  e.what() << std::endl;
    }
  }

//------------------------------------------------------------------------------
void
UpstreamSession::WriteHandler(const boost::system::error_code ec)
  {
    if (!ec)
    {
    this->DeliverQueue().pop();
    }
  else
    {
    boost::system::system_error e(ec);
    std::cerr << "UpstreamSession::WriteHandler: " << e.what() << std::endl;
    ::executive->Terminate();
    }
  }

//------------------------------------------------------------------------------
void
UpstreamSession::Write()
  {
  std::queue<std::string>& q = this->DeliverQueue();
  boost::asio::async_write(this->serial_port,
                           boost::asio::buffer(q.front(), q.front().length()),
                           boost::bind(&UpstreamSession::WriteHandler,
                                       this,
                                       boost::asio::placeholders::error)
                          );
  }

//------------------------------------------------------------------------------
void
UpstreamSession::Shutdown()
  {
  if(this->serial_port.is_open())
    this->serial_port.close();
  }
