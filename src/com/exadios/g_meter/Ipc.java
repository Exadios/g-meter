package com.exadios.g_meter;

import com.exadios.g_meter.G_MeterIPC;
import android.os.Binder;
import android.os.IBinder;

public final class Ipc extends Thread {

  private final G_MeterIPC.Stub INU_Ipc = new G_MeterIPC.Stub () {
    private final class GeodeticPosition {
      public double phi;
      public double lambda;
      public double h;
    };

    private final class GeodeticVelocity {
      public double phi;
      public double lambda;
      public double h;
    };

    private GeodeticPosition position_gps;
    private GeodeticPosition position_inu;
    private GeodeticVelocity velocity_gps;
    private GeodeticVelocity velocity_inu;

    public double position_gps_phi() {
      return this.position_gps.phi;
    };
    public double position_gps_lambda() {
      return this.position_gps.lambda;
    };
    public double position_gps_h() {
      return position_gps.h;
    };
    public double position_inu_phi() {
      return position_inu.phi;
    };
    public double position_inu_lambda() {
      return position_inu.lambda;
    };
    public double position_inu_h() {
      return position_inu.h;
    };
    public double velocity_gps_phi() {
      return velocity_gps.phi;
    };
    public double velocity_gps_lambda() {
      return velocity_gps.lambda;
    };
    public double velocity_gps_h() {
      return velocity_gps.h;
    };
    public double velocity_inu_phi() {
      return velocity_inu.phi;
    };
    public double velocity_inu_lambda() {
      return velocity_inu.lambda;
    };
    public double velocity_inu_h() {
      return velocity_inu.h;
    };
  };

  public final void run() {
    // TODO start an IPC event loop.
  };

  public final Binder asBinder() {
    return this.INU_Ipc;
  };
}
