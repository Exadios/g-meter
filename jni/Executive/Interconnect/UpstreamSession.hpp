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

#ifndef _UPSTREAMSESSION_HPP
#define _UPSTREAMSESSION_HPP

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Session.hpp"

/**
 * A class to manage a session to an upstream device. In general upstream
 * devices generate position and other sensor data. They may accept commands
 * from downstream devices.
 */
class UpstreamSession : public Session
  {
public:
  /**
   * Ctor.
   * @param io The io service running the queue.
   * @param port The fully qualified device name of the serial port. For
   *             instance, "/dev/ttyUSB0".
   */
  UpstreamSession(boost::asio::io_service& io, const std::string port);

  /**
   * Dtor.
   */
  ~UpstreamSession();

  /**
   * Initiate a receive operation on the serial port.
   */
  void Receive();

  /**
   * Initiate a deliver operation on the serial port.
   */
  void Deliver();

  /**
   * Shutdown the link.
   */
  void Shutdown();

private:
  void ReadHandler(const boost::system::error_code ec, std::size_t n);

  void WriteHandler(const boost::system::error_code ec);

  void Write();

  boost::asio::serial_port serial_port;
  };

#endif  // _UPSTREAMSESSION_HPP
