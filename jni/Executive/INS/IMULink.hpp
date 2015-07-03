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

#ifndef LINK_HPP
#define LINK_HPP

#include <tuple>

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
   * Get a reference to the Singleton IMULink object. If the object does not
   * yet it exist then it is created. This is the only way that the object
   * of this class may be created.
   * @return The reference the object. This reference is always valid at the
   *         time this function is called.
   */
  static IMULink& Instance()
      {
      static IMULink instance;
      return instance;
      }

  /**
   * Read a frame from the IMU. This function will block until the frame is
   * read so a return from this function can be used to time the calling
   * system.
   * @return If the link has failed then false.
   */
  bool Read();

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
   * Ctor. Called from IMULink::Instance() only.
   */
  IMULink();

  /**
   * Do not allow copy operator!
   */
  IMULink& operator=(const IMULink&);

  enum state_t
    {
    INIT = 0,   // Initial state.
    SEARCH = 1, // Search for buffer frame by looking for '\r', '\n' pair.
    VERIFY = 2, // Verify sync.
    SYNC = 3    // Have frame sync. Read data.
  };

  state_t state;

  const char *serial_port = "/dev/ttyUSB0";
  const size_t frame_length = sizeof(unsigned int) +
                              9 * sizeof(float) +
                              2 * sizeof(char);

  char *sync_and_read();

  int fd;
  FILE *serial;

  unsigned int tick;
  float acc[3];
  float gyro[3];
  float mag[3];
  };

#endif  // LINK_HPP
