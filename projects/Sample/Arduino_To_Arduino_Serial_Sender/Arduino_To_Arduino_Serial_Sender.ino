// Sender

char str[4];
int counter = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  ++counter;
  
  itoa(counter, str, 10); //Turn value into a character array
  Serial.write(str, 4);

  delay(1000);
}
