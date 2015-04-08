/* Copyright_License {

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

#include "../Inu.hpp"

//-----------------------------------------------------------------------------
int main(int argc, const char *argv[])
  {
    {
    std::cout << "Test 1" << std::endl;
    Inu inu(1.0);
    int i;
    IMUvector w = IMUvector(3, float(0.0));
    IMUvector f = IMUvector(3, float(0.0));
    IMUvector v = IMUvector(3, float(0.0));

    for (i = 0; i < 100000; i++)
      {
      if (inu.Update(w, f, v, inu.gfh(0.0)) == false)
        {
        std::cerr << "Could not compute" << std::endl;
        exit(1);
        }
      }
    std::cout << "v_dot_super_e: " << inu.v_dot_super_e() << std::endl;
    std::cout << "Omega_sub_eb_super_b: " << inu.Omega_sub_eb_super_b() << std::endl;
    std::cout << "R_sub_b_super_e: " << inu.R_sub_b_super_e() << std::endl;
    }
    
    {
    std::cout << "Test 2" << std::endl;
    Inu inu(1.0);
    IMUvector w = IMUvector(3, float(0.0));
    IMUvector f = IMUvector(3, float(0.0));
    IMUvector v = IMUvector(3, float(0.0));

    std::cout << "v_dot_super_e: " << inu.v_dot_super_e() << std::endl;
    std::cout << "Omega_sub_eb_super_b: " << inu.Omega_sub_eb_super_b() << std::endl;
    std::cout << "R_sub_b_super_e: " << inu.R_sub_b_super_e() << std::endl;
    if(inu.Update(w, f, v, inu.gfh(0.0)) == false)
      {
      std::cerr << "Could not compute" << std::endl;
      exit(1);
      }
    std::cout << "v_dot_super_e: " << inu.v_dot_super_e() << std::endl;
    std::cout << "Omega_sub_eb_super_b: " << inu.Omega_sub_eb_super_b() << std::endl;
    std::cout << "R_sub_b_super_e: " << inu.R_sub_b_super_e() << std::endl;
    f(1) = 1.0;
    if (inu.Update(w, f, v, inu.gfh(0.0)) == false)
      {
      std::cerr << "Could not compute" << std::endl;
      exit(1);
      }
    std::cout << "v_dot_super_e: " << inu.v_dot_super_e() << std::endl;
    std::cout << "Omega_sub_eb_super_b: " << inu.Omega_sub_eb_super_b() << std::endl;
    std::cout << "R_sub_b_super_e: " << inu.R_sub_b_super_e() << std::endl;

    f(1) = 0.0;
    if (inu.Update(w, f, v, inu.gfh(0.0)) == false)
      {
      std::cerr << "Could not compute" << std::endl;
      exit(1);
      }
    std::cout << "v_dot_super_e: " << inu.v_dot_super_e() << std::endl;
    std::cout << "Omega_sub_eb_super_b: " << inu.Omega_sub_eb_super_b() << std::endl;
    std::cout << "R_sub_b_super_e: " << inu.R_sub_b_super_e() << std::endl;
    }

  return 0;
  }
