
#include <SPI.h>
#include <TFT.h>

#define cs 10
#define dc 9
#define rst 8

TFT screen = TFT(cs, dc, rst);

void setup() {
  Serial.begin(9600);

  screen.begin();
  //screen.backgrorund(0, 0, 0);
  screen.stroke(255, 255, 255);
  screen.setTextSize(2);
  screen.text("Setup..", 0, 0);
}

void loop() {

}
