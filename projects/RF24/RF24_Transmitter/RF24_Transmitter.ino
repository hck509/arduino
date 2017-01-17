#include <SPI.h>
#include <RF24.h>

const uint64_t pipe = 0xE8E8F0F0E1LL;

#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop() {
  int data[1];
  data[0] = 1;
  bool result = radio.write(data, 1);
  Serial.print("sent:");
  Serial.println(data[0]);
  if (result) {
    Serial.println("succeed");
  } else {
    Serial.println("failed");
  }
  delay(100);
}
