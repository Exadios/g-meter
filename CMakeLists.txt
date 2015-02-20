cmake_minimum_required(VERSION 2.8)

project(G-Meter)

add_subdirectory(jni)

add_custom_target(javabuild ALL
                  DEPENDS bin/AndroidManifest.xml
                          bin/G-Meter-release-unsigned.apk)
set(JAVASRC src/com/exadios/g_meter)
add_custom_command(OUTPUT bin/G-Meter-release-unsigned.apk
                          bin/AndroidManifest.xml
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
add_custom_target(clean
                  COMMAND true)
add_dependencies(clean javaclean)

add_custom_target(doco
                  DEPENDS ./doc/html/index.html)
add_custom_command(OUTPUT ./doc/html/index.html
                   COMMAND mkdir -p doc/html\; doxygen Doxyfile)

add_custom_target(design
                  DEPENDS ./doc/Design/G-Meter.pdf)
add_custom_command(OUTPUT ./doc/Design/G-Meter.pdf
                   COMMAND pdflatex G-Meter.tex
                   DEPENDS ./doc/Design/G-Meter.tex ./doc/Design/G-Meter-fig-001.png
                   WORKING_DIRECTORY doc/Design/)

