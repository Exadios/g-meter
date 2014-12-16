cmake_minimum_required(VERSION 2.8)

project(G-Meter)

# Common 
set(CMAKE_CXX_FLAGS "-std=gnu++11 -I../ -ffast-math  -fno-exceptions -fno-rtti -fno-threadsafe-statics -fmerge-all-constants -fconserve-space -fno-operator-names -fvisibility=hidden -finput-charset=utf-8 -Wall -Wextra -Wwrite-strings -Wcast-qual -Wpointer-arith -Wsign-compare -Wundef -Wmissing-declarations -Wmissing-noreturn -Wno-unused-parameter -Wno-missing-field-initializers -Wcast-align -Werror -I /usr/lib/jvm/java-6-sun/include/ -I /usr/lib/jvm/java-6-sun/include/linux")
add_library(GMeter SHARED Engine/INU/Inu.cpp 
                          Engine/INU/INUKalman.cpp 
                          Engine/Kalman/kstatics.cpp 
                          Executive/Android/GPSSensor.cpp
                          Executive/Android/NonGPSSensors.cpp
                          Executive/Android/Timer.cpp
                          Executive/MajorState.cpp
                          Java/com_exadios_g_meter_InternalGPS.cpp 
                          Java/com_exadios_g_meter_NativeRunnable.cpp 
                          Java/com_exadios_g_meter_NonGPSSensors.cpp 
                          Java/com_exadios_g_meter_Timer.cpp
                          Utility/Mutex.cpp
                          Utility/Observer.cpp Utility/Observed.cpp
                          Utility/DeviceInputBuffer.cpp)


