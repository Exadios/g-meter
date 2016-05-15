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

#ifndef _SUPPORT_TEST_HPP
#define _SUPPORT_TEST_HPP

#include "Support.test.hpp"
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/utility.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>
#include <fstream>

/**
 * Base class of Interconnect tests.
 */
class TestSession
  {
public:
  /**
   * Dtor.
   */
  virtual ~TestSession();

  /**
   * Run the Proactor loop. Return on completion.
   */
  virtual void Run();

protected:
  /**
   * Ctor.
   * @param io  The Proactor io service.
   * @param test_file Base name of the test files.
   */
  TestSession(boost::asio::io_service& io, const std::string& test_file);

  virtual void Deliver() = 0;
  virtual void Delivered(boost::system::error_code ec);

  /**
   *
   */
  virtual void Receive() = 0;

  /**
   *
   */
  virtual void Received(const boost::system::error_code ec, std::size_t n);

  boost::asio::io_service& io;
  std::ifstream in;
  std::ofstream out;
  boost::asio::streambuf downstream_buf;
  boost::asio::streambuf upstream_buf;
  };

/**
 * Base class of TCP connected Interconnect tests.
 */
class TcpCommon : public TestSession
  {
public:
  /**
   * Dtor.
   */
  virtual ~TcpCommon();

protected:
  /**
   * Ctor.
   * @param io  The Proactor io service.
   * @param test_file Base name of the test files.
   */
  TcpCommon(boost::asio::io_service& io, const std::string& test_file);

  /**
   *
   */
  virtual void Connected(const boost::system::error_code& ec);

  boost::asio::ip::tcp::socket s;
  };

#endif  // _SUPPORT_TEST_HPP
