cmake_minimum_required(VERSION 2.8)

project(G-Meter)

set_property(GLOBAL PROPERTY ALLOW_DUPLICATE_CUSTOM_TARGETS)

# Common flags
set(CMAKE_CXX_FLAGS "-std=gnu++11 -I../ -ffast-math  -fno-exceptions -fno-rtti -fno-threadsafe-statics -fmerge-all-constants -fconserve-space -fno-operator-names -fvisibility=hidden -finput-charset=utf-8 -Wall -Wextra -Wwrite-strings -Wcast-qual -Wpointer-arith -Wsign-compare -Wundef -Wmissing-declarations -Wmissing-noreturn -Wno-unused-parameter -Wno-missing-field-initializers -Wcast-align -Werror -I /usr/lib/jvm/java-6-sun/include/ -I /usr/lib/jvm/java-6-sun/include/linux")

include_directories("./"
                    /usr/lib/jvm/java-6-sun/include/
                    /usr/lib/jvm/java-6-sun/include/linux)

add_subdirectory(Native)
add_subdirectory(build-unix32-release)
add_subdirectory(build-unix32-debug)
add_subdirectory(build-android7-release)
add_subdirectory(build-android7-debug)
add_subdirectory(build-unixkobo-release)
