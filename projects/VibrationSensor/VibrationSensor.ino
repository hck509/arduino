// Reference : https://www.dfrobot.com/wiki/index.php?title=DFRobot_Digital_Vibration_Sensor_(SKU:DFR0027)

// Connect the sensor to digital Pin 3 which is Interrupts 1.
const int sensorPin = 3;

void setup() {
  pinMode(sensorPin, INPUT);
  attachInterrupt(1, vibrate, FALLING);// Trigger the blink function when the falling edge is detected
  Serial.begin(9600);
}

void loop() {
  //int value = digitalRead(sensorPin);
  //Serial.println(value);
  //delay(300);
}

void vibrate()
{
  Serial.println("vigrate!");
}

