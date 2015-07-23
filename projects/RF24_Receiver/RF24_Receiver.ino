#include <SPI.h>
#include <RF24.h>

const uint64_t pipe = 0xE8E8F0F0E1LL;

#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    Serial.println("radi avail");
    int buf[1];
    
    bool done = false;
    while (!done) {
      done = radio.read(buf, 1);
      Serial.println(buf[0]);
    }
  }
  delay(100);
  Serial.println("loop");
}
