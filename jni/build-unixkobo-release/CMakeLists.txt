
set_property(GLOBAL PROPERTY ALLOW_DUPLICATE_CUSTOM_TARGETS)

set(JNISRC "../")

add_library(GMeter-unixkobo-release SHARED ${JNISRC}/Engine/INU/Inu.cpp 
                          ${JNISRC}/Engine/INU/INUKalman.cpp 
                          ${JNISRC}/Engine/Kalman/kstatics.cpp 
                          ${JNISRC}/Executive/MajorState.cpp
                          ${JNISRC}/Utility/Mutex.cpp
                          ${JNISRC}/Utility/Observer.cpp 
                          ${JNISRC}/Utility/Observed.cpp
                          ${JNISRC}/Utility/DeviceInputBuffer.cpp)
