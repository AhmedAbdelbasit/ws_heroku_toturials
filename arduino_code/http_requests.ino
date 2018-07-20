void getFromDweet(){
//  if(client.connected()){
//    client.println("GET /get/latest/dweet/for/home_cmd HTTP/1.1");
//    client.println("Host: dweet.io");
//    client.println("Connection: close");
//    client.println();
//    client.stop();
//  }else 
  if(client.connect(server,80)){
    Serial.println("connected to server");
    // Make a request:
    client.println("GET /get/latest/dweet/for/home_cmd HTTP/1.1");
    client.println("Host: dweet.io");
    client.println("Connection: close");
    client.println();
  }
}

void pushToDweet(int s) {

  // Close existing connection
  client.stop();

  // Connect & send request
  if (client.connect(server, 80)) {
    Serial.println("connecting...");

    // Prepare request
    String request = "GET /dweet/for/home_sen";
    request += "?light_intensity=" + String(s);
    request += " HTTP/1.1";
    
    // Send the HTTP request:
    client.println(request);
    client.println("Host: dweet.io");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();

  }
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}
