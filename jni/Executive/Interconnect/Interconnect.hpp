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

#ifndef _INTERCONNECT_HPP_
#define _INTERCONNECT_HPP_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <string>

/**
 * The purpose of this class is to provide for the interconnection of an
 * upstream GPS / Vario / Logger to a downstream XCSoar (or other) flight
 * computer and local INS. tBy necessity this class is highly specialized
 * to perform this task.
 */

class Interconnect : private boost::noncopyable
  {
public:

  /**
   * Ctor.
   * @param io The io service in use.
   * @param serial The fully qualified file name of the special file associated
   *               with the upstream connection to the GPS / Vario / Logger.
   * @param port The TCP port on which to listen for downstream.
   */
  Interconnect(boost::asio::io_service& io,
               std::string& serial,
               const boost::asio::ip::tcp::endpoint &endpoint);

  /**
   * Initialize the links. This will result in the Proactor read loops starting.
   */
  void Initialize();

protected:

private:

  /**
   * Start the TCP accept.
   */
  void StartAccept();

  /**
   * Handle the Proactor accept.
   * @param e Any error.
   */
  void HandleAccept(const boost::system::error_code& e);

  /**
   * Handle the io service stop (no more tasks).
   */
  void HandleStop();

  /**
   * Handle the Proactor completion of a byte read from the upstream.
   */
  void UpstreamReadRecord(const boost::system::error_code& error);

  /**
   * Handle the Proactor completion of a byte written to the upstream.
   */
  void UpstreamWriteRecord(const boost::system::error_code& error);

  /**
   * Handle the Proactor completion of a byte read from the downstream.
   */
  void DownstreamReadRecord(const boost::system::error_code& error);

  /**
   * Handle the Proactor completion of a byte written to the downstream.
   */
  void DownstreamWriteRecord(const boost::system::error_code& error);

  /**
   * Handle the Proactor completion of a formatted INS read.
   */
  void FormattedRead(const boost::system::error_code& error);

  /**
   * Post a Proactor upstream byte read.
   */
  void PostUpstreamRead();

  /**
   * Post a Proactor upstream byte write.
   */
  void PostUpstreamWrite();

  /**
   * Post a Proactor downstream byte read.
   */
  void PostDownstreamRead();

  /**
   * Post a Proactor downstream byte write.
   */
  void PostDownstreamWrite();

  /**
   * Post a formated read of the upstream for the INS.
   */
  void PostFormattedRead();

  void PostByteUpstreamRead();
  void PostByteUpstreamWrite();
  void PostByteDownstreamRead();
  void PostByteDownstreamWrite();
  unsigned char br, bw;
  std::string serial;
//  boost::asio::io_service io;
  boost::asio::serial_port serial_port;
  boost::asio::ip::tcp::socket socket;
  boost::asio::ip::tcp::acceptor acceptor;
  };

#endif  // _INTERCONNECT_HPP_
