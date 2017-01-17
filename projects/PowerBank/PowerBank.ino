// LCD Related includes
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Time Related includes
#include <Time.h>
#include <DS1302RTC.h>

float VIn = 5.03;

// VRef input : VIn v
// VRef external resister : 4.6k ohm
// VRef internal resister : 32k ohm (Calibrated : 35 ohm)
const float VRef = VIn * 35 / (35 + 4.6);

// Analogue reference calibration
const float AnalogRefCalibration = VRef / 5.0;

// set the LCD address to 0x27(or 0x3F. Use I2C_Scanner for sure) for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F,16,2);

// Init the DS1302
// Set pins:  CE, IO,CLK
DS1302RTC RTC(2, 1, 0);

// Voltage divider
const int VoltageDeviderPin = A3;

// Current sensor
// ACS712-30A
const int ACSPin = A2;
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

void setup()
{
  analogReference(EXTERNAL);
  
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
  float voltage = GetVoltage(300);
  float current = GetCurrentValue(300);

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

  if ((nowTickTime / 1000) % 5 == 0)
  {
    // LCD State of Charge (voltage %)
    lcd.setCursor(0, 0);
    lcd.print(stateOfCharge, 0);
    lcd.print("%    ");
  }
  else
  {
    // LCD Voltage
    lcd.setCursor(0, 0);
    lcd.print(voltage, 2);
    lcd.print("V");
  }

  // LCD Current
  lcd.setCursor(8, 0);
  lcd.print(current, 2);
  lcd.print("A  ");

  // LCD Amp-Hour
  lcd.setCursor(0, 1);
  lcd.print(totalAmph, 2);
  lcd.print("Ah");  
  
  // LCD time
  lcd.setCursor(11, 1);
  print2digits(minute() + (hour() * 60));
  lcd.print(":");
  print2digits(second());

  // Serial output for debugging
  Serial.println(voltage, 2);
}

float GetVoltage(int sampleCount)
{
    float averageVoltage = 0;

    for (int i = 0; i < sampleCount; ++i)
    {
      float voltage = analogRead(VoltageDeviderPin) / 40.92 * AnalogRefCalibration;
      averageVoltage += voltage;
      delay(1);
    }

    return averageVoltage / sampleCount;
}

float GetCurrentValue(int sampleCount)
{
    float averageAmps = 0;

    for (int i = 0; i < sampleCount; ++i)
    {
      int readValue = analogRead(ACSPin) * AnalogRefCalibration;
      float voltage = (readValue / 1024.0) * 5000; // Gets you mV
      float amps = ((voltage - ACSoffset) / ACSmVperAmp);
      averageAmps += amps;
      delay(1);
    }

    return averageAmps / sampleCount;
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


