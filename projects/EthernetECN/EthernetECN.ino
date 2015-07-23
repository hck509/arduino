
// https://github.com/jcw/ethercard
#include <EtherCard.h>

static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
static byte myip[] = { 192,168,10,120 };

byte Ethernet::buffer[500];
BufferFiller bfill;

void setup() {
  Serial.begin(9600);
  delay(2000);
  
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) {
    Serial.println( "Failed to access Ethernet controller");
  }
  ether.staticSetup(myip);
  //ether.dhcpSetup();  
  ether.printIp("IP : ", myip);
  Serial.println("Setup Done!");  
}

static word homePage() {
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
    "<meta http-equiv='refresh' content='1'/>"
    "<title>RBBB server</title>"
    "<h1>$D$D:$D$D:$D$D</h1>"),
      h/10, h%10, m/10, m%10, s/10, s%10);
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
}

