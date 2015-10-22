
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

  if (x > 450 && x < 550)
  {
    // Joystic is idle
    int sleepMsec = rand() % 3000 + 500;
    delay(sleepMsec);
    int rot = rand() % 179;
    servo1.write(rot);

    Serial.print("Rand: ");
    Serial.print(rot);    
  }
  else
  {
    int rot1 = map(x, 0, 1023, 0, 179);
    servo1.write(rot1);    

    Serial.print("Joystic X: ");
    Serial.print(x);
    delay(16);
  }
}
