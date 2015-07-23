const int buttonPin = 4;
const int ledPin = 13;

int buttonState = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(buttonPin, HIGH);  // pull up
  digitalWrite(ledPin, LOW);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);
  digitalWrite(ledPin, buttonState);
  Serial.println(buttonState);
  delay(100);
}
