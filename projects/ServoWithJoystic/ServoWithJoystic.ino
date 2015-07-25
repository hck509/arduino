
#include <Servo.h>

Servo servo1;

static int PinServo1 = A0;
static int PinX = A1;
static int PinY = A2;

void setup() {
  pinMode(PinX, INPUT);
  pinMode(PinY, INPUT);

  servo1.attach(PinServo1);

  Serial.begin(9600);
  Serial.println("setup done.");  
}

void loop() {
  int x = analogRead(PinX);
  int y = analogRead(PinY);

  int rot1 = map(x, 0, 1023, 0, 179);
  servo1.write(rot1);

  Serial.print("X: ");
  Serial.print(x);
  Serial.print(", Y: ");
  Serial.println(y);  

  delay(16);
}
