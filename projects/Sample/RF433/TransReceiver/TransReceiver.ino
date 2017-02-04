#include <VirtualWire.h>

char* controller;

const int txPin = 8;
const int rxPin = 12;
const int ledPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  vw_set_tx_pin(txPin);    
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

  uint8_t value = 1;
  vw_send((uint8_t*)&value, sizeof(value));
  vw_wait_tx();
  delay(1000);
}


