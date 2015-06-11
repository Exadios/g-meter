cmake_minimum_required(VERSION 2.8.5)

#set(CMAKE_TOOLCHAIN_FILE ./ArduinoToolchain.cmake)

project(ArduIMU)

add_custom_command(OUTPUT Arduimu.hex
                   COMMAND avr-objcopy -O ihex -R .eeprom Arduimu.elf Arduimu.hex
                  )
add_custom_command(OUTPUT Arduimu.eep
                   COMMAND avr-objcopy -O ihex -j .eeprom Arduimu.elf Arduimu.eep
                  )

add_custom_target(hex
                  DEPENDS Arduimu.hex Arduimu.eep
                 )
add_custom_target(upload /usr/share/arduino/hardware/tools/avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -patmega328p -carduino -P/dev/ttyUSB0 -b57600 -D -Uflash:w:Arduimu.hex:i
                 DEPENDS Arduimu.hex
                 COMMENT Uploading Arduimu.hex
                 )

set(ARDUINO_LIBRARY_SRCDIR "/usr/share/arduino/libraries")
set(ARDUINO_LIBRARY_CORES  "/usr/share/arduino/hardware/arduino/cores/arduino")
add_library(Arduino STATIC
            ${ARDUINO_LIBRARY_SRCDIR}/EEPROM/EEPROM.cpp
            ${ARDUINO_LIBRARY_SRCDIR}/SPI/SPI.cpp
            ${ARDUINO_LIBRARY_SRCDIR}/Wire/Wire.cpp
            ${ARDUINO_LIBRARY_SRCDIR}/Wire/utility/twi.c
           )

add_library(core STATIC
            ${ARDUINO_LIBRARY_CORES}/wiring_digital.c
            ${ARDUINO_LIBRARY_CORES}/wiring_analog.c
            ${ARDUINO_LIBRARY_CORES}/wiring_pulse.c
            ${ARDUINO_LIBRARY_CORES}/wiring_shift.c
            ${ARDUINO_LIBRARY_CORES}/wiring.c
            ${ARDUINO_LIBRARY_CORES}/WInterrupts.c
            ${ARDUINO_LIBRARY_CORES}/main.cpp
            ${ARDUINO_LIBRARY_CORES}/IPAddress.cpp
            ${ARDUINO_LIBRARY_CORES}/HardwareSerial.cpp
            ${ARDUINO_LIBRARY_CORES}/CDC.cpp
            ${ARDUINO_LIBRARY_CORES}/USBCore.cpp
            ${ARDUINO_LIBRARY_CORES}/new.cpp
            ${ARDUINO_LIBRARY_CORES}/WMath.cpp
            ${ARDUINO_LIBRARY_CORES}/Print.cpp
            ${ARDUINO_LIBRARY_CORES}/Stream.cpp
            ${ARDUINO_LIBRARY_CORES}/WString.cpp
            ${ARDUINO_LIBRARY_CORES}/HID.cpp
            ${ARDUINO_LIBRARY_CORES}/Tone.cpp
           )

add_executable(Arduimu.elf
               FreeIMU.cpp
               HMC58X3.cpp
               I2Cdev.cpp
               IMU.cpp
               ITG3200.cpp
               MPU60X0.cpp
               MS561101BA.cpp
               bma180.cpp
              )

target_link_libraries(Arduimu.elf Arduino core)
set_target_properties(Arduimu.elf PROPERTIES LINK_FLAGS -lm
                                             LINK_FLAGS -Wl,--gc-sections)
