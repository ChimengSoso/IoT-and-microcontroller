#include <ESP8266WiFi.h>
// Create an instance of the server
// specify the port to listen on ass an argument
WiFiServer server(80);

const char* ssid = "IoT Lab";
const char* password = "csiot335";

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
  String s = "<!DOCTYPE html>\r\n \
  <html>\r\n \
    <head>\r\n \
      <title>Hello World</title>\r\n \
    </head>\r\n \
    <body>\r\n \
      <h1>Hello Friend!</h1>\r\n \
      <p>I'm board NodeMCU</p>\r\n \
      <p>Google Search</p>\r\n \
      <form action=\"https://www.google.com/search\" method=\"get\">\r\n \
        <input name=\"q\" type=\"text\">\r\n \
        <input type=\"submit\" value=\"Search\">\r\n \
      </form>\r\n \
    </body>\r\n \
  </html>";
//  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n
//  <!DOCTYPE HTML>\r\n<html>\r\nHello World! </html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disconnected");
} 
  
