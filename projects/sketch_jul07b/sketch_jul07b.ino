void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int v = analogRead(A0);
  v = v * 500 / 1024;
  Serial.println(v);
  delay(500);
}
