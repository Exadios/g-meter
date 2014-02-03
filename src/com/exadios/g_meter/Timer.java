/* Copyright_License {

  G-Meter INU.
  Copyright (C) 2000-2014 The XCSoar Project and Peter F Bradshaw
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

package com.exadios.g_meter;

import android.os.Handler;
import android.os.SystemClock;

/**
 * A periodic timer used by the native code.
 */
class Timer implements Runnable
   {
   static Handler handler;

   /**
    * Global initialization of the class.  Must be called from the main
    * event thread, because the Handler object must be bound to that
    * thread.
    */
   public static void Initialize()
     {
     handler = new Handler();
     }

   static long dt = 1000; // 1000 milliseconds.
   long t;

   Timer()
     {
     }

   private void install()
     {
     this.t = SystemClock.uptimeMillis() + dt;
     handler.postAtTime(this, this.t);
     }

   private void uninstall()
     {
     handler.removeCallbacks(this);
     }

   private native void run(long dt);

   @Override public void run()
     {
     this.t = this.t + dt;
     handler.postAtTime(this, this.t);
     run(this.t - dt);
     }
   }
