/* Copyright_License {

  G-Meter INU.
  Copyright (C) 2013-2014 The XCSoar Project and Peter F Bradshaw
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
import android.app.Activity;
import android.os.Build;
import android.os.Handler;
import android.content.res.Resources;

/**
 * A #View which calls the native part of G-Meter.
 */
class NativeRunnable
  implements Runnable {
  private static final String TAG = "G-Meter";

  Handler quitHandler;
  Resources resources;
  Thread thread;

  public NativeRunnable(Activity context, Handler quitHandler) {
    this.quitHandler = quitHandler;
    this.resources = context.getResources();
  }

  private void start() {
    thread = new Thread(this, "NativeMain");
    thread.start();
  }

  @Override public void run() {
    if (initializeNative(Build.VERSION.SDK_INT, Build.PRODUCT))
        runNative();
    Log.d(TAG, "deinitializeNative()");
    deinitializeNative();

    Log.d(TAG, "sending message to quitHandler");
    quitHandler.sendMessage(quitHandler.obtainMessage());
  }

  protected native boolean initializeNative(int sdk_version, String product);
  protected native void runNative();
  protected native void deinitializeNative();
  protected native void pauseNative();
  protected native void resumeNative();
  protected native void setBatteryPercent(int level, int plugged);
  protected native void setHapticFeedback(boolean on);

  public void onResume() {
    resumeNative();
  }

  public void onPause() {
    pauseNative();
  }

  public void exitApp() {
  }
}
