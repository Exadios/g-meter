cmake_minimum_required(VERSION 2.8.5)

project(ArduIMU)

set_property(GLOBAL PROPERTY ALLOW_DUPLICATE_CUSTOM_TARGETS)

set(CMAKE_CXX_FLAGS_DEBUG "-g -gdwarf-2")
set(CMAKE_BUILD_TYPE "Debug")

# TODO Use find library or similar to implement the below.
link_directories("../../../../lib/local/boost/x86_32/lib")
include_directories("../../../../lib/local/boost/x86_32/include")

add_executable(ins-unix32-debug
               ${ALLSRCS}
              )
target_link_libraries(ins-unix32-debug boost_system)
