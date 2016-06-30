#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

char str[5];
int counter = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();  
}

void loop() {

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  int t = dht.readTemperature();
    
  itoa(t * 100 + h, str, 10); //Turn value into a character array
  Serial.write(str, 4);

  delay(1000);
}

