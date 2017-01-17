const float Resister1 = 979;    // ohm
const float Resister2 = 21480;  // ohm

void setup() 
{ 
  analogReference(INTERNAL);
  
  Serial.begin(9600);
}

void loop() 
{
      int val = analogRead(0);
      float inVoltage = val / 1024.0 * 1.1;
      float dividerVoltage = inVoltage / Resister1 * (Resister1 + Resister2);
      
      Serial.print("Raw:");
      Serial.print(val);
      Serial.print(" In Voltage:");
      Serial.print(inVoltage);      
      Serial.print(" Divider Voltage:");
      Serial.print(dividerVoltage);        
      Serial.println("");
      delay(300);
}

