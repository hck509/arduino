const int speakerPin = 9;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  tone(speakerPin, 1000, 500);
  delay(800);
  tone(speakerPin, 3000, 500);
  delay(800);
}

