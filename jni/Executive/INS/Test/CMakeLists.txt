cmake_minimum_required(VERSION 2.8)

project(G-Meter)

link_directories("../../../../lib/local/boost/x86_32/lib")
include_directories("../../../../lib/local/boost/x86_32/include")
add_executable(IMULink IMULink.cpp ../IMULink.cpp)
target_link_libraries(IMULink boost_system)
