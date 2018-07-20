void loop() {
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

  delay(1000);
  lightIntensity = analogRead(A0) * 100 / 1023;
  if(lightIntensity != lastLightIntensity){
    Serial.print("current intensity ");
    Serial.println(lightIntensity);
    pushToDweet(lightIntensity);
    lastLightIntensity = lightIntensity;
  }
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
}
