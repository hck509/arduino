#include <VirtualWire.h>

// Ethernet
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE
};

IPAddress ip(192, 168, 124, 67);
IPAddress myDns(192, 168, 50, 31);
EthernetClient client;
//char server[] = "www.arduino.cc";
// jaguar IP
IPAddress server(192, 168, 59, 34); 



char* controller;
 
const int rxPin = 6;
const int ledPin = 7;
const int btnPin = 4;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT);
  vw_set_rx_pin(rxPin);
  vw_set_ptt_pin(5);
  vw_set_ptt_inverted(true);
  vw_setup(1000);

  // start listening
  vw_rx_start();

  Serial.begin(9600);

  // give ethernet shield time to boot up
  delay(3000);

  Ethernet.begin(mac);
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());  
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  buf[0] = 0;

  if (vw_get_message(buf, &buflen)) // non-blocking
  {
    for (uint8_t i = 0; i < buf[0]; ++i) {
      digitalWrite(ledPin, 1);
      delay(200);
      digitalWrite(ledPin, 0);
      delay(200);
    }
    delay(1000);

    Serial.println(buf[0]);

    // close any connection before send a new request.
    // This will free the socket on the WiFi shield
    client.stop();
  
    // if there's a successful connection:
    if (client.connect(server, 80)) {
      Serial.println("connecting...");
      // send the HTTP PUT request:
      client.println(String("GET /genisys/report_wc2.php?place=wm&status=") + String(buf[0]) + String(" HTTP/1.1"));
      client.println("Host: www.arduino.cc");
      client.println("User-Agent: arduino-ethernet");
      client.println("Connection: close");
      client.println();
    }    
  }

  if (digitalRead(btnPin)) {
    Serial.println('7');
    delay(1000);
  }
}


