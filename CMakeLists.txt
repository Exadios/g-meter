cmake_minimum_required(VERSION 2.8)

project(G-Meter)

add_subdirectory(jni)

add_custom_target(javabuild ALL
                  DEPENDS bin/AndroidManifest.xml
                          bin/G-Meter-release-unsigned.apk)
set(JAVASRC src/com/exadios/g_meter)
add_custom_command(OUTPUT bin/AndroidManifest.xml
                   COMMAND /usr/bin/ant release
                   DEPENDS ${JAVASRC}/GMeter.java
                           ${JAVASRC}/GMeterService.java
                           ${JAVASRC}/InternalGPS.java
                           ${JAVASRC}/Loader.java
                           ${JAVASRC}/NativeRunnable.java
                           ${JAVASRC}/NonGPSSensors.java
                           ${JAVASRC}/NonGPSSensors.java
                           ${JAVASRC}/SafeDestruct.java
                           ${JAVASRC}/Timer.java)

# TODO This does not work. Find a way.
add_custom_target(javaclean
                  COMMAND ant clean)
add_dependencies(clean javaclean)

