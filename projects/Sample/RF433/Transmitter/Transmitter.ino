#include <VirtualWire.h>


const int txPin = 12;
const int ledPin = 13;
const int btn1Pin = 2;
const int btn2Pin = 3;
const int btn3Pin = 4;
const int btn4Pin = 5;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(btn1Pin, INPUT);
  pinMode(btn2Pin, INPUT);
  pinMode(btn2Pin, INPUT);
  pinMode(btn3Pin, INPUT);
  digitalWrite(btn1Pin, HIGH);
  digitalWrite(btn2Pin, HIGH);
  digitalWrite(btn3Pin, HIGH);
  digitalWrite(btn4Pin, HIGH);
  vw_set_tx_pin(txPin);  
  vw_set_ptt_pin(10);
  vw_set_ptt_inverted(true);
  vw_setup(1000);
}

void loop() {
  uint8_t value = 1;
  if (!digitalRead(btn1Pin)) {
    value += 2;
  }
  if (!digitalRead(btn2Pin)) {
    value += 4;
  }
  if (!digitalRead(btn3Pin)) {
    value += 8;
  }
  if (!digitalRead(btn4Pin)) {
    value += 16;
  }
  vw_send((uint8_t*)&value, sizeof(value));
  vw_wait_tx();

  //digitalWrite(ledPin, digitalRead(btn1Pin));

  for (uint8_t i = 0; i < value; ++i) {
    digitalWrite(ledPin, 1);
    delay(200);  
    digitalWrite(ledPin, 0);
    delay(200);
  }
  delay(1000);
  
  /*
  // Blink
  char* controller;
  controller = "1";
  vw_send((uint8_t*)controller, strlen(controller));
  vw_wait_tx();
  digitalWrite(ledPin, 1);
  delay(1000);
  
  controller = "0";
  vw_send((uint8_t*)controller, strlen(controller));
  vw_wait_tx();
  digitalWrite(ledPin, 0);
  delay(1000);
  */
}
