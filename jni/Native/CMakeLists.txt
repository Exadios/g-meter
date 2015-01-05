cmake_minimum_required(VERSION 2.8)

project(G-Meter)

add_custom_target(jni_headers ALL
                  DEPENDS com_exadios_g_meter_InternalGPS.h
                          com_exadios_g_meter_NativeRunnable.h
                          com_exadios_g_meter_NonGPSSensors.h
                          com_exadios_g_meter_Timer.h)

add_custom_command(OUTPUT com_exadios_g_meter_InternalGPS.h
                   COMMAND javah -d . -classpath ../../bin/classes com.exadios.g_meter.InternalGPS
                   DEPENDS ../../bin/classes/com/exadios/g_meter/InternalGPS.class
                   VERBATIM)

add_custom_command(OUTPUT com_exadios_g_meter_NativeRunnable.h
                   COMMAND javah -d . -classpath ../../bin/classes com.exadios.g_meter.NativeRunnable
                   DEPENDS ../../bin/classes/com/exadios/g_meter/NativeRunnable.class
                   VERBATIM)

add_custom_command(OUTPUT com_exadios_g_meter_NonGPSSensors.h
                   COMMAND javah -d . -classpath ../../bin/classes com.exadios.g_meter.NonGPSSensors
                   DEPENDS ../../bin/classes/com/exadios/g_meter/NonGPSSensors.class
                   VERBATIM)

add_custom_command(OUTPUT com_exadios_g_meter_Timer.h
                   COMMAND javah -d . -classpath ../../bin/classes com.exadios.g_meter.Timer
                   DEPENDS ../../bin/classes/com/exadios/g_meter/Timer.class
                   VERBATIM)
