// G-MeterIPC.aidl
package com.exadios.g_meter;

// Declare any non-default types here with import statements

/** Example service interface */
interface G_MeterIPC {
    
    double position_gps_phi();
    double position_gps_lambda();
    double position_gps_h();
    double position_inu_phi();
    double position_inu_lambda();
    double position_inu_h();
    double velocity_gps_phi();
    double velocity_gps_lambda();
    double velocity_gps_h();
    double velocity_inu_phi();
    double velocity_inu_lambda();
    double velocity_inu_h();
}
