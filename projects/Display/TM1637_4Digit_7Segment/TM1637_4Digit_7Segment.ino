#include <Time.h>
#include <TM1637Display.h>
 
#define CLK 11
#define DIO 10
 
TM1637Display display(CLK, DIO);
 
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  setTime(1432823831UL);
  display.setBrightness(0xF);
 
}
 
boolean colon = true ;
 
void loop() {
   
  // put your main code here, to run repeatedly:
  int t = hour() * 100 + minute() ;
  display.setColon(colon);
  colon = !colon ;
  display.showNumberDec(t, true);
  delay(1000) ;
}
