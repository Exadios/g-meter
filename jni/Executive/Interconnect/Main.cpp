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

#include "Executive.hpp"
#include <boost/config/compiler/gcc.hpp>
#include <boost/asio.hpp>
#include <iostream>

Executive *executive;
std::queue<std::string> xcsoar_deliver;
std::queue<std::string> xcsoar_receive;
std::queue<std::string> ins_deliver;
std::queue<std::string> ins_receive;
std::queue<std::string> serial_deliver;
std::queue<std::string> serial_receive;

int Main(int argc, const char *argv[]);

//------------------------------------------------------------------------------
int Main(int argc, const char *argv[])
  {
  try
    {
    boost::asio::io_service io;
    Executive e(io, 4352, 4400, "/dev/ttyUSB1");
    ::executive = &e;

    ::executive->Run();
    }
  catch (std::exception& e)
    {
    std::cerr << "Exception: " << e.what() << "\n";
    }
  return 0;
  }

//------------------------------------------------------------------------------
int
main(int argc, const char *argv[])
  {
  return Main(argc, argv);
  }
