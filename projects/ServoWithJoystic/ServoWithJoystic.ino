
#include <Servo.h>

Servo servo1;

static int PinServo1 = A0;
static int PInMotor1 = 11;
static int PinX = A1;
static int PinY = A2;

void setup() {
  pinMode(PinX, INPUT);
  pinMode(PinY, INPUT);
  pinMode(PInMotor1, OUTPUT);

  servo1.attach(PinServo1);

  Serial.begin(9600);
  Serial.println("setup done.");  
}

void loop() {
  int x = analogRead(PinX);
  int y = analogRead(PinY);

  int rot1 = map(x, 0, 1023, 0, 179);
  servo1.write(rot1);

  if (y > 800) {
    digitalWrite(PInMotor1, HIGH);
  } else {
    digitalWrite(PInMotor1, LOW);
  }

  Serial.print("X: ");
  Serial.print(x);
  Serial.print(", Y: ");
  Serial.println(y);  

  delay(16);
}
