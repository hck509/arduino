#include <TM1637Display.h>
 
#define CLK 11
#define DIO 10

const float Resister1 = 979;    // ohm
const float Resister2 = 21480;  // ohm

TM1637Display display(CLK, DIO);

void setup() 
{ 
  analogReference(INTERNAL);

  display.setBrightness(0xA);

  Serial.begin(9600);
}

void loop() 
{
      int val = analogRead(0);
      float inVoltage = val / 1024.0 * 1.1;
      float dividerVoltage = inVoltage / Resister1 * (Resister1 + Resister2);
      
      Serial.print("Raw:");
      Serial.print(val);
      Serial.print(" In Voltage:");
      Serial.print(inVoltage);      
      Serial.print(" Divider Voltage:");
      Serial.print(dividerVoltage);        
      Serial.println("");

      display.showNumberDec(dividerVoltage * 100, true);
      
      delay(300);
}

