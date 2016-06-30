// http://haneefputtur.com/7-segment-4-digit-led-display-sma420564-using-arduino.html

/* SevSeg Counter Example
 Edited by Haneef Puttur to match SMA420564 (www.haneefputtur.com)
 Copyright 2014 Dean Reading
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 
 
 This example demonstrates a very simple use of the SevSeg library with a 4
 digit display. It displays a counter that counts up, showing 10 deci-seconds.
 */

#include "SevSeg.h"

SevSeg sevseg; //Instantiate a seven segment controller object

char str[5];
int value = 0;

void setup() {
  byte numDigits = 4; 
  byte digitPins[] = {13, 12, 11, 10};
  byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
  
  //sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins); 
  // If your display is common anode type, please edit comment above line and uncomment below line
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(50);

  Serial.begin(9600);
}

void loop() {
  int i = 0;

  if (Serial.available()) {
    // allows all serial sent to be received together    
    unsigned long startTime = millis();
    while (millis() - startTime < 100 || millis() < startTime)
    {
      sevseg.refreshDisplay();      
    }
    

    while(Serial.available() && i < 5) {
      str[i++] = Serial.read();
    }
    str[i++]='\0';
  }

  if(i > 0) {
    value = atoi(str);
  }

  sevseg.setNumber(value, 2);
  sevseg.refreshDisplay();
}

