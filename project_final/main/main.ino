#include <ESP8266WiFi.h>
// Create an instance of the server
// specify the port to listen on ass an argument
WiFiServer server(80);

const char* ssid = "Wifi local";
const char* password = "123456&&";

void setup() {
  Serial.begin(115200);
  delay(10);
  // Connect to WiFi network
  Serial.print("Connecting to WiFi hospot");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Chech if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Wait until the client sends some data
  while (!client.available()) {
    delay(1);
  }
  // Prepare the response
  String s = "<!DOCTYPE html>\
<html>\
 <head>\
   <title>Hello World</title>\
\
 </head>\
 <body>\
   <h1>Hello Friend!</h1>\
   <p>I\'m board NodeMCU</p>\
   <p>Google Search</p>\
   <form action=\"https://script.google.com/macros/s/AKfycbx27Ie6l1cKul6a2_2NlPeG8_g-vtxfKGq3ZMPyIZU/exec\" method=\"get\">\
        status: <input name=\"status\" type=\"text\"> <br>\
        id: <input name=\"id\" type=\"text\"> <br>\
        topic: <input name=\"topic\" type=\"text\"> <br>\
        detail: <input name=\"detail\" type=\"text\"> <br>\
        <input type=\"submit\" value=\"Search\">\
   </form>\
 </body>\
</html>";


  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disconnected");
} 
  
