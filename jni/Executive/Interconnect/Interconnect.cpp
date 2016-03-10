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

#include "Interconnect.hpp"
#include <utility>
#include <memory>

//------------------------------------------------------------------------------
Interconnect::Interconnect(boost::asio::io_service& io,
                           std::string& serial,
                           const boost::asio::ip::tcp::endpoint &endpoint)
  : serial(serial),
//    io(io),
    serial_port(io),
    socket(io),
    acceptor(io,  endpoint)
  {
  }

//------------------------------------------------------------------------------
void
Interconnect::Initialize()
  {
  this->serial_port.open(this->serial);

  // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
  boost::asio::ip::tcp::resolver resolver(this->io);
  boost::asio::ip::tcp::resolver::query query(address, port);
  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
  this->acceptor.open(endpoint.protocol());
  this->acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  this->acceptor.bind(endpoint);
  this->acceptor.listen();
  }

//------------------------------------------------------------------------------
void
Interconnect::StartAccept()
  {
  this->new_connection.reset(new connection(this->io,
                             this->connection_manager,
                             this->request_handler));
  this->acceptor.async_accept(this->new_connection->socket(),
                              boost::bind(&Interconnect::handle_accept,
                              this,
                              boost::asio::placeholders::error));
  }

//------------------------------------------------------------------------------
void
Interconnect::HandleAccept(const boost::system::error_code& e)
  {
  // Check whether the server was stopped by a signal before this completion
  // handler had a chance to run.
  if (!this->acceptor.is_open())
    {
    return;
    }

  if (!e)
    {
    this->connection_manager.start(this->new_connection);
    }

  StartAccept();
  }

//------------------------------------------------------------------------------
void
Interconnect::HandleStop()
  {
  // The server is stopped by cancelling all outstanding asynchronous
  // operations. Once all operations have finished the io_service::run() call
  // will exit.
  this->acceptor.close();
  this->connection_manager.stop_all();

  this->serial_port.close(this->serial);
  }
//------------------------------------------------------------------------------
void
Interconnect::UpstreamReadRecord(const boost::system::error_code& error)
  {
  }

//------------------------------------------------------------------------------
void
Interconnect::UpstreamWriteRecord(const boost::system::error_code& error)
  {
  }

//------------------------------------------------------------------------------
void
Interconnect::DownstreamReadRecord(const boost::system::error_code& error)
  {
  boost::asio::async_read_until(this->serial_port,
                                boost::asio::buffer(this->buffer, nbytes),
                                std::string("\r\n"),
                                boost::bind(&IMULink::ReadH,
                                           this,
                                           boost::asio::placeholders::error)
                         );

  }

//------------------------------------------------------------------------------
void
Interconnect::DownstreamWriteRecord(const boost::system::error_code& error)
  {
  }

//------------------------------------------------------------------------------
void
Interconnect::FormattedRead(const boost::system::error_code& error)
  {
  }

//------------------------------------------------------------------------------
void
Interconnect::PostUpstreamRead()
  {
  }

//------------------------------------------------------------------------------
void
Interconnect::PostUpstreamWrite()
  {
  }

//------------------------------------------------------------------------------
void
Interconnect::PostDownstreamRead()
  {
  }

//------------------------------------------------------------------------------
void
Interconnect::PostDownstreamWrite()
  {
  }

//------------------------------------------------------------------------------
void
Interconnect::PostFormattedRead()
  {
  }

//------------------------------------------------------------------------------
void
Interconnect::PostByteUpstreamRead()
  {
  boost::asio::async_read(this->serial_port,
                          boost::asio::buffer(&this->br, std::size_t(1)),
                          boost::bind(&Interconnect::PostByteUpstreamRead,
                                      this,
                                      boost::asio::placeholders::error)
                         );
  }

//------------------------------------------------------------------------------
void
Interconnect::PostByteUpstreamWrite()
  {
  boost::asio::async_write(this->serial_port,
                           boost::asio::buffer(&this->bw, std::size_t(1)),
                           boost::bind(&Interconnect::PostByteUpstreamWrite,
                                       this,
                                       boost::asio::placeholders::error)
                          );
  }

//------------------------------------------------------------------------------
void
Interconnect::PostByteDownstreamRead()
  {
  }

//------------------------------------------------------------------------------
void
Interconnect::PostByteDownstreamWrite()
  {
  }

