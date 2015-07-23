
// https://github.com/jcw/ethercard
#include <EtherCard.h>

static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
static byte myip[] = { 192,168,10,120 };
static byte gwip[] = { 192,168,10,1 };
static byte severip[] = { 192,168,10,6 };

byte Ethernet::buffer[500];
BufferFiller bfill;

void setup() {
  Serial.begin(9600);
  delay(2000);
  
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) {
    Serial.println( "Failed to access Ethernet controller");
  }
  //ether.staticSetup(myip, gwip);
  //ether.printIp("IP : ", myip);

  if (!ether.dhcpSetup()) {
    Serial.println( "DHCP failed");
    while(1);
  }
  
  while (ether.clientWaitingGw()) {
    ether.packetLoop(ether.packetReceive());
    Serial.println("waiting for gw");
  }
  
  ether.printIp("My IP: ", ether.myip);
  ether.printIp("Netmask: ", ether.netmask);
  ether.printIp("GW IP: ", ether.gwip);
  ether.printIp("DNS IP: ", ether.dnsip);  
  
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
    "$D$D:$D$D:$D$D\r\n"),
      h/10, h%10, m/10, m%10, s/10, s%10);
  return bfill.position();
}

static uint32_t timer = 0;

void loop() {
  ether.packetLoop(ether.packetReceive()); 
  if (millis() > timer) {
    timer = millis() + 2000;
    ether.copyIp(ether.hisip, severip);
    ether.hisport = 8000;
    ether.browseUrl(PSTR("/iot/sensor_report.php?"), "name=n1&data=d1", NULL, my_result_cb);
    //ether.browseUrl(PSTR("/iot/sensor_report.php?"), "name=n1&data=d1", "192.168.10.6", my_result_cb);
    //ether.browseUrl(PSTR("/iot/"), "sensor_report.php?name=n1&data=d1", "192.168.10.6:8000", my_result_cb);
    //ether.browseUrl(PSTR("/"), "", "google.com", &my_result_cb);
    //ether.hisport = 80;
    //delay(1000);
    Serial.println("loop");
  }
}


static void my_result_cb (byte status, word off, word len) {
  Serial.print("<<< reply ");
  Serial.println((const char*) Ethernet::buffer + off);
}

