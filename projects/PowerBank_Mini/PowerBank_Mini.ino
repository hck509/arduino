// LCD Related includes
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Time Related includes
#include <Time.h>
#include <DS1302RTC.h>

float VIn = 5.0;
const float InteralARefCalibration = 1.007;

// set the LCD address to 0x27(or 0x3F. Use I2C_Scanner for sure) for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F,16,2);

// Init the DS1302
// Set pins:  CE, IO,CLK
DS1302RTC RTC(2, 1, 0);

// Current sensor
// ACS712-30A
const float ACInVoltage = VIn;
const float ACSoffset = (ACInVoltage / 2.0) * 1000; 
const float ACSmVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module

// Lead Acid battery voltage to state of charge
const float BatteryChargeVoltage [11] = {
    12.7,
    12.5,
    12.42,
    12.32,
    12.2,
    12.06,
    11.90,
    11.75,
    11.58,
    11.31,
    10.5
  };



float totalAmph = 0;
unsigned long lastTickTime = 0;
float smoothedCurrent = 0;

void setup()
{
  // Initialize the lcd
  lcd.init(); 
  lcd.backlight();

  // And say greeting
  lcd.print("MrHwang's");
  lcd.setCursor(0, 1);
  lcd.print("Power Bank!");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  if (RTC.haltRTC())
    lcd.print("Clock stopped!");
  else
    lcd.print("Clock working.");

  // Check write-protection
  lcd.setCursor(0,1);
  if (RTC.writeEN())
    lcd.print("Write allowed.");
  else
    lcd.print("Write protected.");  

  delay(1000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("RTC Sync");
  setSyncProvider(RTC.get); // the function to get the time from the RTC
  if(timeStatus() == timeSet)
    lcd.print(" Ok!");
  else
    lcd.print(" FAIL!");  

  delay(1000);
  lcd.clear();    

  Serial.begin(9600);

  time_t initTime = 0;
  setTime(initTime);

  lastTickTime = millis();
}

void loop()
{
  float voltage = GetVoltage(100);
  delay(10);
  float current = GetCurrentValue(100);
  smoothedCurrent = smoothedCurrent + ((current - smoothedCurrent) * 0.1);
  current = smoothedCurrent;

  float stateOfCharge = 0;
  for (int i = 0; i < 11; ++i)
  {
    if (voltage > BatteryChargeVoltage[i])
    {
      if (i == 0) stateOfCharge = 100;
      else stateOfCharge = 100 - (i * 10.0) + 10.0 * (voltage - BatteryChargeVoltage[i]) / (BatteryChargeVoltage[i - 1] - BatteryChargeVoltage[i]);
      break;
    }
  }

  unsigned long nowTickTime = millis();
  unsigned long dt = nowTickTime - lastTickTime;
  totalAmph += current * dt / 1000.0 / 60.0 / 60.0;

  lastTickTime = nowTickTime;  

  // LCD Voltage
  lcd.setCursor(0, 0);
  lcd.print(voltage, 2);
  lcd.print("V");
  
  // LCD State of Charge (voltage %)
  lcd.setCursor(0, 1);
  lcd.print(stateOfCharge, 0);
  lcd.print("%    ");

  // LCD Current
  lcd.setCursor(current < 0 ? 10 : 11, 0);
  lcd.print(current,  current < 1 ? 2 : 1);
  lcd.print("A  ");

  // LCD Amp-Hour
  lcd.setCursor(5, 1);
  lcd.print(totalAmph, 1);
  lcd.print("Ah  ");
  
  // LCD time
  lcd.setCursor(11, 1);
  print2digits(minute() + (hour() * 60));
  lcd.print(":");
  print2digits(second());

  ///* Pin Check
  analogReference(INTERNAL);  
  Serial.print("Analogue Raw: ");
  Serial.print(analogRead(0));
  Serial.print(", ");
  Serial.print(analogRead(1));
  Serial.print(", ");
  Serial.print(analogRead(2));
  Serial.print(", ");
  Serial.println(analogRead(3));
  analogReference(DEFAULT);
  //*/

  // Serial output for debugging
  //Serial.println(voltage, 2);
}

float GetVoltage(int sampleCount)
{
  const float Resister1 = 979;    // ohm
  const float Resister2 = 21480;  // ohm
  
  float averageVoltage = 0;

  analogReference(INTERNAL);
  
  for (int i = 0; i < sampleCount; ++i)
  {
    int val = analogRead(0);
    float inVoltage = val / 1023.0 * 1.1 * InteralARefCalibration;
    float dividerVoltage = inVoltage / Resister1 * (Resister1 + Resister2);
    averageVoltage += dividerVoltage;
    delay(1);
  }

  //Serial.print("Voltage V: ");
  //Serial.print(analogRead(0) / 1024.0 * 1.1, 3);
  //Serial.print(" V2: ");
  //Serial.println(analogRead(0) / 1024.0 * 1.1 / Resister1 * (Resister1 + Resister2), 3);  

  analogReference(DEFAULT);
  
  return averageVoltage / sampleCount;
}

float GetCurrentValue(int sampleCount)
{
    const int ACSPin = A1;  
    const float Resister1 = 216.7;    // ohm
    const float Resister2 = 981;  // ohm   
    const float AmpOffset = 0.55;
    
    float averageAmps = 0;

    analogReference(INTERNAL);

    for (int i = 0; i < sampleCount; ++i)
    {
      int val = analogRead(ACSPin);
      float inVoltage = val / 1023.0 * 1.1 * InteralARefCalibration;
      float dividerVoltage = inVoltage / Resister1 * (Resister1 + Resister2);      
      float voltage = dividerVoltage * 1000; // mV
      float amps = ((voltage - ACSoffset) / ACSmVperAmp);
      averageAmps += amps;
      delay(1);
    }

    Serial.print("Current V: ");
    Serial.print(analogRead(ACSPin) / 1023.0 * 1.1 * InteralARefCalibration, 3);
    Serial.print(" Raw: ");
    Serial.println(analogRead(ACSPin), 1);

    analogReference(DEFAULT);

    return averageAmps / sampleCount - AmpOffset;
}

void print2digits(int number) 
{
  // Output leading zero
  if (number >= 0 && number < 10) 
  {
    lcd.write('0');
  }
  lcd.print(number);
}


