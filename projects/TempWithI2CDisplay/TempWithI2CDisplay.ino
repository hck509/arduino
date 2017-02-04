#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// https://hackaday.io/project/3475-sniffing-trinket/log/12363-mq135-arduino-library
#include <MQ135.h>

#define MQ135_ANALOG_PIN 0
#define DHTPIN 12
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3F,16,2);
MQ135 gasSensor = MQ135(MQ135_ANALOG_PIN);

void setup() {
  Serial.begin(9600);
  dht.begin();  

  lcd.init();
  lcd.backlight();
  lcd.print("Hwang's Gadget!"); 
  
  delay(1000);
  lcd.clear();
}

void loop() {

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  int t = dht.readTemperature();

  int mq135Raw = analogRead(MQ135_ANALOG_PIN);
  float rzero = gasSensor.getRZero();
  float rzeroCorrected = gasSensor.getCorrectedRZero(t, h);
  float co2ppm = gasSensor.getPPM();
  float co2ppmCorrected = gasSensor.getCorrectedPPM(t, h);

  Serial.print("Temp:");
  Serial.print(t);
  Serial.print(" Humidity:");
  Serial.print(h);
  Serial.print(" MQ135 Raw:");
  Serial.print(mq135Raw);
  Serial.print(" RZero:");
  Serial.print(rzero);
  Serial.print("(");
  Serial.print(rzeroCorrected);
  Serial.print(")");  
  Serial.print(" CO2 ppm:");
  Serial.print(co2ppm);
  Serial.print("(");
  Serial.print(co2ppmCorrected);
  Serial.println(")");
    
  lcd.setCursor(0, 0);
  lcd.print(t);
  lcd.print("'C ");
  lcd.print(h);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("CO2:");
  lcd.print(co2ppmCorrected, 0);
  lcd.setCursor(9, 1);
  lcd.print("Z:");
  lcd.print(rzeroCorrected, 0);
  lcd.print("  ");
  
  delay(1000);
}

