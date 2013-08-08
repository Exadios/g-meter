package com.exadios.g_meter;

import com.exadios.g_meter.G_MeterINU;
import android.os.Binder;
import android.os.IBinder;

public final class Inu implements G_MeterINU {

  public void start() {
    // TODO start the INU.
  };

  public Binder asBinder() {
    /*
     * No need to return a Binder for this thread.
     */
    return null;
  };
}
