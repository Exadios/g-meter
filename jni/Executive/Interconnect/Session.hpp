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

#ifndef _SESSION_HPP
#define _SESSION_HPP

#include <boost/utility.hpp>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <queue>

class Executive;

/**
 * A pure virtual session class.
 */
class Session : public boost::noncopyable
  {
public:
  /**
   * Virtual dtor.
   */
  virtual ~Session();

  /**
   * Start the session by ussuing the first read.
   */
  virtual void Receive() = 0;

  /**
   * Deliver a record to the device.
   */
  virtual void Deliver() = 0;

protected:

  /**
   * Ctor.
   * @param io The Io Service.
   */
  Session(boost::asio::io_service& io);

  /**
   * The Proactor pattern read completion handler.
   * @param ec The error code of the read operation.
   * @param n Number of bytes read.
   */
  virtual void ReadHandler(const boost::system::error_code ec,
                           std::size_t n) = 0;

  /**
   * The Proactor pattern write completion handler.
   * @param ec The error code of the write operation.
   */
  virtual void WriteHandler(const boost::system::error_code ec) = 0;

  /**
   * Initiate a write operation.
   */
  virtual void Write() = 0;

  /**
   * Notify the Executive that the read has completed.
   */
  virtual void ReadNotify() = 0;

  /**
   * Give the queue of records read.
   * @return The link dependant receive queue.
   */
  virtual std::queue<std::string>& ReceiveQueue() const = 0;

  /**
   * Give the queue of records to write.
   * @return The link dependant deliver queue.
   */
  virtual std::queue<std::string>& DeliverQueue() const = 0;

  /**
   * The io service in use.
   */
  boost::asio::io_service& io;

  /**
   * A streambuf.
   */
  boost::asio::streambuf b; // Device streambuf.
  };

#endif  // _SESSION_HPP
