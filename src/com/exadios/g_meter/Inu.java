package com.exadios.g_meter;

import com.exadios.g_meter.G_MeterINU;
import android.os.Binder;
import android.os.IBinder;

public final class Inu extends Thread {

  public final void run() {
    // TODO start the INU.
  };

  public final Binder asBinder() {
    /*
     * No need to return a Binder for this thread.
     */
    return null;
  };
}
