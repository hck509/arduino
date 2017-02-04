#include <VirtualWire.h>

char* controller;
 
const int rxPin = 12;
const int ledPin = 13;
const int btnPin = 4;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT);
  vw_set_rx_pin(rxPin);
  vw_set_ptt_pin(10);
  vw_set_ptt_inverted(true);
  vw_setup(1000);

  // start listening
  vw_rx_start();

  Serial.begin(9600);
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  //buf[0] = 3;
  if (vw_get_message(buf, &buflen)) // non-blocking
  {
    for (uint8_t i = 0; i < buf[0]; ++i) {
      digitalWrite(ledPin, 1);
      delay(200);
      digitalWrite(ledPin, 0);
      delay(200);
    }
    delay(1000);

    Serial.println(buf[0]);
  }

  if (digitalRead(btnPin)) {
    Serial.println('7');
    delay(1000);
  }
}


