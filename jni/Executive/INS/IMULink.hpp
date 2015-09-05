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

// TODO Unit test this.

#ifndef IMULINK_HPP
#define IMULINK_HPP

#include <tuple>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

typedef std::tuple<float, float, float> Tuple3f;

/**
 * An object of this class is used to manage the link between the ArduIMU V3
 * running 'Arduimu' and the Kobo. There needs to be only one object of this
 * class at any one time. As a consequence this class is a Singleton.
 */
class IMULink
  {
public:
  /**
   * Ctor.
   * @param io The controlling io_service.
   * @param port The FQ special file specifying the serial port - 
   *             e.g. "/dev/ttyUSB0".
   */
  IMULink(boost::asio::io_service& io, std::string& port);

  enum state_t
    {
    INIT = 0,       // Initial state.
    SEARCH = 1,     // Search for buffer frame by looking for '\r', '\n' pair.
    PREVERIFY = 2,  // Setup for a VERIFY
    VERIFY = 3,     // Verify sync.
    SYNC = 4        // Have frame sync. Read data.
    };

  /**
   * Initialize the link by starting a sync.
   */
  void Initialize();

  /**
   * Give the current state.
   * @return The state of the link.
   */
  enum state_t State() const;

  /**
   * Give the current timer tick as set by the previous Read().
   * @return The timer tick.
   */
  unsigned int Tick() const;

  /**
   * Give the current accelerometer state as set by the previous Read().
   * @return The accelerometer state.
   */
  Tuple3f& Acc() const;

  /**
   * Give the current gyro state as set by the previous Read().
   * @return The gyro state.
   */
  Tuple3f& Gyro() const;

  /**
   * Give the current magnetometer state as set by the previous Read().
   * @return The magnetometer state.
   */
  Tuple3f& Mag() const;

private:
  /**
   * Do not allow copy operator!
   */
  IMULink& operator=(const IMULink&);

  /**
   * Read a frame from the IMU. This function is called by the Proactor
   * pattern when the requested number of bytes have been read.
   */
  void ReadH(const boost::system::error_code& error);

  int vv;           // Verify count.
  int vi;           // Number of VERIFYs

  boost::asio::serial_port serial_port;
  state_t state;

#define FRAME_LENGTH (sizeof(unsigned int) + 9 * sizeof(float) + 2 * sizeof(char))
  const size_t frame_length = FRAME_LENGTH;
  char buffer[FRAME_LENGTH * 2];

  char *sync_and_read();

  /**
   * Post a non blocking read.
   * @param nbytes The number of bytes to read.
   */
  void PostRead(int nbytes);

  unsigned int tick;
  float acc[3];
  float gyro[3];
  float mag[3];
  };

#endif  // IMULINK_HPP
