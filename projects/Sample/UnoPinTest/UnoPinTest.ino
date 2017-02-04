void setup() {
  for (int i = 2; i <= 13; ++i)
  {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  for (int i = 2; i <= 13; ++i)
  {
    digitalWrite(i, HIGH);
  }  
  delay(500);              // wait for a second
  for (int i = 2; i <= 13; ++i)
  {
    digitalWrite(i, LOW);
  }    
  delay(100);              // wait for a second
}
