/*
Copyright_License {

  G-Meter INU
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

import android.util.Log;

public class Loader {
  private static final String TAG = "GMeter";

  public static boolean loaded = false;
  public static String error;

  static {
    try {
      System.loadLibrary("g_meter");
      loaded = true;
    } catch (UnsatisfiedLinkError e) {
      Log.e(TAG, e.getMessage());
      error = e.getMessage();
    }
  }
}