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

#include <iostream>
#include <fstream>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#define SERPORT "/dev/ttyUSB0"
#define FRAMELEN sizeof(unsigned int) + 9 * sizeof(float) + 2 * sizeof(char)

enum state_t
  {
  INIT = 0,   // Initial state.
  SEARCH = 1, // Search for buffer frame by looking for '\r', '\n' pair.
  VERIFY = 2, // Verify sync.
  SYNC = 3    // Have frame sync. Read data.
  };

const char *statetext[] =
  {
  "INIT", 
  "SEARCH", 
  "VERIFY",
  "SYNC"
  };

int main()
  {
  enum state_t state = INIT, statejk = SEARCH;
  FILE *serial;
  int fd;

  if ((fd = open(SERPORT, O_NOCTTY, O_RDWR)) == -1)
    {
    perror(strerror(errno));
    exit(1);
    }

    {
    struct termios driver;
    cfmakeraw(&driver);                   // Turn off cannonical etc.
    cfsetspeed(&driver, B230400);
    driver.c_iflag &= ~IXOFF;             // No flow control.
    driver.c_iflag |= IGNPAR | IGNBRK ;   // No parity or break. 
    driver.c_cflag &= ~(CSTOPB | PARENB); // One stop and no parity.
    tcsetattr(fd, TCSANOW, &driver);
    }

  if ((serial = fdopen(fd, "rw")) == (FILE *)NULL)
    {
    perror(strerror(errno));
    exit(1);
    }

  char buf[128];
  do
    {
    if (state != statejk)
      {
      state = statejk;
      std::cerr << statetext[state] << std::endl;
      }

    switch (state)
      {
      case SEARCH:
        {
        int i;

        if (fread(buf, sizeof(char), FRAMELEN, serial) != FRAMELEN)
          {
          perror(strerror(errno));
          exit(1);
          }

        for (i = 0; i < FRAMELEN - 1; i++)
          {
          if (buf[i] == '\r' && buf[i + 1] == '\n')
            {
            fread(buf, sizeof(char), i + 2, serial);
            statejk = VERIFY;
            break;
            }
          }
        if (statejk != VERIFY)
          fread(buf, sizeof(char), 1, serial);  // Read just in case sync on
                                                // buffer boundry.
        break;
        }
      case VERIFY:
        {
        int i, v;

        for (i = 0, v = 0; i < 8; i++)
          {
          fread(buf, sizeof(char), FRAMELEN, serial);
          for (int j = 0; j < FRAMELEN - 1; j++)
            if (buf[j] == '\r' && buf[j + 1] == '\n')
            v++;
          }
        if (v == i)
          statejk = SYNC;
        else if (v == i - 1)
          statejk = VERIFY;   // Try another VERIFY
        else
          statejk = SEARCH;   // Something terribly wrong!
        break;
        }
      case SYNC:
        {
        float val[9];
        unsigned int tick;
        char eor[2];

        fread(&tick, sizeof(tick), 1, serial);
        fread(val, sizeof(float), sizeof(val) / sizeof(float), serial);
        fread(eor, sizeof(char), sizeof(eor) / sizeof(char), serial);
        if (eor[0] == '\r' && eor[1] == '\n')
          {
          std::cout << tick << ": ";
          for (int i = 0; i < sizeof(val) / sizeof(float); i++)
            std::cout << val[i] << ", ";
          std::cout << std::endl;
          }
        else
          statejk = VERIFY;   // Error.
        break;
        }
      }

    } while (true);

  return 0;
  }
