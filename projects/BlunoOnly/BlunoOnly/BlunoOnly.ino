#include "Arduino.h"
#include "PlainProtocol.h"
//#include "U8glib.h"
//#include "blunoAccessory.h"


#define RIGHT 1
#define UP 2
#define LEFT 3
#define DOWN 4
#define PUSH 5
#define MID 0

//PlainProtocol constructor, define the Serial port and the baudrate.
PlainProtocol myBLUNO(Serial,115200);

//blunoAccessory constructor, for setting the relay,buzzer, temperature, humidity, knob, joystick and RGBLED
//blunoAccessory myAccessory;

//OLED constructor, for oled display
//U8GLIB_SSD1306_128X64 myOled(U8G_I2C_OPT_NONE);

String oledDisplay="";      //the display string recieved from the mobile device

int humidity=0;             //humidity read from DHT11
int temperature=0;          //temperature read from DHT11

int ledRed=0;               //RGBLED red value
int ledGreen=0;             //RGBLED green value
int ledBlue=0;              //RGBLED blue value

int knob=0;                 //knob(potentiometer) value read from analog pin

int joyStick=0;             //joystick state

void setup() {
    //myAccessory.begin();
    myBLUNO.init();
    //myAccessory.setRGBLed(0,0,0);   //turn off the RGBLED
}

/*
void draw (void)
{
    myOled.setFont(u8g_font_unifont);
    
    myOled.setPrintPos(10,16);      //set the print position
    myOled.print("H:");
    myOled.print(humidity);         //show the humidity on oled
    myOled.print("%");
    
    myOled.setPrintPos(10,32);
    myOled.print("T:");             //show the temperature on oled
    myOled.print(temperature);
    myOled.print("C");
    
    myOled.setPrintPos(88,16);
    myOled.print("R:");             //show RGBLED red value
    myOled.print(ledRed);
    myOled.setPrintPos(88,32);
    myOled.print("G:");             //show RGBLED green value
    myOled.print(ledGreen);
    myOled.setPrintPos(88,48);
    myOled.print("B:");             //show RGBLED blue value
    myOled.print(ledBlue);

    myOled.setPrintPos(10,48);
    myOled.print("Knob:");
    myOled.print(knob);             //show knob(potentiometer) value read from analog pin
   
    myOled.setPrintPos(10,60);
    if (oledDisplay.length()) {
        myOled.print(oledDisplay);  //if the display string recieved from the mobile device, show the string
    }
    else{
        myOled.print("Joystick:");  //if string is null, show the state of joystick
        switch (joyStick){
            case MID:
                myOled.print("Normal");
                break;
            case RIGHT:
                myOled.print("Right");
                break;
            case UP:
                myOled.print("Up");
                break;
            case LEFT:
                myOled.print("Left");
                break;
            case DOWN:
                myOled.print("Down");
                break;
            case PUSH:
                myOled.print("Push");
                break;
            default:
                break;
        }
    }
}
*/

void loop()
{
  delay(10);
}


