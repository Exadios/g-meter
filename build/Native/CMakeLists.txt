set(JAVA_PACKAGE_PREFIX com/exadios/g_meter)
add_custom_target(jni_headers ALL
                  DEPENDS com_exadios_g_meter_InternalGPS.h
                          com_exadios_g_meter_NativeRunnable.h
                          com_exadios_g_meter_NonGPSSensors.h
                          com_exadios_g_meter_Timer.h)

add_custom_command(OUTPUT com_exadios_g_meter_InternalGPS.h
                   COMMAND javah -jni
                             -d .
                             -classpath ${CLASS_DST}:${ANDROID_SDK_DIR}
                             com.exadios.g_meter.InternalGPS
                   DEPENDS ${CLASS_DST}/${JAVA_PACKAGE_PREFIX}/InternalGPS.class
                   VERBATIM)

add_custom_command(OUTPUT com_exadios_g_meter_NativeRunnable.h
                   COMMAND javah -jni
                             -d .
                             -classpath ${CLASS_DST}:${ANDROID_SDK_DIR}
                             com.exadios.g_meter.NativeRunnable
                   DEPENDS ${CLASS_DST}/${JAVA_PACKAGE_PREFIX}/NativeRunnable.class
                   VERBATIM)

add_custom_command(OUTPUT com_exadios_g_meter_NonGPSSensors.h
                   COMMAND javah -jni
                     -d .
                     -classpath ${CLASS_DST}:${ANDROID_SDK_DIR}
                     com.exadios.g_meter.NonGPSSensors
                   DEPENDS ${CLASS_DST}/${JAVA_PACKAGE_PREFIX}/NonGPSSensors.class
                   VERBATIM)

add_custom_command(OUTPUT com_exadios_g_meter_Timer.h
                   COMMAND javah -jni
                     -d .
                     -classpath ${CLASS_DST}:${ANDROID_SDK_DIR}
                     com.exadios.g_meter.Timer
                   DEPENDS ${CLASS_DST}/${JAVA_PACKAGE_PREFIX}/Timer.class
                   VERBATIM)


