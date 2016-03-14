set(JNISRC ${GMeterRoot}/jni)
set(JAVASRC ${GMeterRoot}/src)
set(CLASS_DST ${GMeterRoot}/out/build/src)
set(SUBMODULES ${GMeterRoot}/lib)
set(BOOST ${SUBMODULES}/local/boost)

# TODO remove hardcoded ANDROID_SDK_DIR and find android.jar automatically!
set(ANDROID_SDK_DIR /home/pfb/opt/android-sdk-linux/platforms/android-19/android.jar)
# TODO move target src up one level.
add_subdirectory(src)
add_subdirectory(Native)
add_subdirectory(jni)

add_custom_target(
                  doco
                  COMMAND doxygen ../../../Doxyfile
                  WORKING_DIRECTORY doc
                 )

