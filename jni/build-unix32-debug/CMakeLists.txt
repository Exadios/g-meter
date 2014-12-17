
set_property(GLOBAL PROPERTY ALLOW_DUPLICATE_CUSTOM_TARGETS)

set(JNISRC "../")

add_library(GMeter-unix32-debug SHARED ${JNISRC}/Engine/INU/Inu.cpp 
                          ${JNISRC}/Engine/INU/INUKalman.cpp 
                          ${JNISRC}/Engine/Kalman/kstatics.cpp 
                          ${JNISRC}/Executive/Android/GPSSensor.cpp
                          ${JNISRC}/Executive/Android/NonGPSSensors.cpp
                          ${JNISRC}/Executive/Android/Timer.cpp
                          ${JNISRC}/Executive/MajorState.cpp
                          ${JNISRC}/Java/com_exadios_g_meter_InternalGPS.cpp 
                          ${JNISRC}/Java/com_exadios_g_meter_NativeRunnable.cpp 
                          ${JNISRC}/Java/com_exadios_g_meter_NonGPSSensors.cpp 
                          ${JNISRC}/Java/com_exadios_g_meter_Timer.cpp
                          ${JNISRC}/Utility/Mutex.cpp
                          ${JNISRC}/Utility/Observer.cpp 
                          ${JNISRC}/Utility/Observed.cpp
                          ${JNISRC}/Utility/DeviceInputBuffer.cpp)
