

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int temp = analogRead(A0);
  temp = temp * 500 / 1024;

  Serial.println(temp);
}
