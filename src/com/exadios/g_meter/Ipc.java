package com.exadios.g_meter;

import com.exadios.g_meter.G_MeterIPC;
import android.os.Binder;
import android.os.IBinder;

public final class Ipc implements G_MeterIPC {

  public void start() {
    // TODO start an IPC event loop.
  };

  public Binder asBinder() {
    /*
     * Need to findout how to get the Binder and return it. In the meantime ...
     */
    return null;
  };
}
