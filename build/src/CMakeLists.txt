# TODO This whole taget is a kludge - fix it up!
set(JAVA_PACKAGE_PREFIX com/exadios/g_meter)
set(JAVA_SRCS ${JAVA_PACKAGE_PREFIX}/GMeter.java
              ${JAVA_PACKAGE_PREFIX}/GMeterService.java
              ${JAVA_PACKAGE_PREFIX}/InternalGPS.java
              ${JAVA_PACKAGE_PREFIX}/Loader.java
              ${JAVA_PACKAGE_PREFIX}/NativeRunnable.java
              ${JAVA_PACKAGE_PREFIX}/NonGPSSensors.java
              ${JAVA_PACKAGE_PREFIX}/SafeDestruct.java
              ${JAVA_PACKAGE_PREFIX}/Timer.java)
set(JAVA_CLASSES ${CLASS_DST}/${JAVA_PACKAGE_PREFIX}/GMeter.class
                 ${CLASS_DST}/${JAVA_PACKAGE_PREFIX}/GMeterService.class
                 ${CLASS_DST}/${JAVA_PACKAGE_PREFIX}/InternalGPS.class
                 ${CLASS_DST}/${JAVA_PACKAGE_PREFIX}/Loader.class
                 ${CLASS_DST}/${JAVA_PACKAGE_PREFIX}/NativeRunnable.class
                 ${CLASS_DST}/${JAVA_PACKAGE_PREFIX}/NonGPSSensors.class
                 ${CLASS_DST}/${JAVA_PACKAGE_PREFIX}/SafeDestruct.class
                 ${CLASS_DST}/${JAVA_PACKAGE_PREFIX}/Timer.class)

#add_custom_target(debug ALL
#                  COMMAND echo `pwd`)

add_custom_target(java_classes ALL
                  DEPENDS ${JAVA_CLASSES})
add_custom_command(OUTPUT ${JAVA_CLASSES}
                   COMMAND cd ${JAVASRC} && javac
                     -d ${CLASS_DST}
                     -classpath ${ANDROID_SDK_DIR}
                     ${JAVA_SRCS})
