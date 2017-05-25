
#include <Servo.h>

Servo servo1;
Servo servo2;

static int PinServo1 = A0;
static int PinServo2 = A1;

int Rot1 = 90;
int Rot2 = 90;

void setup() {
  servo1.attach(PinServo1);
  servo2.attach(PinServo2);

  servo1.write(90);
  servo2.write(90);

  Serial.begin(9600);
  Serial.println("setup done.");  
}

void loop() {
  servo1.write(Rot1);
  servo2.write(Rot1);

  Rot1 += 1;

  if (Rot1 > 180) Rot1 = 0;
  if (Rot1 < 0) Rot1 = 180;

  Serial.print("1: ");
  Serial.print(Rot1);
  Serial.print(", 2: ");
  Serial.println(Rot2);  

  delay(10);
}
