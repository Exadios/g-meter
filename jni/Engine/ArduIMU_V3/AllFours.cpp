/**
 * Streams calibrated sensors readings.
 *
 * @author Fabio Varesano - fvaresano at yahoo dot it and
 * Peter F Bradshaw - pfb@exadios.com
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

//#define DEBUG
#include "DebugUtils.hpp"

#include "Arduino.h"
void setup();
void loop();

float val[11];
unsigned long last_time, this_time, test_time;


void setup()
  { 
  Serial.begin(230400);
  
  test_time = 4;
  for (size_t i = 0; i < sizeof(val) / sizeof(float); i++)
    val[i] = 4.444444444444;
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
    writeVar(&test_time, sizeof(unsigned long));
    writeArr(val, 9, sizeof(float));
    Serial.print("\r\n");
    }
  }

