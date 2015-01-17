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

import android.app.Activity;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;
import android.widget.TextView;
import android.os.Build;
import android.os.Handler;
import android.os.Message;
import android.os.BatteryManager;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.BroadcastReceiver;
import android.util.Log;
import android.provider.Settings;

/**
 * \mainpage G-Meter: An INU for use with XCSoar
 *
 * \par
 * This app exists to provide an INU service for XCSoar on Android.
*/

/**
 * The Android entry point.
 */
public class GMeter extends Activity {
  private static final String TAG = "GMeter";

  BroadcastReceiver batteryReceiver = new BroadcastReceiver() {
    @Override public void onReceive(Context context, Intent intent) {
      if (NativeRunnable.getInstance() == null)
        return;

      int level = intent.getIntExtra(BatteryManager.EXTRA_LEVEL, 0);
      int plugged = intent.getIntExtra(BatteryManager.EXTRA_PLUGGED, 0);
      NativeRunnable.getInstance().setBatteryPercent(level, plugged);
    }
  };

  /**
   * The OS creates this service.
   */
  @Override protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);

    Log.d(TAG, "ABI=" + Build.CPU_ABI);
    Log.d(TAG, "PRODUCT=" + Build.PRODUCT);
    Log.d(TAG, "MANUFACTURER=" + Build.MANUFACTURER);
    Log.d(TAG, "MODEL=" + Build.MODEL);
    Log.d(TAG, "DEVICE=" + Build.DEVICE);
    Log.d(TAG, "BOARD=" + Build.BOARD);
    Log.d(TAG, "FINGERPRINT=" + Build.FINGERPRINT);

    if (!Loader.loaded) {
      TextView tv = new TextView(this);
      tv.setText("Failed to load the native G-Meter libary.\n" +
                 "Report this problem to us, and include the following information:\n" +
                 "ABI=" + Build.CPU_ABI + "\n" +
                 "PRODUCT=" + Build.PRODUCT + "\n" +
                 "FINGERPRINT=" + Build.FINGERPRINT + "\n" +
                 "error=" + Loader.error);
      setContentView(tv);
      return;
    }

    Timer.Initialize();
    InternalGPS.Initialize();
    NonGPSSensors.Initialize();

    // fullscreen mode
    requestWindowFeature(Window.FEATURE_NO_TITLE);
    getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN|
                         WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

    TextView tv = new TextView(this);
    tv.setText("Loading G-Meter...");
    setContentView(tv);

    registerReceiver(batteryReceiver,
                     new IntentFilter(Intent.ACTION_BATTERY_CHANGED));
  }

  private void quit() {
    Log.d(TAG, "in quit()");

    NativeRunnable.getInstance().DeRegister();

    Log.d(TAG, "stopping service");

    TextView tv = new TextView(GMeter.this);
    tv.setText("Shutting down G-Meter...");
    setContentView(tv);

    Log.d(TAG, "finish()");
    finish();
  }

  Handler quitHandler = new Handler() {
    public void handleMessage(Message msg) {
      quit();
    }
  };


  /**
   * The OS removes this service from the run list.
   */
  @Override protected void onPause() {
    if (NativeRunnable.getInstance() != null)
      NativeRunnable.getInstance().onPause();
    super.onPause();
  }

  private void getHapticFeedbackSettings() {
    boolean hapticFeedbackEnabled;
    try {
      hapticFeedbackEnabled =
        (Settings.System.getInt(getContentResolver(),
                                Settings.System.HAPTIC_FEEDBACK_ENABLED)) != 0;
    } catch (Settings.SettingNotFoundException e) {
      hapticFeedbackEnabled = false;
    }

    if (NativeRunnable.getInstance() != null)
      NativeRunnable.getInstance().setHapticFeedback(hapticFeedbackEnabled);
  }

  /**
   * The OS places this service in the run table.
   */
  @Override protected void onResume() {
    super.onResume();

    NativeRunnable.getInstance().onResume();
    getHapticFeedbackSettings();
  }

  /**
   * The OS shuts this service down.
   */
  @Override protected void onDestroy() {
    Log.d(TAG, "in onDestroy()");

    if (NativeRunnable.getInstance() != null) {
      NativeRunnable.getInstance().exitApp();
    }

    super.onDestroy();
    Log.d(TAG, "System.exit()");
    System.exit(0);
  }

}
