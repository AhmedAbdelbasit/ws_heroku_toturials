
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

// Credentials
char ssid[] = "smart network"; // your network SSID (name)
char password[] = "12345678"; // your network password
char server[] = "dweet.io";

int status = WL_IDLE_STATUS; // the Wifi radio's status

WiFiClient client;

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

void loop() {
  // Check the network connection once every 10 seconds:
  delay(1000);
  getFromDweet();
  
  delay(1000);
  
  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
    Serial.print(F("Unexpected response: "));
    Serial.println(status);
    client.stop();
    return;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    Serial.println(F("Invalid response"));
    client.stop();
    return;
  }
  
  // Allocate JsonBuffer
  // Use arduinojson.org/assistant to compute the capacity.
  const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
  DynamicJsonBuffer jsonBuffer(capacity);

  // Parse JSON object
  JsonObject& root = jsonBuffer.parseObject(client);
  if (!root.success()) {
    Serial.println(F("Parsing failed!"));
    client.stop();
    return;
  }

  // Extract values
  Serial.println(F("Response:"));
//  Serial.println(root["this"].as<char*>());
//  Serial.println(root["by"].as<char*>());
//  Serial.println(root["the"].as<char*>());
//  Serial.println(root["with"][0]["thing"].as<char*>());
//  Serial.println(root["with"][0]["created"].as<char*>());
  Serial.println(root["with"][0]["content"]["light"].as<char*>());

  const char* lightState = root["with"][0]["content"]["light"].as<char*>();
  Serial.println(lightState);
  if( strcmp(lightState, "off") == 0 ){
    Serial.println("Light turned Off");
    digitalWrite(14,LOW);
  }else if(strcmp(lightState, "on") == 0 ){
    Serial.println("Light turned On");
    digitalWrite(14,HIGH);
  }else{
    Serial.println("Nothing dweeted");
    client.stop();
  }
}


void getFromDweet(){
  if(client.connected()){
    client.println("GET /get/latest/dweet/for/home HTTP/1.1");
    client.println("Host: dweet.io");
    client.println("Connection: close");
    client.println();
  }else if(client.connect(server,80)){
    Serial.println("connected to server");
    // Make a request:
    client.println("GET /get/latest/dweet/for/home HTTP/1.1");
    client.println("Host: dweet.io");
    client.println("Connection: close");
    client.println();
  }
}

void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // print the MAC address of the router you're attached to:
  uint8* bssid = WiFi.BSSID();
  Serial.print("BSSID: ");
  Serial.print(bssid[5], HEX);
    
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.println(bssid[0], HEX);
  
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);
  // print the encryption type:
  uint8 encryption = WiFi.encryptionType(1);
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}
