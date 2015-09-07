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

// TODO Unit test this.

#include "IMULink.hpp"
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <boost/asio.hpp>   // For Proactor pattern.

//------------------------------------------------------------------------------
IMULink::IMULink(boost::asio::io_service& io, std::string& port)
  : serial_port(io),
    state(IMULink::SEARCH)
  {
  this->serial_port.open(port);
  struct termios driver;
  cfmakeraw(&driver);                   // Turn off cannonical etc.
  cfsetspeed(&driver, B230400);
  driver.c_iflag &= ~IXOFF;             // No flow control.
  driver.c_iflag |= IGNPAR | IGNBRK ;   // No parity or break. 
  driver.c_cflag &= ~(CSTOPB | PARENB); // One stop and no parity.
  tcsetattr(this->serial_port.native_handle(), TCSANOW, &driver);
  }

//------------------------------------------------------------------------------
void
IMULink::Initialize()
  {
  this->state = IMULink::SEARCH;
  this->PostRead(this->frame_length);
  }

//------------------------------------------------------------------------------
void
IMULink::Terminate()
  {
  this->state = TERMINATE;
  }

//------------------------------------------------------------------------------
enum IMULink::state_t
IMULink::State() const
  {
  return (this->state);
  }

//------------------------------------------------------------------------------
void
IMULink::ReadH(const boost::system::error_code& error)
  {
  switch (this->state)
    {
    case INIT:
      {
      this->state = SEARCH;
      break;
      }
    case SEARCH:
      {
      unsigned int i;

      for (i = 0; i < this->frame_length - 1; i++)
        {
        if (this->buffer[i] == '\r' && this->buffer[i + 1] == '\n')
          {
          this->state = PREVERIFY;
          break;
          }
        }
      if (this->state != PREVERIFY)
        this->PostRead(1);  // Read just in case sync on buffer boundry.
      else
        this->PostRead(i + 2);  // Align.
      break;
      }
    case PREVERIFY:
      this->vv = this->vi = 0;
      this->state = IMULink::VERIFY;
      this->PostRead(this->frame_length);
      break;
    case VERIFY:
      {
      if (this->buffer[this->frame_length - 2] == '\r' &&
          this->buffer[this->frame_length - 1] == '\n')
        this->vv++;
      if (this->vv == 7 && this->vi == 7)
        this->state = SYNC;
      else if (this->vv == (this->vi - 1))
        {
        this->vv = this->vi = 0;
        this->state = VERIFY;   // Try another VERIFY
        }
      else
        this->state = SEARCH;   // Something terribly wrong!
      this->PostRead(this->frame_length);
      break;
      }
    case SYNC:
      {
      int p = 0;

      memcpy(&this->tick, &this->buffer[p], sizeof(this->tick));
      p += sizeof(this->tick);
      memcpy(&this->acc,  &this->buffer[p], sizeof(this->acc));
      p += sizeof(this->acc);
      memcpy(&this->gyro, &this->buffer[p], sizeof(this->gyro));
      p += sizeof(this->gyro);
      memcpy(&this->mag,  &this->buffer[p], sizeof(this->mag));
      p += sizeof(this->mag);
      if (this->buffer[p] == '\r' && this->buffer[p + 1] == '\n')
        this->state = SYNC;
      else
        this->state = VERIFY; // Error.
      this->PostRead(this->frame_length);
      break;
      }
    case TERMINATE:
      break;  // Terminate by not calling PostRead().
    }
  }

//------------------------------------------------------------------------------
void
IMULink::PostRead(int nbytes)
  {
  boost::asio::async_read(this->serial_port,
                          boost::asio::buffer(this->buffer, nbytes),
                          boost::bind(&IMULink::ReadH,
                                      this,
                                      boost::asio::placeholders::error)
                         );
  }
