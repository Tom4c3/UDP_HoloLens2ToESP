#include <WiFi.h>
#include <WiFiUdp.h>
//必要な場合はライブラリをインストールしてください

#ifndef LED_BUILTIN
#define LED_BUILTIN 2 //ESP32の場合、内蔵LEDは通常GPIO2に接続されています
#endif

const char* ssid = "SSID";
const char* password = "password";
const int udpPort = 3333;

WiFiUDP Udp; //グローバル変数としてWiFiUDPインスタンスを宣言

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());

  Udp.begin(udpPort);
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    char incomingPacket[255];
    int len = Udp.read(incomingPacket, 255);
    incomingPacket[len] = '\0';
    Serial.printf("UDP packet contents: %s\n", incomingPacket);

    //LEDを制御するコード
    if (strcmp(incomingPacket, "LED_ON") == 0) {
      digitalWrite(LED_BUILTIN, HIGH);
    } else if (strcmp(incomingPacket, "LED_OFF") == 0) {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}
