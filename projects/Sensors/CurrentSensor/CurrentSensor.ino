// ACS712-30

float VIn = 5.03;

// VRef input : VIn v
// VRef external resister : 4.6k ohm
// VRef internal resister : 32k ohm (Calibrated : 35 ohm)
const float VRef = VIn * 35 / (35 + 4.6);

// Analogue reference calibration
const float AnalogRefCalibration = VRef / 5.0;

const int Pin = A2;
const float ACInVoltage = VIn;
const float ACSoffset = (ACInVoltage / 2.0) * 1000; 
const float mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module

void setup() 
{
  analogReference(EXTERNAL);
  Serial.begin(9600);
}

void loop() 
{
  float averageReadValue = 0;
  float averageVoltage = 0;  
  float average = 0;

  for (int i = 0; i < 1000; i++)
  {
    int readValue = analogRead(Pin) * AnalogRefCalibration;
    float voltage = (readValue / 1024.0) * 5000; // Gets you mV
    float amps = ((voltage - ACSoffset) / mVperAmp);

    averageReadValue += readValue / 1000.0;
    averageVoltage += voltage / 1000.0;
    average += amps;

    delay(1);
  }

  Serial.println(analogRead(Pin));

  Serial.print(averageReadValue);
  Serial.print(" : ");
  Serial.print(averageVoltage);
  Serial.print(" : ");  
  Serial.println(average, 2);
  delay(300);  
}

