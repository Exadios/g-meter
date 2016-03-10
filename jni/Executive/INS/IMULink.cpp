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

#include <boost/config/compiler/gcc.hpp>
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
    state(IMULink::SEARCH),
    state_jk(IMULink::SEARCH)
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
  this->state_jk = this->state = IMULink::SEARCH;
  this->PostRead(this->frame_length);
  }

//------------------------------------------------------------------------------
void
IMULink::Terminate()
  {
  this->state_jk = TERMINATE;
  }

//------------------------------------------------------------------------------
enum IMULink::state_t
IMULink::State() const
  {
  return (this->state);
  }

//------------------------------------------------------------------------------
unsigned int
IMULink::Tick() const
  {
  return this->tick;
  }

//------------------------------------------------------------------------------
const Tuple3f&
IMULink::Acc() const
  {
  return this->acc;
  }

//------------------------------------------------------------------------------
const Tuple3f&
IMULink::Gyro() const
  {
  return this->gyro;
  }

//------------------------------------------------------------------------------
const Tuple3f&
IMULink::Mag() const
  {
  return this->mag;
  }

//------------------------------------------------------------------------------
void
IMULink::ReadH(const boost::system::error_code& error)
  {
  this->state = this->state_jk;
  switch (this->state)
    {
    case INIT:
      {
//      std::cout << "INIT\n";
      this->state_jk = SEARCH;
      this->PostRead(this->frame_length);
      break;
      }
    case SEARCH:
      {
//      std::cout << "SEARCH\n";
      unsigned int i;

      for (i = 0; i < this->frame_length - 1; i++)
        {
        if (this->buffer[i] == '\r' && this->buffer[i + 1] == '\n')
          {
          this->state_jk = IMULink::PREVERIFY;
          break;
          }
        }
      if (this->state_jk != IMULink::PREVERIFY)
        {
        this->state_jk = IMULink::INIT;
        this->PostRead(1);  // Read just in case sync on buffer boundary.
        }
      else
        {
        this->PostRead(this->frame_length + i + 2);  // Align.
//        std::cout << "i = " << i << "frame_length = " << this->frame_length << "\n";
        }
      break;
      }
    case PREVERIFY:
      {
//      std::cout << "PREVERIFY\n";
      this->vv = 0;
      this->state_jk = IMULink::VERIFY;
      this->PostRead(this->frame_length);
      break;
      }
    case VERIFY:
      {
//      std::cout << "VERIFY\n";
      if (this->buffer[this->frame_length - 2] == '\r' &&
          this->buffer[this->frame_length - 1] == '\n')
        this->vv++;
      else
        this->state_jk = IMULink::SEARCH;
      if (this->vv >= 32)
        this->state_jk = IMULink::SYNC;
      this->PostRead(this->frame_length);
      break;
      }
    case SYNC:
      {
//      std::cout << "SYNC\n";
      int p = 0;

      memcpy(&this->tick, &this->buffer[p], sizeof(this->tick));
      p += sizeof(this->tick);
      std::get<0>(this->acc) = this->buffer[p];
      p += sizeof(float);
      std::get<1>(this->acc) = this->buffer[p];
      p += sizeof(float);
      std::get<2>(this->acc) = this->buffer[p];
      p += sizeof(float);
      std::get<0>(this->gyro) = this->buffer[p];
      p += sizeof(float);
      std::get<1>(this->gyro) = this->buffer[p];
      p += sizeof(float);
      std::get<2>(this->gyro) = this->buffer[p];
      p += sizeof(float);
      memcpy(&this->mag,  &this->buffer[p], sizeof(this->mag));
      std::get<0>(this->mag) = this->buffer[p];
      p += sizeof(float);
      std::get<1>(this->mag) = this->buffer[p];
      p += sizeof(float);
      std::get<2>(this->mag) = this->buffer[p];
      p += sizeof(float);
      if (this->buffer[p] == '\r' && this->buffer[p + 1] == '\n')
        this->state_jk = IMULink::SYNC;
      else
        this->state_jk = IMULink::VERIFY; // Error.
      this->PostRead(this->frame_length);
      break;
      }
    case TERMINATE:
//      std::cout << "TERMINATE\n";
      break;  // Terminate by not calling PostRead().
    }
  }

//------------------------------------------------------------------------------
void
IMULink::PostRead(int nbytes)
  {
  memset(this->buffer, 0, this->frame_length + 1);
  boost::asio::async_read(this->serial_port,
                          boost::asio::buffer(this->buffer, nbytes),
                          boost::bind(&IMULink::ReadH,
                                      this,
                                      boost::asio::placeholders::error)
                         );
  }
