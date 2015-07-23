
// https://github.com/adafruit/DHT-sensor-library
#include <DHT.h>

// https://github.com/hck509/VirtualWire
#include <VirtualWire.h>

#define USE_LP 1

#if USE_LP
#include <LowPower.h>
#else // USE_LP
// Power Saving Mode
// http://donalmorrissey.blogspot.kr/2010/04/sleeping-arduino-part-5-wake-up-via.html
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#endif // USE_LP


#define DHTPIN 10
#define DHTTYPE DHT11

int doorPin = 4;

DHT dht(DHTPIN, DHTTYPE);

/***************************************************
 *  Name:        ISR(WDT_vect)
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Watchdog Interrupt Service. This
 *               is executed when watchdog timed out.
 *
 ***************************************************/
 /*
ISR(WDT_vect)
{
  Serial.println("WDT!");
}
*/

void setup() {
  Serial.begin(9600);
  Serial.println("setup begin!");

  // Door Sensor
  pinMode(doorPin, INPUT);

  // Setup DHT
  dht.begin();

  // Setup Virtual Wire
  vw_set_ptt_pin(8);
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(9);
  vw_setup(100);


#if !USE_LP
  /*** Setup the WDT ***/
  // http://donalmorrissey.blogspot.kr/2010/04/sleeping-arduino-part-5-wake-up-via.html
  
  // Clear the reset flag.
  MCUSR &= ~(1<<WDRF);
  
  /* In order to change WDE or the prescaler, we need to
   * set WDCE (This will allow updates for 4 clock cycles).
   */
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  
  /* set new watchdog timeout prescaler value */
  WDTCSR = 1<<WDP0 | 1<<WDP3; /* 8.0 seconds */
  
  /* Enable the WD interrupt (note no reset). */
  WDTCSR |= _BV(WDIE);
#endif // USE_LP

  Serial.println("setup finished!");
  delay(500); //Allow for serial print to complete.
}

char buf[VW_MAX_MESSAGE_LEN];
String strBuf;
int sleepCounter = 0;

void loop() {
  if (sleepCounter == 0) {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    int h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    int t = dht.readTemperature();
  
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
    }  
  
    // Read Voltage
    int v = readVcc();
  
    // Compute heat index in Celsius (isFahreheit = false)
    int hic = dht.computeHeatIndex(t, h, false);

    // Get Door Sensor Status
    int doorStatus = digitalRead(doorPin);
  
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %");
    Serial.print("\tTemperature: ");
    Serial.print(t);
      Serial.print(" C");
    Serial.print("\tHeat index: ");
    Serial.print(hic);
    Serial.print(" C");
    Serial.print("\tVoltage: ");
    Serial.print(v);
    Serial.print("\tDoor: ");
    Serial.println(doorStatus);  
    // Send it with Virtual Wire
    
    strBuf = String(h) + String(",") + String(t) + String(",") + String(hic) + String(",") + String(v) + String(",") + String(doorStatus);
    strBuf.toCharArray(buf, VW_MAX_MESSAGE_LEN);
    vw_send((uint8_t*)buf, strlen(buf) + 1);
  
    // Wait until the whole message is gone  
    vw_wait_tx(); 
  }

  sleepCounter = (sleepCounter + 1) % 10;

  // Sleep

#if USE_LP
  // Enter power down state for 8 s with ADC and BOD module disabled
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
#else  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  
  power_adc_disable();
  power_spi_disable();
  power_timer0_disable();
  power_timer1_disable();
  power_timer2_disable();
  power_twi_disable();
  
  sleep_mode();             // here the device is actually put to sleep!!
                            // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
 
  sleep_disable();          // first thing after waking from sleep:
                            // disable sleep...

  power_all_enable();              
#endif // USE_LP
}

long readVcc() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  return result;
}
