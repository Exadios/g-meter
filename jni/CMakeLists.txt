cmake_minimum_required(VERSION 2.8)

project(G-Meter)

set_property(GLOBAL PROPERTY ALLOW_DUPLICATE_CUSTOM_TARGETS)

# Common flags
set(CMAKE_CXX_FLAGS "-std=gnu++11 -I../ -I../lib -ffast-math  -fexceptions -fno-threadsafe-statics -fmerge-all-constants -fconserve-space -fno-operator-names -fvisibility=hidden -finput-charset=utf-8 -pthread -Wall -Wextra -Wwrite-strings -Wcast-qual -Wpointer-arith -Wsign-compare -Wundef -Wmissing-declarations -Wmissing-noreturn -Wno-unused-parameter -Wno-missing-field-initializers -Wcast-align -Werror -I /usr/lib/jvm/java-6-sun/include/ -I /usr/lib/jvm/java-6-sun/include/linux")

include_directories("./"
                    ../lib
                    /usr/lib/jvm/java-6-sun/include/
                    /usr/lib/jvm/java-6-sun/include/linux)

set(JNISRC "../")
set(UNIXSRCS
    ${JNISRC}/Engine/INU/Inu.cpp
    ${JNISRC}/Engine/INU/INUKalman.cpp
    ${JNISRC}/Engine/Kalman/kstatics.cpp
    ${JNISRC}/Executive/MajorState.cpp
    ${JNISRC}/Utility/Mutex.cpp
    ${JNISRC}/Utility/Observer.cpp
    ${JNISRC}/Utility/Observed.cpp
    ${JNISRC}/Utility/DeviceInputBuffer.cpp)
set(ANDROIDSRCS
    ${JNISRC}/Executive/Android/GPSSensor.cpp
    ${JNISRC}/Executive/Android/NonGPSSensors.cpp
    ${JNISRC}/Executive/Android/Timer.cpp
    ${JNISRC}/Java/com_exadios_g_meter_InternalGPS.cpp
    ${JNISRC}/Java/com_exadios_g_meter_NativeRunnable.cpp
    ${JNISRC}/Java/com_exadios_g_meter_NonGPSSensors.cpp
    ${JNISRC}/Java/com_exadios_g_meter_Timer.cpp)
set(ALLSRCS ${ANDROIDSRCS} ${UNIXSRCS})

add_subdirectory(Native)
add_subdirectory(build-unix32-release)
add_subdirectory(build-unix32-debug)
add_subdirectory(build-android7-release)
add_subdirectory(build-android7-debug)
add_subdirectory(build-unixkobo-release)
