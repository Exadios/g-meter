/*
 * G-Meter INU.
 * Copyright (C) 2013-2015 Peter F Bradshaw
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * FOUNDATION OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _DOWNSTREAMSESSION_HPP
#define _DOWNSTREAMSESSION_HPP

#include "Session.hpp"
#include <string>
#include <boost/utility.hpp>
#include <boost/asio.hpp>
#include <string>
#include <queue>

/**
 * A class to manage the session to a downstream device. In general the
 * downstream devices accept position and other sensor data. Downstream devices
 * may issue commands and requests to upstream devices.
 */
class DownstreamSession : public Session
  {
public:
  /**
   * Ctor.
   * @param io The Io Service.
   * @param port TCP port on which to listen.
   */
  DownstreamSession(boost::asio::io_service& io, int port);

  /**
   * Dtor. Cleanup.
   */
  virtual ~DownstreamSession();

  /**
   * Start by scheduling a read on the downstream.
   */
  void Receive();

  /**
   * Deliver a record from the upstream to the downstream.
   */
  void Deliver();

  /**
   * Shutdown the link.
   */
  void Shutdown();

private:
  void ReadHandler(const boost::system::error_code ec, std::size_t n);

  void WriteHandler(boost::system::error_code ec);

  void AcceptHandler(boost::system::error_code ec);

  void Write();

  void Accept();

  boost::asio::ip::tcp::socket socket;
  boost::asio::ip::tcp::acceptor acceptor;
  };


#endif // _DOWNSTREAMSESSION_HPP
