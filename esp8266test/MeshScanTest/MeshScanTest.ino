/* ESP8266 MeshScanTest 
 *  
 * Works with: https://github.com/esp8266/arduino
 * 
 * Set ESP8266 to AP_STA mode with SSID "ESP"
 * Let all of them scan at the same time to see if they will detect each other
 * 
 */
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <WiFiServer.h>

#define NODE_ID     1
#define NODES       4
#define MY_SSID             "ESP"

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(MY_SSID);
  //IPAddress myIP = WiFi.softAPIP();
  Serial.println("Setup done");
}

void scanNetwork() {
    // WiFi.scanNetworks will return the number of networks found
    int starttijd = millis();   
    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; ++i)
    { 
      String test = WiFi.SSID(i);
      if (test.indexOf("ESP") >= 0) { 
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" - ");
        Serial.print(WiFi.BSSIDstr(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");
        Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      }
    }
    int scantijd = millis() - starttijd;
    Serial.print("Scantime: ");
    Serial.print(scantijd);
    Serial.println();
}

void loop() {
  scanNetwork();
  delay(random(0,500)); 
}
  
