
static int PinX = A1;
static int PinY = A2;

void setup() {
  pinMode(PinX, INPUT);
  pinMode(PinY, INPUT);

  Serial.begin(9600);
  Serial.println("setup done.");  
}

void loop() {
  int x = analogRead(PinX);
  int y = analogRead(PinY);

  Serial.print("X: ");
  Serial.print(x);
  Serial.print(", Y: ");
  Serial.println(y);  

  delay(300);
}
