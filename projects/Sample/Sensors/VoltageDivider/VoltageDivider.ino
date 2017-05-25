// VRef external resister : 4.6k ohm
// VRef internal resister : 32k ohm (Calibrated : 35 ohm)
const float VIn = 5.03;
const float VRef = VIn * 35 / (35 + 4.6);

void setup() 
{ 
  analogReference(EXTERNAL);
  
  Serial.begin(9600);
}

void loop() 
{
      int val;
      float temp;
      val=analogRead(3);//This divider module will divide the measured voltage by 5, the maximum voltage it can measure is 25V.

      // This is original value
      temp=val / 40.92;

      Serial.print(val);
      Serial.print(" : ");
      Serial.print(val / 1024.0 * 5.0);
      Serial.print(" : ");
      Serial.print(val / 1024.0 * VRef);
      Serial.print(" : ");
      Serial.print(temp, 2);      
      Serial.print("v : ");
      Serial.print(temp * VRef / 5.0, 2);
      Serial.print("v : ");
      Serial.print(val / 1024.0 * VRef * 5.0, 2);      
      Serial.println("v");
      delay(300);
}

// Calibration
// Test
// 5.1 -> 5.43 (+0.33)
// 10.05 -> 10.75 (+0.7)
// 14.75 -> 15.80 (+1.05)

