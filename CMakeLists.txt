cmake_minimum_required(VERSION 2.8)

project(G-Meter)

add_custom_target(package ALL
                  COMMAND make
                  DEPENDS jni
                  WORKING_DIRECTORY jni)
