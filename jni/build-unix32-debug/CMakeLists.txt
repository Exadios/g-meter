
set_property(GLOBAL PROPERTY ALLOW_DUPLICATE_CUSTOM_TARGETS)

set(CMAKE_CXX_FLAGS_DEBUG "-g -gdwarf-2")
set(CMAKE_BUILD_TYPE "Debug")

add_library(GMeter-unix32-debug SHARED ${UNIXSRCS}) 
