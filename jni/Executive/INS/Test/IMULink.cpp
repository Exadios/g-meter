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

#include "../IMULink.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>

//------------------------------------------------------------------------------
void timerC(const boost::system::error_code&,/*e*/
            boost::asio::deadline_timer *t,
            IMULink *imulink)
  {
  enum IMULink::state_t state;

  state = imulink->State();
//  std::cout << "timerC(): State = " << state << std::flush << "\n";
  if (state == IMULink::SYNC)
    {
    std::cout << imulink->Tick() << " "
              << std::get<0>(imulink->Acc())  << " "
              << std::get<1>(imulink->Acc())  << " "
              << std::get<2>(imulink->Acc())  << " "
              << std::get<0>(imulink->Gyro()) << " "
              << std::get<1>(imulink->Gyro()) << " "
              << std::get<2>(imulink->Gyro()) << "\n";
    }
  t->expires_at(t->expires_at() + boost::posix_time::milliseconds(10));
  t->async_wait(boost::bind(timerC,
                            boost::asio::placeholders::error,
                            t,
                            imulink));

  return;
  }

//------------------------------------------------------------------------------
int Main(const int argc, const char *argv[])
  {
  boost::asio::io_service io;
  std::string port(argv[1]);
  IMULink imulink(io, port);
  boost::asio::deadline_timer t(io, boost::posix_time::milliseconds(10));

  imulink.Initialize();
  t.async_wait(boost::bind(timerC,
                           boost::asio::placeholders::error,
                           &t,
                           &imulink));

  io.run();
  return 0;
  }

//------------------------------------------------------------------------------
int main(const int argc, const char*argv[])
  {
  if (argc < 2)
    {
    std::cerr << "Usage: " << argv[0] << " <tty>" << std::endl;
    exit(1);
    }
  return Main(argc, argv);
  }

