/**
 * Includes
 */
#include <Adafruit_CC3000.h>
#include <SocketIOClient.h>
#include <SPI.h>
#include "utility/debug.h"

/**
 * Network config
 */
#define WLAN_SSID "Meyer 2.4GHz"
#define WLAN_PASS "rickyis#1"
#define WLAN_SECURITY WLAN_SEC_WPA2

/**
 * Pins
 */
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10

Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIV2); // you can change this clock speed

SocketIOClient client;

//22 25 26 29 30 33 34 37 38 41 42
const int LI_r1 = 22;//1
const int LI_g1 = 25;//2
const int LI_r2 = 26;//3
const int LI_g2 = 29;//4
const int LI_r3 = 30;//5
const int LI_g3 = 33;//6
const int LI_r4 = 34;//7
const int LI_g4 = 37;//8
const int LI_top = 38;//9
const int LI_center = 41;//10
const int LI_ext = 42;//external
const int LI_testled = 13;//Test LED
unsigned long count=0;

void ondata(SocketIOClient client, char *data) {
  count=0;//Reset the auto reset count
  String parsedData;
  int datalength=strlen(data);
  
  Serial.println(F("Incoming data!"));
  Serial.println(data);

  Serial.print(data[datalength-18]);
  Serial.print(data[datalength-17]);
  Serial.print(data[datalength-16]);
  Serial.print(data[datalength-15]);
  Serial.print(data[datalength-14]);
  Serial.print(data[datalength-13]);
  Serial.print(data[datalength-12]);
  Serial.print(data[datalength-11]);
  Serial.print(data[datalength-10]);
  Serial.print(data[datalength-9]);
  Serial.print(data[datalength-8]);
  Serial.print(data[datalength-7]);
  Serial.println(F(""));
  Serial.println(F("----------"));
  Serial.println(F(""));
  digitalWrite(LI_r1, data[datalength-18]=='1');
  digitalWrite(LI_g1, data[datalength-17]=='1');
  digitalWrite(LI_r2, data[datalength-16]=='1');
  digitalWrite(LI_g2, data[datalength-15]=='1');
  digitalWrite(LI_r3, data[datalength-14]=='1');
  digitalWrite(LI_g3, data[datalength-13]=='1');
  digitalWrite(LI_r4, data[datalength-12]=='1');
  digitalWrite(LI_g4, data[datalength-11]=='1');
  digitalWrite(LI_top, data[datalength-10]=='1');
  digitalWrite(LI_center, data[datalength-9]=='1');
  digitalWrite(LI_ext, data[datalength-8]=='1');
  digitalWrite(LI_testled, data[datalength-7]=='1');
}

const convertNumToHL(char num){
  Serial.println(num);
  if(strcmp(num, "0") == 0){
    Serial.println(F("UP"));
    return HIGH;
  } else{
    Serial.println(F("DOWN"));
    return LOW;
  }
}

void setup() {
  pinMode(LI_r1, OUTPUT);
  pinMode(LI_g1, OUTPUT);
  pinMode(LI_r2, OUTPUT);
  pinMode(LI_g2, OUTPUT);
  pinMode(LI_r3, OUTPUT);
  pinMode(LI_g3, OUTPUT);
  pinMode(LI_r4, OUTPUT);
  pinMode(LI_g4, OUTPUT);
  pinMode(LI_top, OUTPUT);
  pinMode(LI_center, OUTPUT);
  pinMode(LI_ext, OUTPUT);
  pinMode(LI_testled, OUTPUT);
  Serial.begin(115200);
  InitializeCC30000();

  client.setDataArrivedDelegate(ondata);
  if (!client.connect(cc3000, "bjm904.bjm904.com", 80)) {
    Serial.println(F("Not connected."));
  }
}

void loop() {
  client.monitor(cc3000);
  count++;
  if(count>35000){
    Serial.println(F("Resetting"));
    asm volatile ("  jmp 0");
    count=0;
  }
}

void InitializeCC30000(void){
  // initialise the module
  Serial.println(F("Initializing..."));

  // initialize CC3000 chip
  if (!cc3000.begin()) {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while(1);
  }

  // optional SSID scan
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }

  Serial.println(F("Connected!"));

  // wait for DHCP to complete
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP()) {
    delay(100);
  }  
}
