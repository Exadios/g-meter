// G-MeterIPC.aidl
package com.exadios.g_meter;

// Declare any non-default types here with import statements

/** G-Meter service interface */
interface G_MeterIPC {
    /**
     * Give the current GPS latitude.
     * @return Current phi in radians, equator is zero.
     */
    double position_gps_phi();

    /**
     * Give the current GPS longitude.
     * @return Current lambda in radians, Greenwich is zero.
     */
    double position_gps_lambda();

    /**
     * Give the current GPS height above the Geod.
     * @return Current height above Geod reference, in meters.
     */
    double position_gps_h();

    /**
     * Give the current INU latitude.
     * @return Current phi in radians, equator is zero.
     */
    double position_inu_phi();

    /**
     * Give the current INU longitude.
     * @return Current lambda in radians, Greenwich is zero.
     */
    double position_inu_lambda();

    /**
     * Give the current INU height above the Geod.
     * @return Current height above Geod reference, in meters.
     */
    double position_inu_h();

    /**
     * Give the current GPS north - south velocity.
     * @return Current phi velocity in radians per second.
     */
    double velocity_gps_phi();

    /**
     * Give the current GPS east - west velocity.
     * @return Current lambda velocity in radians per second.
     */
    double velocity_gps_lambda();

    /**
     * Give the current GPS up - down velocity.
     * @return Current h velocity in meters per second.
     */
    double velocity_gps_h();

    /**
     * Give the current INU north - south velocity.
     * @return Current phi velocity in radians per second.
     */
    double velocity_inu_phi();

    /**
     * Give the current INU east - west velocity.
     * @return Current lambda velocity in radians per second.
     */
    double velocity_inu_lambda();

    /**
     * Give the current INU up - down velocity.
     * @return Current h velocity in meters per second.
     */
    double velocity_inu_h();
}
