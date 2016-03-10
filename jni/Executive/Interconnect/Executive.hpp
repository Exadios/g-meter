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

#ifndef _EXECUTIVE_HPP
#define _EXECUTIVE_HPP

#include "XcsoarLink.hpp"
#include "InsLink.hpp"
#include "SerialLink.hpp"
#include <boost/utility.hpp>
#include <boost/asio.hpp>
#include <string>

//class DownstreamSession;
//class UpstreamSession;

/**
 * A simple executive to handle the downstream link to XCSoar, the upstream
 * link to the GPS/ IGC logger / Flarm etc, the INS and its link.
 */
class Executive : public boost::noncopyable
  {
public:
  /**
   * Executive ctor.
   */
  Executive(boost::asio::io_service& io,
            int xcsoar_port,
            int ins_port,
            const std::string& tty);

  /**
   * Run the executive. Return when the queue is empty (for what ever reason).
   */
  void Run();

  /**
   * Close the downstream.
   */
  void CloseDownstream();

  /**
   * Close the upstream.
   */
  void CloseUpstream();

  /**
   * Terminate.
   */
  void Terminate();

  /**
   * The XCSoar stream read has completed.
   */
  void XcsoarReadHandled();

  /**
   * The INS stream read has completed
   */
  void InsReadHandled();

  /**
   * The serail stream read has completed.
   */
  void SerialReadHandled();

private:
  boost::asio::io_service& io;
  XcsoarLink xcsoar_link;
  InsLink    ins_link;
  SerialLink serial_link;
  };


#endif  // _EXECUTIVE_HPP