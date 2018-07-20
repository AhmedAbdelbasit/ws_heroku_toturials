
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

// Credentials
char ssid[] = "ahmedpoto"; // your network SSID (name)
char password[] = "password2020"; // your network password
char server[] = "dweet.io";

int status = WL_IDLE_STATUS; // the Wifi radio's status

WiFiClient client;

float lightIntensity = 0;
float lastLightIntensity = 0;


void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid, password);
  
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    delay(2000);
  }
  
  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();

  pinMode(14,OUTPUT);
  
}







