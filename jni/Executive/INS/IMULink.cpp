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
#include <string.h>

//------------------------------------------------------------------------------
IMULink::IMULink()
  : fd(-1),
    serial(NULL)
  {
  this->state = SEARCH;
  this->fd    = open(this->serial_port, O_NOCTTY, O_RDWR);
    {
    struct termios driver;
    cfmakeraw(&driver);                   // Turn off cannonical etc.
    cfsetspeed(&driver, B230400);
    driver.c_iflag &= ~IXOFF;             // No flow control.
    driver.c_iflag |= IGNPAR | IGNBRK ;   // No parity or break. 
    driver.c_cflag &= ~(CSTOPB | PARENB); // One stop and no parity.
    tcsetattr(this->fd, TCSANOW, &driver);
    }
  if (this->fd != -1)
    this->serial = fdopen(fd, "rw");
  }

//------------------------------------------------------------------------------
bool
IMULink::Read()
  {
  if (this->serial == NULL)
    return false;

  do
    {
    char buf[128];

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

        fread(buf, sizeof(char), this->frame_length, this->serial);
        for (i = 0; i < this->frame_length - 1; i++)
          {
          if (buf[i] == '\r' && buf[i + 1] == '\n')
            {
            fread(buf, sizeof(char), i + 2, serial);
            this->state = VERIFY;
            break;
            }
          }
        if (this->state != VERIFY)
          fread(buf, sizeof(char), 1, this->serial);  // Read just in case sync
                                                      // on buffer boundry.
        break;
        }
      case VERIFY:
        {
        int i, v;

        for (i = 0, v = 0; i < 8; i++)
          {
          fread(buf, sizeof(char), frame_length, this->serial);
          for (unsigned int j = 0; j < frame_length - 1; j++)
            if (buf[j] == '\r' && buf[j + 1] == '\n')
            v++;
          }
        if (v == i)
          this->state = SYNC;
        else if (v == i - 1)
          this->state = VERIFY;   // Try another VERIFY
        else
          this->state = SEARCH;   // Something terribly wrong!
        break;
        }
      case SYNC:
        {
        char eor[2];

        fread(&this->tick, sizeof(this->tick), 1, this->serial);
        fread(&this->acc, sizeof(this->acc), 1, this->serial);
        fread(&this->gyro, sizeof(this->gyro), 1, this->serial);
        fread(&this->mag, sizeof(this->mag), 1, this->serial);
        fread(eor, sizeof(char), sizeof(eor) / sizeof(char), serial);
        if (eor[0] == '\r' && eor[1] == '\n')
          return true;
        else
          this->state = VERIFY;   // Error.
        break;
        }
      }
    } while (true);
  }

