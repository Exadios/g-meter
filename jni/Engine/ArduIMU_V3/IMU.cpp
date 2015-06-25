/**
 * Streams calibrated sensors readings.
 *
 * @author Fabio Varesano - fvaresano at yahoo dot it
*/ 

/*
Development of this code has been supported by the Department of Computer Science,
Universita' degli Studi di Torino, Italy within the Piemonte Project
http://www.piemonte.di.unito.it/


This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "CommunicationUtils.hpp"
#include "ADXL345.hpp"
#include "bma180.hpp"
#include "HMC58X3.hpp"
#include "ITG3200.hpp"
#include "MS561101BA.hpp"
#include "I2Cdev.hpp"
#include "MPU60X0.hpp"

//#define DEBUG
#include "DebugUtils.hpp"
#include "FreeIMU.hpp"
#include <Wire.h>
#include <SPI.h>
#include <EEPROM.h>

#include "Arduino.h"
void setup();
void loop();

float val[11];
unsigned long last_time, this_time;


// Set the default object
FreeIMU my3IMU = FreeIMU();

void setup()
  { 
  Serial.begin(230400);
  Wire.begin();
  
  delay(500);
  my3IMU.init(true); // the parameter enable or disable fast mode
  delay(500);
  last_time = millis();
  }

void loop() 
  {
  // Run every 10mS.
  this_time = millis();

  if (((this_time = millis()) - last_time) >= 10)
    {
    last_time = this_time;
    writeVar(&this_time, sizeof(unsigned long));
    my3IMU.getValues(val);
    writeArr(val, 9, sizeof(float));
    Serial.print("\r\n");
    }
  }

