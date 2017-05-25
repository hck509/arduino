
#include <Servo.h>

Servo servo1;
Servo servo2;

static int PinServo1 = A0;
static int PinServo2 = A1;

const int NUMBER_OF_FIELDS = 3; // how many comma separated fields we expect
int fieldIndex = 0;            // the current field being received
int values[NUMBER_OF_FIELDS];   // array holding values for all the fields


int Rot1 = 90;
int Rot2 = 90;

void setup() {
  servo1.attach(PinServo1);
  servo2.attach(PinServo2);

  servo1.write(90);
  servo2.write(90);

  Serial.begin(9600);
  Serial.println("setup done.");  
}

void loop() {
  if( Serial.available())
  {
    char ch = Serial.read();
    if(ch >= '0' && ch <= '9') // is this an ascii digit between 0 and 9?
    {
      // yes, accumulate the value
      values[fieldIndex] = (values[fieldIndex] * 10) + (ch - '0'); 
    }
    else if (ch == ',')  // comma is our separator, so move on to the next field
    {
      if(fieldIndex < NUMBER_OF_FIELDS-1)
        fieldIndex++;   // increment field index
    }
    else
    {
      Rot1 = values[0];
      Rot2 = values[1];
        
      // any character not a digit or comma ends the acquisition of fields
      // in this example it's the newline character sent by the Serial Monitor
      Serial.print( fieldIndex +1);
      Serial.println(" fields received:");
      for(int i=0; i <= fieldIndex; i++)
      {
        Serial.println(values[i]);
        values[i] = 0; // set the values to zero, ready for the next message
      }
      fieldIndex = 0;  // ready to start over
    }
  }
  
  servo1.write(Rot1);
  servo2.write(Rot2);

  Serial.print(Rot1);
  Serial.print(",");
  Serial.println(Rot2);  

  delay(10);
}
