/* Copyright_License {

  G-Meter INU.
  Copyright (C) 2013-2015 The XCSoar Project and Peter F Bradshaw
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

  private static NativeRunnable reference = null;

  /**
   * The public accessable call to create the Singleton object of this class.
   */
  public static NativeRunnable getInstance() {
    return NativeRunnable.reference;
    }

  public NativeRunnable(Activity context, Handler quitHandler) {
    this.quitHandler = quitHandler;
    this.resources = context.getResources();
    reference = this;
  }

  /**
   * To be used by objects that are 'in the know' that this object is
   * deregistered.
   */
  public void DeRegister() {
    NativeRunnable.reference = null;
  }

  /**
   * Global access. This assumes that the object of this class is a Singleton.
   * This Singleton behavour is not enforced. Do not abuse this requirement!
   */
  static public NativeRunnable singleton;

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
  protected native void onCreateNative();
  protected native void onDestroyNative();
  protected native void onStartNative();
  public void onResume() {
    resumeNative();
  }

  public void onPause() {
    pauseNative();
  }

  
  public void exitApp() {
    NativeRunnable.reference = null;
  }

  /**
   * Used by the service to indicate onCreate() to the native code.
   */
  public void onCreate() {
    onCreateNative();
  }

  /**
   * Used by the service to indicate onDestroy() to the native code.
   */
  public void onDestroy() {
    onDestroyNative();
  }

  /**
   * Used by the service to indicate onStart() to the native code.
   */
  public void onStart() {
    onStartNative();
  }
}
