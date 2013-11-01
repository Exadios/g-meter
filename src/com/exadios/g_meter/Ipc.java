package com.exadios.g_meter;

import com.exadios.g_meter.G_MeterIPC;
import android.os.Binder;
import android.os.IBinder;

public final class Ipc extends Thread {

  private final G_MeterIPC.Stub INU_Ipc = new G_MeterIPC.Stub () {
    class GeodeticPosition {
      public double phi;
      public double lambda;
      public double h;
      public synchronized GeodeticPosition position() {
        return this;
      };
    };

    class GeodeticVelocity {
      public double phi;
      public double lambda;
      public double h;
      public synchronized GeodeticVelocity velocity() {
        return this;
      };
    };

    class Position {
      public GeodeticPosition gps;
      public GeodeticPosition inu;
    };

    class Velocity {
      public GeodeticVelocity gps;
      public GeodeticVelocity inu;
    };

    private Position position;
    private Velocity velocity;

    public double position_gps_phi() {
      return this.position.gps.phi;
    };
    public double position_gps_lambda() {
      return this.position.gps.lambda;
    };
    public double position_gps_h() {
      return this.position.gps.h;
    };
    public double position_inu_phi() {
      return this.position.inu.phi;
    };
    public double position_inu_lambda() {
      return this.position.inu.lambda;
    };
    public double position_inu_h() {
      return this.position.inu.h;
    };
    public double velocity_gps_phi() {
      return this.velocity.gps.phi;
    };
    public double velocity_gps_lambda() {
      return this.velocity.gps.lambda;
    };
    public double velocity_gps_h() {
      return this.velocity.gps.h;
    };
    public double velocity_inu_phi() {
      return this.velocity.inu.phi;
    };
    public double velocity_inu_lambda() {
      return this.velocity.inu.lambda;
    };
    public double velocity_inu_h() {
      return this.velocity.inu.h;
    };
  };

  public final void run() {
    // TODO start an IPC event loop.
  };

  public final Binder asBinder() {
    return this.INU_Ipc;
  };
}
