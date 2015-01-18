/*
 * G-Meter INU.
 * Copyright (C) 2009-2015 Max Kellermann <max@duempel.org> and 
 * Peter F Bradshaw
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

#ifndef MAJORSTATE_HPP
#define MAJORSTATE_HPP

#include "Utility/Observer.hpp"
#include "Utility/PosixMutex.hpp"

/**
 * Generate and maintain the system's major states.
 *
 * This class is a singleton.
 */

class MajorState : public Observer
  {
public:
  /**
   * Get a reference to the singleton MajorState object. If the object does not
   * yet it exist then it is created. This is the only way that the object
   * of this class may be created.
   * @return The reference the object. This reference is always valid at the
   *         time theis function is called.
   */
  static MajorState& Instance()
      {
      static MajorState instance;
      return instance;
      }

  /** 
   * The values of the state vector.
   */
  enum StateVector
    {
    INITIAL=0,    // The initial state
    STARTUP,      // Start threads and processes and start data.
    AQUIRE_GPS,   // Aquire and validate GPS.
    PRE_ALIGN,    // Meet conditions for platform align.
    ALIGN,        // Align the platform.
    OPERATE,      // Operational mode.
    FINAL         // Shutdown.
    };

  /**
   * Reset to the initial state and start the machine.
   */
  void Reset();

  /**
   * Receive ticks from the clock.
   * @param t The time in an arbitary epoch.
   */
  void Action(long t);

  /**
   * Give the major state vector.
   * @return The current major state vector.
   */
  StateVector State() const;

private:
  /**
   * Ctor. Called from GPSSensor::Instance() only.
   */
  MajorState();

  /**
   * Do not allow copying by any method!
   */
  MajorState(const MajorState&);
  MajorState& operator=(const MajorState&);

  StateVector state;

  /**
   * Start the Accelerometers at 10mS sample rate.
   */
  void StartAccelerometers();

  /**
   * Stop the Accelerometers.
   */
  void StopAccelerometers();

  /**
   * Start the Gyros at 10mS sample rate.
   */
  void StartGyros();

  /**
   * Stop the Gyros.
   */
  void StopGyros();

  /**
   * Start the GPS at 1S sample rate.
   * @return If the GPS is operational and tracking then true.
   */
  bool StartGPS();

  /**
   * Stop theGPS.
   */
  void StopGPS();

  /**
   * Assure that GPS is aquired ad of sufficient quality to proceed.
   * @return If the GPS is suitable for platofrm alignment then true.
   */
  bool StabilizeGPS();

  /**
   * Run the platform pre alignment (coarse alignment) program.
   * @return If the program was sucessful then true.
   */
  bool Pre_Align_Program();

  /**
   * Run the platform aligment (fine alignment) program.
   * @return If the platform is aligned sufficiently to operate then true.
   */
  bool Align_Program();
  };

#endif // MAJORSTATE_HPP
