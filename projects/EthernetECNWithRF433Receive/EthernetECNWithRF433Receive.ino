
// https://github.com/jcw/ethercard
#include <EtherCard.h>

// https://github.com/hck509/VirtualWire
#include <VirtualWire.h>

static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
static byte myip[] = { 192,168,10,120 };
static byte gwip[] = { 192,168,10,1 };
static byte severip[] = { 192,168,10,6 };

byte Ethernet::buffer[500];
BufferFiller bfill;

String sensorData;

void setup() {
  Serial.begin(9600);
  delay(2000);
  
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) {
    Serial.println( "Failed to access Ethernet controller");
  }
  ether.staticSetup(myip, gwip);
  ether.printIp("IP : ", myip);

  /*
  if (!ether.dhcpSetup()) {
    Serial.println( "DHCP failed");
    while(1);
  } 
  */ 

  // Setup Virtual Wire
  vw_set_ptt_pin(4);
  vw_set_ptt_inverted(true);
  vw_set_rx_pin(5);
  vw_setup(100);
  vw_rx_start();

  // Virtual Wire Indicator
  pinMode(13, OUTPUT);
  
  Serial.println("Setup Done!");  
}

static word homePage() {
  char buf[256];
  sensorData.toCharArray(buf, sizeof(buf));
  
  long t = millis() / 1000;
  word h = t / 3600;
  byte m = (t / 60) % 60;
  byte s = t % 60;
  bfill = ether.tcpOffset();
  bfill.emit_p(PSTR(
    "HTTP/1.0 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Pragma: no-cache\r\n"
    "\r\n"
    "$D$D:$D$D:$D$D\r\n"
    "$S"),
      h/10, h%10, m/10, m%10, s/10, s%10, buf);
  return bfill.position();
}

void loop() {
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);

  // check if valid tcp data is received  
  if (pos) {
    // send web page data
    ether.httpServerReply(homePage()); 
  }

  // Receive Virtual Wire
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    sensorData = String((char*)buf);
    Serial.println(sensorData);

    String data = String("name=s1&data=") + sensorData;
  
    char buf2[256];
    data.toCharArray(buf2, sizeof(buf2));    

    ether.copyIp(ether.hisip, severip);
    ether.hisport = 8000;
    ether.browseUrl(PSTR("/iot/sensor_report.php?"), buf2, NULL, my_result_cb);
    //ether.browseUrl(PSTR("/iot/"), "sensor_report.php?name=n1&data=d1", "192.168.10.6:8000", my_result_cb);
    //ether.browseUrl(PSTR("/"), "", "google.com", my_result_cb);
    ether.hisport = 80;
    
    digitalWrite(13, 1);
    delay(500);
    digitalWrite(13, 0);
  }
}


static void my_result_cb (byte status, word off, word len) {
  Serial.print("<<< reply ");
  Serial.println((const char*) Ethernet::buffer + off);
}

