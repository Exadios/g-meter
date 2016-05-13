# Ignore this stuff for now - using DIYDrones ArduIMU+ V3 at this time.
#set(UNIXSRCS
#    ${JNISRC}/Engine/INU/Inu.cpp
#    ${JNISRC}/Engine/INU/INUKalman.cpp
#    ${JNISRC}/Engine/Kalman/kstatics.cpp
#    ${JNISRC}/Executive/MajorState.cpp
#    ${JNISRC}/Utility/Mutex.cpp
#    ${JNISRC}/Utility/Observer.cpp
#    ${JNISRC}/Utility/Observed.cpp
#    ${JNISRC}/Utility/DeviceInputBuffer.cpp)
#set(ANDROIDSRCS
#    ${JNISRC}/Executive/Android/GPSSensor.cpp
#    ${JNISRC}/Executive/Android/NonGPSSensors.cpp
#    ${JNISRC}/Executive/Android/Timer.cpp
#    ${JNISRC}/Java/com_exadios_g_meter_InternalGPS.cpp
#    ${JNISRC}/Java/com_exadios_g_meter_NativeRunnable.cpp
#    ${JNISRC}/Java/com_exadios_g_meter_NonGPSSensors.cpp
#    ${JNISRC}/Java/com_exadios_g_meter_Timer.cpp)
set(INSSRC ${JNISRC}/Executive/INS)
set(INUSRC ${JNISRC}/Engine/INU)
set(INTERCONNECTSRC ${JNISRC}/Executive/Interconnect)
set(INSMAIN ${INSSRC}/Main.cpp)
set(INTERCONNECTMAIN ${INTERCONNECTSRC}/Main.cpp)

set(INSSRCS
    ${INSSRC}/Main.cpp
    ${INSSRC}/IMULink.cpp
    ${INUSRC}/Inu.cpp
    ${INUSRC}/INUKalman.cpp
    ${JNISRC}/Engine/Kalman/kstatics.cpp
    CACHE INTERNAL "INS Sources"
   )
set(INTERCONNECTSRCS
    ${INTERCONNECTSRC}/Session.cpp
    ${INTERCONNECTSRC}/DownstreamSession.cpp
    ${INTERCONNECTSRC}/UpstreamSession.cpp
    ${INTERCONNECTSRC}/SerialLink.cpp
    ${INTERCONNECTSRC}/InsLink.cpp
    ${INTERCONNECTSRC}/XcsoarLink.cpp
    ${INTERCONNECTSRC}/Executive.cpp
    ${INTERCONNECTSRC}/Main.cpp
    CACHE INTERNAL "Interconnect Sources"
   )
set(UNIXSRCS ${INSSRCS} ${INTERCONNECTSRCS})
set(ALLSRCS ${ANDROIDSRCS} ${UNIXSRCS})

set(SERIALLINK.TEST.SRCS ${INTERCONNECTSRC}/SerialLink.test.cpp)
set(INTERCONNECT.TEST.SRCS ${INTERCONNECTSRC}/Interconnect.test.cpp)

set(warnings "-Wno-error=unused-parameter -Wall -Wextra -Wwrite-strings -Wcast-qual -Wpointer-arith -Wsign-compare -Wundef -Wmissing-declarations -Wredundant-decls -Wmissing-noreturn -Wno-unused-parameter -Wno-missing-field-initializers  -Wcast-align -Werror")
set(flags "-fno-rtti -std=gnu++0x -fno-threadsafe-statics -fmerge-all-constants -fvisibility=hidden -fpic -funwind-tables -finput-charset=utf-8")
set(defines "")
    set(CMAKE_CXX_FLAGS "${warnings} ${defines} ${flags}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings} ${defines}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
include_directories(${JNISRC})

add_subdirectory(unix)
#add_subdirectory(android7) # Don't bother with android - 
                            # using DIYDrones ArduIMU+ V3
#add_subdirectory(unixkobo)

add_subdirectory(Engine)

link_directories("${BOOST}/x86_32/lib")
include_directories("${BOOST}/x86_32/include")
#add_executable(IMULink EXCLUDE_FROM_ALL 
#                ${JNISRC}/Executive/INS/Test/IMULink.cpp
#                ${JNISRC}/Executive/INS/IMULink.cpp)
#target_link_libraries(IMULink boost_system)
