cmake_minimum_required(VERSION 2.8.5)

project(ArduIMU)

set_property(GLOBAL PROPERTY ALLOW_DUPLICATE_CUSTOM_TARGETS)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_BUILD_TYPE "Release")

# TODO Use find library or similar to implement the below.
link_directories("../../../lib/local/boost/x86_32/lib")
include_directories("../../../lib/local/boost/x86_32/include")

add_executable(ins-unix32-release
               ${ALLSRCS}
              )
target_link_libraries(ins-unix32-release boost_system)
